#include "draw.h"
#include <graphics.h>

void dw::print_player_score(int score){
	static TCHAR text[64];
	_stprintf_s(text, _T("��ǰ��ҵ÷֣�%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}
