#include "enemy.h"
#include "define.h"
#include "bullet.h"
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iostream>

Enemy::Enemy(int &enemy_speed,Anim * anim) {
    idx_cur_anim = 0;
    speed = enemy_speed;
    is_move_left = false;
    is_move_right = false;
    alive = true;
    start_time = GetTickCount();
    anim_ptr = anim;
    int op = rand() % 4;
    switch (op) {
    case UP_EDGE:
        x = rand() % WINDOW_WIDTH;
        y = -ENEMY_HEIGHT;
        break;
    case DOWN_EDGE:
        x = rand() % WINDOW_WIDTH;
        y = WINDOW_HEIGHT;
        break;
    case RIGHT_EDGE:
        x = WINDOW_WIDTH;
        y = rand() % WINDOW_HEIGHT;
        break;
    case LEFT_EDGE:
        x = -ENEMY_WIDTH;
        y = rand() % WINDOW_HEIGHT;
        break;
    }
}



#pragma comment(lib,"MSIMG32.LIB")

void Enemy::put_img(IMAGE* img, int x, int y) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h,
        { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Enemy::put_enemy_img() {
    put_shadow_img();

    if (is_move_left) put_left_img();
    else put_right_img();

    DWORD end_time = GetTickCount();
    if (end_time - start_time > 100) {
        idx_increase();
        start_time = end_time;
    }
}

void Enemy::put_shadow_img() {
    int shadow_x = x + ENEMY_WIDTH / 2 - SHADOW_WIDTH / 2;
    int shadow_y = y + ENEMY_HEIGHT - 30;
    put_img((anim_ptr->get_shadow()), shadow_x, shadow_y);
}

void Enemy::put_left_img() {
    put_img(anim_ptr->get_left(idx_cur_anim), x, y);
}

void Enemy::put_right_img() {
    put_img(anim_ptr->get_right(idx_cur_anim), x, y);
}

void Enemy::idx_increase() {
    idx_cur_anim = (idx_cur_anim + 1) % ENEMY_ANIM_NUM;
}

void Enemy::move_toward(const Player & player) {
    int dir_x = player.x - x;
    int dir_y = player.y - y;
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (dir_x > 0) {
        is_move_right = true;
        is_move_left = false;
    }
    else {
        is_move_right = false;
        is_move_left = true;
    }
    if (len_dir) {
        x += (int)(dir_x / len_dir * speed);
        y += (int)(dir_y / len_dir * speed);
    }
}

bool Enemy::check_player_collision(const Player& player) {
    int mid_x = x + ENEMY_WIDTH / 2;
    int mid_y = y + ENEMY_HEIGHT / 2;
    return player.x < mid_x && mid_x < player.x + player.PLAYER_WIDTH &&
           player.y < mid_y && mid_y < player.y + player.PLAYER_HEIGHT;
}

bool Enemy::check_bullet_collision(std::vector<Bullet*>& bullet_vector){
    for (int i = 0; i < bullet_vector.size(); i++) {
        int bx = bullet_vector[i]->get_x();
        int by = bullet_vector[i]->get_y();
        if (x < bx && bx < x + ENEMY_WIDTH && y < by && by < y + ENEMY_HEIGHT) {
            return true;
        }
    }
    return false;
}

void Enemy::hurt(){
    alive = false;
}

bool Enemy::is_alive(){
    return alive;
}
