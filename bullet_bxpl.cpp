#include "bullet_bxpl.h"
#include "player.h"

void bxpl::activate(vec2d pos){}

bx_circle::bx_circle():bx_circle(15){
}

bx_circle::bx_circle(int r){
	rad = r;
	texture.load_pic("./texturepack/explode_circle.png");
	vec2d temp;
	temp.x = 0;
	temp.y = 0;
	texture.set_sector(temp,32,32);
	temp.x = r;
	temp.y = r;
	texture.set_translation_point(temp);
	texture.set_scale_x( (2.4 * r) / 32.0 );
	texture.set_scale_y( (2.4 * r) / 32.0 );
	texture.set_layer(3);
}

void bx_circle::activate(vec2d pos){
	for(int i = 0; i < 2; i++){
		if( (players[i].get_pos() - pos).getLength() < rad ){
			players[i].damage(25);
		}
	}
	
	for(int i = -rad; i <= rad; i++){
		int y = SCREEN_HEIGHT - (( pos.y ) - i * i / rad + rad);/*pos.y -> SCREEN_HEIGHT - earth.get_high(pos.x + i)*/
		if(y < earth.get_high(pos.x + i)){
			earth.set_high(pos.x + i,y);
		}
	}
	
	main_renderer.update_world();
	main_renderer.show();
	
	texture.set_translation(pos);
	texture.set_visible(true);
	vec2d temp;
	temp.y = 0;
	for(int i = 0; i < 4; i++){
		temp.x = i * 32;
		texture.set_sector(temp,32,32);
		main_renderer.show();
		SDL_Delay(100);
	}
	texture.set_visible(false);
}

void bx_circle::set_damage(int d){
	damage = d;
}

void bx_circle::set_radius(int r){
	rad = r;
	texture.set_scale_x(rad * 2.4 / 32.0);
	texture.set_scale_y(rad * 2.4 / 32.0);
	vec2d temp;
	temp.x = rad;
	temp.y = rad;
	texture.set_translation_point(temp);
}

bx_nuke::bx_nuke(){
	texture.load_pic("./texturepack/nuke.png");
	texture.set_layer(3);
	vec2d temp;
	temp.x = 80;
	temp.y = 288;
	texture.set_translation_point(temp);
}

void bx_nuke::activate(vec2d pos){
	texture.set_translation(pos);
	texture.set_visible(true);
	
	for(int i = 0; i < 2; i++){
		if( players[i].get_pos().x - pos.x > - 80 && players[i].get_pos().x - pos.x < 80){
			players[i].damage(damage);
			players[i].update_y();		
		}
	}
	
	for(int i = pos.x - 80; i <= pos.x + 80; i++){
		if(SCREEN_HEIGHT - pos.y < earth.get_high(i)){
			earth.set_high(i, SCREEN_HEIGHT - pos.y);
			
		}
	}
	main_renderer.update_world();
	
	main_renderer.show();
	SDL_Delay(4000);
	texture.set_visible(false);
	main_renderer.show();
}

void bx_nuke::set_damage(int d){
	damage = d;
}