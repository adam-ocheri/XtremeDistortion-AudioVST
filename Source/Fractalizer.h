#pragma once
#include <vector>
#include <complex>

class Fractalizer
{
public:

    Fractalizer();
    Fractalizer(int height, int width);
    Fractalizer(int height, int width, double x_min, double x_max, double y_min, double y_max, float max_iter);

    double X_min = -1.5;
    double X_max = 0.5;
    double Y_min = -1;
    double Y_max = 1;
    int Width;
    int Height;
    int MaxIteration = 100;

    int levelOfDetail = 2;

    std::vector<std::vector<int>> Fractals;

    int Mandelbrot(std::complex<double>& c, int max_iter);

    void Fractalize();
};

