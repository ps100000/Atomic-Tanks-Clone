#ifndef WORLD_H
#define WORLD_H

#include <time.h>
#include <stdlib.h>

#include "config.h"

class world{
	private:
		int highmap [SCREEN_WIDTH];
	public:
		void generate();
		int get_high(int pos);
		void set_high(int pos, int high);
};

extern world earth;

#endif