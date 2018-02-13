#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <SDL2/SDL.h>
#include <stdio.h>

class input{
	private:
		std::vector<bool*> out;
		std::vector<int> keycode;
		SDL_Event event;
	public:
		void update();
		void clear();
		void add_event(bool* o, int key);
		void delete_event(int key);
};

extern input input_controller;

#endif