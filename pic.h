#ifndef PIC_H
#define PIC_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vec2d.h"
#include "render.h"

class render;

class pic{
	protected:
		SDL_Texture* texture = NULL;
		SDL_Rect src;
		SDL_Rect dest;
		bool visible = false;
		SDL_Point rotation_point;
		vec2d translation_point;
		float rotation = 0;
		int layer = 1;
		static unsigned long id_counter;
		unsigned long id = id_counter++;
	public:
		
		friend render;
		
		pic(); //register in renderer
		~pic(); //^
		void load_pic(std::string file);
		int get_layer();
		void set_layer(int l); //0 background 4gui
		
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
		 
		unsigned int get_width();
		unsigned int get_height();
		
		void set_sector(vec2d corner, int width, int high);
		
		void set_pixel(vec2d pos, int r,int g, int b, int a = 255);
		void draw_line(vec2d begin, vec2d end,int r,int g, int b, int a = 255);
		void draw_rect(vec2d corner, int width, int high, int r,int g, int b, int a = 255, bool filled = true);
		void draw_bx_circle(vec2d center, int rad, int r,int g, int b, int a = 255);
		void copy_pic(pic* src, vec2d corner_src, int w_src, int h_src,vec2d corner_dest, int w_dest, int h_dest);
};

#endif