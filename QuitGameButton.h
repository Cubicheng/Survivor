#pragma once

# include "button.h"
# include "define.h"
# include "music.h"

class QuitGameButton : public Button {
public:
	QuitGameButton(int top,LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) :
		Button(top,path_img_idle, path_img_hovered, path_img_pushed) {};
	~QuitGameButton() = default;
protected:
	void on_click() {
		mus::play_click_music();
		df::running = false;
	}
};