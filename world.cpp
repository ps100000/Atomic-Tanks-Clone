#include "world.h"

world earth;

void world::generate(){
	srand(time(NULL));
	
	int n = rand() % 3 + 4;		// y=(x-b)^2/a+c
	int a[n];	//1---20
	int b[n];	//SCREEN_WIDTH*j/n---SCREEN_WIDTH*(j+1)/n
	int c[n];	//SCREEN_HEIGHT/3---SCREEN_HEIGHT*2/3
	
	for(int i = 0;i < n; i++){
		a[i] = (rand() % 100 + 25) * -1;
		b[i] = rand() % (SCREEN_WIDTH/n) + SCREEN_WIDTH*i/n;
		c[i] = rand() % (SCREEN_HEIGHT/3) + SCREEN_HEIGHT/3;
	}
	int y = 0;
	for(int i = 0;i < SCREEN_WIDTH; i++){
		highmap[i] = SCREEN_HEIGHT/n;
		for(int j = 0; j < n; j++){
			y = (i - b[j]) * (i - b[j]) / a[j] + c[j];
			if(y > highmap[i]){
				highmap[i] = y;
			}
		}
	}
}

int world::get_high(int pos){
	if(pos >= 0 && pos < SCREEN_WIDTH){
		return highmap[pos];
	}
	return (-999);
}

void world::set_high(int pos, int high){
	if(pos >= 0 && pos < SCREEN_WIDTH){
		if(high < SCREEN_HEIGHT / 6){
			high = SCREEN_HEIGHT / 6;
		}else if(high > SCREEN_HEIGHT * 5 / 6){
			high = SCREEN_HEIGHT * 5 / 6;
		}
		highmap[pos] = high;
	}
}
