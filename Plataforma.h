#include <allegro5/allegro.h>

class Objeto
{
private:
	int x;
	int y;
	int vida;
	int ID;

public:
	Objeto(int x, int y, int vida, int ID);

	void Draw(ALLEGRO_BITMAP* buffer);
	void Control_left();
	void Control_right();
	void colidir();


};

