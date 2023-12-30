#include "WelcomeScene.h"
#include "audio/include/AudioEngine.h"
#include <string.h>
#include <SettingScene.h>
#include <HelpScene.h>
#include <SelectScene.h>
#include "GameScene.h"
#include "Level1.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::experimental;

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    return WelcomeScene::create();
}

// 添加菜单静态图形
void WelcomeScene::setMenu(char picture[], Vec2 position)
{
    // 添加界面
    auto sprite = Sprite::create(picture);

    // 将 Sprite 放置在 position 位置
    sprite->setPosition(position);
      
    // 将 Sprite 作为子项添加到此层
    if (picture == "WelcomeScene/lock.PNG")
        this->addChild(sprite, 1);
    else
        this->addChild(sprite, 0);
}

// 初始化欢迎界面
bool WelcomeScene::init()
{
    /* 初始化场景 */
    if ( !Scene::init() )
    {
        return false;
    }
    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* 背景贴图 */
    setMenu("WelcomeScene/MainBG.PNG", Vec2(visibleSize.width / 2, visibleSize.height / 2));

    /* 漂浮的云 */
    auto cloud = Sprite::create("WelcomeScene/Cloud.PNG");
    cloud->setOpacity(140); // 设置云的透明度
    cloud->setPosition(Vec2(-cloud->getContentSize().width, 550)); // 设置云的初始位置
    this->addChild(cloud, 0);
    // 实现横穿屏幕
    auto move = MoveTo::create(5.0f, Vec2(visibleSize.width + 100, cloud->getPositionY()));
    auto resetPosition = CallFunc::create([=]() {
        cloud->setPosition(Vec2(-cloud->getContentSize().width, cloud->getPositionY()));
        });
    auto sequence = Sequence::create(move, resetPosition, nullptr);
    auto repeat = RepeatForever::create(sequence);
    cloud->runAction(repeat);

    setMenu("WelcomeScene/Leaf1.PNG", Vec2(410, 470));//  萝卜叶子1
    setMenu("WelcomeScene/Leaf2.PNG", Vec2(540, 470));//  萝卜叶子2
    setMenu("WelcomeScene/Leaf3.PNG", Vec2(480, 505));//  萝卜叶子3
    setMenu("WelcomeScene/CarrotBody.PNG", Vec2(visibleSize.width / 2, visibleSize.height * 0.6)); // 中心萝卜
    setMenu("WelcomeScene/MainTitle.PNG", Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 30));// “保卫萝卜”字样
    //背景音乐//
    //******************************************************************//
    AudioEngine::preload("sound/backGround.ogg");
    int AudioID = AudioEngine::play2d("sound/backGround.ogg");
    //*******************************************************************//
    /* 上下移动的怪兽 */ 
    auto flymonster = Sprite::create("WelcomeScene/FlyMonster.PNG");
    flymonster->setPosition(Vec2(180, 470)); // 设置怪兽的初始位置
    this->addChild(flymonster, 1);
    // 实现上下移动
    auto moveUp = MoveBy::create(1.5f, Vec2(0, 50)); // 向上移动50个单位
    auto moveDown = moveUp->reverse(); // 向下移动同样的距离
    auto floatAction = RepeatForever::create(Sequence::create(moveUp, moveDown, nullptr)); // 不断重复上下移动的动作
    flymonster->runAction(floatAction);
    /* 设置按钮 */
    auto settingsButton = ui::Button::create("Btn_Set.PNG", "Btn_SetLight.PNG");
    settingsButton->setPosition(Vec2(210, 230)); // 设置按钮的初始位置
    // 按钮点击事件处理逻辑
    settingsButton->addClickEventListener([=](Ref*) {
        // 创建遮罩层
        auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
        this->addChild(maskLayer);
       
        float duration = 0.1f; // 动画的持续时间
        float targetY = visibleSize.height; // 目标位置的Y坐标

        auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
        auto callback = CallFunc::create([]() {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SettingScene::create(), Color3B::BLACK)); // 切换到新场景
            });
        auto sequence = Sequence::create(moveUp, callback, nullptr);
        maskLayer->runAction(sequence);
        });
    this->addChild(settingsButton, 0);

    /* 帮助按钮 */
    auto helpButton = ui::Button::create("Btn_Help.PNG", "Btn_HelpLight.PNG");
    helpButton->setPosition(Vec2(770, 230)); // 设置按钮的初始位置
    // 按钮点击事件处理逻辑
    helpButton->addClickEventListener([=](Ref*) {
        // 创建遮罩层
        auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
        this->addChild(maskLayer);

        float duration = 0.1f; // 动画的持续时间
        float targetY = visibleSize.height; // 目标位置的Y坐标

        auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
        auto callback = CallFunc::create([]() {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelpScene::create(), Color3B::BLACK)); // 切换到新场景
            });
        auto sequence = Sequence::create(moveUp, callback, nullptr);
        maskLayer->runAction(sequence);
        });
    this->addChild(helpButton, 0);

    /* 冒险模式 */
    auto Normal = MenuItemImage::create("WelcomeScene/Btn_NormalModle.PNG", 
        "WelcomeScene/Btn_NormalModleLight.PNG", 
        CC_CALLBACK_1(WelcomeScene::gotoSelectScene, this));

    Normal->setPosition(Vec2(150, 80));
    auto menu = Menu::create(Normal, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /* Boss模式 */ 
    auto Boss = MenuItemImage::create("WelcomeScene/Btn_Boss.PNG", 
        "WelcomeScene/Btn_BossLight.PNG", 
        CC_CALLBACK_1(WelcomeScene::bossLock, this));

    Boss->setPosition(Vec2(480, 80));
    menu = Menu::create(Boss, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /* 怪物窝模式 */ 
    auto MonsterNest = MenuItemImage::create("WelcomeScene/Btn_MonsterNest.PNG",
        "WelcomeScene/Btn_MonsterNestLight.PNG",
        CC_CALLBACK_1(WelcomeScene::nestLock, this));

    MonsterNest->setPosition(Vec2(810, 80));
    menu = Menu::create(MonsterNest, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /* lock图标 */
    setMenu("WelcomeScene/lock.PNG", Vec2(610, 70)); 
    setMenu("WelcomeScene/lock.PNG", Vec2(940, 70)); 
}

/* 进入关卡选择界面 */ 
void WelcomeScene::gotoSelectScene(cocos2d::Ref* pSender)
{
    AudioEngine::stopAll();
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 创建遮罩层
    auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
    this->addChild(maskLayer);

    float duration = 0.1f; // 动画的持续时间
    float targetY = visibleSize.height; // 目标位置的Y坐标

    auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
    auto callback = CallFunc::create([]() {                                   //修改此处
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::create(), Color3B::BLACK)); // 切换到新场景
        });
    auto sequence = Sequence::create(moveUp, callback, nullptr);
    maskLayer->runAction(sequence);
}

void WelcomeScene::bossLock(Ref* pSender)
{
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 创建提示框
    auto bosslock = ui::ImageView::create("WelcomeScene/boss_lock_image.png");
    bosslock->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bosslock);

    // 创建关闭按钮
    auto closeButton = ui::Button::create("WelcomeScene/lock_btn_normal.PNG",
        "WelcomeScene/lock_btn_selected.PNG");
    closeButton->setPosition(Vec2(270, 60));
    bosslock->addChild(closeButton); // 将按钮添加到提示框下

    // 添加点击事件监听器
    closeButton->addClickEventListener([=](Ref*) {
        bosslock->removeFromParent(); // 移除提示框
        });
}

void WelcomeScene::nestLock(Ref* pSender)
{
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 创建提示框
    auto bosslock = ui::ImageView::create("WelcomeScene/nest_lock_image.png");
    bosslock->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bosslock);

    // 创建关闭按钮
    auto closeButton = ui::Button::create("WelcomeScene/lock_btn_normal.PNG",
        "WelcomeScene/lock_btn_selected.PNG");
    closeButton->setPosition(Vec2(270, 60));
    bosslock->addChild(closeButton); // 将按钮添加到提示框下

    // 添加点击事件监听器
    closeButton->addClickEventListener([=](Ref*) {
        bosslock->removeFromParent(); // 移除提示框
        });
}