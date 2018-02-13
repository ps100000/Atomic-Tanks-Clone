#ifndef BULLET_EXPLOSION_H
#define BULLET_EXPLOSION_H

#include "pic.h"
#include "vec2d.h"
#include "render.h"
#include "config.h"
#include "world.h"

class bxpl{
	protected:
		pic texture;
	public:
		void activate(vec2d pos);
};

class bx_circle:public bxpl{
		int damage = 15;
		int rad = 10;
	public:
		bx_circle();
		bx_circle(int r);
		void activate(vec2d pos);
		void set_damage(int d);
		void set_radius(int r);
};

class bx_nuke:public bxpl{
	private:
		int damage = 60;
	public:
		bx_nuke();
		void activate(vec2d pos);
		void set_damage(int d);
		
};

#endif