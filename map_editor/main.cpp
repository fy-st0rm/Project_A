// #TODO:
// LAYER SYSTEM
// OPEN MAP FILES

#include "sparky.h"
#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<experimental/filesystem>
#include <thread>
#include <fstream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define MAP_HEIGHT 64
#define MAP_WIDTH 64

#define TOOL_ADD 0
#define TOOL_ERASE 1
#define TOOL_POINTER 2


struct ArgStruct
{
	Sparky::Application* app;
};

class Main : public Sparky::Scene
{

private:
	// App
	Sparky::Application* app;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;


	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	//Entity Manager
	std::shared_ptr<Sparky::EntityManager> manager;

	std::shared_ptr<Sparky::Entity> map_tiles[MAP_WIDTH][MAP_HEIGHT];

	// Entity Texture
	std::shared_ptr<Sparky::Texture> white;

	// Entity Component
	Sparky::TransformComponent* t_component;

	Uint32 buttons;
	int mouse_x;
	int mouse_y;

	int map[MAP_HEIGHT][MAP_WIDTH];

	int current_tool_state = TOOL_POINTER;

	// CAMERA STUFF
	glm::vec3 camera_pos;
	glm::vec3 camera_pos_grid;

	// ALL ENTITY TILES
	Sparky::Entity* entity_tiles[MAP_HEIGHT][MAP_WIDTH];

	// NFD STUFF
	nfdchar_t *outPath = NULL;
	nfdresult_t result;
	std::string directory;
	int index = 0;
	int files_pos = 0;
	bool imported = false;

	// TEXTURE CHANGING
	std::shared_ptr<Sparky::Texture> textures[100];
	std::string texture_paths[100];
	int current_texture = 0;



public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Creating renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// texture
		this->white = std::make_shared<Sparky::Texture>();
		

		//init entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		//Entiy 
		Sparky::Entity* entity = this->manager->add_entity<Sparky::Entity>(this->manager);
		this->t_component = entity->add_component<Sparky::TransformComponent>(glm::vec3(convert_grid(mouse_x, TILE_WIDTH) * TILE_WIDTH, convert_grid(SCREEN_HEIGHT - mouse_y, TILE_WIDTH)* TILE_HEIGHT, 0), glm::vec2(TILE_WIDTH, TILE_HEIGHT));
		entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,0.5f), glm::vec4(0,0,1,1), this->white);
		
		
		
		
	}
	~Main() {};
public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.4f, 0.478f, 1.0f});
		
		glm::vec3 pos = {(convert_grid(mouse_x, TILE_WIDTH) * TILE_WIDTH), (convert_grid(SCREEN_HEIGHT - mouse_y, TILE_WIDTH))* TILE_HEIGHT, 0};
		pos.x += get_camera_grid().x * TILE_WIDTH;
		pos.y += get_camera_grid().y* TILE_HEIGHT;
		this->t_component->set_pos(pos);
		this->manager->update(this->renderer);
				
	}

	void on_imgui_render()
	{
		ImGui::Begin("Tools");
		if(ImGui::Button("Pen Tool")) this->current_tool_state = TOOL_ADD;
		if(ImGui::Button("Eraser Tool")) this->current_tool_state = TOOL_ERASE;
		if(ImGui::Button("Pointer")) this->current_tool_state = TOOL_POINTER;
		ImGui::End();

		ImGui::Begin("Options");
		if(ImGui::Button("Save")) save_map();
		if(ImGui::Button("Open")) open_map();
		ImGui::End();

		draw_texture_win();

	}

	void on_event(SparkyEvent event) 
	{
		if(event.type == SDL_KEYDOWN)
		{
			glm::vec3 pos = this->camera->get_position();
			switch (event.key.keysym.sym)
            {
                // Camera movement
                case SDLK_w:
                    this->camera->set_position({ pos.x, 5 + pos.y, pos.z });
                    break;
                case SDLK_a:
                    this->camera->set_position({ pos.x - 5, pos.y, pos.z });
                    break;
                case SDLK_s:
                    this->camera->set_position({ pos.x, pos.y - 5, pos.z });
                    break;
                case SDLK_d:
                    this->camera->set_position({ pos.x + 5, pos.y, pos.z });
                    break;
				case SDLK_p:
					current_tool_state = TOOL_ADD;
					break;
				case SDLK_e:
					current_tool_state = TOOL_ERASE;
					break;
				case SDLK_c:
					current_tool_state = TOOL_POINTER;
					break;
			}
		}
		SDL_PumpEvents();
		buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
		if((buttons & SDL_BUTTON_LMASK ) != 0)
		{
			switch(current_tool_state){
				case TOOL_ADD:
				{
					glm::vec3 entity_pos = {this->t_component->get_pos()};
					glm::vec3 grid_pos;
					grid_pos.x = convert_grid(entity_pos.x, TILE_HEIGHT);
					grid_pos.y = convert_grid(entity_pos.y, TILE_HEIGHT);

					if(grid_pos.x >= MAP_WIDTH ) return;
					if(grid_pos.y >= MAP_HEIGHT) return;
					if(map[(int)grid_pos.y][(int)grid_pos.x] == current_texture +1 ) return;
					map[(int)grid_pos.y][(int)grid_pos.x] = current_texture + 1;

					this->entity_tiles[(int)grid_pos.y][(int)grid_pos.x] = this->manager->add_entity<Sparky::Entity>(this->manager);
					this->entity_tiles[(int)grid_pos.y][(int)grid_pos.x]->add_component<Sparky::TransformComponent>(entity_pos, glm::vec2(TILE_WIDTH, TILE_HEIGHT));
					this->entity_tiles[(int)grid_pos.y][(int)grid_pos.x]->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->textures[current_texture]);
					break;
				}
				case TOOL_ERASE:
				{
					glm::vec3 entity_pos = {this->t_component->get_pos()};
					glm::vec3 grid_pos;
					grid_pos.x = convert_grid(entity_pos.x, TILE_HEIGHT);
					grid_pos.y = convert_grid(entity_pos.y, TILE_HEIGHT);
					if(grid_pos.x >= MAP_WIDTH ) return;
					if(grid_pos.y >= MAP_HEIGHT) return;
					if(map[(int)grid_pos.y][(int)grid_pos.x] == 0) return;
					map[(int)grid_pos.y][(int)grid_pos.x] = 0;
					this->manager->remove_entity(std::make_shared<Sparky::Entity>(*entity_tiles[(int)grid_pos.y][(int)grid_pos.x]));
					break;

				}
			}
			
		}
	}
	
private:
	int convert_grid(int position, int tile_side)
	{
		return (int)round(position/tile_side);
	}

	glm::vec3 get_camera_grid()
	{
		
		this->camera_pos = this->camera->get_position();
		this->camera_pos_grid = {convert_grid(camera_pos.x, TILE_WIDTH), convert_grid(camera_pos.y, TILE_HEIGHT),0};
		return camera_pos_grid;
	}

	std::string get_ext(std::string file_name)
	{
		return(file_name.substr(file_name.length() - 4));
	}

	void draw_texture_win()
	{
		ImGui::Begin("Textures"); // Window Name
		ImGui::Text("Main Textures Folder");
		ImGui::Text((this->directory).c_str()); // Directory Displayer
		if(ImGui::Button("Import",{60,30})) // Import Folder Button
		{
			this->result = NFD_PickFolder(NULL, &this->outPath); // Folder Path

			//
			// NFD ERROR CHECKING
			if(result == NFD_OKAY)
			{
				directory = this->outPath;
				std::cout << "open folder sucess" << std::endl;
				
			}
			else if(result == NFD_CANCEL)
			{
				std::cout << "open folder cancelled" << std::endl;
			}
			else{
				std::cout << "Folder Doesnt Exist Or Error Loading Folder" << std::endl;
			}

		}

		// LOADING PNG FILES
		if(result == NFD_OKAY){	
			for(int i = 0; i<= this->index; i++)
			{
				this->texture_paths[i] = "";
				
			}
			this->index = 0;	
			for(auto& directory_entry : std::experimental::filesystem::directory_iterator(this->directory))
			{
				
				auto& path = directory_entry.path();
				if(get_ext(path.string()) == ".png"){

					//
					// Adding Texture Path To An Array
					this->texture_paths[index] = path.string();

					//
					// Loading That As A Texture And Puttin It in An Array
					this->textures[index] = std::make_shared<Sparky::Texture>((path.string()).c_str());


					this->index++;
				}
				
			}


			this->imported = true;
			result = NFD_CANCEL;
			
		}
		// UI STUFF
		ImGui::Text(("page:" + std::to_string(this->files_pos/5)).c_str());

		if(ImGui::Button(get_name(this->texture_paths[files_pos], "1"))){
			this->current_texture = files_pos;
		}
		else if(ImGui::Button(get_name(this->texture_paths[files_pos+1], "2"))){
			this->current_texture = files_pos + 1;
		}
		else if(ImGui::Button(get_name(this->texture_paths[files_pos+2], "3"))){
			this->current_texture = files_pos + 2;
		}
		else if(ImGui::Button(get_name(this->texture_paths[files_pos+3],"4"))){
			this->current_texture = files_pos + 3;
		}
		if(ImGui::Button(get_name(this->texture_paths[files_pos+4], "5"))){
			this->current_texture = files_pos + 4;
		}
		if(imported)
		{
			if(ImGui::Button("->"))
			{
				files_pos += 5;
			}
			if(ImGui::Button("<-"))
			{
				if(files_pos > 0)
				{
					files_pos -= 5;
				}
			}
		}
		ImGui::End();

	}

	void save_map()
	{
		nfdchar_t *savePath = NULL;
		nfdresult_t result = NFD_SaveDialog( ".lgo", NULL, &savePath );
		if ( result == NFD_OKAY )
		{
			std::ofstream outdata;
			int x;
			int y;
			std::string path = savePath;
			outdata.open((path + ".lgo").c_str());
			for(y = 0; y <= MAP_HEIGHT; y++ )
			{
				for(x=0; x <= MAP_WIDTH; x++)
				{
					outdata << map[y][x] << ",";
				}
				outdata << std::endl;
			}
			outdata.close();

		}
		else if ( result == NFD_CANCEL )
		{
			puts("User pressed cancel.");
		}
		else 
		{
			printf("Error: %s\n", NFD_GetError() );
		}

	}

	void open_map()
	{

		nfdchar_t *outPath = NULL;
		nfdresult_t result = NFD_OpenDialog( ".lgo", NULL, &outPath );
		if ( result == NFD_OKAY )
		{
			std::string path = outPath;
			std::ifstream myfile (path.c_str());
			while(!myfile.eof())
			{
				std::string map_line;
				myfile >> map_line;
				std::cout << map_line << std::endl;
			}
			
		}
		else if ( result == NFD_CANCEL )
		{
			puts("User pressed cancel.");
		}
		else 
		{
			printf("Error: %s\n", NFD_GetError() );
		}

	}

	const char* get_name(std::string data, std::string additional_data)
	{
		if(data == "")
		{
			return (additional_data + ". NULL").c_str();
		}
		else{
			return (additional_data +". "+ data).c_str();
		}
	}
};


class App : public Sparky::Application
{
public:
	App()  {}
	~App() {}

public:
	void on_start()
	{
		set_mode(Sparky::DEBUG_MODE);
		ArgStruct app = {this};
		add_scene<Main>("Main", &app);
		switch_scene("Main");
	}
};


int main(int argc, char** argv)
{
	App app;
	app.run("map_editor", SCREEN_WIDTH, SCREEN_HEIGHT, 60, 0);
	return 0;
}
