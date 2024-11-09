#include "entity.h"
#include "define.h"
#include <string>
#include <cmath>

Entity::Entity() {
    idx_cur_anim = 0;
    x = WINDOW_WIDTH / 2;
    y = WINDOW_HEIGHT / 2;
    speed = 10;
    face = 0;
    is_move_up = false;
    is_move_down = false;
    is_move_left = false;
    is_move_right = false;
    start_time = GetTickCount();
    LoadAnimation();
}

inline void Entity::LoadAnimation() {
    for (int i = 0; i < ANIM_NUM; i++) {
        std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
        loadimage(&img_left[i], path.c_str());
    }
    for (int i = 0; i < ANIM_NUM; i++) {
        std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
        loadimage(&img_right[i], path.c_str());
    }
    loadimage(&img_shadow, L"img/shadow_player.png");
}

#pragma comment(lib,"MSIMG32.LIB")

void Entity::put_img(IMAGE* img, int x, int y) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h,
        { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Entity::put_player_img() {
    put_shadow_img();

    if (face) put_right_img();
    else put_left_img();

    DWORD end_time = GetTickCount();
    if (end_time - start_time > 100) {
        idx_increase();
        start_time = end_time;
    }
}

void Entity::put_shadow_img() {
    int shadow_x = x + WIDTH / 2 - WIDTH / 2;
    int shadow_y = y + HEIGHT - 8;
    put_img(&img_shadow, shadow_x, shadow_y);
}

void Entity::put_left_img() {
    put_img(&img_left[idx_cur_anim], x, y);
}

void Entity::put_right_img() {
    put_img(&img_right[idx_cur_anim], x, y);
}

void Entity::idx_increase() {
    idx_cur_anim = (idx_cur_anim + 1) % ANIM_NUM;
}