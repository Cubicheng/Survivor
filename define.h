#pragma once

# define UP_EDGE 0
# define DOWN_EDGE 1
# define LEFT_EDGE 2
# define RIGHT_EDGE 3

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define BUTTON_WIDTH 192
# define BUTTON_HEIGHT 75

namespace df {
	extern bool running;
	extern bool is_game_start;
	extern int score;
	extern int enemy_duration;
	extern int enemy_speed;
}