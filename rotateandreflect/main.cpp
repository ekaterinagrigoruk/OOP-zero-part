#include <iostream>
#include"BMP_rotatereflect.h"
#include "CImg.h"



int main() {

	std::string name_image;
	std::cout << "Input the image name: \n";
	std::cin >> name_image;

	const char* nameimage = name_image.c_str();
	cimg_library::CImg<unsigned char> image(nameimage);
	BMP newimage(image);

	name_image.erase(name_image.end() - 4, name_image.end());

	cimg_library::CImg<unsigned char> newimage_90(image.height(), image.width(), 1, 3);
	newimage_90 = newimage.rotate(newimage_90, Angle::rotate90);

	std::string angle = "_90.bmp";
	std::string newname = name_image + angle;

	newimage_90.save_bmp(newname.c_str());


	cimg_library::CImg<unsigned char> newimage_270(image.height(), image.width(), 1, 3);
	newimage_270 = newimage.rotate(newimage_270, Angle::rotate270);

	angle = "_270.bmp";
	newname = name_image + angle;

	newimage_270.save_bmp(newname.c_str());

	cimg_library::CImg<unsigned char> newimage_180(image.width(), image.height(), 1, 3);
	newimage_180 = newimage.rotate(newimage_180, Angle::rotate180);

	angle = "_180.bmp";
	newname = name_image + angle;

	newimage_180.save_bmp(newname.c_str());


	cimg_library::CImg<unsigned char> newimage_v(image.width(), image.height(), 1, 3);
	newimage_v = newimage.reflect(newimage_v, Angle::reflectvertical);

	angle = "_v.bmp";
	newname = name_image + angle;

	newimage_v.save_bmp(newname.c_str());


	cimg_library::CImg<unsigned char> newimage_h(image.width(), image.height(), 1, 3);
	newimage_h = newimage.reflect(newimage_h, Angle::reflecthorizontal);

	angle = "_h.bmp";
	newname = name_image + angle;

	newimage_h.save_bmp(newname.c_str());


	return 0;
}