//--=== STL ===--
#include <iostream>

//--=== Dependencies ===--
#include <png++/png.hpp>

//--=== Other files ===--
#include "maths.h"
#include "neural_network.h"

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
		std::cout << net << std::endl;
		matrix<double> out = net.flow((std::vector<double>){1, 1});
		std::cout << "Output: \n" << out << std::endl;
	}

	return 0;
}
