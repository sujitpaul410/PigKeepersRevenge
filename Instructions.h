#pragma once
#ifndef __Instructions__
#define ____Instructions____

#include "cocos2d.h"

class Instructions : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//Testing..
	void JumpToMainMenu(cocos2d::Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Instructions);
};


#endif
