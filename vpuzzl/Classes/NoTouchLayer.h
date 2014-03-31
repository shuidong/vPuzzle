#ifndef __NOTOUCH_SCENE_H__
#define __NOTOUCH_SCENE_H__

#include "cocos2d.h"

class NoTouchLayer : public cocos2d::CCLayerColor{ 
public: 
	bool m_bTouchedMenu; 
	cocos2d::CCMenu* pPauseBoardMenu;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone 
    virtual bool init();   
     
    // implement the "static node()" method manually 
    NODE_FUNC(NoTouchLayer); 
	//static NoTouchLayer::CCLayerColor* node(); 
     
    virtual void registerWithTouchDispatcher(); 
     
    virtual bool ccTouchBegan (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
    virtual void ccTouchMoved (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
    virtual void ccTouchEnded (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
}; 

#endif