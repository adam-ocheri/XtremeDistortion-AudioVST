#include "Fractalizer.h"

Fractalizer::Fractalizer() : Height(100), Width(100)
{
}

Fractalizer::Fractalizer(int height, int width) : Height(height), Width(width)
{
}

Fractalizer::Fractalizer(int height, int width, double x_min, double x_max, double y_min, double y_max, float max_iter)
	: Height(height), Width(width), X_min(x_min), X_max(x_max), Y_min(y_min), Y_max(y_max), MaxIteration(max_iter)
{
}

FractalData Fractalizer::Mandelbrot(std::complex<double>& c, int max_iter)
{
	std::complex<double> z = 0;

	for (int i = 0; i < max_iter; ++i)
	{
		z = z * z + c;
		if (std::abs(z) > levelOfDetail)
		{
			return FractalData(i, z.real());
		}
	}

	return FractalData(max_iter);
}

void Fractalizer::Fractalize()
{
	std::vector<std::vector<int>> fractals(Height, std::vector<int>(Width, 0));
	std::vector<std::vector<float>> fractalZ(Height, std::vector<float>(Width, 0.0f));

	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			double X = X_min + j * (X_max - X_min) / Width;
			double Y = Y_min + i * (Y_max - Y_min) / Height;
			std::complex<double> c(X, Y);

			FractalData Data = Mandelbrot(c, MaxIteration);
			int iter = Data.Iteration;
			float z = static_cast<float>(Data.Z);

			fractals[i][j] = iter;
			fractalZ[i][j] = z;
		}
	}

	Fractals = fractals;
	FractalZ = fractalZ;
}

float Fractalizer::ForgeCrystal(float prev, float current, float next)
{
	float topology = (prev + current + next) / 3.0f;
	return topology;
}
