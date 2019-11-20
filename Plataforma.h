#include <allegro5/allegro.h>

class Objeto
{
private:
	int x;
	int y;
	int vida;
	int velocidade;

public:
	Objeto(int x, int y, int vida, int velocidade);

	void Draw(ALLEGRO_BITMAP* buffer);
	void Control_left();
	void Control_right();
	void colidir();


};