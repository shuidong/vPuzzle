#ifndef __MENU_UNIT_H__
#define __MENU_UNIT_H__

#include "cocos2d.h"
#include "Block.h"
using namespace cocos2d;

class Unit
{
public:
	int ox;//ͼƬ���ĵ�
	int oy;
	int idxOfX;//���ݷ�������
	int idxOfY;

	int dtX;//λ��
	int dtY;
	Block * parentBlock;
	CCSprite* mSprite;

	Unit(int x, int y, CCSprite* msprite, int xIdx, int yIdx);
	void setBlock(Block*);
	~Unit(void);
};

#endif