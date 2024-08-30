#include <array>
#include "BMP_rotatereflect.h"
#include "CImg.h"

const static int red = 0;
const static int green = 1;
const static int blue = 2;

BMP::BMP(cimg_library::CImg<unsigned char> image) {

	Width = image.width();
	Height = image.height();
	cimg_forXY(image, x, y) {
		int red_value = (int)image(x, y, 0);
		int green_value = (int)image(x, y, 1);
		int blue_value = (int)image(x, y, 2);
		Pixel pixel = { red_value, green_value, blue_value };
		pixels.push_back(pixel);
	}
}

void BMP::rotate90_270(cimg_library::CImg<unsigned char>& image, int x, int y) {
	image(x, y, red) = pixels.at((size_t)Width * (size_t)(x + 1) - 1 - y).red;
	image(x, y, green) = pixels.at((size_t)Width * (size_t)(x + 1) - 1 - y).green;
	image(x, y, blue) = pixels.at((size_t)Width * (size_t)(x + 1) - 1 - y).blue;
}

void BMP::rotate180(cimg_library::CImg<unsigned char>& image, int x, int y) {
	image(x, y, red) = pixels.at((size_t)Width * Height - 1 - (size_t)Width * y - x).red;
	image(x, y, green) = pixels.at((size_t)Width * Height - 1 - (size_t)Width * y - x).green;
	image(x, y, blue) = pixels.at((size_t)Width * Height - 1 - (size_t)Width * y - x).blue;
}

void BMP::reflect_v(cimg_library::CImg<unsigned char>& image, int x, int y) {
	image(x, y - 1, red) = pixels.at((size_t)Width * y - 1 - x).red;
	image(x, y - 1, green) = pixels.at((size_t)Width * y - 1 - x).green;
	image(x, y - 1, blue) = pixels.at((size_t)Width * y - 1 - x).blue;
}

void BMP::reflect_h(cimg_library::CImg<unsigned char>& image, int x, int y) {
	image(x, y - 1, red) = pixels.at((size_t)Width * Height - (size_t)Width * y + x).red;
	image(x, y - 1, green) = pixels.at((size_t)Width * Height - (size_t)Width * y + x).green;
	image(x, y - 1, blue) = pixels.at((size_t)Width * Height - (size_t)Width * y + x).blue;
}

cimg_library::CImg<unsigned char> BMP::rotate(cimg_library::CImg<unsigned char>& image, Angle angle) {
	for (int x = 0; x < image.width(); x++) {
		for (int y = 0; y < image.height(); y++) {
			(this->*funcs[(int)angle])(image, x, y);
		}
	}

	return image;
}

cimg_library::CImg<unsigned char> BMP::reflect(cimg_library::CImg<unsigned char>& image, Angle angle) {
	for (int x = 0; x < Width; x++) {
		for (int y = 1; y < Height + 1; y++) {
			(this->*funcs[(int)angle])(image, x, y);
		}
	}

	return image;
}