#pragma once
#include <vector>
#include <array>
#include <string>
#include "CImg.h"

enum class Angle {
	rotate90 = 0,
	rotate180 = 1,
	rotate270 = 0,
	reflectvertical = 2,
	reflecthorizontal = 3
};

struct Pixel {
	int red;
	int green;
	int blue;
};

class BMP final {
public:
	BMP(cimg_library::CImg<unsigned char> image);
	~BMP() = default;

	cimg_library::CImg<unsigned char> rotate(cimg_library::CImg<unsigned char>& image, Angle angle);
	cimg_library::CImg<unsigned char> reflect(cimg_library::CImg<unsigned char>& image, Angle angle);

protected:
	int Width;
	int Height;
	std::vector<Pixel> pixels;
private:

	void rotate90_270(cimg_library::CImg<unsigned char>& image, int x, int y);
	void rotate180(cimg_library::CImg<unsigned char>& image, int x, int y);
	void reflect_v(cimg_library::CImg<unsigned char>& image, int x, int y);
	void reflect_h(cimg_library::CImg<unsigned char>& image, int x, int y);
	std::array <void(BMP::*) (cimg_library::CImg<unsigned char>&, int, int), 4> funcs = { &BMP::rotate90_270, &BMP::rotate180, &BMP::reflect_v, &BMP::reflect_h };
};
