#include "render.h"

render main_renderer;

void render::add_pic(pic* p){
	pictures.push_back(p);
}


void render::delete_pic(pic* p){
	if(!pictures.empty()){
		for(int i = 0; i < pictures.size() ; i++){
			if(pictures[i]->id == p->id){
				pictures.erase(pictures.begin() + i);
			}
		}
	}
}

render::render(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED| SDL_TEXTUREACCESS_TARGET);
	if (renderer == NULL)
	{
		printf("We were not able to create the renderer! SDL Error: %s\n", SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
		return;
	}
	
	buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (buffer == NULL)
	{
		printf("Buffer could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	background = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (buffer == NULL)
	{
		printf("Background could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	world = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (buffer == NULL)
	{
		printf("World could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	layers = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (buffer == NULL)
	{
		printf("Layers could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(buffer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(world, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(layers, SDL_BLENDMODE_BLEND);
	
	//set background blue
	{
		SDL_SetRenderTarget(renderer,background);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,191,191,255,255);
		SDL_Rect r;
		r.x = 0;
		r.y = 0;
		r.w = SCREEN_WIDTH;
		r.h = SCREEN_HEIGHT;
		SDL_RenderFillRect(renderer, &r);
	}
	
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	
	return;
}

render::~render(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(buffer);
	SDL_DestroyTexture(world);
	SDL_DestroyTexture(layers);
	for(int i = 0; i < pictures.size(); i++){
		delete pictures[i];
		pictures.clear();
	}
}

void render::update_world(){
	SDL_SetRenderTarget(renderer,world);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	for(int i = 0; i < SCREEN_WIDTH; i++){
		SDL_RenderDrawLine(renderer,i,SCREEN_HEIGHT - earth.get_high(i),i,SCREEN_HEIGHT);
	}
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
}

void render::show(){
	//printf("pictures.size() %d\n",pictures.size());
	SDL_SetRenderTarget(renderer,background);
	
	for(int i = 0; i < pictures.size(); i++){
		if((pictures[i]->layer == 0) && (pictures[i]->visible)){
			SDL_RenderCopyEx(renderer,
				pictures[i]->texture,
				&pictures[i]->src,
				&pictures[i]->dest,
				pictures[i]->rotation,
				&pictures[i]->rotation_point,
				SDL_FLIP_NONE
				);
		}
	}
	
	SDL_SetRenderTarget(renderer,layers);
	SDL_RenderClear(renderer);
	for(int i = 1; i <= 4; i++){
		for(int j = 0; j < pictures.size(); j++){
			if((pictures[j]->layer == i) && (pictures[j]->visible)){
				SDL_RenderCopyEx(renderer,
					pictures[j]->texture,
					&pictures[j]->src,
					&pictures[j]->dest,
					pictures[j]->rotation,
					&pictures[j]->rotation_point,
					SDL_FLIP_NONE
					);
			}
		}
	}
	
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	
	SDL_SetRenderTarget(renderer,buffer);
	SDL_RenderCopy(renderer, background,NULL,NULL);
	SDL_RenderCopy(renderer, world,NULL,NULL);
	SDL_RenderCopy(renderer, layers,NULL,NULL);
	
	SDL_SetRenderTarget(renderer,NULL);
	SDL_RenderCopy(renderer, buffer,NULL,NULL);
	
	SDL_RenderPresent(renderer);
}
