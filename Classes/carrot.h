#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"

class Carrot : public cocos2d::Sprite
{
public:
    static Carrot* createCarrot();

    virtual bool init();

    // 添加血量属性和相关方法
    CC_SYNTHESIZE(int, m_hp, Hp);  // 血量属性

    void decreaseHp(int value);  // 减少血量的方法

    CREATE_FUNC(Carrot);
};

#endif