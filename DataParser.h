#pragma once

#include "rapidcsv.h"
#include "Route.h"

class DataParser {

    public:
        DataParser(std::string airports_file, std::string routes_file);

        void getRoutesData(std::vector<double> & distances, std::vector<ID> & sourceID,
             std::vector<ID> & destinationID);  //Input empty vector, loads it with the data
        void getAirportsData(std::vector<std::string> & portNames, std::vector<ID> & portID,
             std::vector<double> & portLatitudes, std::vector<double> & portLongitudes);

    private:

        rapidcsv::Document airports;
        rapidcsv::Document routes;

    //routes stats
        std::vector<double> distance;
        std::vector<ID> srcID, dstID;

    //airports stats
        std::vector<double> lat, lon;
        std::vector<ID> id;
        std::vector<std::string> icao;

        void airports_helper();
        void routes_helper();

};
