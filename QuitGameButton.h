#pragma once

# include "button.h"
# include "define.h"

class QuitGameButton : public Button {
public:
	QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) :
		Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {};
	~QuitGameButton() = default;
protected:
	void on_click() {
		df::running = false;
	}
};