#include "animation.h"

unsigned long animation::id_counter = 1;

animation::animation(){
	texture = new pic;
	main_renderer.add_animation(this);
}

animation::animation(std::string filename){
	texture = new pic;
	main_renderer.add_animation(this);
	load(filename);
	
}

animation::~animation(){
	main_renderer.delete_animation(this);
	delete texture;
}

void animation::update(){
	if(playing && frames.size() > 0){
		if(!delay--){
			playing = set_frame(active_frame + 1);
			if(playing){
				playing = !frames[active_frame].stop;
			}
			if((active_frame == frames.size() - 1) && selfdestruct){
				delete this;
			}
		}
	}
}

void animation::load(std::string filename){
	std::ifstream file;
	file.open(filename.c_str(), std::ios_base::in);
	if(!file.is_open()){
		printf("could not open %s",filename.c_str());
		return;
	}
	std::string pic_name;
	getline(file,pic_name);
	texture->load_pic(pic_name);
	file >> frame_width;
	file >> frame_height;
	
	int in;
	file >> in;
	selfdestruct = (in > 0)?(true):(false);
	
	int i;
	file >> i;
	for(i--; i >= 0; i--){
		frame temp;
		file >> in;
		temp.delay = in & 0xff;
		file >> in;
		temp.stop = (in > 0)?(true):(false);
		frames.push_back(temp);
	}
	set_frame(0);
}

void animation::play(bool p){
	playing = p;
}

unsigned int animation::get_frame(){
	return active_frame;
}

bool animation::set_frame(unsigned int new_frame){
	if(frames.size() > new_frame){
		active_frame = new_frame;
		vec2d temp;
		temp.x = active_frame * frame_width;
		temp.y = 0;
		texture->set_sector(temp,frame_width,frame_height);
		delay = frames[active_frame].delay;
		return true;
	}
	return false;
}

int animation::get_layer(){
	return texture->get_layer();
}

void animation::set_layer(int l){
	texture->set_layer(l);
}

bool animation::is_visible(){
	return texture->is_visible();
}

void animation::set_visible(bool v){
	texture->set_visible(v);
}

void animation::set_translation(vec2d t){
	texture->set_translation(t);
}

vec2d animation::get_translation(){
	return texture->get_translation();
}

void animation::set_translation_point(vec2d point){
	texture->set_translation_point(point);
}

vec2d animation::get_translation_point(){
	return texture->get_translation_point();
}

void animation::set_rotation(float r){
	texture->set_rotation(r);
}

float animation::get_rotation(){
	texture->get_rotation();
}

void animation::set_rotation_point(vec2d point){
	texture->set_rotation_point(point);
}

vec2d animation::get_rotation_point(){
	return texture->get_rotation_point();
}

void animation::set_scale_x(float scale){
	texture->set_scale_x(scale);
}

void animation::set_scale_y(float scale){
	texture->set_scale_y(scale);
}

float animation::get_scale_x(){
	return texture->get_scale_x();
}

float animation::get_scale_y(){
	return texture->get_scale_y();
}
