#pragma  once

#include <queue>
#include <string.h>
#include "../JuceLibraryCode/JuceHeader.h"
// #include "Thread.h"
// #include "Package.h"
// #include "TCPConnection.h"

#define SRV_TCP_IP  "10.86.6.243"
#define SRV_TCP_PORT 6113
#define BUFSIZE 256
#define POOL_INCREASE_SIZE 10

enum udp_cmd
{
	UC_JOIN_MAP_REQ = 0x00,
	UC_JOIN_MAP_RES = 0x01,
	UC_CHECK_OK_REQ = 0x10,
	UC_CHECK_OK_RES = 0x11,
};


// | 1 1     1    | N |    1   |
// | * * TOTAL_LEN|MSG|CHECKSUM|
enum TCP_MSG_
{
	MSG_HEADER = 0xFF,
	MSG_HEARER2 = 0XFC,
	MSG_HEADER_LENGTH = 3,

	MSG_HEADER_POS = 0,
	MSG_HEARER2_POS = 1,
	MSG_TOTAL_LEN_POS = 2,
	MSG_CMDID_POS = 3,
	MSG_START_POS = 4,
};

enum TCP_CMD_ID
{
	CMD_SYNC_DATA	= 0xA1,
	CMD_JOIN_ROOM	= 0xA2,
	CMD_CREATE_ROOM = 0xA3,
	CMD_HEARTBEAT	= 0xAA,
	CMD_HEARTBEAT_RES = 0xAB,
};

enum SYNC_DATA_TAG
{
	TAG_GAMES	= 0xB0,
	TAG_ROOMS	= 0xB1,
	TAG_FRIENDS = 0xB2,
};
enum GAME_TYPE
{
	TYPE_WARCRAFT = 0xC1,
};

