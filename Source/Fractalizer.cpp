#include "Fractalizer.h"

Fractalizer::Fractalizer() : Height(100), Width(100)
{
}

Fractalizer::Fractalizer(int height, int width) : Height(height), Width(width)
{
}

int Fractalizer::Mandelbrot(std::complex<double>& c, int max_iter)
{
	std::complex<double> z = 0;

	for (int i = 0; i < max_iter; ++i)
	{
		z = z * z + c;
		if (std::abs(z) > levelOfDetail)
		{
			return i;
		}
	}

	return max_iter;
}

void Fractalizer::Fractalize()
{
	std::vector<std::vector<int>> fractals(Height, std::vector<int>(Width, 0));

	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			double X = X_min + j * (X_max - X_min) / Width;
			double Y = Y_min + i * (Y_max - Y_min) / Height;
			std::complex<double> c(X, Y);

			int iter = Mandelbrot(c, MaxIteration);

			fractals[i][j] = iter;
		}
	}

	Fractals = fractals;
}
