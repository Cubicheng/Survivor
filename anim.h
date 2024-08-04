#pragma once

# include <graphics.h>

class Anim {
public:
    Anim();
    void LoadAnimation();
    IMAGE* get_left(int &index);
    IMAGE* get_right(int& index);
    IMAGE* get_shadow();
private:
    const int ANIM_NUM = 6;
    IMAGE img_left[6];
    IMAGE img_right[6];
    IMAGE img_shadow;
};