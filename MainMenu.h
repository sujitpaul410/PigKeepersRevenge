#ifndef __Main_Menu_SCENE_H__
#define __Main_Menu_SCENE_H__

#include<cocos2d.h>

class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);

private:

	//Test
	void JumpToGameScene(cocos2d::Ref* sender);

	void Instructions(cocos2d::Ref* sender);
	void About(cocos2d::Ref* sender);
	void ExitButton(cocos2d::Ref* pSender);

};

#endif //__Main_Menu_SCENE_H__

