#include "button.h"
#include "define.h"

Button::Button(int top,LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed){
	init_region(top);
	loadimage(&img_idle, path_img_idle);
	loadimage(&img_hovered, path_img_hovered);
	loadimage(&img_pushed, path_img_pushed);
}

void Button::draw(){
	switch (status) {
	case Status::IDEL:
		putimage(region.left, region.top, &img_idle);
		break;
	case Status::HOVERED:
		putimage(region.left, region.top, &img_hovered);
		break;
	case Status::PUSHED:
		putimage(region.left, region.top, &img_pushed);
		break;
	}
}

void Button::process_event(const ExMessage& msg){
	switch (msg.message) {
	case WM_MOUSEMOVE:
		if (status == Status::IDEL && check_mouse_position(msg.x, msg.y))
			status = Status::HOVERED;
		else if (status == Status::HOVERED && !check_mouse_position(msg.x, msg.y))
			status = Status::IDEL;
		break;
	case WM_LBUTTONDOWN:
		if (check_mouse_position(msg.x, msg.y))
			status = Status::PUSHED;
		break;
	case WM_LBUTTONUP:
		if (status == Status::PUSHED && check_mouse_position(msg.x, msg.y))
			on_click();
		else status = Status::IDEL;
	}
}

void Button::init_region(int top){
	region.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region.right = region.left + BUTTON_WIDTH;
	region.top = top;
	region.bottom = region.top + BUTTON_HEIGHT;
}


bool Button::check_mouse_position(int x, int y){
	return region.left <= x && x <= region.right && region.top <= y && y <= region.bottom;
}
