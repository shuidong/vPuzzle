#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


#include "WelcomeScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad)
    {
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
    }
    else if (target == kTargetIphone)
    {
        // iphone
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
       
    }
    else 
    {
        // android, windows, blackberry, linux or mac
        // use 960*640 resources as design resolution size
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
    }

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    

    // create a scene. it's an autorelease object
	CCScene *pScene = Welcome::scene();

	// run
	pDirector->runWithScene(pScene);

    return true;
}
// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
