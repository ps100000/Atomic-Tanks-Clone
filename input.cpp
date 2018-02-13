#include "input.h"

void input::update(){
	while(SDL_PollEvent(&event)){
		for(int i = 0; i < keycode.size(); i++){
			switch(event.type){
			case 0x300:
				if(event.key.keysym.sym == keycode[i]){
					*out[i] = true;
				}
				break;
			case 0x301:
				if(event.key.keysym.sym == keycode[i]){
					*out[i] = false;
				}
				break;
			default:
				break;
			}
		}
	}
}

void input::clear(){
	while(SDL_PollEvent(&event)){}
	for(int i = 0; i < out.size(); i++){
		*out[i] = false;
	}
}

void input::add_event(bool* o, int key){
	delete_event(key);
	out.push_back(o);
	keycode.push_back(key);
}

void input::delete_event(int key){
	for(int i; i < keycode.size(); i++){
		if(keycode[i] == key){
			out.erase(out.begin() + i);
			keycode.erase(keycode.begin() + i);
		}
	}
}

input input_controller;