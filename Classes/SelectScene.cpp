#include "SimpleAudioEngine.h"
#include "SelectScene.h"
#include "WelcomeScene.h"
#include "HelpScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"

USING_NS_CC;

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
}

void SelectScene::scroll()
{
    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();

    int numLevels = 5;
    int levelPreviewWidth = 501;
    int gapX = 30;
    // 创建滑动容器
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));
    scrollView->setInnerContainerSize(Size(numLevels * (levelPreviewWidth + gapX) + 300, visibleSize.height));
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    this->addChild(scrollView);

    // 循环打印关卡预览图
    for (int i = 0; i < numLevels; i++) {
        char a[30] = "SelectScene/Level_1.PNG";
        a[18] = '1' + i;
        auto imageView = Sprite::create(a);

        // 设置ImageView的位置
        float posX = visibleSize.width / 2 + i * levelPreviewWidth;
        float posY = visibleSize.height / 2 + 30;
        imageView->setPosition(Vec2(posX, posY));

        // 将ImageView添加为滑动容器的子节点
        scrollView->addChild(imageView);
    }

    // 设置滑动相关参数
    bool isDragging = false;  // 是否正在拖动
    Vec2 startTouchPos;  // 开始触摸位置
    Vec2 startInnerContainerPos;  // 开始滑动时的滑动容器内部位置

    // 添加触摸事件监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        if (scrollView->isTouchEnabled() && scrollView->getBoundingBox().containsPoint(touch->getLocation())) {
            isDragging = true;
            startTouchPos = touch->getLocation();
            startInnerContainerPos = scrollView->getInnerContainerPosition();
            return true;
        }
        return false;
    };
    listener->onTouchMoved = [&](Touch* touch, Event* event) {
        if (isDragging) {
            Vec2 delta = touch->getLocation() - startTouchPos;
            Vec2 newPosition = startInnerContainerPos + delta;
            scrollView->setInnerContainerPosition(newPosition);

            // 更新关卡预览图的透明度
           // updateLevelPreviewOpacity(newPosition.x);
        }
    };
    listener->onTouchEnded = [&](Touch* touch, Event* event) {
        if (isDragging) {
            isDragging = false;

            // 恢复关卡预览图的透明度
            //resetLevelPreviewOpacity();
        }
    };
    listener->onTouchCancelled = [&](Touch* touch, Event* event) {
        if (isDragging) {
            isDragging = false;

            // 恢复关卡预览图的透明度
          //  resetLevelPreviewOpacity();
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scrollView);
}