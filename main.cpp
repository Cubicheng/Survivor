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
#include "music.h"
#include "timer.h"
#include "game.h"

#pragma comment(lib,"Winmm.lib")

void init() {
	srand(time(0));

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	mus::init();

	gm::init();

	BeginBatchDraw();

	mus::play_menu_music();
}

void loop() {
	while (df::running) {

		timer::frame_start_time = GetTickCount();

		if (df::is_game_start) {

			gm::upd_player();

			gm::add_enemy();

			gm::check_enemy_collision();

			gm::print();
		}
		else
			gm::menu_progress();

		FlushBatchDraw();

		timer::frame_sleep();
	}
}

void exit() {
	EndBatchDraw();
}

int main() {

	init();

	loop();

	exit();

	return 0;
}
