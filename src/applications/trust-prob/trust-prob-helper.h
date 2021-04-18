#ifndef TRUSTPROB_HELPER_H
#define TRUSTPROB_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "trust-prob.h"

namespace ns3 {
namespace rapidnet {
namespace trustprob {

class TrustProb;

class TrustProbHelper: public RapidNetApplicationHelper
{
public:
  TrustProbHelper ()
  {
    m_factory.SetTypeId (TrustProb::GetTypeId ());
  }
  virtual ~TrustProbHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<TrustProb> ();
  }
};

} // namespace trustprob
} // namespace rapidnet
} // namespace ns3

#endif // TRUSTPROB_HELPER_H

