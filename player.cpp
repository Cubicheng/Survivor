#include "player.h"
#include "define.h"
#include <string>
#include <cmath>

Player::Player() {
    idx_cur_anim = 0;
    x = WINDOW_WIDTH/2;
    y = WINDOW_HEIGHT/2;
    speed = 10;
    face = 0;
    is_move_up = false;
    is_move_down = false;
    is_move_left = false;
    is_move_right = false;
    start_time = GetTickCount();
    LoadAnimation();
}

inline void Player::LoadAnimation() {
    for (int i = 0; i < PLAYER_ANIM_NUM; i++) {
        std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
        loadimage(&img_player_left[i], path.c_str());
    }
    for (int i = 0; i < PLAYER_ANIM_NUM; i++) {
        std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
        loadimage(&img_player_right[i], path.c_str());
    }
    loadimage(&img_player_shadow, L"img/shadow_player.png");
}

#pragma comment(lib,"MSIMG32.LIB")

void Player::put_img(IMAGE* img, int x, int y) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h,
        { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Player::put_player_img() {
    put_shadow_img();

    if (face) put_right_img();
    else put_left_img();

    DWORD end_time = GetTickCount();
    if (end_time - start_time > 100) {
        idx_increase();
        start_time = end_time;
    }
}

void Player::put_shadow_img() {
    int shadow_x = x + PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2;
    int shadow_y = y + PLAYER_HEIGHT - 8;
    put_img(&img_player_shadow,shadow_x,shadow_y);
}

void Player::put_left_img() {
    put_img(&img_player_left[idx_cur_anim], x, y);
}

void Player::put_right_img() {
    put_img(&img_player_right[idx_cur_anim], x, y);
}

void Player::idx_increase() {
    idx_cur_anim = (idx_cur_anim + 1) % PLAYER_ANIM_NUM;
}

void Player::move() {
    int dir_x = is_move_right - is_move_left;
    int dir_y = is_move_down - is_move_up;
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (len_dir) {
        int xx = x + (int)(dir_x / len_dir * speed);
        int yy = y + (int)(dir_y / len_dir * speed);
        if (0 < xx && xx + PLAYER_WIDTH < WINDOW_WIDTH && 0 < yy && yy + PLAYER_HEIGHT < WINDOW_HEIGHT) {
            x = xx;
            y = yy;
        }
    }
}

void Player::keyboard_process(ExMessage& msg) {
    while (peekmessage(&msg)) {
        if (msg.message == WM_KEYDOWN) {
            switch (msg.vkcode) {
            case VK_UP:
                is_move_up = true;
                break;
            case VK_DOWN:
                is_move_down = true;
                break;
            case VK_LEFT:
                is_move_left = true;
                face = 0;
                break;
            case VK_RIGHT:
                is_move_right = true;
                face = 1;
                break;
            }
        }
        else if (msg.message == WM_KEYUP) {
            switch (msg.vkcode) {
            case VK_UP:
                is_move_up = false;
                break;
            case VK_DOWN:
                is_move_down = false;
                break;
            case VK_LEFT:
                is_move_left = false;
                break;
            case VK_RIGHT:
                is_move_right = false;
                break;
            }
        }
    }
}