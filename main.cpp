#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <time.h>
#include "Plataforma.h"

using namespace std;

// variaveis globais
const float FPS = 60;
const int SCREEN_W = 830; //largura da tela
const int SCREEN_H = 570; //altura da tela

//variaveis allegro
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_EVENT_QUEUE* fila_eventos = nullptr;
ALLEGRO_BITMAP* fundo = nullptr;
ALLEGRO_BITMAP* folha_sprite = nullptr;

int main()
{
	//objeto plataforma
	Objeto Plataforma(250, 500, 0, 0);

//----------------------- rotinas de inicializacao ---------------------------------------
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

// ----------------------------- CREATING THE BITMAPS -----------------------------------
  //inicia imagem
	al_init_image_addon();

	fundo = al_load_bitmap("fundo.png");
	folha_sprite = al_load_bitmap("plataforma.png");
	
	if (!fundo) {
		cout << "failed to create bitmaps!\n";
		al_destroy_display(display);
		al_destroy_bitmap(folha_sprite);
		al_destroy_timer(timer);
		return -1;
	}

	//avisa o allegro que agora eu quero modificar as propriedades da tela
	al_set_target_bitmap(al_get_backbuffer(display));

// --------------------------- CREATING THE EVENT QUEUE --------------------------------
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

	while (1)
	{
		//espera por um evento e o armazena na variavel de evento ev
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			//verifica a tecla apertada, chama a funcao para testar se acertou a nota. Se sim, faz um sinal sonoro e aumenta um ponto. Se não, a tela para por 0.3 segundos e perde um ponto
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

		//P1.Draw(folha_sprite);
		Plataforma.Draw(folha_sprite);

		//atualiza a tela
		al_flip_display();
	}

	//destroi a tela criada para o jogo
	al_destroy_display(display);
	al_destroy_bitmap(fundo);
	al_destroy_timer(timer);
	al_destroy_bitmap(folha_sprite);
	return 0;
}