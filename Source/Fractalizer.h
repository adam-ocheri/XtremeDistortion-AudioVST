#pragma once
#include <vector>
#include <complex>

struct FractalData
{
    int Iteration = 0;
    double Z = 0;

    FractalData() : Iteration(0), Z(0)
    {}
    FractalData(int iter) : Iteration(iter), Z(0)
    {}
    FractalData(double z) : Iteration(0), Z(z)
    {}
    FractalData(int iter, double z) : Iteration(iter), Z(z)
    {}
};

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
    std::vector<std::vector<float>> FractalZ;

    FractalData Mandelbrot(std::complex<double>& c, int max_iter);
    void Fractalize();
    float ForgeCrystal(float prev, float current, float next);
};

