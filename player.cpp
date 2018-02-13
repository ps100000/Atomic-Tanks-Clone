#include "player.h"

player::player(){
	
	turret.load_pic("./texturepack/turret.png"); //128 x 8
	body.load_pic("./texturepack/body.png"); //64 x 32
	vec2d temp;
	temp.x = 4;
	temp.y = 26;
	turret.set_translation_point(temp);
	temp.x = 4;
	temp.y = 4;
	turret.set_rotation_point(temp);
	temp.x = 32;
	temp.y = 28;
	body.set_translation_point(temp);
	body.set_rotation_point(temp);
	srand(time(NULL));
}

void player::update(){
	if(!init){
		init = true;
		for(int i = 0; i < 15; i++){
			arsenal[i] = rand() % WEAPON_COUNT;
		}
		vec2d temp;
		int i = rand() % SCREEN_WIDTH;
		temp.x = i;
		temp.y = earth.get_high(i);
		body.set_translation(temp);
		body.set_visible(true);
		turret.set_layer(2);
		turret.set_visible(true);
		printf("init\n");
	}else if(!active){
		active = true;
		fuel = MAX_FUEL;
		input_controller.clear();
		input_controller.add_event(&left, SDLK_a);
		input_controller.add_event(&right, SDLK_d);
		input_controller.add_event(&up, SDLK_w);
		input_controller.add_event(&down, SDLK_s);
		input_controller.add_event(&wep_up, SDLK_e);
		input_controller.add_event(&wep_down, SDLK_q);
		input_controller.add_event(&power_up, SDLK_r);
		input_controller.add_event(&power_down, SDLK_f);
		input_controller.add_event(&fire, SDLK_SPACE);
		menue.set_life(life);
		printf("active\n");
		fire = false;
	}
	
	
	if(fuel > 0){
		vec2d pos;
		pos = body.get_translation();
		pos.x += left * (-1) + right;
		fuel -= abs(left * (-1) + right);
		if(pos.x < 0 ){
			pos.x = 0;
		}else if(pos.x > SCREEN_WIDTH - 1){
			pos.x = SCREEN_WIDTH - 1;
		}
		pos.y = SCREEN_HEIGHT - earth.get_high(pos.x);
		body.set_translation(pos);
		turret.set_translation(pos);
		menue.set_fuel(fuel);
	}
	
	angle += down + up * (-1) + 360;
	angle = angle % 360;
	turret.set_rotation(angle);
	
	power += power_down * (-1) + power_up + 100;
	power = power % 100;
	turret.set_scale_x(power / 100.0);
	
	if(!(wep_down || wep_up)){
		wep_changed = false;
	}
	
	if(!wep_changed && (wep_down || wep_up)){
		wep_changed = true;
		selected_wep += wep_down * (-1) + wep_up + 15;
		selected_wep = selected_wep % 15; //grafik sector move
	}
	menue.set_weapon(arsenal[selected_wep]);
	
	if(fire){
		vec2d temp1;
		temp1.x = 1;
		temp1.y = 0;
		temp1.setAngleDeg(angle);
		temp1.setLength(power / 2.5);
		vec2d temp2;
		temp2.x = 0;
		temp2.y = -22;
		temp2 += body.get_translation();
		
		switch(arsenal[selected_wep]){
			case 0:
				new b_std(temp2, temp1);
				break;
			case 1:
				new b_sub_mine(temp2, temp1);
				break;
			case 2:
				new b_bounce(temp2, temp1);
				break;
			case 3:
				new b_nuke(temp2, temp1);
				break;
			case 4:
				{
					temp1.setAngleDeg(angle - 10);
					b_missile* m1_ptr = new b_missile(temp2, temp1);
					temp1.setAngleDeg(angle + 10);
					b_missile* m2_ptr = new b_missile(temp2, temp1);
					temp1.setAngleDeg(angle);
					new b_missile_marker(temp2, temp1, m1_ptr, m2_ptr);
					break;
				}
			case 5:
				for(int i = -5; i <= 5;i++){
					temp1.setAngleDeg(angle + i);
					new b_std(temp2, temp1,4);
				}
				break;
			default:
				printf("Schwerwiegender Fehler!");
		}
		
		input_controller.delete_event(SDLK_a);
		input_controller.delete_event(SDLK_d);
		input_controller.delete_event(SDLK_w);
		input_controller.delete_event(SDLK_s);
		input_controller.delete_event(SDLK_e);
		input_controller.delete_event(SDLK_q);
		input_controller.delete_event(SDLK_r);
		input_controller.delete_event(SDLK_f);
		input_controller.delete_event(SDLK_SPACE);
		printf("fired\n");
		arsenal[selected_wep] = 0;
		active = false;
	}
}

bool player::is_active(){
	return (active);
}

vec2d player::get_pos(){
	return body.get_translation();
}

bool player::alife(){
	return (life > 0)?(true):(false);
}

void player::damage(int dmg){
	life -= dmg;
}

void player::update_y(){
	vec2d temp;
	temp = body.get_translation();
	temp.y = SCREEN_HEIGHT - earth.get_high(temp.x);
	body.set_translation(temp);
	turret.set_translation(temp);
}

player players[2];
