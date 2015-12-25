/*
 * Dialog.cpp
 *
 *  Created on: 2015.09.28
 *      Author: kerlw
 */

#include "Dialog.h"

#include "ui/UIButton.h"
#include "ui/UIScale9Sprite.h"

static const char* kDefaultDialogBackground = "dialog_bg.png";
static const char* kDefaultDialogButton = "dialog_btn.png";
static const int kButtonFontSize = 30;
static const int kButtonWidth = 200;
static const int kButtonHeight = 60;

DialogBuilder* DialogBuilder::create(Node* parent, DialogEventListener* listener /*= nullptr*/) {
	DialogBuilder* pRet = new (std::nothrow) DialogBuilder();
	if (pRet) {
		assert(parent);
		pRet->m_pParent = parent;
		pRet->m_pListener = listener;
		pRet->autorelease();
		return pRet;
	}
	return nullptr;
}

Dialog* DialogBuilder::build() {
	if (!m_pParent)
		return nullptr;

	Dialog* pRet = new (std::nothrow) Dialog(m_pListener);
	if (!pRet || !pRet->init())
		return nullptr;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size bodySize = visibleSize - Size(m_iPaddingLeft + m_iPaddingRight, m_iPaddingTop + m_iPaddingBottom);

	pRet->autorelease();
	pRet->setContentSize(visibleSize);
	pRet->setColor(Color3B(0,0,0));
	pRet->setOpacity(188);

	auto body = ui::Scale9Sprite::create(kDefaultDialogBackground);
	body->setCapInsets(Rect(64,64,1,1));
	body->setPreferredSize(bodySize);
	body->setPosition(Vec2(visibleSize.width / 2 + (m_iPaddingLeft - m_iPaddingRight),
							visibleSize.height / 2 + (m_iPaddingBottom - m_iPaddingTop)));

	if (!m_strMessage.empty()) {
		auto label = Label::createWithTTF(m_strMessage, "fonts/Marker Felt.ttf", 120);
		label->setTextColor(Color4B(0x6f, 0x26, 0xf6, 0xff));
		label->setPosition(Vec2(bodySize.width / 2, bodySize.height / 2 + kButtonHeight));
		body->addChild(label);
	}

	int btnCount = 0;
	if (!m_strPositive.empty())
		btnCount++;
	if (!m_strNegative.empty())
		btnCount++;

	if (btnCount > 0) {
		float posX = bodySize.width / btnCount / 2;
		float posY = kButtonHeight;
		if (!m_strPositive.empty()) {
			auto btn = ui::Button::create(kDefaultDialogButton);
			btn->setScale9Enabled(true);
			btn->setCapInsets(Rect(16, 16, 1, 1));
			btn->setTitleText(m_strPositive);
			btn->setTitleFontSize(kButtonFontSize);
			btn->setContentSize(Size(kButtonWidth, kButtonHeight));
			btn->setPosition(Vec2(posX, posY));
			btn->addClickEventListener(CC_CALLBACK_1(Dialog::onPositiveButtonClicked, pRet));

			body->addChild(btn);
			posX += bodySize.width / btnCount;
		}

		if (!m_strNegative.empty()) {
			auto btn = ui::Button::create(kDefaultDialogButton);
			btn->setScale9Enabled(true);
			btn->setCapInsets(Rect(16, 16, 1, 1));
			btn->setTitleText(m_strNegative);
			btn->setTitleFontSize(kButtonFontSize);
			btn->setContentSize(Size(kButtonWidth, kButtonHeight));
			btn->setPosition(Vec2(posX, posY));
			btn->addClickEventListener(CC_CALLBACK_1(Dialog::onNegativeButtonClicked, pRet));

			body->addChild(btn);
		}
	}
	pRet->addChild(body);

	pRet->setPosition(0,0);
	m_pParent->addChild(pRet, 99);

	return pRet;
}

Dialog::Dialog(DialogEventListener* listener)
	: m_eResult(DialogButtonType::DBT_NEGATIVE) , m_pListener(listener) {

	auto l = EventListenerTouchOneByOne::create();
	l->setSwallowTouches(true);

	l->onTouchBegan = CC_CALLBACK_2(Dialog::onTouchBegan, this);
	l->onTouchMoved = CC_CALLBACK_2(Dialog::onTouchMoved, this);
	l->onTouchEnded = CC_CALLBACK_2(Dialog::onTouchEnded, this);
	l->onTouchCancelled = CC_CALLBACK_2(Dialog::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(l, this);

}

Dialog::~Dialog() {
}

void Dialog::onPositiveButtonClicked(Ref* sender) {
	if (m_pListener)
		m_pListener->onDialogButtonClicked(this, DialogButtonType::DBT_POSITIVE);
}

void Dialog::onNegativeButtonClicked(Ref* sender) {
	if (m_pListener)
		m_pListener->onDialogButtonClicked(this, DialogButtonType::DBT_NEGATIVE);

}

bool Dialog::onTouchBegan(Touch *touch, Event *unused_event) {
	return true;
}
void Dialog::onTouchMoved(Touch *touch, Event *unused_event) {
}
void Dialog::onTouchEnded(Touch *touch, Event *unused_event) {
}
void Dialog::onTouchCancelled(Touch *touch, Event *unused_event) {
}
