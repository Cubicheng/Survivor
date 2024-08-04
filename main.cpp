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

#pragma comment(lib,"Winmm.lib")

int main() {

	srand(time(0));

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	mciSendString(_T("open mus/bgm2.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);
	mciSendString(_T("open mus/weep.mp3 alias weep"), NULL, 0, NULL);

	mciSendString(_T("setaudio bgm volume to 800"), 0, 0, 0);
	mciSendString(_T("setaudio weep volume to 1000"), 0, 0, 0);

	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	
	ExMessage msg;
	IMAGE img_background;
	bool running = true;
	DWORD start_time = GetTickCount();
	int score = 0;
	int enemy_duration = 1000;
	int enemy_speed = 4;

	Player* player = new Player();
	std::vector <Enemy*> enemy_vector;
	std::vector <Bullet*> bullet_vector(3);

	for (int i = 0; i < bullet_vector.size(); i++) {
		bullet_vector[i] = new Bullet();
	}

	loadimage(&img_background, _T("img/background.png"));

	BeginBatchDraw();

	while (running) {

		DWORD frame_start_time = GetTickCount();

		player->keyboard_process(msg);

		player->move();

		Bullet::upd_position(bullet_vector, *player);

		DWORD now_time = GetTickCount();
		if (now_time - start_time > enemy_duration) {
			Enemy* enemy = new Enemy(enemy_speed);
			enemy_vector.push_back(enemy);
			start_time = now_time;
			enemy_duration -= 10;
			enemy_speed = 4 + (1000 - enemy_duration) / 100;
		}

		for (int i = 0; i < enemy_vector.size(); i++) {
			if (enemy_vector[i]->check_player_collision(*player)) {
				mciSendString(_T("play weep repeat from 0"), NULL, 0, NULL);
				MessageBox(GetHWnd(), _T("Äã±»Å¶°¡°¡ÚÀÚÀ°¡ÁË"), _T("ÓÎÏ·½áÊø"), MB_OK);
				running = false;
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
