CC=g++ -w
OUT=server
LIB=
INC=-I../vendor/json
JSON=../vendor/json/jsoncpp.cpp

build:
	$(CC) -c $(INC) *.cpp $(JSON)
	$(CC) -o $(OUT) *.o $(LIB)
	rm *.o
	./$(OUT)

