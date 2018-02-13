#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "pic.h"
#include "vec2d.h"
#include "input.h"
#include "world.h"
#include "player.h"
#include "gui.h"
#include "bullet.h"

bool quit;
bool quit_in;

int main(int argc, char* args[]){
	
	pic start;
	start.load_pic("./texturepack/start.png");
	start.set_visible(true);
	start.set_layer(4);
	bool a = false;
	input_controller.add_event(&a,SDLK_SPACE);
	main_renderer.show();
	while(a == false){
		input_controller.update();
	}
	start.set_visible(false);
	
	earth.generate();
	main_renderer.update_world();
	menue.set_visible(true);
	players[0].update();
	players[1].update();
	
	input_controller.add_event(&quit_in, SDLK_x);
	
	while(!quit){
		for(int i = 0; i < 2; i++){
			input_controller.clear();
			do{
				players[i].update();
				input_controller.update();
				
				if(quit_in){quit = true;}
				
				std::vector<int> destroyed;
				for(int j = 0; j < bullets.size(); j++){
					if(!bullets[j]->update()){
						destroyed.push_back(j);
					}
					
				}
				for(int j = destroyed.size() - 1; j >= 0; j--){
					delete bullets[destroyed[j]];
					bullets.erase(bullets.begin() + destroyed[j]);
				}
				main_renderer.show();
				SDL_Delay(20);
				
			}while(players[i].is_active());
			
			bool update_bullets = true;
			while(update_bullets){
				input_controller.clear();
				
				std::vector<int> destroyed;
				update_bullets = false;
				
				for(int j = 0; j < bullets.size(); j++){
					
					if(!bullets[j]->next_phase()){
						update_bullets = true;
					}
					
					if(!bullets[j]->update()){
						destroyed.push_back(j);
					}
					
				}
				for(int j = destroyed.size() - 1; j >= 0; j--){
					delete bullets[destroyed[j]];
					bullets.erase(bullets.begin() + destroyed[j]);
				}
				main_renderer.show();
				SDL_Delay(20);
			}
			
			if(!players[0].alife()){
				start.load_pic("./texturepack/victory1.png");
				start.set_visible(true);
				start.set_layer(4);
				menue.set_visible(false);
				main_renderer.show();
				SDL_Delay(5000);
				return 0;
			}
			if(!players[1].alife()){
				start.load_pic("./texturepack/victory2.png");
				start.set_visible(true);
				start.set_layer(4);
				menue.set_visible(false);
				main_renderer.show();
				SDL_Delay(5000);
				return 0;
			}
			SDL_Delay(1000);
		}
	}
}
