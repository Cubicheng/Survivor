#pragma once
#include <graphics.h>
#include <conio.h>

class Player {
public:
    Player();
    void LoadAnimation();
    void put_img(IMAGE* img, int x, int y);
    void put_player_img();
    void put_left_img();
    void put_right_img();
    void put_shadow_img();
    void idx_increase();
    void move();
    void keyboard_process(ExMessage &msg);

    int is_move_up;
    int is_move_down;
    int is_move_left;
    int is_move_right;
    int face;
    int x, y;
    const int PLAYER_WIDTH = 80;
    const int PLAYER_HEIGHT = 80;

private:
    const int PLAYER_ANIM_NUM = 6;
    const int SHADOW_WIDTH = 32;
    int idx_cur_anim;
    int speed;
    DWORD start_time;
    IMAGE img_player_left[6];
    IMAGE img_player_right[6];
    IMAGE img_player_shadow;
};