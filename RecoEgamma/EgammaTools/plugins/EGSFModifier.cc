#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/EgammaTools/interface/json_wrapper.h"

class EGSFModifier : public ModifyObjectValueBase {
public:
  EGSFModifier(const edm::ParameterSet& conf);
  ~EGSFModifier() override{}
  
  void modifyObject(pat::Electron& ele) const final;
  void modifyObject(pat::Photon& pho) const final;
  

};

EGSFModifier::EGSFModifier(const edm::ParameterSet& conf):
  ModifyObjectValueBase(conf)
{
  //std::string sfName="filename";
  std::string sfName="run2_eleIDs.json";
  if(1){
  }else{
    throw cms::Exception("ConfigError") <<"Error constructing EGSFModifier, sf file name "<<sfName<<" not valid";
  } 

}


void EGSFModifier::modifyObject(pat::Electron& ele)const
{
  //auto eta = ele.eta();
  //auto pt  = ele.pt();

  //std::string pt_str;
  //std::string eta_str;

  //std::string year = "2018";
  //std::string ID = "mvaEleID-Fall17-noIso-V2-wp80";

  //// FIND RIGHT PT BIN
  //if (eta > -2.5   && pt < -2.0  ) {eta_str = "eta:[-2.5,-2.0]";    }
  //if (eta > -2.0   && pt < -1.566) {eta_str = "eta:[-2.0,-1.566]";  }
  //if (eta > -1.566 && pt < -1.444) {eta_str = "eta:[-1.566,-1.444]";}
  //if (eta > -1.444 && pt < -0.8  ) {eta_str = "eta:[-1.444,-0.8]";  }
  //if (eta > -0.8   && pt < 0.0   ) {eta_str = "eta:[-0.8,0.0]";     }
  //if (eta > 0.0    && pt < 0.8   ) {eta_str = "eta:[0.0,0.8]";      }
  //if (eta > 0.8    && pt < 1.444 ) {eta_str = "eta:[0.8,1.444]";    }
  //if (eta > 1.444  && pt < 1.566 ) {eta_str = "eta:[1.444,1.566]";  }
  //if (eta > 1.566  && pt < 2.0   ) {eta_str = "eta:[1.566,2.0]";    }
  //if (eta > 2.0    && pt < 2.5   ) {eta_str = "eta:[2.0,2.5]";      }

  //if (pt > 10.0  && pt < 20.0 ) {pt_str = "pt:[10.0,20.0]";  }
  //if (pt > 20.0  && pt < 35.0 ) {pt_str = "pt:[20.0,35.0]";  }
  //if (pt > 35.0  && pt < 50.0 ) {pt_str = "pt:[35.0,50.0]";  }
  //if (pt > 50.0  && pt < 100.0) {pt_str = "pt:[50.0,100.0]"; }
  //if (pt > 100.0 && pt < 200.0) {pt_str = "pt:[100.0,200.0]";}
  //if (pt > 200.0 && pt < 500.0) {pt_str = "pt:[200.0,500.0]";}

  
  //SF_Reader sf;
  //sf.read_json("run2_eleIDs.json");
  //cout << sf.error (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]") << endl;

  //double value = sf.value (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]");
  //double error = sf.error (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]");

  //ele.addUserFloat(ID + "_value", value);
  //ele.addUserFloat(ID + "_error", error);
  ele.addUserFloat("daje",1);
						
}

void EGSFModifier::modifyObject(pat::Photon& pho)const
{
  pho.addUserFloat("daje",1);
}

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGSFModifier,
		  "EGSFModifier");
