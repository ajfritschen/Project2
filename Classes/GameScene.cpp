#include "GameScene.h"
#include "WinScene.h"
#include "SimpleAudioEngine.h"

b2World* world;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("birds006.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("birds006.wav");
        
    mySprite = Sprite::create("bird.png");
    
    mySprite->setPosition(Point(50, 50));
    
    this->addChild(mySprite);
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(0, visibleSize.height / 2);
    bezier.controlPoint_2 = Point(200, -visibleSize.height / 2);
    bezier.endPosition = Point(200,100);
    
    auto action = RepeatForever::create(BezierBy::create(2, bezier));
    
    mySprite->runAction(action);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto homeButton = MenuItemImage::create("homeButton.png","homeButton.png",
                                            CC_CALLBACK_1(GameScene::homeButtonCallBack, this));
    
    homeButton->setPosition(Vec2(origin.x + visibleSize.width - homeButton->getContentSize().width/2 ,
                                 origin.y + homeButton->getContentSize().height/2));
    
    auto homeButtonMenu = Menu::create(homeButton,NULL);
    homeButtonMenu->setPosition(Point::ZERO);
    this->addChild(homeButtonMenu,1);
    
    schedule(schedule_selector(GameScene::tick));
    
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *Event){

    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if (mySprite->boundingBox().containsPoint(location)) {
        mySprite->runAction(FadeOut::create(2));
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Play(WinScene::createScene());
    }
    
    
    return true;
}
void GameScene::tick(float dt){
    
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *Event){
    //CCLOG("onTouchMoved x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
    
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *Event){
    //CCLOG("onTouchEnded x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
}

void GameScene::Play(cocos2d::Ref *pSender){
    auto scene = WinScene::createScene();
    
    Director::getInstance()->pushScene(scene);
}

void GameScene::homeButtonCallBack(Object* pSender){
    Director::getInstance()->popScene();
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
