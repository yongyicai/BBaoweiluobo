#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    void setMenu(char picture[], cocos2d::Vec2 position);

    virtual bool init();

    void bossLock(cocos2d::Ref* pSender);

    void nestLock(cocos2d::Ref* pSender);

    void returnToWelcomeScene(int tag);

    void gotoSelectScene(cocos2d::Ref* pSender);

    CREATE_FUNC(WelcomeScene);
};


#endif