#pragma once
#include "player.h"
#include <vector>

class Bullet {

public:
	Bullet() = default;
	~Bullet() = default;
	void draw_bullet() const;
	int get_x();
	int get_y();



	static void upd_position(std::vector<Bullet*>& bullet_vector, const Player& player) {
		const double RADIAL_SPEED = 0.0045;
		const double TANGENT_SPEED = 0.0055;
		double radian_interval = 2 * 3.14159 / bullet_vector.size();
		double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
		for (int i = 0; i < bullet_vector.size(); i++) {
			double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
			bullet_vector[i]->x = player.x + player.PLAYER_WIDTH / 2 + (int)(radius * sin(radian));
			bullet_vector[i]->y = player.y + player.PLAYER_HEIGHT / 2 + (int)(radius * cos(radian));
		}
	}
	
private:
	const int RADIUS = 10;
	int x, y;
};

