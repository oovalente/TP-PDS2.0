#include "Plataforma.h"

Objeto::Objeto(int x, int y, int vida, int ID)
{
	this->x = x;
	this->y = y;
	this->vida = vida;
	this->ID = ID;
}

void Objeto::Draw(ALLEGRO_BITMAP* buffer)
{
	//usa a cor rosa como transparencia
	al_convert_mask_to_alpha(buffer, al_map_rgb(255, 0, 255));
	//desenha o quadrado na tela nas posicoes X e Y
	al_draw_bitmap(buffer, this->x, this->y, 0);
}

void Objeto::Control_left()
{
	int dir_xx = 5;

	
		if (x <= 100) {
			x = 100;
		}
		//movimenta objeto 
		this->x -= 8 * dir_xx;
}

void Objeto::Control_right()
{
	int dir_xx = 5;
	
		if (x >= 1000) {
			x = 1000;
		}
		//movimenta objeto
		this->x += 8 * dir_xx;
}

void Objeto::colidir()
{
	
}

