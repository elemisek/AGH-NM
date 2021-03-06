#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>

int main()
{
	double delta, krok=0.02, xMin = -5.0, xMax = 5.0;
	std::ofstream output;
	std::ofstream output2;
	output.open("czebyszew.txt");
	output2.open("points.txt");

	for(int n=5; n<=20; n+=5)
	{
		std::vector<std::vector<double>> W(n, std::vector<double>(n));
		std::vector<std::vector<double>> y(n + 1, std::vector<double>(n + 1));
		std::vector<double> x(n + 1);

		x[0] = xMin;
		delta = (xMax - xMin) / n;
		for (int i = 1; i < n + 1; i++)
		{
			//x[i] = x[i - 1] + delta;
			x[i] = (xMin - xMax)*cos(M_PI*(2.0*i + 1.0) / (2.0*n + 2.0) + (xMin + xMax)) / 2.0;
		}

		for (int i = 0; i < n + 1; i++)
		{
			y[i][0] = 1.0 / (1.0 + pow(x[i], 2));
			output2 << x[i] << "   " << y[i][0] << std::endl;
		}

		for (int j = 1; j < n + 1; j++)
		{
			for (int i = j; i < n + 1; i++)
			{
				y[i][j] = (y[i][j - 1] - y[i - 1][j - 1]) / (x[i] - x[i - j]);
			}
		}

		for (double X = xMin; X <= xMax; X+=krok)
		{
			double dwumian = 1.0, wnx = 0.0;
			for (int j = 0; j < n + 1; j++)
			{
				dwumian = 1.0;
				for (int i = 0; i < j; i++)
				{
					dwumian *= (X - x[i]);
				}
				wnx += y[j][j] * dwumian;
			}
			output << X << "   " << wnx << "   " << std::endl; //"   " << 1.0 / (1.0 + pow(X, 2)) << std::endl;
		}
		output << "\n\n";
	}

	output.close();
	output2.close();
	return 0;
}