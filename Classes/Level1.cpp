#include "SimpleAudioEngine.h"
#include <string.h>
#include"Global.h"
#include <vector>
using namespace cocos2d;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* Level1Scene::createScene()
{
    return Level1Scene::create();
}

bool Level1Scene::init()
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
    auto bg = Sprite::create("Level_1/Level_1_1_bg.png");
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg);

    /* 设置游戏画面 */
    auto gamescene = GameScene::create();
    this->addChild(gamescene);

    /* 打印放置炮台的位置 */
    auto gamemap = GameMap::create();
    this->addChild(gamemap);

    /* 初始化网格路径 */
    vector<GameMap::Grid>path_ = {
    { 1,5 },
    { 1,4 },
    { 1,3 },
    { 1,2 },
    { 2,2 },
    { 3,2 },
    { 4,2 },
    { 4,3 },
    { 5,3 },
    { 6,3 },
    { 7,3 },
    { 7,2 },
    { 8,2 },
    { 9,2 },
    { 10,2 },
    { 10,3 },
    { 10,4 },
    { 10,5 } };
    for (int i = 0; i < path_.size(); i++) {
        gamemap->addPathPoint(path_[i]);
    }

    /* 初始化像素路径和波次 */
    currentWave = 0;
    getPath(gamemap);

    /* 设置起点 */
    auto startPoint = Sprite::create("Level_1/startPoint.PNG");
    startPoint->setPosition(path[0]);
    this->addChild(startPoint);

    /* 初始化萝卜 */
    globalCarrot = Carrot::create();
    globalCarrot->setPosition(path[path.size() - 1]);
    this->addChild(globalCarrot);

    /* 点击事件 */
    Level1Scene::click(gamemap);

    /* 倒计时动画 */
    gamescene->createCountdownAnimation();

    /* 开始第一波 */
    this->schedule(CC_SCHEDULE_SELECTOR(Level1Scene::startNextWave), 6.0f);

    return true;
}

void Level1Scene::getPath(GameMap* gamemap)
{
    // 计算路径的像素坐标
    for (const auto& grid : gamemap->path)
    {
        path.push_back(gamemap->gridToPixel(grid.x, grid.y));
    }
}

void Level1Scene::click(GameMap* gamemap)
{
    for (int y = 0; y < gamemap->GRID_HEIGHT; ++y) {
        for (int x = 0; x < gamemap->GRID_WIDTH; ++x) {
            if (gamemap->gridMap[y][x]) {
                auto startSprite = ImageView::create("GameScene/click.png");
                // 修改位置计算方式，确保图片位置与点击位置一致
                startSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
                startSprite->setPosition(gamemap->gridToPixel(x, y));
                startSprite->setVisible(false);  // 将图片设置为不可见
                addChild(startSprite);
            }
        }
    }
    // 添加触摸事件监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 location = touch->getLocation();
        bool clickedOnImage = false;

        // 遍历所有子节点，查找包含点击位置的图片节点
        for (auto image : getChildren()) {
            if (auto sprite = dynamic_cast<ImageView*>(image)) {
                if (sprite->getBoundingBox().containsPoint(location)) {
                    sprite->setVisible(true);
                    clickedOnImage = true;
                }
                else {
                    sprite->setVisible(false);
                }
            }
        }
        // 如果点击位置没有图片且没有点击到其他非图片的区域，则不进行任何操作
        if (!clickedOnImage) {
            return false;
        }

        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void Level1Scene::startNextWave(float dt) {
    if (currentWave >= totalWaves) {
        // 所有波次完成，游戏结束
        unschedule(CC_SCHEDULE_SELECTOR(Level1Scene::startNextWave));
        endGame();
        return;
    }

    // 开始下一波怪物的生成
    spawnMonsters(currentWave);

    // 准备下一波
    currentWave++;
}

void Level1Scene::spawnMonsters(int waveIndex) {
    // 根据波次决定生成怪物的类型和数量
    int monsterType = (waveIndex % 3) + 1; // 举例：每波切换一种怪物类型
    int monsterCount = 4 + (waveIndex % 3); // 举例：每波怪物数量在5到7之间

    for (int i = 0; i < monsterCount; ++i) {
        // 创建怪物并设置位置到路径起点
        auto monster = Monster::createWithType(monsterType);
        monster->setPosition(path.front()); // 假设路径的第一个点是起点
        this->addChild(monster);
        monster->setVisible(false);
        monsters.push_back(monster);

        // 设置怪物间的出现时间间隔
        this->scheduleOnce([this, monster](float dt) {
            monster->setVisible(true);
            monster->moveOnPath(this->path);
            // 萝卜血量先为0，则游戏结束
            if (globalCarrot->health <= 0) {
                endGame();
            }
            
            }, i * 0.7f, "spawn_monster_" + std::to_string(i)); // 每隔0.7秒出现一只怪物
    }
}

void Level1Scene::endGame() {
    // 处理游戏结束逻辑

    /* 出现获胜提示框 */
    // 蒙版层
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 150));
    this->addChild(maskLayer, 6);

    // 创建提示框
    ImageView* tips;
    if (globalCarrot->health <= 0) {
        tips = ImageView::create("GameScene/lose.png");
    }
    else {
        tips = ImageView::create("GameScene/win.png");
    }
    
    tips->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    maskLayer->addChild(tips, 2);

    // 以下按钮都添加在 tips 层上 
    // 再试一次按钮
    auto restartButton = ui::Button::create("GameScene/again_normal.png", "GameScene/again_selected.png");
    restartButton->setPosition(Vec2(210, 185));
    tips->addChild(restartButton);
    restartButton->addClickEventListener([=](Ref*) {
        Director::getInstance()->resume();
        Director::getInstance()->getScheduler()->setTimeScale(1);

        // 重新开始游戏
        auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 透明的遮罩层
        this->addChild(maskLayer);
        float duration = 0.1f; // 动画的持续时间
        float targetY = visibleSize.height; // 目标位置的Y坐标

        auto moveUp = MoveTo::create(duration, Vec2(0, targetY));
        auto callback = CallFunc::create([]() {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Level1Scene::create(), Color3B::BLACK)); // 切换到新场景
            });
        auto sequence = Sequence::create(moveUp, callback, nullptr);
        maskLayer->runAction(sequence);
        });

    // 选择关卡按钮
    auto returnButton = ui::Button::create("GameScene/return_normal.png", "GameScene/return_selected.png");
    returnButton->setPosition(Vec2(210, 90));
    tips->addChild(returnButton);
    returnButton->addClickEventListener([=](Ref*) {
        Director::getInstance()->resume();
        Director::getInstance()->getScheduler()->setTimeScale(1);

        // 返回选择界面
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
        });

    /* 游戏暂停逻辑 */
    // 游戏暂停
    Director::getInstance()->pause();

    // 确保用户不能点击暂停菜单后面的元素，可以通过添加一个监听器到暂停菜单层来吞噬所有点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        return true; // 吞噬触摸事件
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, maskLayer);

    /* 让萝卜的指针归零 */
    globalCarrot = nullptr;
}