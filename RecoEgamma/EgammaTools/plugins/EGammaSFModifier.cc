#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class EGammaSFModifier : public ModifyObjectValueBase {
public:
  EGammaSFModifier(const edm::ParameterSet& conf);
  ~EGammaSFModifier() override{}
  
  void modifyObject(pat::Electron& ele) const final;
  void modifyObject(pat::Photon& pho) const final;
  

};

EGammaSFModifier::EGammaSFModifier(const edm::ParameterSet& conf):
  ModifyObjectValueBase(conf)
{
  std::string sfName="filename";
  if(1){
  }else{
    throw cms::Exception("ConfigError") <<"Error constructing EGammaSFModifier, sf file name "<<sfName<<" not valid";
  } 

}


void EGammaSFModifier::modifyObject(pat::Electron& ele)const
{

  ele.addUserFloat("daje",1);
						
}

void EGammaSFModifier::modifyObject(pat::Photon& pho)const
{
  pho.addUserFloat("daje",1);
}

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGammaSFModifier,
		  "EGammaSFModifier");
