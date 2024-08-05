#pragma once

# include "button.h"
# include "define.h"
# include "music.h"

class StartGameButton : public Button {
public:
	StartGameButton(int top, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) :
		Button(top, path_img_idle, path_img_hovered, path_img_pushed) {};
	~StartGameButton() = default;
protected:
	void on_click() {
		df::is_game_start = true;
		mus::play_click_music();
		mus::pause_menu_music();
		mus::play_bgm_music();
	}
};