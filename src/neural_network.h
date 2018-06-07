#pragma once 

#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <numeric>

#include "maths.h"

double square_euclidean_distance (std::vector<double> a, std::vector<double> b);

double mse (std::vector< std::vector<double> > y, std::vector< std::vector<double> > Y);

double sigmoid (double x);

double ReLU(double x);

double identity (double x);

matrix<double> flow_layer(matrix<double> input, matrix<double> bias, matrix<double> weights);

class mlp {
	public:
		mlp(int in_size, int out_size, std::vector<int> hid_size, int ran_min = -2, int ran_max = 2);
		matrix<double> flow(matrix<double> inputs, int i = 0);
		matrix<double> flow(std::vector<double> inputs);

		friend std::ostream& operator<< (std::ostream& os, mlp& mlp);

	private:
		int hidden_layers, input_size, output_size;
		std::vector<int> hidden_size;
		std::vector< matrix<double> > weight;//previous-layer x next-layer
		std::vector< matrix<double> > bias;//row matrix with one value for each neuron
};
