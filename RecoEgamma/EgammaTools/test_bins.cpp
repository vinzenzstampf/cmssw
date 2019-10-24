#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> chooseCategory( double pt, vector<double> pt_bndrs, double eta, vector<double> eta_bndrs); 
string stripZeros (string bin_str);

string stripZeros (string bin_str) {
    while (bin_str[bin_str.length() - 1] == '0' and bin_str[bin_str.length() - 2] != '.') {
        bin_str.erase(bin_str.length() - 1); 
    }
    return bin_str;
}

vector<string> chooseCategory( double pt, vector<double> pt_bndrs, double eta, vector<double> eta_bndrs) {
        //// should return 0 if mva above all the numbers, 1 if below the first, ..., boundaries.size()-N if below the Nth, ...
        //this is for mva, then you have mx
        string pt_str = "nope";
        string pt_lower_edge = "nope";
        string pt_upper_edge = "nope";
        cout << ", pt: " << pt << " (double) pt: " << (double) pt << endl;
        for( int n = 0 ; n < ( int ) pt_bndrs.size() ; n++ ) {
            cout << to_string( pt_bndrs[n] ) << ", ";
            if( ( double ) pt > pt_bndrs[pt_bndrs.size() - n - 1] ) {
                pt_lower_edge = to_string( pt_bndrs[pt_bndrs.size() - n - 1] );
                pt_upper_edge = to_string( pt_bndrs[pt_bndrs.size() - n] );

                cout << ", pt_low: " << stripZeros(pt_lower_edge) << ", pt_up: " << stripZeros(pt_upper_edge) << endl;
                pt_str = "pt:[" + pt_lower_edge + "," + pt_upper_edge + "]";
                break;
            }
        }

        // assert pt bin
        //if (pt_str == "nope" or pt_lower_edge == "nope" or pt_upper_edge == "nope") { cout << "fail pt" << endl; return -1; }// Does not pass, object will not be produced
        
        string eta_str = "nope";
        string eta_lower_edge = "nope";
        string eta_upper_edge = "nope";
        cout << ", eta: " << eta << " (double) eta: " << (double) eta << endl;
        for( int n = 0 ; n < ( int ) eta_bndrs.size() ; n++ ) {
            cout << to_string( eta_bndrs[n] ) << ", ";
            if( ( double ) eta > eta_bndrs[eta_bndrs.size() - n - 1] ) {
                eta_lower_edge = to_string( eta_bndrs[eta_bndrs.size() - n - 1] );
                eta_upper_edge = to_string( eta_bndrs[eta_bndrs.size() - n] );
                cout << ", eta_low: " << stripZeros(eta_lower_edge) << ", eta_up: " << stripZeros(eta_upper_edge) << endl;
                eta_str = "eta:[" + eta_lower_edge + "," + eta_upper_edge + "]";
                break;
            }
        }

        // assert eta bin
        // if (eta_str == "nope" or eta_lower_edge == "nope" or eta_upper_edge == "nope") { cout << "fail eta" << endl; return -1; }// Does not pass, object will not be produced

        vector<string> cat {pt_str, eta_str};

        return cat;
    }

int main () {

double pt = 46.5;
double eta = -1.7;

vector<double> pt_bins = {10., 20., 35.0, 50., 100., 200., 500.};
vector<double> eta_bins = {-2.5, -2.0, -1.566, -1.444, -0.8, 0.0, 0.8, 1.444, 1.566, 2.0, 2.5};

vector<string> test = chooseCategory(pt, pt_bins, eta, eta_bins); 

cout << "pt: " << pt << ", pt_str: " << test[0] << ", eta" << eta << ", eta_str" << test[1] << endl; 

return 0;
}
