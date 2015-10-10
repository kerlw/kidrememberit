/*
 * GameScene.h
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "Dialog.h"

#include <vector>

class Card;
class CardSlot;
class CardBar;
class Puzzle;

USING_NS_CC;

class GameScene: public Layer, DialogEventListener {
public:
	GameScene();
	virtual ~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init() override;

	void menuBackCallback(Ref* pSender);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

	virtual void onDialogButtonClicked(Dialog* dlg, const DialogButtonType& which) override;
	virtual void onDialogDismissed(Dialog* dlg) override;

	virtual void onEnterTransitionDidFinish() override;

protected:
	void initGameBoardLayout(int w, int h);

	void showStartCounting();

	void startCountingCallback(float delta);
	void countdownTimerCallback(float delta);

	void showGameBoard();

	void onRememberTimerDone(float left);
	void onRepresentTimerDone(float left);

	static const int kMaxColumns;

protected:
	Label* m_pLabelCounting;
	ProgressTimer* m_pProgressTimer;
	CardBar* m_pCardBar;
	Card* m_pSelectedCard;

	enum {
		UNKNONW_TIMER,
		READYGO_TIMER,
		REMEMBER_TIMER,
		REPRESENT_TIMER,
	} m_eTimerType;

	int m_iCounter;
	float m_fTimeCounter;
	Puzzle* m_pPuzzle;

	std::vector<Card*> m_vctCards;
	std::vector<CardSlot*> m_vctSlots;

	bool m_bInRepresentStage;
};

#endif /* GAMESCENE_H_ */
