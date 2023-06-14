#pragma once
#include <vector>
#include <complex>

class Fractalizer
{
public:

    Fractalizer();
    Fractalizer(int height, int width);

    double X_min = -2.5;
    double X_max = 1.5;
    double Y_min = -2;
    double Y_max = 2;
    int Width;
    int Height;
    int MaxIteration = 10;

    int levelOfDetail = 2;

    std::vector<std::vector<int>> Fractals;

    int Mandelbrot(std::complex<double>& c, int max_iter);

    void Fractalize();
};

