#ifndef _CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H
#define _CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H

#include "src/servers/Server_Common/Common.h"
#include "src/servers/Server_Common/Network/CommonNetwork.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* Structural representation of the packet sent by the server as response
* to a tell request
*/
struct FFXIVIpcTell : FFXIVIpcBasePacket<Tell>
{
   uint32_t u1;
   uint16_t u2a;
   uint16_t u2b;
   uint8_t preName;
   char receipientName[32];
   char msg[1031];
};

   /**
* Structural representation of the packet sent by the server as response
* to a failed tell because of unavailable target player
*/
struct FFXIVIpcTellErrNotFound : FFXIVIpcBasePacket<TellErrNotFound>
{
   char receipientName[32];
};

} /* Server */
} /* Packets */
} /* Network */
} /* Core */



#endif /*_CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H*/
