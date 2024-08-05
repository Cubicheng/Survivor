#include "game.h"
#include "draw.h"

namespace gm {
	StartGameButton* start_game_button;
	QuitGameButton* quit_game_button;
	ExMessage msg;
	IMAGE img_background;
	IMAGE img_menu;
	Anim* anim;
	Player* player;
	std::vector <Enemy*> enemy_vector;
	std::vector <Bullet*> bullet_vector(3);
	DWORD start_time;
	DWORD now_time;
	bool running;
	bool is_game_start;
	int score;
	int enemy_duration;
	int enemy_speed;

	
	void gm::init() {

		start_time = GetTickCount();

		start_game_button = new StartGameButton(430,
			_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));

		quit_game_button = new QuitGameButton(550,
			_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));
	
		anim = new Anim();
		player = new Player();

		for (int i = 0; i < bullet_vector.size(); i++) {
			bullet_vector[i] = new Bullet();
		}

		loadimage(&img_background, _T("img/background.png"));
		loadimage(&img_menu, _T("img/menu.png"));
	}

	void menu_progress(){
		putimage(0, 0, &img_menu);
		start_game_button->draw();
		quit_game_button->draw();
		while (peekmessage(&msg)) {
			start_game_button->process_event(msg);
			quit_game_button->process_event(msg);
		}
	}

	void print(){
		cleardevice();

		putimage(0, 0, &img_background);

		player->put_player_img();

		for (int i = 0; i < enemy_vector.size(); i++) {
			enemy_vector[i]->put_enemy_img();
		}

		for (int i = 0; i < bullet_vector.size(); i++) {
			bullet_vector[i]->draw_bullet();
		}

		dw::print_player_score(df::score);
	}

	void add_enemy(){
		now_time = GetTickCount();
		if (now_time - start_time > df::enemy_duration) {
			Enemy* enemy = new Enemy(df::enemy_speed, anim);
			enemy_vector.push_back(enemy);
			start_time = now_time;
			df::enemy_duration -= 10;
			df::enemy_speed = 4 + (1000 - df::enemy_duration) / 100;
		}
	}

	void upd_player(){
		player->keyboard_process(msg);
		player->move();
		Bullet::upd_position(bullet_vector, *player);
	}

	void check_enemy_collision(){
		for (int i = 0; i < enemy_vector.size(); i++) {

			check_enemy_player_collision(i);
			if (!df::running) break;

			enemy_vector[i]->move_toward(*player);

			check_enemy_bullet_collision(i);
		}
	}

	void check_enemy_player_collision(int i){
		if (enemy_vector[i]->check_player_collision(*player)) {
			mus::play_weep_music();
			MessageBox(GetHWnd(), _T("Äã±»Å¶°¡°¡ÚÀÚÀ°¡ÁË"), _T("ÓÎÏ·½áÊø"), MB_OK);
			df::running = false;
		}
	}

	void check_enemy_bullet_collision(int i){
		if (enemy_vector[i]->check_bullet_collision(bullet_vector)) {
			enemy_vector[i]->hurt();
			std::swap(enemy_vector[i], enemy_vector.back());
			delete enemy_vector.back();
			enemy_vector.pop_back();
			mus::play_hit_music();
			df::score++;
		}
	}
}
