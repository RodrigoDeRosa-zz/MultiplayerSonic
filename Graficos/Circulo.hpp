#ifndef CIRCULO_HPP
#define CIRCULO_HPP

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

class Circulo: public Sprite {
	Mat3b text_img;
	Mat3b aux_img;
	Texture* colored_texture;
	Texture* colored_aux_texture;
	int radius;
	void CrearImagenCircular(Mat3b im);
public:
	Circulo(int x, int y, int r);
	void render(camara*);
	void setTexture(string);
	//falta modificar el free
};

#endif
