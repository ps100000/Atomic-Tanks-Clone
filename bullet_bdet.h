#ifndef BULLET_DETONATOR_H
#define BULLET_DETONATOR_H

#include "vec2d.h"
#include "world.h"


class bdet{
	public:
		bool check(vec2d pos);
};

class bd_impact:public bdet{
		bool inverted = false;
	public:
		bool check(vec2d pos);
		void invert(bool i);
};

class bd_contact:public bdet{
	private:
		int rad = 10;
	public:
		bool check(vec2d pos);
		void set_rad(int r);
};

#endif