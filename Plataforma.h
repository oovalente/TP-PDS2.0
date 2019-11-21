#include <allegro5/allegro.h>

class Plataforma
{
private:
	int x;
	int y;
	int vida;
	int velocidade;
	int ID;

public:
	Plataforma(int x, int y, int vida, int velocidade);

	void Draw(ALLEGRO_BITMAP* buffer);
	void Control_left();
	void Control_right();
	void colidir();


};