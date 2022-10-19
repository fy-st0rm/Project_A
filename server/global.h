#pragma once

// Std's includes
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unordered_map>
#include <memory>
#include <cassert>

// Socket includes
#include <sys/socket.h>
#include <netinet/in.h>

// Json
#include "json/json.h"

#include "opcode.h"
