#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/EgammaTools/interface/json_wrapper.h"

std::string get_eta_bin(double eta);
std::string get_pt_bin(double pt);
//std::vector<std::string> chooseCategory(float pt, float eta);
std::vector<std::string> chooseCategory( float pt, std::vector<double> ele_pt_bndrs, float eta, std::vector<double> ele_eta_bndrs); 

class EGammaSFModifier : public ModifyObjectValueBase {

public:
  EGammaSFModifier(const edm::ParameterSet& conf);
  ~EGammaSFModifier() override{}
  
  void modifyObject(pat::Electron& ele) const final;
  void modifyObject(pat::Photon& pho) const final;
  //std::vector<std::string> chooseCategory(float pt, float eta);

private:
  std::string json_file;
  std::string year;
  std::string ele_sf_name;
  std::string pho_sf_name;
  std::vector<double> ele_pt_bndrs;
  std::vector<double> pho_pt_bndrs;
  std::vector<double> ele_eta_bndrs;
  std::vector<double> pho_eta_bndrs;
};

EGammaSFModifier::EGammaSFModifier(const edm::ParameterSet& conf):
  ModifyObjectValueBase(conf),
  json_file            (conf.getParameter<std::string> ("filename") ), 
  year                 (conf.getParameter<std::string> ("year") ), 
  ele_sf_name          (conf.getParameter<std::string> ("ele_sf_name") ),
  pho_sf_name          (conf.getParameter<std::string> ("pho_sf_name") ),
  ele_pt_bndrs         (conf.getParameter<std::vector<double>> ("ele_pt_bndrs") ),
  pho_pt_bndrs         (conf.getParameter<std::vector<double>> ("pho_pt_bndrs") ), 
  ele_eta_bndrs        (conf.getParameter<std::vector<double>> ("ele_eta_bndrs") ),
  pho_eta_bndrs        (conf.getParameter<std::vector<double>> ("pho_eta_bndrs") ) {

  // ASSERTIONS
  if(not static_cast<bool>(std::ifstream(json_file))) { 
    throw cms::Exception("ConfigError") << "Error constructing EGammaSFModifier, sf file " << json_file << " doesn't exist" << std::endl;
  } 

  if (year!="2016" and year!="2017" and year!="2018") {
    throw cms::Exception("ConfigError") <<"Error constructing EGammaSFModifier, year "<< year << " not valid" << std::endl;
  } 
}

void EGammaSFModifier::modifyObject(pat::Electron& ele) const {

  std::string pt_str  = get_pt_bin(ele.pt());
  std::string eta_str = get_eta_bin(ele.eta());

  SF_Reader sf;
  sf.read_json( json_file );

  ele.addUserFloat(ele_sf_name + "_value", sf.value(year, ele_sf_name, pt_str, eta_str));
  ele.addUserFloat(ele_sf_name + "_error", sf.error(year, ele_sf_name, pt_str, eta_str));

  // TESTING 
  bool test = false; 

  if (test == true) {
    std::cout << "json_file test: " << json_file << std::endl;

    std::cout << "year: " << year << ", ele_sf_name: " <<  ele_sf_name << ", pt: " <<  ele.pt() << ", pt_str: " << pt_str << ", eta: " <<  ele.eta() << ", eta_str: " <<  eta_str << std::endl;
    //std::cout << ", value: " << value;
    //std::cout << ", error: " << error << std::endl;

    std::cout << "user float :: value: " << ele.userFloat(ele_sf_name + "_value");
    std::cout << ", error: " << ele.userFloat(ele_sf_name + "_error") << std::endl << std::endl;
  }
}

void EGammaSFModifier::modifyObject(pat::Photon& pho) const {

  std::string pt_str  = get_pt_bin(pho.pt());
  std::string eta_str = get_eta_bin(pho.eta());

  SF_Reader sf;
  sf.read_json( json_file );

  pho.addUserFloat(pho_sf_name + "_value", sf.value(year, pho_sf_name, pt_str, eta_str));
  pho.addUserFloat(pho_sf_name + "_error", sf.error(year, pho_sf_name, pt_str, eta_str));

  // TESTING 
  bool test = true; 

  if (test == true) {
    std::cout << "json_file test: " << json_file << std::endl;
 
    //std::cout << "test cat: " << chooseCategory(pho.pt(), pho.eta())[0] << std::endl;
    std::cout << "test cat: " << chooseCategory(pho.pt(), ele_pt_bndrs, pho.eta(), ele_eta_bndrs)[0] << chooseCategory(pho.pt(), ele_pt_bndrs, pho.eta(), ele_eta_bndrs)[1] << std::endl;

    std::cout << "year: " << year << ", pho_sf_name: " <<  pho_sf_name << ", pt: " <<  pho.pt() << ", pt_str: " << pt_str << ", eta: " <<  pho.eta() << ", eta_str: " <<  eta_str << std::endl;
    //std::cout << ", value: " << value;
    //std::cout << ", error: " << error << std::endl;

    std::cout << "user float :: value: " << pho.userFloat(pho_sf_name + "_value");
    std::cout << ", error: " << pho.userFloat(pho_sf_name + "_error") << std::endl << std::endl;
  }
}

//std::vector<std::string> EGammaSFModifier::chooseCategory( float pt, float eta) {// TODO ALSO SPECIFY IF E OR G ?!
std::vector<std::string> chooseCategory( float pt, std::vector<double> ele_pt_bndrs, float eta, std::vector<double> ele_eta_bndrs) {
        //// should return 0 if mva above all the numbers, 1 if below the first, ..., boundaries.size()-N if below the Nth, ...
        //this is for mva, then you have mx
        std::string pt_str = "nope";
        std::string pt_lower_edge = "nope";
        std::string pt_upper_edge = "nope";
        for( int n = 0 ; n < ( int ) ele_pt_bndrs.size() ; n++ ) {
            std::cout << std::to_string( ele_pt_bndrs[n] ) << std::endl;
            if( ( double ) pt > ele_pt_bndrs[ele_pt_bndrs.size() - n - 1] ) {
                pt_lower_edge = std::to_string( ele_pt_bndrs[n-1] );
                pt_upper_edge = std::to_string( ele_pt_bndrs[n] );
                pt_str = "pt:[" + pt_lower_edge + "," + pt_upper_edge + "]";
                break;
            }
        }

        //if (pt_str == "nope" or pt_lower_edge == "nope" or pt_upper_edge == "nope") { std::cout << "fail pt" << std::endl; return -1; }// Does not pass, object will not be produced

        std::string eta_str = "nope";
        std::string eta_lower_edge = "nope";
        std::string eta_upper_edge = "nope";
        for( int n = 0 ; n < ( int ) ele_eta_bndrs.size() ; n++ ) {
            std::cout << std::to_string( ele_eta_bndrs[n] ) << std::endl;
            if( ( double ) pt > ele_eta_bndrs[ele_eta_bndrs.size() - n - 1] ) {
                eta_lower_edge = std::to_string( ele_eta_bndrs[n-1] );
                eta_upper_edge = std::to_string( ele_eta_bndrs[n] );
                eta_str = "pt:[" + eta_lower_edge + "," + eta_upper_edge + "]";
                break;
            }
        }

        //if (eta_str == "nope" or eta_lower_edge == "nope" or eta_upper_edge == "nope") { std::cout << "fail eta" << std::endl; return -1; }// Does not pass, object will not be produced

        std::vector<std::string> cat {pt_str, eta_str};

        return cat;
    }

std::string get_eta_bin(double eta) {

  std::string eta_str;

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

  return eta_str;
}

std::string get_pt_bin(double pt) {

  std::string pt_str;

  if (pt > 10.0  && pt < 20.0 ) {pt_str = "pt:[10.0,20.0]";  }
  if (pt > 20.0  && pt < 35.0 ) {pt_str = "pt:[20.0,35.0]";  }
  if (pt > 35.0  && pt < 50.0 ) {pt_str = "pt:[35.0,50.0]";  }
  if (pt > 50.0  && pt < 100.0) {pt_str = "pt:[50.0,100.0]"; }
  if (pt > 100.0 && pt < 200.0) {pt_str = "pt:[100.0,200.0]";}
  if (pt > 200.0 && pt < 500.0) {pt_str = "pt:[200.0,500.0]";}

  return pt_str;
}

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGammaSFModifier,
		  "EGammaSFModifier");
