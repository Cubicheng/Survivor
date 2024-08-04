#pragma once

# include <graphics.h>

class Button {
protected:
	virtual void on_click() = 0;
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed );
	~Button() = default;
	void draw();
	void process_event(const ExMessage& msg);
private:

	bool check_mouse_position(int x, int y);
	
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;

	enum class Status {
		IDEL = 0,
		HOVERED,
		PUSHED
	};

	Status status;
};