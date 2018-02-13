#include "bullet_bdet.h"
#include "player.h"

bool bdet::check(vec2d pos){}

bool bd_impact::check(vec2d pos){
	if(inverted){
		if(earth.get_high(pos.x) < SCREEN_HEIGHT - pos.y ){
			return true;
		}
	}else{
		if(earth.get_high(pos.x) > SCREEN_HEIGHT - pos.y ){
			return true;
		}
	}
	return false;
}

void bd_impact::invert(bool i){
	inverted = i;
}

bool bd_contact::check(vec2d pos){
	for(int i = 0; i < 2; i++){
		if( (players[i].get_pos() - pos).getLength() < rad ){
			return true;
		}
	}
	return false;
}

void bd_contact::set_rad(int r){
	rad = r;
}