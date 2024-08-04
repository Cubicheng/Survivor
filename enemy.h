#pragma once
#include <graphics.h>
#include <conio.h>
#include "player.h"
#include "bullet.h"
#include <vector>


class Enemy {
public:
    Enemy(int &enemy_speed);
    void LoadAnimation();
    void put_img(IMAGE* img, int x, int y);
    void put_enemy_img();
    void put_left_img();
    void put_right_img();
    void put_shadow_img();
    void idx_increase();
    void move_toward(const Player& player);
    bool check_player_collision(const Player& player);
    bool check_bullet_collision(std::vector<Bullet*>& bullet_vector);
    void hurt();
    bool is_alive();

private:
    const int ENEMY_ANIM_NUM = 6;
    const int ENEMY_WIDTH = 80;
    const int ENEMY_HEIGHT = 80;
    const int SHADOW_WIDTH = 48;
    int idx_cur_anim;
    int x, y;
    int speed;
    int is_move_left;
    int is_move_right;
    bool alive;
    DWORD start_time;
    IMAGE img_enemy_left[6];
    IMAGE img_enemy_right[6];
    IMAGE img_enemy_shadow;
};