#pragma once

#include "Airport.h"
#include "Extra.h"
#include <cstdlib>
#include <math.h>
#include <iostream>

class Route {
private:
    ID startID, endID;
    double distance;

public:
    Route() : startID(0), endID(0), distance(0.0) {}

    Route(ID startID,ID endID, double distance)
        : startID(startID), endID(endID), distance(distance) {}

    Route(Airport start, Airport end) : startID(start.getID()), endID(end.getID()) {
        distance = calcDistance(start.getLat(), start.getLong(), end.getLat(), end.getLong());
    }

    unsigned int getStart() {return startID;}

    unsigned int getEnd() {return endID;}

    double getDist() {return distance;}

    void setDist(double dist) {distance = dist;}

    void setStart(ID id) {startID = id;}

    void setEnd(ID id) {endID = id;}

    bool operator<(Route r) const {return distance < r.distance;}

    bool operator>(Route r) const {return distance > r.distance;}

    bool operator==(Route r) const {return distance == r.distance;}
};
