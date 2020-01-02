#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include<cocos2d.h>

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onMouseDown(cocos2d::Event *ev);
	void onMouseMove(cocos2d::Event *ev);

	CREATE_FUNC(GameScene);

	void update(float) override;


private:
	cocos2d::Sprite* sprite;
	cocos2d::Label* scoreLabel;
	int score;
	bool danger;
	bool oneLoop;
	int lives;
	cocos2d::Label* livesLabel;
	bool elevating, delevating;

};

#endif //__Game_SCENE_H__