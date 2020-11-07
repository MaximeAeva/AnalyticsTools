#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
#include <cstdlib>

struct Axis{
    float range[2];
    float step = 1;
    char color = 'w';
    char* title = "axis";
};

struct Point{
    float x;
    float y;
};

class plot{

    public:
        plot(Axis x, Axis y, std::vector<Point> data = {}, char* title = "Title", char color = 'w');
        ~plot();

    private:
        Axis ord;
        Axis abs;
};

#endif