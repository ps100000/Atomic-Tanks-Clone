#include "pic.h"

unsigned long pic::id_counter = 1;

pic::pic(){
	main_renderer.add_pic(this);
}

pic::~pic(){
	main_renderer.delete_pic(this);
	SDL_DestroyTexture(texture);
}

void pic::load_pic(std::string file)
{
	if(texture != NULL){
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());
	if (loadedSurface == NULL)
		printf("Unable to load the image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	else
	{
		SDL_Texture* temp = SDL_CreateTextureFromSurface(main_renderer.renderer, loadedSurface);
		
		if (temp == NULL)
			printf("Unable to create the texture from %s! SDL Error: %s\n", file.c_str(), SDL_GetError());

		SDL_FreeSurface(loadedSurface);
		
		int w;
		int h;
		SDL_QueryTexture(temp, NULL, NULL, &w, &h);
		
		texture = SDL_CreateTexture(main_renderer.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		if (texture == NULL)
		{
			printf("texture could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}
		
		SDL_SetRenderTarget(main_renderer.renderer,texture);
		SDL_RenderClear(main_renderer.renderer);
		SDL_RenderCopy(main_renderer.renderer, temp,NULL,NULL);
		
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		
		translation_point.x = 0;
		translation_point.y = 0;
		rotation_point.x = w / 2;
		rotation_point.y = h / 2;
		
		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;
		
		dest.x = 0;
		dest.y = 0;
		dest.w = w;
		dest.h = h;
		
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(main_renderer.renderer,0,0,0,0);
		
		SDL_DestroyTexture(temp);
		
		printf("w%d  h%d \n",w,h);
	}
}

int pic::get_layer(){
	return layer;
}

void pic::set_layer(int l){
	if(l > 4){
		l = 4;
	}
	if(l < 0){
		l = 0;
	}
	layer = l;
}

 bool pic::is_visible(){
	return visible;
}


void pic::set_visible(bool v){
	visible = v;
	return;
}

 void pic::set_translation(vec2d t){
	t -= translation_point;
	dest.x = t.x;
	dest.y = t.y;
}

 vec2d pic::get_translation(){
	vec2d temp(dest.x, dest.y);
	temp += translation_point;
	return temp;
}

 void pic::set_translation_point(vec2d point){
	translation_point = point;
}

 vec2d pic::get_translation_point(){
	return translation_point;
}


 void pic::set_rotation(float r){
	while(r > 360){
		r -= 360;
	}
	while(r < 0){
		r += 360;
	}
	rotation = r;
}

 float pic::get_rotation(){
	return rotation;
}

 void pic::set_rotation_point(vec2d point){
	rotation_point.x = point.x;
	rotation_point.y = point.y;
}

 vec2d pic::get_rotation_point(){
	vec2d rp;
	rp.x = rotation_point.x;
	rp.y = rotation_point.y;
	return rp;
}

	
 void pic::set_scale_x(float scale){
	dest.w = src.w * scale;
}

 void pic::set_scale_y(float scale){
	dest.h = src.h * scale;
}

 float pic::get_scale_x(){
	return (1.0 * dest.w / src.w);
}

 float pic::get_scale_y(){
	return (1.0 * dest.h / src.h);
}

	
void pic::set_sector(vec2d corner, int width, int high){
	float sx = get_scale_x();
	float sy = get_scale_y();
	
	src.x = corner.x;
	src.y = corner.y;
	src.w = width;
	src.h = high;
	
	set_scale_x(sx);
	set_scale_y(sy);
}

void pic::set_pixel(vec2d pos, int r,int g, int b, int a){
	SDL_SetRenderTarget(main_renderer.renderer,texture);
	SDL_SetRenderDrawColor(main_renderer.renderer,r,g,b,a);
	SDL_RenderDrawPoint(main_renderer.renderer,pos.x,pos.y);
	SDL_SetRenderDrawColor(main_renderer.renderer,0,0,0,0);
}

void pic::draw_line(vec2d begin, vec2d end,int r,int g, int b, int a){
	SDL_SetRenderTarget(main_renderer.renderer,texture);
	SDL_SetRenderDrawColor(main_renderer.renderer,r,g,b,a);
	SDL_RenderDrawLine(main_renderer.renderer,begin.x,begin.y,end.x,end.y);
	SDL_SetRenderDrawColor(main_renderer.renderer,0,0,0,0);
}

void pic::draw_rect(vec2d corner, int width, int high, int r,int g, int b, int a, bool filled){
	SDL_SetRenderTarget(main_renderer.renderer,texture);
	SDL_SetRenderDrawColor(main_renderer.renderer,r,g,b,a);
	SDL_Rect temp;
	temp.x = corner.x;
	temp.y = corner.y;
	temp.w = width;
	temp.h = high;
	if(filled){
		SDL_RenderFillRect(main_renderer.renderer,&temp);
	}else{
		SDL_RenderDrawRect(main_renderer.renderer,&temp);
	}
	SDL_SetRenderDrawColor(main_renderer.renderer,0,0,0,0);
}

void pic::draw_bx_circle(vec2d center, int rad, int r,int g, int b, int a){
	SDL_SetRenderTarget(main_renderer.renderer,texture);
	SDL_SetRenderDrawColor(main_renderer.renderer,r,g,b,a);
    int x=0;
    int y=rad;
    int p=3 - 2 * rad;
 
    while(x <= y)
    {
        SDL_RenderDrawPoint(main_renderer.renderer,center.x+x,center.y+y);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x-x,center.y+y);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x+x,center.y-y);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x-x,center.y-y);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x+y,center.y+x);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x-y,center.y+x);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x+y,center.y-x);
        SDL_RenderDrawPoint(main_renderer.renderer,center.x-y,center.y-x);
 
        if(p < 0)
            p += 4 * x++ + 6;
        else
            p += 4 * (x++ - y--) + 10;
    }
	SDL_SetRenderDrawColor(main_renderer.renderer,0,0,0,0);
}

void pic::copy_pic(pic* src, vec2d corner_src, int w_src, int h_src,vec2d corner_dest, int w_dest, int h_dest){
	SDL_SetRenderTarget(main_renderer.renderer,texture);
	SDL_Rect rect_src;
	rect_src.x = corner_src.x;
	rect_src.y = corner_src.y;
	rect_src.w = h_src;
	rect_src.h = w_src;
	SDL_Rect rect_dest;
	rect_dest.x = corner_dest.x;
	rect_dest.y = corner_dest.y;
	rect_dest.w = h_dest;
	rect_dest.h = w_dest;
	SDL_RenderCopy(main_renderer.renderer, src->texture, &rect_src, &rect_dest);
}