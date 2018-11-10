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
	}

	matrix<double> img(4,4);
	{
		int c = 0;
		img.for_each([&c](double& x){x = sqrt(c++);});
	}
		std::cout << "img: " << "\n" << img << std::endl;
	convolution<double> conv(3, 1, 5, -5, 1);
	std::cout << "Conv:\n" << conv;
	auto output = conv.flow(img);
	for (int i = 0; i < conv.get_depth(); i++)
		std::cout << "Layer: " << i << "\n" << output[i] << std::endl;

	return 0;
}
