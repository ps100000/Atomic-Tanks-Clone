#include "gui.h"

void gui::set_fuel(int f){//line angle 32x32
	if(f >= 0 && f <= MAX_FUEL){
		vec2d temp1;
		vec2d temp2;
		
		temp1.x = 6;
		temp1.y = 5;
		main.draw_rect(temp1, 20, 21, 128, 128, 128);
		
		
		temp1.x = 6;
		temp1.y = 25;
		temp2.x = 20;
		temp2.y = 0;
		temp2.rotateBy( -1 * (3.1415 / 2) * (1.0 * f / MAX_FUEL) );
		temp2 += temp1;
		
		main.draw_line(temp1,temp2,255,0,0);
	}
}

void gui::set_life(int l){//bar + color 64x32
	if(l >= 0 && l <= MAX_LIFE){
		vec2d temp;
		temp.x = 37;
		temp.y = 15;
		main.draw_rect(temp, 54, 5, 255, 255, 255);
		main.draw_rect(temp, 54  * l / MAX_LIFE, 5, 255 - 255  * l / MAX_LIFE, 255  * l / MAX_LIFE, 0);
	}
}

void gui::set_weapon(int w){//test
	if(w >= 0 && w < WEAPON_COUNT){
		vec2d temp;
		temp.x = 0;
		temp.y = w * 32;
		weapon.set_sector(temp, 128, 32);
	}
}


gui::gui(){
	main.load_pic("./texturepack/main_gui.png");
	weapon.load_pic("./texturepack/weapons.png");
	vec2d temp;
	temp.x = SCREEN_WIDTH / 2 - 112;
	temp.y = SCREEN_HEIGHT - 32;
	main.set_translation(temp);
	temp.x = SCREEN_WIDTH / 2 - 16;
	weapon.set_translation(temp);
	set_weapon(0);
	set_fuel(0);
	set_life(0);
}

void gui::set_visible(bool v){
	main.set_visible(v);
	weapon.set_visible(v);
}


gui menue;