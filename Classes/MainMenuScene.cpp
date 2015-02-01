#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool touchesbegan = false;


Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
    
        
    auto listener2 = EventListenerTouchAllAtOnce::create();
    
    
    listener2->onTouchesBegan = CC_CALLBACK_2(MainMenuScene::onTouchesBegan,this);
    listener2->onTouchesMoved = CC_CALLBACK_2(MainMenuScene::onTouchesMoved,this);
    //listener2->onTouchesEnded = CC_CALLBACK_2(MainMenuScene::onTouchesEnded,this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    
                                                                            
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Birdy Smash", "fonts/Marker Felt.ttf", 36);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height - 50));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("deadBird.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto helpButton = MenuItemImage::create("helpButton.png","helpButton.png",
                                            CC_CALLBACK_1(MainMenuScene::helpButtonCallBack, this));
    auto gameButton = MenuItemImage::create("gameButton.png","gameButton.png",
                                            CC_CALLBACK_1(MainMenuScene::gameButtonCallBack, this));
    auto gpsButton = MenuItemImage::create("gpsButton.png","gpsButton.png",
                                            CC_CALLBACK_1(MainMenuScene::gpsButtonCallBack, this));
    
    helpButton->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200);
    gameButton->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 250);
    gpsButton->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 150);
    
    auto helpButtonMenu = Menu::create(helpButton,NULL);
    helpButtonMenu->setPosition(Point::ZERO);
    this->addChild(helpButtonMenu,1);
    
    auto gameButtonMenu = Menu::create(gameButton,NULL);
    gameButtonMenu->setPosition(Point::ZERO);
    this->addChild(gameButtonMenu,1);
    
    auto gpsButtonMenu = Menu::create(gpsButton,NULL);
    gpsButtonMenu->setPosition(Point::ZERO);
    this->addChild(gpsButtonMenu,1);
    
    //Detail for hidden bird sprite
    birdSprite = Sprite::create("bird.png");
    birdSprite->setPosition(Point(150, 350));
    birdSprite->setVisible(false);
    
    this->addChild(birdSprite,1);
    
    return true;
}
void MainMenuScene::onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event){
    //CCLOG("%s","onTouchesBegan");
}
//MultiTouchEvent to show bird.png on the screen breifly

void MainMenuScene::onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event){
//CCLOG("%s","Multi touches have moved");
    touchesbegan = true;
    
    
    if (touchesbegan == true) {
        //CCLOG("%s", "touchesBegan = true");
        birdSprite->setVisible(true);
        birdSprite->runAction(FadeOut::create(3));
        return;
        
    }
}

void MainMenuScene::helpButtonCallBack(Object* pSender){
    Director::getInstance()->pushScene(HelpScene::createScene());
}
void MainMenuScene::gameButtonCallBack(Object* pSender){
    Director::getInstance()->pushScene(GameScene::createScene());
}
void MainMenuScene::gpsButtonCallBack(Object* pSender){
    Director::getInstance()->pushScene(GpsScene::createScene());
}
void MainMenuScene::menuCloseCallback(Ref* pSender)
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
