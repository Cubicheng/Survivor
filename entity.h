#pragma once

# include <graphics.h>

class Entity {
public:
    Entity();
    void LoadAnimation();
    void put_img(IMAGE* img, int x, int y);
    void put_player_img();
    void put_left_img();
    void put_right_img();
    void put_shadow_img();
    void idx_increase();

    int is_move_up;
    int is_move_down;
    int is_move_left;
    int is_move_right;
    int face;
    int x, y;
    int WIDTH;
    int HEIGHT;

private:
    int ANIM_NUM;
    int SHADOW_WIDTH;
    int idx_cur_anim;
    int speed;
    DWORD start_time;
    IMAGE img_left[6];
    IMAGE img_right[6];
    IMAGE img_shadow;
};