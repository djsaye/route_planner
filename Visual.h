#pragma once

#include <queue>
#include "Route.h"
#include "Image.h"
#include "DrawText.h"
#define PARALLEL 0
// 0: no multithreading
// 1: draw line in multi threaded
// 2: addTour is multithreaded

class Visual {
    private:
    Image worldMap;
    unsigned priority;
    DrawText dt, dt_stats;

    //adds and generates Image of line to stickersheet 
    void createLine(int x1, int y1, int x2, int y2);

    //return is {{x_left, y_left}, {x_right, y_right}}
    std::vector<std::pair<double, double>> convertToCoords(double lat, double lon);

    //Calculates the distances between linear points, usually pixels
    double linearDistance(double x1, double y1, double x2, double y2);  

    //Draw a circle at the given x and y coordinates, with a default radius of 5
    void drawCircle(double x1, double y1, double r = 5);

    //draws the given text on the map by calling DrawText::DrawTextPNG()
    void drawText(DrawText &dt, unsigned int x, unsigned int y, const std::string text);

#if (PARALLEL == 1)
    typedef struct _PixelInfo {
        double x, y;
        bool slope;
        cs225::HSLAPixel * pixel;
        Image * img;
    } PixelInfo;

    static void *writePixels(void *  pixelInfo);
#endif

#if (PARALLEL == 2)
    typedef struct _LineInfo {
        int x1, y1, x2, y2;
        Image * img;
    } LineInfo;

    static void *createLine(void * lineInfo);
    std::tuple<int, int, int, int> addLine(double lat1, double long1, double lat2, double long2, LineInfo & li, pthread_t & thread);
#endif

    public:
    Visual(Image world_map); //constructor: sets worldMap as base of map and loads font

    
    //creates the shortest line between two lat, long pts. Prefers left side
    std::tuple<int, int, int, int> addLine(double lat1, double long1, double lat2, double long2);

    //Generates an image based given a path of airports
    void addTour(std::vector<Airport> path, double dist);

    //Returns image to map with path on it
    void getVisualOutput(Image & img);
};
