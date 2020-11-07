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

struct data{
    std::vector<Point> values;
    char* legend;
    char color;
};

void plot(Axis x, Axis y, std::vector<data> dataCluster = {}, char* title = "Title", bool legend = false);


#endif