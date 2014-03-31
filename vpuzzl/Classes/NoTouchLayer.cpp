#include "NoTouchLayer.h"

using namespace cocos2d;

bool NoTouchLayer::init(){ 
    if (!this->initWithColor( ccc4(128, 128, 0, 80)) )  
    {  
		return false;  
    }
    setTouchEnabled(true); 
    return true;  
}  

void NoTouchLayer::registerWithTouchDispatcher(){   
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);  
   CCLayer::registerWithTouchDispatcher();  
}
   
bool NoTouchLayer::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent){   
	pPauseBoardMenu = (CCMenu*)this->getChildByTag(0);
	m_bTouchedMenu = ((CCMenu*)pPauseBoardMenu) ->ccTouchBegan(pTouch, pEvent);  
    return true;  
}  
   
void NoTouchLayer::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent){
	if (m_bTouchedMenu) {  
        ((CCMenu*)pPauseBoardMenu)->ccTouchMoved(pTouch, pEvent);  
    } 
}  
  
 
void NoTouchLayer::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent){ 
	if (m_bTouchedMenu) {  
        pPauseBoardMenu->ccTouchEnded(pTouch, pEvent);  
        m_bTouchedMenu = false;  
    }  
}  

void NoTouchLayer::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent){ 
	if (m_bTouchedMenu) {  
		pPauseBoardMenu->ccTouchEnded(pTouch, pEvent);  
		m_bTouchedMenu = false;  
	}  
}  