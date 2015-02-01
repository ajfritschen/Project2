#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void homeButtonCallBack(cocos2d::Ref* pSender);
    
    void tick(float dt);
    void touchPoint(Point p);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void Play(Ref *pSender);
    cocos2d::Sprite *mySprite;
    
    
    
};

#endif // __GAME_SCENE_H__
