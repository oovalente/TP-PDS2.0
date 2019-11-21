#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <time.h>
#include "Plataforma.h"
#define TAM_BLOCOS 8

using namespace std;

// variaveis globais
const float FPS = 60;
const int SCREEN_W = 1600; //largura da tela
const int SCREEN_H = 700; //altura da tela
int CAMP_W = 1170; // largura do campo de jogo
int CAMP_H = 670; // altura do campo de jogo

//variaveis allegro
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_EVENT_QUEUE* fila_eventos = nullptr;
ALLEGRO_BITMAP* fundo = nullptr;
ALLEGRO_BITMAP* folha_sprite = nullptr;
ALLEGRO_BITMAP* bloco_sprite = nullptr;

struct Item
{
	int x;
	int y;
	int largura_x;
	int altura_y;
	int largura;
	int altura;
};

Item Bloco[TAM_BLOCOS][TAM_BLOCOS];

void cria_Blocos(Item B[TAM_BLOCOS][TAM_BLOCOS])
{
	int i,j;
	for (i = 0; i < TAM_BLOCOS; i++)
	{
		for (j = 0; j < TAM_BLOCOS; j++)
		{
			B[i][j].largura_x = 0;
			B[i][j].altura_y = 0;
			B[i][j].x = 86; //desenha sprite regiao x 
			B[i][j].y = 20; //desenha sprite regiao y; 80 eh um bloco
			B[i][j].largura = 80 + (i * 76);//80 eh pos inicial
			B[i][j].altura = 76+ 40*j; //eh a posicao da imagem no campo. 80 eh o ultimo bloco
		}
	}
}

void desenha_Blocos(Item B[TAM_BLOCOS][TAM_BLOCOS])
{
	int i, j;

	for(i = 0; i < TAM_BLOCOS; i++)
	{
		for (j = 0; j < TAM_BLOCOS; j++)
		{
			//al_draw_bitmap_region(folha_sprite,regiao_x_folha, regiao_y_folha, largura_sprite, altura_sprite,pos_x_sprite, pos_y_sprite, 0);
			al_draw_bitmap_region(bloco_sprite, B[i][j].largura_x, B[i][j].altura_y, B[i][j].x, B[i][j].y, B[i][j].largura, B[i][j].altura, 0);

		}
	}
}

int inicializar()
{
//--------------------------- INITIALIZATION PROCEDURES -----------------------------------------------------------------------

	if (!al_init()) {
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		cout << "failed to create display!\n";
		al_destroy_timer(timer);
		return -1;
	}

//_____________________________________________________________________________________________________________________________
// --------------------------- CREATING THE EVENT QUEUE -----------------------------------------------------------------------
	al_install_keyboard();

	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		cout << "failed to create event queue!\n";
		al_destroy_display(display);
		al_destroy_bitmap(folha_sprite);
		al_destroy_timer(timer);
		return -1;
	}
	//registra eventos do display em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(display));
	//registra na fila de eventos que eu quero identificar quando o tempo alterou de t para t+1
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	//registra teclado na fila de eventos
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());

	//atualiza a tela
	al_flip_display();
	//inicia o temporizador
	al_start_timer(timer);

	return 1;

//_____________________________________________________________________________________________________________________________
}

int main()
{
	//cria objeto
	Plataforma Plataforma(CAMP_W/2, CAMP_H * 0.95, 0, 0);

	if (!inicializar())
	{
		return -1;
	}

// ----------------------------- CREATING THE BITMAPS -------------------------------------------------------------------------
  
	//inicia imagem
	al_init_image_addon();

	fundo = al_load_bitmap("cenario.png");
	folha_sprite = al_load_bitmap("plataforma.png");
	bloco_sprite = al_load_bitmap("itens-paint.png");
	//usa a cor rosa como transparencia
	al_convert_mask_to_alpha(bloco_sprite, al_map_rgb(255, 0, 255));
	
	if (!fundo || !folha_sprite || !bloco_sprite) {
		cout << "failed to create bitmaps!\n";
		al_destroy_display(display);
		al_destroy_bitmap(folha_sprite);
		al_destroy_bitmap(fundo);
		al_destroy_bitmap(bloco_sprite);
		al_destroy_timer(timer);
		return -1;
	}

	//avisa o allegro que agora eu quero modificar as propriedades da tela
	al_set_target_bitmap(al_get_backbuffer(display));

//_____________________________________________________________________________________________________________________________
//------------------------------ THE GAME -------------------------------------------------------------------------------------
	cria_Blocos(Bloco);

	while (1)
	{
		//espera por um evento e o armazena na variavel de evento
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			//verifica a tecla apertada
			switch (evento.keyboard.keycode) 
			{
				//se a tecla for o A
			case ALLEGRO_KEY_A:
				Plataforma.Control_left();
				break;
				//se a tecla for o D
			case ALLEGRO_KEY_D:
				Plataforma.Control_right();
				break;

			case ALLEGRO_KEY_ESCAPE:
				return 0;
				break;
			}
		}

		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return 0;
		}

		//colore a tela de preto (rgb(0,0,0))
		al_clear_to_color(al_map_rgb(0, 0, 0));

		//desenha fundo
		al_draw_bitmap(fundo, 10, 10, 0);

		desenha_Blocos(Bloco);

		Plataforma.Draw(folha_sprite);

		//atualiza a tela
		al_flip_display();
	}

// ---------------------- FINISHING THE GAME ----------------------------------------------------------------------------------

	al_destroy_display(display);
	al_destroy_bitmap(fundo);
	al_destroy_timer(timer);
	al_destroy_bitmap(folha_sprite);
	al_destroy_bitmap(bloco_sprite);

	return 0;
}