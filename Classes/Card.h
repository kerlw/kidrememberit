/*
 * Card.h
 *
 *  Created on: 2015.08.18
 *      Author: kerlw
 */

#ifndef CARD_H_
#define CARD_H_

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

#include <string>

USING_NS_CC;

class Card: public Layer {
public:
	enum class CardType {
		CARD_MIN = 0,
	    CARD_MAX = 8,
		CARD_0 = 0,
		CARD_1 = 1,
		CARD_2 = 2,
		CARD_3 = 3,
		CARD_4 = 4,
		CARD_5 = 5,
		CARD_6 = 6,
		CARD_7 = 7,
		CARD_8 = 8,
	};

	bool init(const CardType& type, bool front);
	virtual ~Card();

	static Card* create(const CardType& type, bool front);

	void flipCard();

	void setClickable(bool enabled);
	const CardType type() { return m_eType; }
	bool isFront() { return m_bFront; }

    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;

    Card* clone();

private:
	Card();

private:
	Sprite* m_pFront;
	Sprite* m_pBack;

	ActionInterval* m_pAnimIn;
	ActionInterval* m_pAnimOut;

	CardType m_eType;
	bool m_bFront;

	bool m_bTouchEnabled;
	EventListenerTouchOneByOne* m_pTouchListener;
};

class CardSlot : public Layer {
public:
	virtual ~CardSlot() {}

	static CardSlot* create(const std::string& file);

	virtual bool init(const std::string& file);

	void setOriginalCardType(const Card::CardType& type) { m_eOriginalType = type;	}

	const Card* getCard() const { return m_pCard;	}
	void setCard(Card* card);

	bool isSetCardCorrectly() {
		if (!m_pCard || m_pCard->type() != m_eOriginalType)
			return false;
		return true;
	};

	bool hitTest(const Vec2& loc);

	virtual void setContentSize(const Size & var) override;

private:
	CardSlot() : m_pBg(nullptr), m_pCard(nullptr) {}

private:
	ui::Scale9Sprite* m_pBg;
	Card* m_pCard;

	Card::CardType m_eOriginalType;

};

#endif /* CARD_H_ */
