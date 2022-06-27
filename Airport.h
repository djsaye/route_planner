#pragma once
#include <string>

typedef unsigned int ID;

class Airport {
private:
    ID id;
    double latitude, longitude;
    std::string name;

public:
    Airport(unsigned int id, double latitude, double longitude, std::string name)
        : id(id), latitude(latitude), longitude(longitude), name(name) {}

    Airport() : id(0), latitude(0.0), longitude(0.0) {}

    unsigned int getID() {return id;}

    double getLong() {return longitude;}

    double getLat() {return latitude;}

    std::string getName() {return name;}
};
