#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <windows.h>
#include <cstdlib>

#include "struct.hpp"

void plot(Axis x, Axis y, std::vector<data> dataCluster = {}, 
            char* title = "Title", bool legend = false, int xStart = 0, int yStart = 0);

void subplot(Axis x, Axis y, std::vector<data> dataCluster,
             char* title, bool legend, int pos, int nH, int nW);

#endif