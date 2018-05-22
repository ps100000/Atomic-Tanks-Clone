#ifndef ANIMATION_H
#define ANIMATION_H

#include <fstream>
#include <iostream>

#include "pic.h"
#include "render.h"
#include "vec2d.h"

class pic;
class render;

struct frame{
	unsigned char delay;
	bool stop;
};

class animation{
	private:
		pic* texture;
		
		bool playing = false;
		bool selfdestruct = false;
		unsigned int active_frame = 0;
		std::vector<frame> frames;
		unsigned int frame_width;
		unsigned int frame_height;
		
		unsigned char delay;
		
		static unsigned long id_counter;
		unsigned long id = id_counter++;
	protected:
		void update();
	public:
		friend render;
		
		animation();
		animation(std::string filename);
		~animation();
		
		void load(std::string filename);
		void play(bool p);
		
		unsigned int get_frame();
		bool set_frame(unsigned int frame);
		
		
		int get_layer();
		void set_layer(int l);
		
		bool is_visible();
		void set_visible(bool v);
		
		void set_translation(vec2d t);
		vec2d get_translation();
		void set_translation_point(vec2d point);
		vec2d get_translation_point();
		
		void set_rotation(float r);
		float get_rotation();
		void set_rotation_point(vec2d point);
		vec2d get_rotation_point();
		
		void set_scale_x(float scale);
		void set_scale_y(float scale);
		float get_scale_x();
		float get_scale_y();
};

#endif