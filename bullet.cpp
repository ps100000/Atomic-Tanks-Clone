#include "bullet.h"

std::vector<bullet*> bullets;

bullet::~bullet(){
	
}

bool bullet::next_phase(){
	return phase;
}

b_std::b_std(){
	
}

b_std::b_std(vec2d pos,vec2d velocity){
	bullets.push_back(this);
	mov.init(pos,velocity);
	texture.load_pic("./texturepack/std_bullet.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_std::b_std(vec2d pos,vec2d velocity, int radius):b_std(pos,velocity){
	exp.set_radius(radius);
}


b_std::~b_std(){
	
}

bool b_std::update(){
	if(!init){
		init = true;
	}
	
	mov.update();
	vec2d pos = mov.get_pos();
	
	if(pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y >= SCREEN_HEIGHT){
		return false;
	}
	
	if(det.check(pos)){
		texture.set_visible(false);
		exp.activate(pos);
		return false;
	}
	
	texture.set_translation(mov.get_pos());
	return true;
}

b_sub_mine::b_sub_mine(){
	
}

b_sub_mine::b_sub_mine(vec2d pos,vec2d velocity){
	bullets.push_back(this);
	mov.init(pos,velocity);
	texture.load_pic("./texturepack/sub_mine.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_sub_mine::~b_sub_mine(){
	
}

bool b_sub_mine::update(){
	if(!init){
		init = true;
	}
	if(state < 2){
		mov.update();
	}
	
	vec2d pos = mov.get_pos();
	if(det.check(pos)){
		texture.set_visible(false);
		exp.activate(pos);
		return false;
	}
	
	if(pos.x < 0 || pos.x >= SCREEN_WIDTH || (pos.y >= SCREEN_HEIGHT && state == 0) || (pos.y < 0 && state == 1)){
		return false;
	}
	
	if(flip.check(pos)){
		state++;
		if(state == 1){
			mov.invert(true);
			flip.invert(true);
		}else if(state == 2){
			phase = true;
		}
	}
	
	texture.set_translation(mov.get_pos());
	return true;
}

b_bounce::b_bounce(){
	
}

b_bounce::b_bounce(vec2d pos,vec2d velocity):exp(12){
	bullets.push_back(this);
	exp.set_damage(8);
	mov.init(pos,velocity);
	texture.load_pic("./texturepack/bounce.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_bounce::~b_bounce(){
}

bool b_bounce::update(){
	if(!init){
		init = true;
	}
	mov.update();
	vec2d temp = mov.get_pos();

	if(temp.x < 0 || temp.x >= SCREEN_WIDTH || temp.y >= SCREEN_HEIGHT){
		return false;
	}	
	if(det.check(temp)){
		state++;
		texture.set_visible(false);
		exp.activate(temp);
		if(state == 5){
			return false;
		}
		
		texture.set_visible(true);
		vec2d temp2;
		temp2.x = 0;
		temp2.y = -15;
		mov.init(temp, temp2);
		
	}
	texture.set_translation(temp);
	return true;
}

b_nuke::b_nuke(){
	
}

b_nuke::b_nuke(vec2d pos,vec2d velocity){
	bullets.push_back(this);
	mov.init(pos,velocity);
	texture.load_pic("./texturepack/marker.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_nuke::~b_nuke(){
}

bool b_nuke::update(){
	if(!init){
		init = true;
	}
	mov.update();
	vec2d temp = mov.get_pos();

	if(temp.x < 0 || temp.x >= SCREEN_WIDTH || temp.y >= SCREEN_HEIGHT){
		return false;
	}	
	if(det.check(temp)){
		if(state){	
			texture.set_visible(false);
			exp.activate(temp);
			return false;
		} else{
			SDL_Delay(500);
			state = true;
			vec2d temp2;
			temp2.x = 0;
			temp2.y = 0;
			temp.y -= SCREEN_HEIGHT;
			mov.init(temp, temp2);
			texture.load_pic("./texturepack/nuke_bullet.png");
			
		}
	
	}
	texture.set_translation(mov.get_pos());
	return true;
}


b_missile_marker::b_missile_marker(){
	
}

b_missile_marker::b_missile_marker(vec2d pos,vec2d velocity, b_missile* m1_ptr, b_missile* m2_ptr){
	m1 = m1_ptr;
	m2 = m2_ptr;
	bullets.push_back(this);
	mov.init(pos,velocity);
	texture.load_pic("./texturepack/marker.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_missile_marker::~b_missile_marker(){
}

bool b_missile_marker::update(){
	if(!init){
		init = true;
	}
	mov.update();
	vec2d temp = mov.get_pos();

	if(temp.x < 0 || temp.x >= SCREEN_WIDTH || temp.y >= SCREEN_HEIGHT){
		m1->target = temp;
		m2->target = temp;
		m1->state = 2;
		m2->state = 2;
		return false;
	}	
	if(det.check(temp)){
		texture.set_visible(false);
		m1->target = temp;
		m2->target = temp;
		m1->state = 2;
		m2->state = 2;
		return false;
	}
	texture.set_translation(mov.get_pos());
	return true;
}

b_missile::b_missile(){
	
}

b_missile::b_missile(vec2d pos,vec2d velocity){
	bullets.push_back(this);
	mov1.init(pos,velocity);
	texture.load_pic("./texturepack/missile.png");
	vec2d temp;
	temp.x = 4;
	temp.y = 4;
	texture.set_translation_point(temp);
	texture.set_layer(2);
	texture.set_visible(true);
}

b_missile::~b_missile(){
}

bool b_missile::update(){
	if(state == 0){
		mov1.update();
		vec2d temp = mov1.get_pos();

		if(temp.x < 0 || temp.x >= SCREEN_WIDTH || temp.y >= SCREEN_HEIGHT){
			return false;
		}	
		if(det.check(temp)){
			state = 1;
		}
		texture.set_translation(mov1.get_pos());
		return true;
	}else if(state == 2){
		if(!init){
			init = true;
			vec2d temp;
			temp.x = 0;
			temp.y = -10;
			vec2d temp2 = mov1.get_pos();
			temp2.y -= 15;
			mov2.init(temp2, temp);
			mov2.set_target(target);
		}
		mov2.update();
		vec2d temp = mov2.get_pos();

		if(temp.x < 0 || temp.x >= SCREEN_WIDTH || temp.y >= SCREEN_HEIGHT){
			return false;
		}	
		if(det.check(temp)){
			texture.set_visible(false);
			exp.activate(temp);
		return false;
		}
		texture.set_translation(mov2.get_pos());
		return true;
	}

}