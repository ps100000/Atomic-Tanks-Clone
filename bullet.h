#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <stdio.h>

#include "vec2d.h"
#include "bullet_bdet.h"
#include "bullet_bxpl.h"
#include "bullet_bmov.h"
#include "pic.h"
#include "config.h"

class b_missile;

class bullet{
	protected:
		pic texture;
		bool phase = false; // is game allowed to let next player control
		bool init = false;
	public:
		virtual ~bullet();
		bool next_phase();
		virtual bool update() = 0;
};

class b_std:bullet{
	public:
		bd_impact det;
		bx_circle exp;
		bm_gravity mov;
		
		b_std();
		b_std(vec2d pos,vec2d velocity);
		b_std(vec2d pos,vec2d velocity, int radius);
		~b_std();
		bool update();
};

class b_sub_mine:bullet{
	private:
		int state = 0;
	public:
		bd_impact flip;
		bd_contact det;
		bx_circle exp;
		bm_gravity mov;
		
		b_sub_mine();
		b_sub_mine(vec2d pos,vec2d velocity);
		~b_sub_mine();
		bool update();
};




class b_bounce:bullet{
	private:
		int state = 0;
	public:
		bm_gravity mov;
		bd_impact det;
		bx_circle exp;
		b_bounce();
		b_bounce(vec2d pos,vec2d velocity);
		~b_bounce();
		bool update();
};

class b_nuke:bullet{
	private:
		bool state = false;
	public:
		bd_impact det;
		bx_nuke exp;
		bm_gravity mov;
		
		b_nuke();
		b_nuke(vec2d pos,vec2d velocity);
		~b_nuke();
		bool update();
};

class b_missile_marker:bullet{
	private:
		b_missile* m1 = NULL;
		b_missile* m2 = NULL;
	public:
		bd_impact det;
		bm_gravity mov;
		
		b_missile_marker();
		b_missile_marker(vec2d pos,vec2d velocity, b_missile* m1_ptr, b_missile* m2_ptr);
		~b_missile_marker();
		bool update();
		
};

class b_missile:bullet{
	friend b_missile_marker;
	private:
		int state = 0;
		vec2d target;
	public:
		bd_impact det;
		bx_circle exp;
		bm_search mov2;
		bm_gravity mov1;
		
		b_missile();
		b_missile(vec2d pos,vec2d velocity);
		~b_missile();
		bool update();
};

extern std::vector<bullet*> bullets;

#endif