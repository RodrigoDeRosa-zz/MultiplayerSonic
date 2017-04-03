#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Circulo.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Logger2.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

using namespace cv;
using namespace std;

Circulo::Circulo(int x, int y, int r)
: Sprite(x, y, r*2, r*2){

	radius = r;
	//calculo el centro del circulo
	originX = x + (radius);
	originY = y + (radius);

	//esta textura se podria cargar de afuera
	aux_texture = NULL;
}

void Circulo::setTexture(SDL_Surface* aux){
	aux_texture = aux;
//	aux->w = width;
//	aux->h = height;
}

void CrearImagenCircular(Mat3b im){
		// Mat3b img = imread("Graficos/f.png",IMREAD_UNCHANGED);
		// Size size(400,400);
		// Mat3b im;
		// resize(img,im,size);
		Mat1b mask(400, 400, uchar(0));
		circle(mask, Point(200, 200), 200, Scalar(255), CV_FILLED);

		int nx = (mask.cols / im.cols) + 1;
		int ny = (mask.rows / im.rows) + 1;

		Mat3b repeated = repeat(im, nx, ny);

		Mat3b crop= repeated(Rect(0, 0, mask.cols, mask.rows));

		Mat3b result(mask.rows, mask.cols, Vec3b(32, 25, 55));

		crop.copyTo(result, mask);
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		imwrite("Graficos/test1.png", result ,compression_params);
}

void resizeCircle(){
// 	// min_x, min_y should be valid in A and [width height] = size(B)
// cv::Rect roi = cv::Rect(200, 200, im.cols, im.rows);
//
// // "out_image" is the output ; i.e. A with a part of it blended with B
// cv::Mat out_image = def_col_img.clone();
//
// // Set the ROIs for the selected sections of A and out_image (the same at the moment)
// cv::Mat A_roi= def_col_img(roi);
// cv::Mat out_image_roi = out_image(roi);
//
// // Blend the ROI of A with B into the ROI of out_image
// cv::addWeighted(A_roi,alpha,im,1-alpha,0.0,out_image_roi);

}


void Circulo::render(camara* cam){
    	//CrearImagenCircular();
			Size size(400,400);
		  Mat3b im = imread("Graficos/negro.jpg",IMREAD_UNCHANGED);
		  Mat3b colored_img = imread("Graficos/texture.png",IMREAD_UNCHANGED);
		  Mat def_col_img, def_img;
		  colored_img.setTo(cv::Scalar(13,255,24));
		  resize(colored_img, def_col_img, size,INTER_NEAREST);

			im.copyTo(def_col_img(Rect(0,0,im.cols,im.rows)));
			vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);
			CrearImagenCircular(def_col_img);
			//imwrite("Graficos/test2.png", def_col_img ,compression_params);


			// Texture* tex = new Texture();
		// tex -> loadFromFile("Graficos/test.png");
		// if(tex) tex->render(auxX, auxY, &rectangle);
      /*else{
            if(!Renderer::getInstance().fillCircle((Sint16)auxX,(Sint16) auxY,(Sint16) radius, red, green, blue)){
            	Logger::getInstance().log("In Circulo::render: Failed to fill circle color");
            }
        }*/
    }
