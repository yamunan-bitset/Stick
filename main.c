#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdlib.h>

const float FPS = 60;

int main(int argc, char *argv[])
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* bitmap = NULL;

	bool running = true;
	bool redraw = true;

	// Initialize allegro
	if (!al_init())
	{
		fprintf(stderr, "Failed to initialize allegro.\n");
		return 1;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "Failed to install keyboard\n");
		return 1;
	}

	// Initialize the timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "Failed to create timer.\n");
		return 1;
	}

	// Create the display
	display = al_create_display(640, 480);
	if (!display)
	{
		fprintf(stderr, "Failed to create display.\n");
		return 1;
	}

	// Create the event queue
	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		fprintf(stderr, "Failed to create event queue.\n");
		return 1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Failed to load primitevs addon.\n");
		return 1;
	}

	// Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	// Display a black screen
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	// Start the timer
	al_start_timer(timer);

	float x=0,y=0; // Player position

	// Game loop
	while (running)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_KEYBOARD_STATE key_state;
		al_get_keyboard_state(&key_state);
	
		// Draw figure
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 1)); 
		al_draw_line(x,y,al_get_display_width(display),
			al_get_display_height(display),al_map_rgb(255,255,255),5.0f);
		al_flip_display();

		// Draw enemy primitives
		if (draw_enemy)
		{
			// TODO
		}

		// Fetch the event (if one exists)
		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		// Initialize timeout
		al_init_timeout(&timeout,0.06);

		// Handle the event
		if (get_event)
		{
			switch (event.type)
			{
				case ALLEGRO_EVENT_TIMER:
					redraw = true;
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					running = false;
					break;
				default:
					fprintf(stderr, "Unsupported event received: %d\n", event.type);
					break;
			}
			if (al_key_down(&key_state,ALLEGRO_KEY_RIGHT))
				x+=10;
			if (al_key_down(&key_state,ALLEGRO_KEY_LEFT ))
				x-=10;
			if (al_key_down(&key_state,ALLEGRO_KEY_DOWN ))
				y+=10;
			if (al_key_down(&key_state,ALLEGRO_KEY_UP   ))
				y-=10;
		}

		// Check if we need to redraw
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			// Redraw
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			redraw = false;
		}
	} 

	// Clean up
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_event_queue(event_queue);
		
	return 0;
}
