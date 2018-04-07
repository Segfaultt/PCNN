//--=== STL ===--
#include <iostream>

//--=== Dependencies ===--
#include <png++/png.hpp>

//--=== Other files ===--
#include "maths.h"

const long img_w = 512, img_h = 512;

int main(int argc, char** argv)
{
	//check arg count and display help page
	if (argc < 4 || (strcmp(argv[1], "c") && strcmp(argv[1], "t"))) {
		std::cout << "--===  Help ===--\nTrain model\n\t" << argv[0] << " t <model directory> <data A> <data B> <data C> ...\n"\
			<< "Classify image\n\t" << argv[0] << " c <model directory> <image>" << std::endl;
		return -1;
	}

	if (!strcmp(argv[1], "t")) {
		//--=== Training ===--
		std::cout << "Training neural network at: " << argv[2] << std::endl;
	} else if (!strcmp(argv[1], "c")) {
		//--=== Classification ===--
		std::cout << "Classifying image with: " << argv[2] << std::endl;
		try {
			std::vector<double> v = {5, 6, 3, 2, 4, 1, -2, 0.5, 0.6, 3, 5, 7};
			matrix<double> A(4, 3, v);
			matrix<double> B(4, 3, {1, 0, 0, 0, 0, 5, 4, 3, 1, 0, 0, 3});
			matrix<double> C = B + A;
			std::cout << A << "\n+\n" << B << "\n=\n" << C;
		} catch (std::string e) {
			std::cout << "[ERROR][MATRIX TESTING] " << e << std::endl;
		}
	}

	return 0;
}
