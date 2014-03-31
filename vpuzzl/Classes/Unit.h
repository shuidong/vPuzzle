#ifndef __MENU_UNIT_H__
#define __MENU_UNIT_H__

#include "cocos2d.h"
#include "Block.h"
using namespace cocos2d;

class Unit
{
public:
	int ox;//图片中心点
	int oy;
	int idxOfX;//横纵方块索引
	int idxOfY;

	int dtX;//位移
	int dtY;
	Block * parentBlock;
	CCSprite* mSprite;

	Unit(int x, int y, CCSprite* msprite, int xIdx, int yIdx);
	void setBlock(Block*);
	~Unit(void);
};

#endif