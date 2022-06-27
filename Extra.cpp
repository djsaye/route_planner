#pragma once

#include <math.h>

static double calcDistance(double slatitude, double slongitude, double elatitude, double elongitude){
        double slatRads = slatitude*M_PI/180;   //Convert all of the lats and longs to radians
        double slonRads = slongitude*M_PI/180;
        double elatRads = elatitude*M_PI/180;
        double elonRads = elongitude*M_PI/180;

        double latdistance = elatRads - slatRads;   //haversine formula needs these
        double londistance = elonRads - slonRads;

        double radius = 6378.1;   //Update to the radius of the earth in whatever units we want it to be in

        double ret = 2 * radius * asin(sqrt(pow(sin(latdistance/2), 2) + cos(slatRads) * cos(elatRads) * pow(sin(londistance/2), 2)));
        //The above line is haversine formula
        
        return ret;
}
