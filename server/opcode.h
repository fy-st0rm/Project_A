#pragma once

// Socket buffer size
#define BUFF_SZ 2048

// Opcodes
#define OP_OK         0x00
#define OP_FAILED     0x01

#define OP_CREATE_SV  0x10
#define OP_JOIN_SV    0x11
#define OP_DISCONNECT 0x12

#define OP_UPDATE     0x20
