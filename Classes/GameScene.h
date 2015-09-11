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

	virtual void onEnterTransitionDidFinish() override;

protected:
	void showStartCounting();
	void startCountingCallback(float tm);

	void showGameBoard();

protected:
	Label* m_pLabelCounting;
	int m_iCounter;
	float m_fTimeCounter;
};

#endif /* GAMESCENE_H_ */
