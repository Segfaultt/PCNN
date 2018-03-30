//--=== STL ===--
#include <iostream>
#include <filesystem> //only c++>=14 

//--=== Dependencies ===--
#include <png++/png.hpp>

//--=== Other files ===--

const long img_w = 512, img_h = 512;

int main(int argc, char** argv)
{
	//check arg count and display help page
	if (argc < 3) {
		std::cout << "--===  Help ===--\nTrain model\n\t" << argv[0] << " <model directory> <data A> <data B> <data C> ...\n"\
			<< "Classify image\n\t" << argv[0] << " <model directory> <image>" << std::endl;
		return -1;
	}


	std::filesystem::path path(argv[2]);
	if (path.is_directory) {
		//--=== Training ===--
		std::cout << "Training neural network at: " << argv[0] << std::endl;
	} else {
		//--=== Classification ===--
		std::cout << "Classifying image with" << argc - 2 << std::endl;
	}
	png::image<png::rgb_pixel> img(img_w, img_h);
	img.read(argv[2]);
	
	return 0;
}
