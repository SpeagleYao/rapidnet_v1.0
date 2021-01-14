#ifndef PACKETFORWARD_HELPER_H
#define PACKETFORWARD_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "packet-forward.h"

namespace ns3 {
namespace rapidnet {
namespace packetforward {

class PacketForward;

class PacketForwardHelper: public RapidNetApplicationHelper
{
public:
  PacketForwardHelper ()
  {
    m_factory.SetTypeId (PacketForward::GetTypeId ());
  }
  virtual ~PacketForwardHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<PacketForward> ();
  }
};

} // namespace packetforward
} // namespace rapidnet
} // namespace ns3

#endif // PACKETFORWARD_HELPER_H

