#include "DataParser.h"

DataParser::DataParser(std::string airports_file, std::string routes_file) {
        airports = rapidcsv::Document(airports_file);  //Load file with rapidcsv
        routes = rapidcsv::Document(routes_file);

        airports_helper();
        routes_helper();

}

void DataParser::airports_helper(){
    //This stuff is for Airports
    icao = airports.GetColumn<std::string>("ICAO");
    lat = airports.GetColumn<double>("lat");
    lon = airports.GetColumn<double>("long");

    id = airports.GetColumn<ID>("ID");

    /*for (int i=0; i<5; i++) {     //Test to see that rapicsv works for airports
        std::cout << id[i] << " " << name[i] << " " << iata[i] << icao[i] << std::endl; 
    }*/
}
void DataParser::routes_helper(){
    //This stuff should be for Routes
    std::vector<double> srclatitudes = routes.GetColumn<double>("src airport lat");   //Needed for distance calcs
    std::vector<double> srclongitudes = routes.GetColumn<double>("src airport long");
    std::vector<double> dstlatitudes = routes.GetColumn<double>("dst airport lat");
    std::vector<double> dstlongitudes = routes.GetColumn<double>("dst airport long");
    
    srcID = routes.GetColumn<ID>("src airport ID");
    dstID = routes.GetColumn<ID>("dst airport ID");


    /*for (int i=0; i<5; i++) {     //Test to see that rapicsv works for routes
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        std::cout << srcID[i] << " " << dstID[i] << " " << tempdistance << std::endl; 
    }*/

    //Loop here setting up the distances
    for(unsigned i = 0; i < srclatitudes.size() - 1; i++){   //all the vectors should be the same size, so
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        distance.push_back(tempdistance);
    }
}

void DataParser::getRoutesData(std::vector<double> & distances, std::vector<ID> & sourceID,
    std::vector<ID> & destinationID){
        distances = this->distance;
        sourceID = this->srcID;
        destinationID = this->dstID;
    }


void DataParser::getAirportsData(std::vector<std::string> & portNames, std::vector<ID> & portID,
    std::vector<double> & portLatitudes, std::vector<double> & portLongitudes){
        portNames= this->icao;
        portID = this->id;
        portLatitudes = this->lat;
        portLongitudes = this->lon;
    }
