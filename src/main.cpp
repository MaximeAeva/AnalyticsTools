#include <iostream>
#include <ctime>
#include "plot.hpp"
#include "leastSquares.hpp"
#include "signal.hpp"
#include "matrix.hpp"
#include "interpolation.hpp"

int main()
{
    srand(time(NULL));

    //Struct that handle time function parameters
    std::vector<fdata> fd1;
    fdata f1;
    f1.amp = 2;
    f1.f = 0.5;
    f1.phi = 0;
    fd1.push_back(f1);

    //A struct that template a function
    data d1;
    d1.legend = "Periodic func";
    data d2;
    d2.legend = "PSD";

    //Define a range to get values
    float wdw[2] = {0, 10};
    float wdw2[2] = {0, 1};
    int pts = 500;

    //Will contain timeFunc data points
    d1.values = tapering(periodic(fd1, pts, wdw), "blackman");
    d2.values = PSD(d1.values);

    //Define axis properties
    Axis x;
    Axis y;
    y.color = 'g';
    x.color = 'r'; 
    x.range[0] = -0.01;
    x.range[1] = 11;
    y.range[0] = -1.1;
    y.range[1] = 1.1;

    //Define axis properties for PSD
    Axis x1;
    Axis y1;
    y1.color = 'g';
    x1.color = 'r'; 
    x1.range[0] = 0.039;
    x1.range[1] = 0.055;
    /*y1.range[0] = -0.1;
    y1.range[1] = 1;*/

    //Improving display resolution
    std::vector<float> linspc = linspace(wdw2, 1000);

    //Clustering
    std::vector<data> cluster;
    cluster.push_back(d1);
    std::vector<data> clusterPSD;
    clusterPSD.push_back(d2);

    std::vector<Point> buff;

    clearScreen();
    int a;
    for(int i = 2; i<100; i++)
    {
        char t[10];
        sprintf(t, "%f", fd1.front().f);
        char str[50];
        strcpy(str, "Time function. F = ");
        strcat(str, t);
        subplot(x, y, cluster, str , true, 0, 2, 1);
        subplot(x1, y1, clusterPSD, "PSD" , true, 1, 2, 1);
        std::cin >> a;
        fd1.front().f = 0.5/i;
        cluster.front().values = tapering(periodic(fd1, pts, wdw), "blackman");
        clusterPSD.front().values = sample(PSD(cluster.front().values), 1000, "linear", x1.range);
         
    }

    return 0;
}