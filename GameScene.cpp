#include <stdlib.h>
#include <string>
#include <sstream>
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "PhysicsShapeCache.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	//auto scene = Scene::create();
	auto layer = GameScene::create();
	//scene->addChild(layer);
	return layer;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	elevating = false; delevating = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EventListenerMouse *mouseListener = EventListenerMouse::create();

	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//EventListenerMouse *mouseListenerm = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	
	sprite = Sprite::create("bird.png");
	sprite->setPosition(this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width + 200, this->getBoundingBox().getMidY());
	this->addChild(sprite, 0);

	danger = false;
	score = 0;
	lives = 3;
	ShowCursor(false);

	std::ostringstream o;
	o << "Score: " << score;

	scoreLabel = Label::createWithSystemFont(o.str(), "Arial", 10);
	scoreLabel->setPosition(Vec2(visibleSize.width, visibleSize.height));
	scoreLabel->setDimensions(visibleSize.width / 3, 0);
	this->addChild(scoreLabel);

	std::ostringstream l;
	l << "Pigs Left: " << lives;

	livesLabel = Label::createWithSystemFont(l.str(), "Arial", 10);
	livesLabel->setPosition(Vec2(visibleSize.width/5, visibleSize.height));
	livesLabel->setDimensions(0, visibleSize.height / 3);
	this->addChild(livesLabel);


	this->scheduleUpdate();

	return true;
}

void GameScene::onMouseDown(cocos2d::Event *ev) {
	EventMouse* e = (EventMouse*)ev;

	auto glView = static_cast<cocos2d::GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView());
	ShowCursor(false);
	log("\n\nCursor %f, %f",e->getCursorX(), e->getCursorY());
	log("When clicked, Sprite X pos is: %f, %f",sprite->getPositionX(), sprite->getPositionY());

	double xDiff = double(e->getCursorX() - sprite->getPositionX());
	double yDiff = double(e->getCursorY() - sprite->getPositionY());
	log("xDiff: %lf, yDiff: %lf",xDiff,yDiff);

	if ((xDiff <= 10 && xDiff >= -10) && (yDiff <= 10 && yDiff >= -10))
	{
		log("\nScored..");
		if (danger == false)
		{
			score++;
			std::ostringstream o;
			o << "Score: " << score;
			scoreLabel->setString(o.str());
			sprite->setVisible(false);
		}
		else
		{
			auto glView = static_cast<cocos2d::GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView());
			auto buffer = experimental::FrameBuffer::getOrCreateDefaultFBO(glView);
			buffer->setClearColor(Color4F(1.0f, 1.0f, 1.0f, 1.0f));

			lives--;
			std::ostringstream l;
			l << "Pigs Left: " << lives;
			livesLabel->setString(l.str());
			sprite->setVisible(false);
		}
	}
}

void GameScene::onMouseMove(cocos2d::Event *ev)
{
	EventMouse* e = (EventMouse*)ev;
	
	auto sprite1 = Sprite::create("Crosshair.png");
	sprite1->setTag(11);
	sprite1->setScale(0.25);
	auto l = Director::getInstance()->getRunningScene();
	if (l != NULL || l != nullptr)
	{
		l->removeChildByTag(11,true);
		sprite1->setPosition(e->getCursorX(), e->getCursorY());
		l->addChild(sprite1);

	}
	else
	{
		log("\nNULL POINTER..");
	}
}

void GameScene::update(float delta) {
	int chk = int(delta) + rand() % 100 + 10;
	int randNum = (rand() % 5) + 1;
	log("\nCHK: %i", randNum);

	if (chk % 2 == 0 && oneLoop == true)
	{
		sprite->setTexture("danger1.png");
		danger = true;
	}
	else if (chk % 2 == 1 && oneLoop == true)
	{
		if (randNum == 0)
		{
			sprite->setTexture("bird.png");
		}
		else if (randNum == 1)
		{
			sprite->setTexture("bird1.png");
		}
		else if (randNum == 2)
		{
			sprite->setTexture("bird2.png");
		}
		else if (randNum == 3)
		{
			sprite->setTexture("bird3.png");
		}
		else if (randNum == 4)
		{
			sprite->setTexture("bird4.png");
		}
		else
		{
			sprite->setTexture("bird.png");
		}
		danger = false;
	}
	/*else*/
	{
		oneLoop = false;
		//sprite->setTexture("bird.png");
		//danger = false;
		auto position = sprite->getPosition();
		position.x -= 125 * delta;
		if (position.x < 0 - (sprite->getBoundingBox().size.width / 2))
		{
			if (sprite->isVisible() && !danger)
			{
				auto glView = static_cast<cocos2d::GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView());
				auto buffer = experimental::FrameBuffer::getOrCreateDefaultFBO(glView);
				buffer->setClearColor(Color4F(1.0f, 1.0f, 1.0f, 0.5f));

				lives--;
				std::ostringstream o;
				o << "Pigs Left: " << lives;
				livesLabel->setString(o.str());
			}
			else
			{
				sprite->setVisible(true);
			}
			int randPos = rand() % 250 + 20;
			position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width / 2;
			position.y = randPos;
			oneLoop = true;
			auto glView = static_cast<cocos2d::GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView());
			auto buffer = experimental::FrameBuffer::getOrCreateDefaultFBO(glView);
			buffer->setClearColor(Color4F(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();

			if (position.y > visibleSize.height/1.25)
			{
				elevating = false;
				delevating = true;
				log("Position Max");
			}
			if (position.y <= 0)
			{
				delevating = false;
				elevating = true;
				log("Position Zero");
			}
			if(elevating)
			{
				position.y += 125 * delta;
				log("Elevation set true");
			}
			if (delevating)
			{
				position.y -= 125 * delta;
				log("Delevation set true");
			}
			/*log("position: %f", visibleSize.height);*/
			
		}
		sprite->setPosition(position);
		if (lives <= 0)
		{
			ShowCursor(true);
			auto scene = MainMenu::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
		}
	}
}
