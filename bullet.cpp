#include "bullet.h"
#include <graphics.h>
#include <cmath>

void Bullet::draw_bullet() const{
	setlinecolor(RGB(255, 155, 50));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(x, y, RADIUS);
}

int Bullet::get_x(){
	return x;
}

int Bullet::get_y(){
	return y;
}
