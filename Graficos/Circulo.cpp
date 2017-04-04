#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Circulo.hpp"
//#include <SDL2/SDL2_gfxPrimitives.h>
#include "Logger2.hpp"
#include <vector>

Circulo::Circulo(int x, int y, int r)
: Sprite(x - r, y - r, r*2, r*2){

	radius = r;
	//calculo el centro del circulo

	//chequeo que no queden valores negativos
	if (originX < 0){
		rectangle.x = x;
	}
	if (y < 0){
		rectangle.y = y;
	}

	originX = x;
	originY = y;

	colored_texture = NULL;
	colored_aux_texture = NULL;

	//se define una textura circular de color
	Size size(width,height);
	//podria cargar cualquier textura aca
	Mat3b colored_img = imread("Graficos/texture.png",IMREAD_UNCHANGED);
	//el circulo por default se seta blanco
	colored_img.setTo(cv::Scalar(255,255,255));
	resize(colored_img, aux_img, size,INTER_NEAREST);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	imwrite("Graficos/circularcolor.png", aux_img ,compression_params);

	//se guarda una textura auxiliar para usar con la textura original
	Texture* aux_color = new Texture();
	aux_color->loadFromFile("circularcolor.png");
	colored_aux_texture = aux_color;

	//se define una textura de color
	CrearImagenCircular(aux_img);
	Texture* color = new Texture();
	color->loadFromFile("Graficos/circulartexture.png");
	colored_texture = color;

}

void Circulo::setTexture(string path){
	Mat3b text_img = imread(path ,IMREAD_UNCHANGED);
	if((text_img.cols < aux_img.cols)&&(text_img.rows<aux_img.rows)){
		text_img.copyTo(aux_img(Rect(0,0,text_img.cols,text_img.rows)));
		CrearImagenCircular(aux_img);
	}
	else{
		CrearImagenCircular(text_img);
	}
	Texture* aux_texture = new Texture();
	aux_texture->loadFromFile("Graficos/circulartexture.png");
	texture = aux_texture;

}

void Circulo::CrearImagenCircular(Mat3b im){

		Mat1b mask(width, height, uchar(0));
		circle(mask, Point(originX , originY), radius, Scalar(255), CV_FILLED);

		int nx = (mask.cols / im.cols) + 1;
		int ny = (mask.rows / im.rows) + 1;

		Mat3b repeated = repeat(im, nx, ny);

		Mat3b crop= repeated(Rect(0, 0, mask.cols, mask.rows));

		//color key por defecto
		Mat3b result(mask.rows, mask.cols, Vec3b(255, 255, 0));


		crop.copyTo(result, mask);
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		imwrite("Graficos/circulartexture.png", result ,compression_params);
}

void Circulo::render(camara* cam){
	//Si no tiene textura cargada, pinta con el color de fondo.
	int auxX = originX - cam->getX();
	int auxY = originY - cam->getY();

	if(texture) texture->render(auxX, auxY, &rectangle);
			else{
				colored_texture->setBackgroundColor(red, green, blue);
				colored_texture->render(auxX, auxY, &rectangle);
			}
		}
