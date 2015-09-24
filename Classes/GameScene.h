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
class CardBar;
class Puzzle;

USING_NS_CC;

class GameScene: public Layer {
public:
	GameScene();
	virtual ~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init() override;

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

	virtual void onEnterTransitionDidFinish() override;

protected:
	void initGameBoardLayout(int w, int h);

	void showStartCounting();
	void startCountingCallback(float tm);

	void showGameBoard();

	void onRememberTimerDone(float left);
	void onRepresentTimerDone(float left);

	static const int kMaxColumns;

protected:
	Label* m_pLabelCounting;
	CardBar* m_pCardBar;
	Card* m_pSelectedCard;

	int m_iCounter;
	float m_fTimeCounter;
	Puzzle* m_pPuzzle;

	std::vector<Card*> m_vctCards;
};

#endif /* GAMESCENE_H_ */
