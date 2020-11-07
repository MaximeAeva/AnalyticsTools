#include <iostream>
#include "plot.hpp"

int main()
{
    Axis x;
    Axis y; 
    data f1;
    data f2;
    data f3;
    x.range[0] = -5;
    x.range[1] = 5;
    x.step = 0.1;
    y.step = 0.5;
    y.range[0] = -8;
    y.range[1] = 8;
    for(int i = -50; i<50; i++)
    {
        f1.color = 'r';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = 5*sin(k);
        f1.values.push_back(pt);
        f1.legend = "f1 : 5*sin(x)";
    }
    for(int i = -50; i<50; i++)
    {
        f2.color = 'b';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = 5*cos(k);
        f2.values.push_back(pt);
        f2.legend = "f2 : 5*cos(x)";
    }
    for(int i = -50; i<50; i++)
    {
        f3.color = 'g';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = 5*(cos(k)+sin(k));
        f3.values.push_back(pt);
        f3.legend = "f3 : f1(x)+f2(x)";
    }
    std::vector<data> dclust;
    dclust.push_back(f3);
    dclust.push_back(f1);
    dclust.push_back(f2);
    plot(x, y, dclust, "Some functions", true);
    return 0;
}