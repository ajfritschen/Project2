#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "HelpScene.h"
#include "GameScene.h"
#include "GpsScene.h"

#include "Box2D/Box2D.h"

using namespace cocos2d;

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void gameButtonCallBack(cocos2d::Ref* pSender);
    void helpButtonCallBack(cocos2d::Ref* pSender);
    void gpsButtonCallBack(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    //void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

    cocos2d::Sprite *birdSprite;
    
};

#endif // __MAINMENU_SCENE_H__
