#include "bullet_bmov.h"
#include <stdio.h>

void bmov::init(vec2d p, vec2d v){
	if(!initalized){
		pos = p;
		vel = v;
	}
}

vec2d bmov::get_pos(){
	return pos;
}

vec2d bmov::get_vel(){
	return vel;
}

void bmov::update(){}

void bm_gravity::update(){
	vel.y += (1 - inverted * 2) * 0.4;
	vel *= 0.99;
	pos += vel / 2;
}

void bm_gravity::invert(bool i){
	inverted = i;
}

void bm_search::update(){
	pos += vel / 2;
	vec2d temp = target - pos;
	temp.setLength(2.5);
	vel =  vel + vel + vel + temp;
	vel.setLength(10);
}

void bm_search::set_target(vec2d t){
	target = t;
}