#include <iostream>
#include "plot.hpp"
#include "leastSquares.hpp"

int main()
{
    Axis x;
    Axis y; 
    data f1;
    data f2;
    data f3;
    std::vector<Point> toSort;
    std::vector<Point> sorted;

    for(int i = 0; i<30; i++)
    {
        Point pt;
        pt.x = int(10*cos(i));
        pt.y = 0;
        std::cout << pt.x << " ";
        toSort.push_back(pt);
    }
    float wd[2] = {-5, 5};
    sorted = sample(toSort, 3, "linear", wd);
    std::cout << std::endl;
    for(int i = 0; i<sorted.size(); i++)
    {
        std::cout << sorted[i].x << " ";
    }
    x.range[0] = -20;
    x.range[1] = 20;
    x.step = 0.25;
    y.color = x.color = 'b';
    y.step = 0.25;
    y.range[0] = -4;
    y.range[1] = 6;
    for(int i = -150; i<150; i++)
    {
        f1.color = 'v';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = -5/k;
        f1.values.push_back(pt);
        f1.legend = "f1 : 5*sin(x)";
    }
    for(int i = -150; i<150; i++)
    {
        f2.color = 'g';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = 5/k;
        f2.values.push_back(pt);
        f2.legend = "f2 : 1/x";
    }
    for(int i = -150; i<150; i++)
    {
        f3.color = 'r';
        float k = i*0.1;
        Point pt;
        pt.x = k; 
        pt.y = 5*sin(k)/k;;
        f3.values.push_back(pt);
        f3.legend = "f3 : sinc(x)";
    }

    std::vector<data> dclust;
    dclust.push_back(f3);
    //dclust.push_back(f1);
    dclust.push_back(f2);
    //plot(x, y, dclust, "Hat function", true);
    return 0;
}