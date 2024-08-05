#pragma once

# include "StartGameButton.h"
# include "QuitGameButton.h" 
# include "anim.h"
# include "player.h"
# include "enemy.h"

namespace gm {
	extern StartGameButton* start_game_button;
	extern QuitGameButton* quit_game_button;
	extern ExMessage msg;
	extern IMAGE img_background;
	extern IMAGE img_menu;
	extern Anim* anim;
	extern Player* player;
	extern DWORD start_time;
	extern DWORD now_time;

	extern std::vector <Enemy*> enemy_vector;
	extern std::vector <Bullet*> bullet_vector;

	

	void init();

	void menu_progress();

	void print();

	void add_enemy();

	void upd_player();

	void check_enemy_collision();

	void check_enemy_player_collision(int i);

	void check_enemy_bullet_collision(int i);
}