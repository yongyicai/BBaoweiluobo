#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "Tower.h"


USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocos2d;

Tower::Tower() : level(1), attackPower(10), attackSpeed(1.0f), towerType(0)
{
    // 初始化代码
}

//Tower::~Tower()
//{
//    // 清理代码
//}
Tower* Tower::create(Vec2 position,int towerType)
{
    Tower* tower = new (std::nothrow) Tower();
    if (tower && tower->initWithFile("tower_base.png"))
    {
        tower->autorelease();
        tower->towerType = towerType;
        tower->setPosition(position);
        // 根据类型初始化不同的属性
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return nullptr;
}

bool Tower::init()
{
    /**以下是init函数的所调用函数的注释，可以理解为判断一个精灵是否被正常初始化
     * Initializes a sprite with a texture and a rect in points, optionally rotated.
     *
     * After initialization, the offset will be (0,0).
     * @note    This is the designated initializer.
     *
     * @param   texture    A Texture2D object whose texture will be applied to this sprite.
     * @param   rect        A rectangle assigned the contents of texture.
     * @param   rotated     Whether or not the texture rectangle is rotated.
     * @return  True if the sprite is initialized properly, false otherwise.
     */
    if (!Sprite::init())
    {
        return false;
    }

    // 初始化炮台
    return true;
}
void Tower::attack()
{
    // 实现攻击逻辑
    // 这可能涉及到创建一个 Projectile 类，并将其发射到目标
}

void Tower::upgrade()
{
    // 升级炮台，提高属性
    //将原先的炮台移除，重新生成一个新炮台
    
}

void Tower::remove()
{
    // 移除炮台
    this->removeFromParentAndCleanup(true);
}

// 更多的炮台类型可以通过继承Tower类并覆盖其方法来实现
void Tower::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    // 创建一个绘制节点
    auto drawNode = cocos2d::DrawNode::create();
    // 设置圆的颜色和透明度
    cocos2d::Color4F color(1.0f, 0.0f, 0.0f, 0.3f); // 这里使用红色作为示例
    // 绘制一个圆形，参数依次为：圆心坐标、半径、绘制时使用的颜色
    drawNode->drawSolidCircle(getPosition(), attackRange, 0, 20, color);
    // 将绘制节点添加到场景中
    getParent()->addChild(drawNode);
}

void Tower::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event) {
    // 找到并移除攻击范围的绘制节点
    auto drawNode = getParent()->getChildByName("AttackRangeNode");
    if (drawNode) {
        drawNode->removeFromParent();
    }
}

void Tower::setTowerImage(const std::string& imagePath) {
    auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(imagePath);
    setTexture(texture);
}