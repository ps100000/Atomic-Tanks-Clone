#ifndef PLAYER_H
#define PLAYER_H

#include <time.h>
#include <stdlib.h>

#include "gui.h"
#include "vec2d.h"
#include "pic.h"
#include "input.h"
#include "config.h"
#include "world.h"
#include "bullet.h"

class player{
	private:
		pic turret;
		pic body;
		int life = MAX_LIFE;
		int fuel = MAX_FUEL;
		int arsenal[15];
		int selected_wep = 0;
		int angle = 0;
		int power = 75;
		bool active = false;
		bool init = false;
		
		//input bools
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
		bool wep_up = false;
		bool wep_down = false;
		bool power_up = false;
		bool power_down = false;
		bool fire = false;
		
		bool wep_changed = false;
	public:
		player();
		void update();
		bool is_active();
		vec2d get_pos();
		bool alife();
		void damage(int dmg);
		void update_y();
};

extern player players[2];

#endif