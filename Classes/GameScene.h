/*
 * GameScene.h
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

#include <vector>

class Card;

USING_NS_CC;

class GameScene: public Layer {
public:
	GameScene();
	virtual ~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init() override;

	virtual void onEnterTransitionDidFinish() override;

protected:
	void initGameBoardLayout(int w, int h);

	void showStartCounting();
	void startCountingCallback(float tm);

	void showGameBoard();

protected:
	Label* m_pLabelCounting;
	int m_iCounter;
	float m_fTimeCounter;

	std::vector<Card*> m_vctCards;
};

#endif /* GAMESCENE_H_ */
