//--=== STL ===--
#include <iostream>
#include <vector>

//--=== Dependencies ===--

//--=== Other files ===--
#include "maths.h"
#include "neural_network.h"
#include "convolution.h"

const unsigned long img_w = 256, img_h = 256;

int main(int argc, char** argv)
{
	//check arg count and display help page
	if (argc < 4 || (strcmp(argv[1], "c") && strcmp(argv[1], "t"))) {
		std::cout << "--===  Help ===--\nTrain model\n\t" << argv[0] << " t <model directory> <data A> <data B> <data C> ...\n"\
			<< "Classify image\n\t" << argv[0] << " c <model directory> <image>" << std::endl;
		return -1;
	}

	if (!strcmp(argv[1], "t")) {
		//		--=== Training ===--
		std::cout << "Training neural network at: " << argv[2] << std::endl;
	} else if (!strcmp(argv[1], "c")) {
		//		--=== Classification ===--
		std::cout << "Classifying image with: " << argv[2] << std::endl;
		mlp net(2, 2, {2, 3}, -1, 1);
		//std::cout << net << std::endl;
		//matrix<double> out = net.flow((std::vector<double>){1, 1});
		//std::cout << "Output: \n" << out << std::endl;
	}

	std::vector< matrix<int> > img;
	{
		int c = 0;
		for (int i = 0; i < 3; i++) {
			matrix<int> M(10, 10);
			M.for_each([&c](int& x){x = c++;});
			img.push_back(M);
		}
	}
	for (int i = 0; i < 3; i++)
		std::cout << "Layer: " << i << "\n" << img[i] << std::endl;
	convolution<int> conv(3, 2, 2, 5, -5, 1);
	std::cout << "Conv:\n" << conv;
	auto output = conv.flow(img);
	for (int i = 0; i < 3; i++)
		std::cout << "Layer: " << i << "\n" << output[i] << std::endl;

	return 0;
}
