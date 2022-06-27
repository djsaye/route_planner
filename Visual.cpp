#include "Visual.h"
#include <algorithm>
#include <pthread.h>


    //return is [{x_left, y_left}, {x_right, y_right}]
std::vector<std::pair<double, double>> Visual::convertToCoords(double lat, double lon){ //Convert latitude and longitude to x and y coordinates. Returns a vector with both possible points.
    std::vector<std::pair<double, double>> ret;
    std::pair<double, double> point1{floor((lon/180)*1022.5 + 1022.5), floor(510 - (lat/90)*510)};  //Normalize each point and then multiply and add offset
    std::pair<double, double> point2{floor((lon/180)*1022.5 + 3067.5), floor(510 - (lat/90)*510)};
    ret.push_back(point1);  //Push the points into the queue indexed by side, 0 = left, 1 = right, similar to priority
    ret.push_back(point2);
    return ret;
}


Visual::Visual(Image world_map){ //sets worldMap as base of map and initialized priority side
    worldMap = world_map;
    priority = 0;  //0 = left, 1 = right. 0 is always default, input will be corrected to match
    dt.LoadFont("fonts/fixed-6x13.bdf");
    dt_stats.LoadFont("fonts/fixed-10x20.bdf");
}


void Visual::getVisualOutput(Image & img) { //Returns the output image of the map
    img = worldMap;   
}

double Visual::linearDistance(double x1, double y1, double x2, double y2){  //Distance formula for finding the correct point to plot on map
    double ret = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    return ret;
}

void Visual::drawCircle(double x1, double y1, double r){
    double ymaxbound = y1 + r + 1;    //Bounds of area to draw circle
    double yminbound = y1 - r;
    double xmaxbound = x1 + r + 1;
    double xminbound = x1 - r;
    
    cs225::HSLAPixel green(120, 1, .5); //Desired color of the circle to draw

    for(double x = xminbound; x < xmaxbound; x++){  //Iterate through specified bounds to draw circle
        for(double y = yminbound; y < ymaxbound; y++){
            if(linearDistance(x, y, x1, y1) <= r + 0.75){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y);
                temp = green;
            }
        }
    }
}

void Visual::drawText(DrawText &dt, unsigned int x, unsigned int y, const std::string text) {
	cs225::HSLAPixel px_white(0, 0, 1),
	                 px_black(0, 0, 0);
	// drop shadow
	dt.DrawTextPNG(worldMap, px_black, x - 1, y, text);
	dt.DrawTextPNG(worldMap, px_black, x + 1, y, text);
	dt.DrawTextPNG(worldMap, px_black, x, y - 1, text);
	dt.DrawTextPNG(worldMap, px_black, x, y + 1, text);
	// primary text
	dt.DrawTextPNG(worldMap, px_white, x, y, text);
}

#if (PARALLEL == 1)
void Visual::createLine(int x1, int y1, int x2, int y2) {
    cs225::HSLAPixel red(0, 1, .5); //Desired color of the line to draw
    //Find and draw equation of line using point slope formula
    double m;
    if((x2 - x1) != 0) m = ((double) y2 - (double) y1)/((double) x2 - (double) x1); //Slope of the line
    else m = 0;  //Test case when a divide by 0 error could be met

    std::vector<pthread_t> threads;
    std::vector<PixelInfo> pi;

    if(abs(m) <= 3 && (x1 - x2) != 0){  //Based on the slop of the line, plots out the lone on worldMap.

        double leftbound = fmin(x1, x2);
        double rightbound = fmax(x1, x2);

        threads.resize((unsigned)(rightbound-leftbound));
        pi.resize((unsigned)(rightbound-leftbound));

        int rc, ind;
        for(double x = leftbound; x < rightbound; x++){ //Plot the line within the given bounds
            ind = x- leftbound;


            pi[ind].x = x;
            pi[ind].y = floor(m*(x - x1) + y1);
            pi[ind].pixel = &red;
            pi[ind].img = &worldMap;
            pi[ind].slope = 1;

            rc = pthread_create(&threads[ind], NULL, &writePixels, (void *)&pi[ind]);
            if (rc) exit(-1);
            //std::cout << "LOOP" << x << "\n";

        }
        //std::cout << "DONE\n";
    }
    else{   //This is the same thing as above, but for more vertical cases

        double botbound = fmin(y1, y2);
        double topbound = fmax(y1, y2);
        if(m != 0) m = 1/m; //Handles another divide by 0 error.

        threads.resize((unsigned)(topbound-botbound));
        pi.resize((unsigned)(topbound-botbound));

        int rc, ind;
        for(double y = botbound; y < topbound; y++){
            ind = y- botbound;

            pi[ind].x = floor(m*(y-y1) + x1);
            pi[ind].y = y;
            pi[ind].pixel = &red;
            pi[ind].img = &worldMap;
            pi[ind].slope = 0;
            
            rc = pthread_create(&threads[ind], NULL, &writePixels, (void *)&pi[ind]);
            if (rc) exit(-1);
        }

    }

    for (auto & t : threads) pthread_join(t, NULL);
}

void *Visual::writePixels(void *  pixelInfo) {
    PixelInfo * pi = (PixelInfo *) pixelInfo;

    if(pi->slope) for(int index = -1; index <=1; index++){
        cs225::HSLAPixel & temp = pi->img->getPixel(pi->x, pi->y + index);
        temp = *(pi->pixel);
    } else for(int index = -1; index <=1; index++){
        cs225::HSLAPixel & temp = pi->img->getPixel(pi->x + index, pi->y);
        temp = *(pi->pixel);
    }
    //std::cout << "THREAD" << pi->x << "\n";
    pthread_exit(NULL);

}
#else
void Visual::createLine(int x1, int y1, int x2, int y2) {
    cs225::HSLAPixel red(0, 1, .5); //Desired color of the line to draw
    //Find and draw equation of line using point slope formula
    double m;
    if((x2 - x1) != 0){
        m = ((double) y2 - (double) y1)/((double) x2 - (double) x1); //Slope of the line
    }
    else{
        m = 0;  //Test case when a divide by 0 error could be met
    }
    if(abs(m) <= 3 && (x1 - x2) != 0){  //Based on the slop of the line, plots out the lone on worldMap.
        double leftbound = fmin(x1, x2);
        double rightbound = fmax(x1, x2);

        for(double x = leftbound; x < rightbound; x++){ //Plot the line within the given bounds
            double y = floor(m*(x - x1) + y1);
            for(int index = -1; index <= 1; index++){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y + index);
                temp = red;
            }
        }
    }
    else{   //This is the same thing as above, but for more vertical cases
        double botbound = fmin(y1, y2);
        double topbound = fmax(y1, y2);
        if(m != 0){ //Handles another divide by 0 error.
            m = 1/m;
        }
        for(double y = botbound; y < topbound; y++){
            double x = floor(m*(y-y1) + x1);
            for(int index = -1; index <=1; index++){
                cs225::HSLAPixel & temp = worldMap.getPixel(x + index, y);
                temp = red;
            }
        }
    }
}
#endif

#if (PARALLEL == 2)
void Visual::addTour(std::vector<Airport> path, double dist) {
    if(path[0].getLong() - path[path.size() - 1].getLong() < -90){  //Ensure that the default priority is 0
        std::reverse(path.begin(), path.end());
    }

    std::vector<pthread_t> threads(path.size() - 1);
    std::vector<LineInfo> li(path.size() - 1);

    for (size_t i = 0; i < path.size() - 1; ++i) {      //Iterate through airports drawing a line between each!
        Airport &cur    = path[i];
        Airport &target = path[i + 1];


        auto px_vals = addLine(cur.getLat(), cur.getLong(), target.getLat(), target.getLong(),
            li[i], threads[i]);

        drawText(dt, std::get<0>(px_vals) + 5, std::get<1>(px_vals) + 5, cur.getName()); // draw name of cur
        if (i == path.size() - 2) // draw name of target, but only for the last line in the path
            drawText(dt, std::get<2>(px_vals) + 5, std::get<3>(px_vals) + 5, target.getName());

        drawCircle(std::get<2>(px_vals), std::get<3>(px_vals));
        if (!i) drawCircle(std::get<0>(px_vals), std::get<1>(px_vals));
    }
    drawText(dt_stats, 10, 10, "Total distance: " + std::to_string(dist) + " km");

    for (auto & p : threads) pthread_join(p, NULL);
    std::cout << "DONE \n";
}

std::tuple<int, int, int, int> Visual::addLine(double lat1, double long1, double lat2, double long2, LineInfo & li, pthread_t & thread) {
    //First, create the points
    std::vector<std::pair<double, double>> pair1 = convertToCoords(lat1, long1);
    std::vector<std::pair<double, double>> pair2 = convertToCoords(lat2, long2);
    //Then, find the combination that yields the shortest distance (Prioritize the side that its already on from plot. 0 = left, 1 = right)
    double distance1 = linearDistance(pair1[0].first, pair1[0].second, pair2[1].first, pair2[1].second);    //Point 1 on left, Point 2 on right
    double distance2 = linearDistance(pair2[0].first, pair2[0].second, pair1[1].first, pair2[1].second);    //Point 2 on left, Point 1 on right
    //The next distance is the same for both types of inputs, but prio determines which is used
    double priodistance = linearDistance(pair1[priority].first, pair1[priority].second, pair2[priority].first, pair2[priority].second); //Both points on same side
    //Create the line of shortest distance
    int x1, y1, x2, y2;
    if(distance1 < distance2 && distance1 < priodistance){
        x1 = pair1[0].first,
        y1 = pair1[0].second,
        x2 = pair2[1].first,
        y2 = pair2[1].second;

        priority = 1;   //Update the priority side
    }
    else if(distance2 < priodistance){
        x1 = pair1[1].first,
        y1 = pair1[1].second,
        x2 = pair2[0].first,
        y2 = pair2[0].second;

        priority = 0;
    }
    else {
        x1 = pair1[priority].first,
        y1 = pair1[priority].second,
        x2 = pair2[priority].first,
        y2 = pair2[priority].second;
    }

    li.x1 = x1;
    li.y1 = y1;
    li.x2 = x2;
    li.y2 = y2;
    li.img = &worldMap;
    
    int rc = pthread_create(&thread, NULL, &createLine, (void *)&li);
    if (rc) exit(-1);

    return std::make_tuple(x1, y1, x2, y2);
}

void *Visual::createLine(void * lineInfo) {
    std::cout << "smth ";
    LineInfo * li = (LineInfo *) lineInfo;
    double x1 = (double) li->x1;
    double x2 = (double) li->x2;
    double y1 = (double) li->y1;
    double y2 = (double) li->y2;
    Image * img = li->img;

    cs225::HSLAPixel red(0, 1, .5); //Desired color of the line to draw
    //Find and draw equation of line using point slope formula
    double m;
    if((x2 - x1) != 0){
        m = (y2 - y1)/( x2 - x1); //Slope of the line
    }
    else{
        m = 0;  //Test case when a divide by 0 error could be met
    }
    if(abs(m) <= 3 && (x1 - x2) != 0){  //Based on the slop of the line, plots out the lone on worldMap.
        double leftbound = fmin(x1, x2);
        double rightbound = fmax(x1, x2);

        for(double x = leftbound; x < rightbound; x++){ //Plot the line within the given bounds
            double y = floor(m*(x - x1) + y1);
            for(int index = -1; index <= 1; index++){
                cs225::HSLAPixel & temp = img->getPixel(x, y + index);
                temp = red;
            }
        }
    }
    else{   //This is the same thing as above, but for more vertical cases
        double botbound = fmin(y1, y2);
        double topbound = fmax(y1, y2);
        if(m != 0){ //Handles another divide by 0 error.
            m = 1/m;
        }
        for(double y = botbound; y < topbound; y++){
            double x = floor(m*(y-y1) + x1);
            for(int index = -1; index <=1; index++){
                cs225::HSLAPixel & temp = img->getPixel(x + index, y);
                temp = red;
            }
        }
    }
    std::cout << "bruh";
    pthread_exit(NULL);
}
#else
void Visual::addTour(std::vector<Airport> path, double dist) {
    if(path[0].getLong() - path[path.size() - 1].getLong() < -90){  //Ensure that the default priority is 0
        std::reverse(path.begin(), path.end());
    }

    for (size_t i = 0; i < path.size() - 1; ++i) {      //Iterate through airports drawing a line between each!
        Airport &cur    = path[i];
        Airport &target = path[i + 1];


        auto px_vals = addLine(cur.getLat(), cur.getLong(), target.getLat(), target.getLong());

        drawText(dt, std::get<0>(px_vals) + 5, std::get<1>(px_vals) + 5, cur.getName()); // draw name of cur
        if (i == path.size() - 2) // draw name of target, but only for the last line in the path
            drawText(dt, std::get<2>(px_vals) + 5, std::get<3>(px_vals) + 5, target.getName());

        drawCircle(std::get<2>(px_vals), std::get<3>(px_vals));
        if (!i) drawCircle(std::get<0>(px_vals), std::get<1>(px_vals));
    }
    drawText(dt_stats, 10, 10, "Total distance: " + std::to_string(dist) + " km");
}
#endif

//creates the shortest line between two lat, long pts. Prefers left side (Prio = 0). lat1 and long1 = current lat/long, lat2 and long2 = target lat/long
std::tuple<int, int, int, int> Visual::addLine(double lat1, double long1, double lat2, double long2) {
    //First, create the points
    std::vector<std::pair<double, double>> pair1 = convertToCoords(lat1, long1);
    std::vector<std::pair<double, double>> pair2 = convertToCoords(lat2, long2);
    //Then, find the combination that yields the shortest distance (Prioritize the side that its already on from plot. 0 = left, 1 = right)
    double distance1 = linearDistance(pair1[0].first, pair1[0].second, pair2[1].first, pair2[1].second);    //Point 1 on left, Point 2 on right
    double distance2 = linearDistance(pair2[0].first, pair2[0].second, pair1[1].first, pair2[1].second);    //Point 2 on left, Point 1 on right
    //The next distance is the same for both types of inputs, but prio determines which is used
    double priodistance = linearDistance(pair1[priority].first, pair1[priority].second, pair2[priority].first, pair2[priority].second); //Both points on same side
    //Create the line of shortest distance
    int x1, y1, x2, y2;
    if(distance1 < distance2 && distance1 < priodistance){
        x1 = pair1[0].first,
        y1 = pair1[0].second,
        x2 = pair2[1].first,
        y2 = pair2[1].second;

        priority = 1;   //Update the priority side
    }
    else if(distance2 < priodistance){
        x1 = pair1[1].first,
        y1 = pair1[1].second,
        x2 = pair2[0].first,
        y2 = pair2[0].second;

        priority = 0;
    }
    else {
        x1 = pair1[priority].first,
        y1 = pair1[priority].second,
        x2 = pair2[priority].first,
        y2 = pair2[priority].second;
    }
    createLine(x1, y1, x2, y2);
    return std::make_tuple(x1, y1, x2, y2);
}