#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"

class Carrot : public cocos2d::Node {
public:
    virtual bool init() override;
    int health;
    std::vector<std::string> healthTextures; // 贴图数组，用于不同血量的贴图
   
    cocos2d::Sprite* aCarrot;
    cocos2d::Sprite* bloodBar;
    void setupCarrot(const cocos2d::Vec2& position);
    void setupBloodBar();

    void setupSwingAction();
    void decreaseHealth();
    void updateAppearance();

    CREATE_FUNC(Carrot);
};

#endif
