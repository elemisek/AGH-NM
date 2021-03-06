#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <array>
#include <vector>

double f(double i, double h, double k, double m)
{
	return std::pow(h * i, m) * std::sin(k * h * i);
}
double sinSeries(double i, double m, double k, double x)
{
	return pow(-1, i) * ((std::pow(k * x, 2 * i + m + 2) / (std::pow(k, m + 1) * tgamma(2 * i + 2) * (2 * i + m + 2))));
}

double taylorintegral(double m, double k, double a, double b, int fileNumber)
{
	double sum = 0;
	std::ofstream file("wyniki" + std::to_string(fileNumber) + ".txt");

	for (double l = 1; l <= 30; l++)
	{
		sum = 0;
		for (double i = 0; i < l; i++)
		{
			sum += sinSeries(i, m, k, b) - sinSeries(i, m, k, a);
		}
		file << std::setprecision(8) << sum << std::endl;
	}
	file.close();
	return sum;
}

void simpsonintegral(double m, double k, double n, double a, double b, int fileNumber)
{
	double p = (n - 1) / 2;
	double h = (b - a) / (n - 1.), sum = 0;
	std::ofstream file("wyniki_simp" + std::to_string(fileNumber) + ".txt", std::ofstream::out | std::ofstream::app);

	for (double j = 1; j <= p; j++)
	{
		sum += f(2. * j - 2., h, k, m) + (4. * f(2. * j - 1., h, k, m)) + f(2. * j, h, k, m);
	}
	sum *= (h / 3.);

	file << std::setprecision(8) << std::fabs(sum - taylorintegral(m, k, a, b, fileNumber)) << std::endl;
	file.close();
}

int main()
{
	double m = 0, k = 1;
	double a = 0, b = M_PI;
	int fileNumber = 1;
	std::array<double, 5> nArr = { 11, 21, 51, 101, 201 };

	std::for_each(nArr.begin(), nArr.end(), [=](double n) { simpsonintegral(m, k, n, a, b, fileNumber); });
	system("py .\\chart_script.py 1 0 1");
	system("py .\\chart_script_simp.py 1 0 1");

	m = k = 1;
	fileNumber++;
	std::for_each(nArr.begin(), nArr.end(), [=](double n) { simpsonintegral(m, k, n, a, b, fileNumber); });
	system("py .\\chart_script.py 2 1 1");
	system("py .\\chart_script_simp.py 2 1 1");

	m = k = 5;
	fileNumber++;
	std::for_each(nArr.begin(), nArr.end(), [=](double n) { simpsonintegral(m, k, n, a, b, fileNumber); });
	system("py .\\chart_script.py 3 5 5");
	system("py .\\chart_script_simp.py 3 5 5");

	return 0;
}