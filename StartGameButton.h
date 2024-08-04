#pragma once

# include "button.h"
# include "define.h"

class StartGameButton : public Button {
public:
	StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) :
		Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {};
	~StartGameButton() = default;
protected:
	void on_click() {
		df::is_game_start = true;
		mciSendString(_T("pause menubgm"), NULL, 0, NULL);
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
};