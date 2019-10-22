#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/EgammaTools/interface/json_wrapper.h"

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
  std::cout<<conf.getParameter<std::string>("filename")<<std::endl;
  std::string sfName="filename";
  if(1){
  }else{
    throw cms::Exception("ConfigError") <<"Error constructing EGammaSFModifier, sf file name "<<sfName<<" not valid";
  } 

}


void EGammaSFModifier::modifyObject(pat::Electron& ele)const
{

  auto eta = ele.eta();
  auto pt  = ele.pt();

  std::string pt_str;
  std::string eta_str;

  std::string year = "2018";
  std::string ID = "mvaEleID-Fall17-noIso-V2-wp80";

  //// FIND RIGHT PT BIN
  // TODO maybe put this in a function: get_bin () ?
  if (eta > -2.5   && eta < -2.0  ) {eta_str = "eta:[-2.5,-2.0]";    }
  if (eta > -2.0   && eta < -1.566) {eta_str = "eta:[-2.0,-1.566]";  }
  if (eta > -1.566 && eta < -1.444) {eta_str = "eta:[-1.566,-1.444]";}
  if (eta > -1.444 && eta < -0.8  ) {eta_str = "eta:[-1.444,-0.8]";  }
  if (eta > -0.8   && eta < 0.0   ) {eta_str = "eta:[-0.8,0.0]";     }
  if (eta > 0.0    && eta < 0.8   ) {eta_str = "eta:[0.0,0.8]";      }
  if (eta > 0.8    && eta < 1.444 ) {eta_str = "eta:[0.8,1.444]";    }
  if (eta > 1.444  && eta < 1.566 ) {eta_str = "eta:[1.444,1.566]";  }
  if (eta > 1.566  && eta < 2.0   ) {eta_str = "eta:[1.566,2.0]";    }
  if (eta > 2.0    && eta < 2.5   ) {eta_str = "eta:[2.0,2.5]";      }

  if (pt > 10.0  && pt < 20.0 ) {pt_str = "pt:[10.0,20.0]";  }
  if (pt > 20.0  && pt < 35.0 ) {pt_str = "pt:[20.0,35.0]";  }
  if (pt > 35.0  && pt < 50.0 ) {pt_str = "pt:[35.0,50.0]";  }
  if (pt > 50.0  && pt < 100.0) {pt_str = "pt:[50.0,100.0]"; }
  if (pt > 100.0 && pt < 200.0) {pt_str = "pt:[100.0,200.0]";}
  if (pt > 200.0 && pt < 500.0) {pt_str = "pt:[200.0,500.0]";}

  
  SF_Reader sf;
  sf.read_json("./json_converter_egID/jsons/run2_eleIDs.json");

  double value = sf.value (year, ID, pt_str, eta_str);
  double error = sf.error (year, ID, pt_str, eta_str);

  ele.addUserFloat(ID + "_value", value);
  ele.addUserFloat(ID + "_error", error);
  ele.addUserFloat("daje",1);

  // TESTING 
  bool test = true; 
  if (test == true) {
    std::cout << "year: " << year << ", ID: " <<  ID << ", pt: " <<  pt << ", pt_str: " << pt_str << ", eta: " <<  eta << ", eta_str: " <<  eta_str;
    std::cout << ", value: " << value;
    std::cout << ", error: " << error << std::endl;

    std::cout << "user float :: value: " << ele.userFloat(ID + "_value");
    std::cout << ", error: " << ele.userFloat(ID + "_error") << std::endl << std::endl;
  }
						
}

void EGammaSFModifier::modifyObject(pat::Photon& pho)const
{
  pho.addUserFloat("daje",1);
}

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGammaSFModifier,
		  "EGammaSFModifier");
