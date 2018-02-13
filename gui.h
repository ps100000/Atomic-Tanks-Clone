#ifndef GUI_H
#define GUI_H



#include "player.h"
#include "pic.h"
#include "config.h"
#include "vec2d.h"

class player;

class gui{
	private:
		pic main;
		pic weapon;
	protected:
		void set_fuel(int f);
		void set_life(int l);
		void set_weapon(int w);
	public:
		friend player;
		gui();
		void set_visible(bool v);
};

extern gui menue;

#endif