/*
 * GameScene.h
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameScene: public Layer {
public:
	GameScene();
	virtual ~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init() override;

protected:
};

#endif /* GAMESCENE_H_ */
