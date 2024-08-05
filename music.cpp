# include "music.h"
#include <graphics.h>

namespace mus {
	void init() {
		mciSendString(_T("open mus/bgm2.mp3 alias bgm"), NULL, 0, NULL);
		mciSendString(_T("open mus/oldsite.mp3 alias menubgm"), NULL, 0, NULL);
		mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);
		mciSendString(_T("open mus/weep.mp3 alias weep"), NULL, 0, NULL);
		mciSendString(_T("open mus/click.mp3 alias click"), NULL, 0, NULL);

		mciSendString(_T("setaudio bgm volume to 800"), 0, 0, 0);
		mciSendString(_T("setaudio weep volume to 1000"), 0, 0, 0);
	}

	void play_menu_music() {
		mciSendString(_T("play menubgm from 0"), NULL, 0, NULL);
	}

	void play_weep_music() {
		mciSendString(_T("play weep repeat from 0"), NULL, 0, NULL);
	}

	void play_hit_music() {
		mciSendString(_T("play hit from 0"), NULL, 0, NULL);
	}

	void play_click_music() {
		mciSendString(_T("play click from 0"), NULL, 0, NULL);
	}

	void pause_menu_music() {
		mciSendString(_T("pause menubgm"), NULL, 0, NULL);
	}

	void play_bgm_music() {
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
}