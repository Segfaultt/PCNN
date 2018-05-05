#include "neural_network.h"

double sigmoid (double x)
{
	double ex = exp(x);
	return ex/(ex + 1);
}

double ReLU(double x)
{
	return std::max(x, 0.0);
}

double identity (double x)
{
	return x;
}

matrix<double> flow_layer(matrix<double> input, matrix<double> bias, matrix<double> weights)
{
	try {
		matrix<double> M = ((input * weights) + bias).apply(sigmoid);
		return M;
	} catch (std::string e) {
		std::cout << "[ERROR][FLOW_LAYER]: "<< e << std::endl;
	}
}

matrix<double> mlp::flow(matrix<double> inputs, int i)
{
	assert(inputs.get_cols() == input_size);
	matrix<double> M = inputs;
	for (int i = 0; i < hidden_layers + 1; i++) {
		M = flow_layer(M, bias[i], weight[i]);
	}

	return M;
}

matrix<double> mlp::flow(std::vector<double> inputs)
{
	matrix<double> M(1, inputs.size(), inputs);
	return flow(M);
}

mlp::mlp(int in_size, int out_size, std::vector<int> hid_size, int ran_min, int ran_max)
{
	//		--=== variables ===--
	input_size = in_size;
	output_size = out_size;
	hidden_size = hid_size;
	hidden_layers = hidden_size.size();

	if (hidden_layers < 1) {
		std::ostringstream message;
		message << "needs at least one hidden layer";
		throw message.str();
	}
	//weight/bias randomisation
	//a neural net requires hidden_size + 1 matrices
	int seed = time(NULL);

	//		--=== Weights ===--
	//input to hidden weights
	{
		std::vector<double> init_data;
		for (int k = 0; k < input_size * hidden_size[0]; k++) {
			srand(seed++);
			init_data.push_back((double)rand()/RAND_MAX * abs(ran_min - ran_max) + std::min(ran_min, ran_max));
		}

		matrix<double> M (input_size, hidden_size[0], init_data);
		weight.push_back(M);
	}
	//hidden to hidden weights
	for (int i = 0; i < hidden_layers - 1; i++) {
		std::vector<double> init_data;
		for (int k = 0; k < hidden_size[i] * hidden_size[i+1]; k++) {
			srand(seed++);
			init_data.push_back((double)rand()/RAND_MAX * abs(ran_min - ran_max) + std::min(ran_min, ran_max));
		}

		matrix<double> M (hidden_size[i], hidden_size[i+1], init_data);
		weight.push_back(M);
	}

	//hidden to output weights
	{
		std::vector<double> init_data;
		for (int k = 0; k < output_size * hidden_size[hidden_layers-1]; k++) {
			srand(seed++);
			init_data.push_back((double)rand()/RAND_MAX * abs(ran_min - ran_max) + std::min(ran_min, ran_max));
		}

		matrix<double> M (hidden_size[hidden_layers-1], output_size, init_data);
		weight.push_back(M);
	}


	//		--=== biases (one matrix per layer except input) ===--
	//hidden layer
	for (int i = 0; i < hidden_layers; i++) {
		std::vector<double> init_data;
		for (int k = 0; k < hidden_size[i]; k++) {
			srand(seed++);
			init_data.push_back((double)rand()/RAND_MAX * abs(ran_min - ran_max) + std::min(ran_min, ran_max));
		}
		matrix<double> M (1, hidden_size[i], init_data);
		bias.push_back(M);
	}
	//output layer
	{
		std::vector<double> init_data;
		for (int k = 0; k < output_size; k++) {
			srand(seed++);
			init_data.push_back((double)rand()/RAND_MAX * abs(ran_min - ran_max) + std::min(ran_min, ran_max));
		}
		matrix<double> M (1, output_size, init_data);
		bias.push_back(M);
	}
}

std::ostream& operator << (std::ostream& os, mlp& mlp)
{
	os << "Input:\t" << mlp.input_size << std::endl;
	os << "Output:\t" << mlp.output_size << std::endl;
	os << "Hidden:\t" << mlp.hidden_layers << " { ";
	for (auto i : mlp.hidden_size)
		os << i << " ";
	os << "}\nWeights:\n";
	for (auto M : mlp.weight)
		os << M << std::endl;
	os << "Biases:\n";
	for (auto M : mlp.bias)
		os << M << std::endl;

	return os;
}

