#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>

namespace pt = boost::property_tree;
using namespace std;

class SF_Reader {
    map< string, map< string, map< string, map< string, map<string, double> > > > > map_sf;

    public:
    void read_json(string);
    double value (string, string, string, string);
    double error (string, string, string, string);
};

#endif
