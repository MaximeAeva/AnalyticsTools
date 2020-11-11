#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
#include <cstdlib>

#include "struct.hpp"

void plot(Axis x, Axis y, std::vector<data> dataCluster = {}, char* title = "Title", bool legend = false);

#endif