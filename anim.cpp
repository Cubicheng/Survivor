# include "anim.h"
# include <string>

Anim::Anim(){
    LoadAnimation();
}

inline void Anim::LoadAnimation() {
    for (int i = 0; i < ANIM_NUM; i++) {
        std::wstring path = L"img/enemy_left_" + std::to_wstring(i) + L".png";
        loadimage(&img_left[i], path.c_str());
    }
    for (int i = 0; i < ANIM_NUM; i++) {
        std::wstring path = L"img/enemy_right_" + std::to_wstring(i) + L".png";
        loadimage(&img_right[i], path.c_str());
    }
    loadimage(&img_shadow, L"img/shadow_enemy.png");
}

IMAGE* Anim::get_left(int& index){
    return &img_left[index];
}

IMAGE* Anim::get_right(int& index) {
    return &img_right[index];
}

IMAGE* Anim::get_shadow(){
    return &img_shadow;
}
