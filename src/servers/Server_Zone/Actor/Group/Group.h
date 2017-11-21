#ifndef _GROUP_H
#define _GROUP_H

#include <Server_Common/Common.h>
#include <Server_Common/Forwards.h>
#include <Server_Zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>

namespace Core {
namespace Entity {
namespace Group {

struct GroupMember
{
   uint64_t inviterId;
   PlayerPtr pPlayer;
   uint32_t role;
};

enum class GroupType : uint8_t
{
   None,
   Party,
   Friends,
   FreeCompany,
   Linkshell,

   FreeCompanyPetition,
   Blacklist,
   ContentGroup
};

class Group : public boost::enable_shared_from_this< Group >
{
private:
   GroupType m_type{ GroupType::None };
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   uint32_t m_maxCapacity{ 250 };
   uint32_t m_maxRoles{ 50 };
   time_point m_createTime{ std::chrono::steady_clock::now() };
   std::map< uint64_t, GroupMember > m_members;
   std::map< uint64_t, uint64_t > m_invites; // <recipient, sender>
   bool m_reloadGroup;

   void addMember( uint64_t senderId = 0, uint64_t recipientId = 0 );
   void inviteMember( uint64_t senderId, uint64_t recipientId = 0 );
   void removeMember( uint64_t id = 0 );
public:
   Group( uint64_t id, uint64_t ownerId, uint32_t maxCapacity, time_point createTime ) :
      m_id( id ), m_ownerId( m_ownerId ), m_maxCapacity( maxCapacity ),  m_createTime( createTime ){};
   ~Group(){};

   virtual void load() = 0;
   virtual void update() = 0;
   virtual void disband() = 0;

   virtual Core::Network::Packets::GamePacketPtr addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr inviteMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr removeMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr kickMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual void sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo = false );

   void reload();
   bool canReload() const;
};

}
}
};
#endif // ! _GROUP_H