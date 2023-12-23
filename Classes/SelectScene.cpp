#include "SimpleAudioEngine.h"
#include "SelectScene.h"
#include "WelcomeScene.h"
#include "HelpScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d;

Scene* SelectScene::createScene()
{
    return SelectScene::create();
}

bool SelectScene::init()
{
    /* 初始化场景 */
    if (!Scene::init())
    {
        return false;
    }

    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* 设置背景 */
    auto backGround = Sprite::create("SelectScene/stages_bg-hd_0.PNG");
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround, 0);

    /* 云朵背景 */
    auto cloud1 = Sprite::create("SelectScene/BG_Left.PNG");
    cloud1->setPosition(Vec2(130, 75));
    this->addChild(cloud1, 0);

    auto cloud2 = Sprite::create("SelectScene/BG_Right.PNG");
    cloud2->setPosition(Vec2(830, 75));
    this->addChild(cloud2, 0);

    /* 返回主界面按钮 */
    auto backToWelcome = ui::Button::create("SelectScene/stages_bg-hd_41.PNG", "SelectScene/stages_bg-hd_40.PNG");
    backToWelcome->setPosition(Vec2(40, 610)); // 设置按钮的初始位置
    // 按钮点击事件处理逻辑
    backToWelcome->addClickEventListener([=](Ref*) {
        // 创建遮罩层
        auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
        this->addChild(maskLayer);

        float duration = 0.1f; // 动画的持续时间
        float targetY = visibleSize.height; // 目标位置的Y坐标

        auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
        auto callback = CallFunc::create([]() {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::create(), Color3B::BLACK)); // 切换到新场景
            });
        auto sequence = Sequence::create(moveUp, callback, nullptr);
        maskLayer->runAction(sequence);
        });
    this->addChild(backToWelcome, 1);
  
    /* 帮助按钮 */
    auto helpButton = ui::Button::create("SelectScene/stages_bg-hd_42.PNG", "SelectScene/stages_bg-hd_33.PNG");
    helpButton->setPosition(Vec2(920, 610)); // 设置按钮的初始位置
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
    this->addChild(helpButton, 1);

    /* 进入滑动选关部分 */ 
    SelectScene::scroll();

    return true;
}

void SelectScene::scroll()
{
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int numLevels = 5; // 五张地图

    // 创建 PageView
    auto pageView = ui::PageView::create();
    pageView->setContentSize(visibleSize);
    pageView->setPosition(origin);
    pageView->setTag(TAG_PAGE_VIEW);
    this->addChild(pageView);

    // 循环打印关卡预览图并加入滑动容器
    for (int i = 0; i < numLevels; i++) {
        // 设置页面展示容器
        auto layout = Layout::create();
        layout->setContentSize(Size(visibleSize.width, visibleSize.height));
        layout->setTag(TAG_LEVEL_1 + i); // 设置不同的标签

        // 添加关卡图片
        char level[30] = "SelectScene/Level_1.PNG";
        level[18] = '1' + i;
        auto levelImage = ImageView::create(level);
        levelImage->setTag(TAG_LEVEL_IMAGE);
        levelImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
        layout->addChild(levelImage);
     
        // 添加是否锁定
        if (isLock) {
            // 创建锁的图案
            auto lock = ImageView::create("SelectScene/stages_bg-hd_31.PNG");
            lock->setTag(TAG_LOCK_IMAGE);
            lock->setPosition(Vec2(layout->getContentSize().width / 2 + 140, layout->getContentSize().height / 2 - 70));
            layout->addChild(lock);

            // 创建“已锁定”按钮
            auto lockButton = ImageView::create("SelectScene/stages_bg-hd_39.PNG");
            lockButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 235));
            this->addChild(lockButton,2);
        }

        // 添加是否完成关卡
        if (isFinish) {
            // 创建锁的图案
            auto finish = ImageView::create("SelectScene/finish.png");
            finish->setTag(TAG_FINISH_IMAGE);
            finish->setPosition(Vec2(layout->getContentSize().width / 2 + 150, layout->getContentSize().height / 2 - 50));
            layout->addChild(finish);
        }

        // 将每一张图添加到滑动页面上
        pageView->addPage(layout);
    }

    // 初始化，使第一页成为当前页
    this->updateLevelState(pageView->getCurrentPageIndex());

    // 设置 PageView 事件监听器，监听页面变化，更新关卡状态
    pageView->addEventListener([this](Ref* sender, ui::PageView::EventType type) {
        if (type == ui::PageView::EventType::TURNING) {
            auto pageView = dynamic_cast<PageView*>(sender);
            int pageIndex = pageView->getCurrentPageIndex();
            this->updateLevelState(pageIndex);
        }
        });

    // 创建开始游戏按钮
    auto startButton = ui::Button::create("SelectScene/stages_bg-hd_30.PNG", "SelectScene/stages_bg-hd_28.PNG");
    startButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240)); // 按钮位置在页面底部
    startButton->setTag(TAG_START_BUTTON);
    // 点击按钮事件
    startButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED)
        {
            this->gotoGameScene(sender);
        }
        });
    this->addChild(startButton);
}

/* 监听页面变化，更新关卡状态 */
void SelectScene::updateLevelState(int pageIndex)
{
    auto pageView = dynamic_cast<ui::PageView*>(this->getChildByTag(TAG_PAGE_VIEW));

    /* 对地图的透明度进行更新 */
    for (auto& item : pageView->getChildren()) {
        auto layout = dynamic_cast<ui::Layout*>(item);
        auto levelImage = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_LEVEL_IMAGE));
        // 根据是否是当前页面来设置透明度
        levelImage->setOpacity(layout->getTag() == (TAG_LEVEL_1 + pageIndex) ? 255 : 50);

        // 锁的透明度变化
        if (isLock) {
            auto lock = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_LOCK_IMAGE));
            lock->setOpacity(layout->getTag() == (TAG_LEVEL_1 + pageIndex) ? 255 : 50);
        }
        // 完成标志的透明度变化
        if (isFinish) {
            auto finish = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_FINISH_IMAGE));
            finish->setOpacity(layout->getTag() == (TAG_LEVEL_1 + pageIndex) ? 255 : 50);
        }
    }

    /* 对每一页的固定部件进行更新 */
    // 定义固定部件的标签
    const int TAG_FIXED_PART = 1000;

    // 添加固定部件，每个页面的部件都不一样
    auto tower1 = ImageView::create("SelectScene/Tower_1.PNG");
    tower1->setTag(TAG_FIXED_PART);
    auto tower2 = ImageView::create("SelectScene/Tower_2.PNG");
    tower2->setTag(TAG_FIXED_PART + 1);
    auto tower3 = ImageView::create("SelectScene/Tower_3.PNG");
    tower3->setTag(TAG_FIXED_PART + 2);
    auto tower4 = ImageView::create("SelectScene/Tower_4.PNG");
    tower4->setTag(TAG_FIXED_PART + 3);
    auto tower5 = ImageView::create("SelectScene/Tower_5.PNG");
    tower5->setTag(TAG_FIXED_PART + 4);
    auto labelText1 = Label::createWithTTF("A total of 15 waves", "fonts/Marker Felt.ttf", 22);
    labelText1->setTag(TAG_FIXED_PART + 5);
    auto labelText2 = Label::createWithTTF("A total of 20 waves", "fonts/Marker Felt.ttf", 22);
    labelText2->setTag(TAG_FIXED_PART + 6);

    // 移除上一次添加的固定部件
    for (int i = 0; i < 7; i++) {
        this->removeChildByTag(TAG_FIXED_PART + i);
    }

    if (pageIndex == 0) {
        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 + 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        labelText1->setPosition(Vec2(pageView->getContentSize().width / 2 + 130, pageView->getContentSize().height / 2 + 200));
        this->addChild(labelText1);

    }
    else if (pageIndex == 1) {
        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower3->setPosition(Vec2(pageView->getContentSize().width / 2 + 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower3);

        labelText1->setPosition(Vec2(pageView->getContentSize().width / 2 + 130, pageView->getContentSize().height / 2 + 200));
        this->addChild(labelText1);
    }
    else if (pageIndex == 2) {
        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower4->setPosition(Vec2(pageView->getContentSize().width / 2 + 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower4);

        labelText2->setPosition(Vec2(pageView->getContentSize().width / 2 + 130, pageView->getContentSize().height / 2 + 200));
        this->addChild(labelText2);
    }
    else if (pageIndex == 3) {
        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 - 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower5->setPosition(Vec2(pageView->getContentSize().width / 2 + 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower5);

        labelText2->setPosition(Vec2(pageView->getContentSize().width / 2 + 130, pageView->getContentSize().height / 2 + 200));
        this->addChild(labelText2);
    }
    else if (pageIndex == 4) {
        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 - 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower4->setPosition(Vec2(pageView->getContentSize().width / 2 + 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower4);

        labelText2->setPosition(Vec2(pageView->getContentSize().width / 2 + 130, pageView->getContentSize().height / 2 + 200));
        this->addChild(labelText2);
    }

}

/* 进入游戏场景 */
void SelectScene::gotoGameScene(Ref* sender)
{
     // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 创建遮罩层
    auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
    this->addChild(maskLayer);

    float duration = 0.1f; // 动画的持续时间
    float targetY = visibleSize.height; // 目标位置的Y坐标

    auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
    auto callback = CallFunc::create([]() {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::create(), Color3B::BLACK)); // 切换到新场景
        });
    auto sequence = Sequence::create(moveUp, callback, nullptr);
    maskLayer->runAction(sequence);
}