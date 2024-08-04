#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

#include "define.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "draw.h"
#include "anim.h"
#include "StartGameButton.h"
#include "QuitGameButton.h"

#pragma comment(lib,"Winmm.lib")

void init_button(RECT& rect,int top) {
	rect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	rect.right = rect.left + BUTTON_WIDTH;
	rect.top = top;
	rect.bottom = rect.top + BUTTON_HEIGHT;
}

int main() {

	srand(time(0));

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	mciSendString(_T("open mus/bgm2.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/oldsite.mp3 alias menubgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);
	mciSendString(_T("open mus/weep.mp3 alias weep"), NULL, 0, NULL);

	mciSendString(_T("setaudio bgm volume to 800"), 0, 0, 0);
	mciSendString(_T("setaudio weep volume to 1000"), 0, 0, 0);

	RECT region_start_game_button, region_quit_game_button;

	init_button(region_start_game_button, 430);
	init_button(region_quit_game_button, 550);

	StartGameButton * start_game_button = new StartGameButton(region_start_game_button,
		_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));

	QuitGameButton* quit_game_button = new QuitGameButton(region_quit_game_button,
		_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

	
	ExMessage msg;
	IMAGE img_background;
	IMAGE img_menu;

	DWORD start_time = GetTickCount();
	int score = 0;
	int enemy_duration = 1000;
	int enemy_speed = 4;
	Anim* anim = new Anim();
	Player* player = new Player();

	std::vector <Enemy*> enemy_vector;
	std::vector <Bullet*> bullet_vector(3);

	for (int i = 0; i < bullet_vector.size(); i++) {
		bullet_vector[i] = new Bullet();
	}

	loadimage(&img_background, _T("img/background.png"));
	loadimage(&img_menu, _T("img/menu.png"));

	BeginBatchDraw();

	mciSendString(_T("play menubgm from 0"), NULL, 0, NULL);

	while (df::running) {
		DWORD frame_start_time = GetTickCount();
		if (df::is_game_start) {

			player->keyboard_process(msg);

			player->move();

			Bullet::upd_position(bullet_vector, *player);

			DWORD now_time = GetTickCount();
			if (now_time - start_time > enemy_duration) {
				Enemy* enemy = new Enemy(enemy_speed, anim);
				enemy_vector.push_back(enemy);
				start_time = now_time;
				enemy_duration -= 10;
				enemy_speed = 4 + (1000 - enemy_duration) / 100;
			}

			for (int i = 0; i < enemy_vector.size(); i++) {
				if (enemy_vector[i]->check_player_collision(*player)) {
					mciSendString(_T("play weep repeat from 0"), NULL, 0, NULL);
					MessageBox(GetHWnd(), _T("Äã±»Å¶°¡°¡ÚÀÚÀ°¡ÁË"), _T("ÓÎÏ·½áÊø"), MB_OK);
					df::running = false;
					break;
				}
				enemy_vector[i]->move_toward(*player);
				if (enemy_vector[i]->check_bullet_collision(bullet_vector)) {
					enemy_vector[i]->hurt();
					std::swap(enemy_vector[i], enemy_vector.back());
					delete enemy_vector.back();
					enemy_vector.pop_back();
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					score++;
				}
			}

			cleardevice();

			putimage(0, 0, &img_background);

			player->put_player_img();

			for (int i = 0; i < enemy_vector.size(); i++) {
				enemy_vector[i]->put_enemy_img();
			}

			for (int i = 0; i < bullet_vector.size(); i++) {
				bullet_vector[i]->draw_bullet();
			}

			dw::print_player_score(score);
		}
		else {
			putimage(0, 0, &img_menu);
			start_game_button->draw();
			quit_game_button->draw();
			while (peekmessage(&msg)) {
				start_game_button->process_event(msg);
				quit_game_button->process_event(msg);
			}
		}

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_time = frame_end_time - frame_start_time;
		if (frame_time < 1000 / 120) {
			Sleep(1000 / 60 - frame_time);
		}
	}

	EndBatchDraw();

	return 0;
}
