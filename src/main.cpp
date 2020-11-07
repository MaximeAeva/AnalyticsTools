#include <iostream>
#include "plot.hpp"

int main()
{
    Axis x;
    Axis y; 
    std::vector<Point> data;
    x.range[0] = -5;
    x.range[1] = 5;
    x.color = 'g';
    x.step = 0.1;
    y.step = 0.5;
    y.range[0] = -10;
    y.range[1] = 10;
    y.color = 'b';
    for(int i = -25; i<25; i++)
    {
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = k*k*k+1;
        data.push_back(pt);
    }
    plot p(x, y, data, "x^3", 'r');
    return 0;
}