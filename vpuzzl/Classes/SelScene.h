#ifndef __SEL_SCENE_H__
#define __SEL_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Sel : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuBackCallback(CCObject* pSender);
	virtual void menuHelpCallback(CCObject* pSender);
	virtual void menuSoundPlayCallback(CCObject* pSender);

	void stageAction(float dt);
    // implement the "static node()" method manually
    NODE_FUNC(Sel);
private:
	cocos2d::CCSize winSize;
	cocos2d::CCSprite* pvlogoSprite;
	CCLayer* l_menu_main;
	CCLayer* l_stage_main;
	float stageChoserY;
};

#endif  // __SEL_SCENE_H__
