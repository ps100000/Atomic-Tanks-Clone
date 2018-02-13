#ifndef BULLET_BMOV_H
#define BULLET_BMOV_H

#include "vec2d.h"

class bmov{
	protected:
		bool initalized = false;
		vec2d pos;
		vec2d vel;
	public:
		void init(vec2d p, vec2d v);
		vec2d get_pos();
		vec2d get_vel();
		void update();
};

class bm_gravity:public bmov{	//gravity center = surface at x of projectile
	private:
		bool inverted = false;
	public:
		void update();
		void invert(bool i);
};

class bm_search:public bmov{
	private:
		vec2d target;
	public:
		void update();
		void set_target(vec2d t);
};

#endif