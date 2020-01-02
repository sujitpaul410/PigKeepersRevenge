#include "MainMenu.h"
#include "GameScene.h"
#include "Instructions.h"

USING_NS_CC;


Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto glView = static_cast<cocos2d::GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView());
	auto buffer = experimental::FrameBuffer::getOrCreateDefaultFBO(glView);
	buffer->setClearColor(Color4F(0.0f, 0.0f, 0.0f, 1.0f));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto playButton = MenuItemImage::create("Play1.png", "Play1Selected.png", CC_CALLBACK_1(MainMenu::JumpToGameScene,this));
	auto Instructions = MenuItemImage::create("Instructions1.png", "Instructions1Selected.png", CC_CALLBACK_1(MainMenu::Instructions, this));
	//auto About = MenuItemImage::create("TestAbout.png", "TestAbout.png", CC_CALLBACK_1(MainMenu::About, this));
	auto Exit = MenuItemImage::create("Exit1.png", "Exit1Selected.png", CC_CALLBACK_1(MainMenu::ExitButton, this));

	playButton->setPosition(Point(Point::ZERO));
	Instructions->setPosition(playButton->getPositionX() - origin.x, playButton->getPositionY()- origin.y);
	//About->setPosition(Instructions->getPositionX() - origin.x, Instructions->getPositionY() - origin.y);
	Exit->setPosition(Instructions->getPositionX() - origin.x, Instructions->getPositionY() - origin.y);

	auto menu = Menu::create(playButton, Instructions, Exit, NULL);
	menu->setPosition(Point( visibleSize.width/2 + origin.x,	visibleSize.height/2 +origin.y));
	this->addChild(menu);

	return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void MainMenu::JumpToGameScene(cocos2d::Ref* sender)
{
	log("\n\njumping to Game Scene..");
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}

void MainMenu::About(cocos2d::Ref* sender)
{
	log("\n\nAbout Called");
	
}
void MainMenu::ExitButton(cocos2d::Ref * pSender)
{
	log("\n\Exit Called");
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
void MainMenu::Instructions(cocos2d::Ref* sender)
{
	log("\n\nInstructions Called");
	auto scene = Instructions::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}

