/*
 * Dialog.h
 *
 *  Created on: 2015.09.28
 *      Author: kerlw
 */

#ifndef DIALOG_H_
#define DIALOG_H_

#include "cocos2d.h"

#include <string>

USING_NS_CC;

class Dialog;
class EventListner;

enum class DialogButtonType {
	DBT_POSITIVE,
	DBT_NEGATIVE,
};

class DialogEventListener {
public:
	virtual ~DialogEventListener() {}

	virtual void onDialogButtonClicked(Dialog* dlg, const DialogButtonType& which) = 0;
	virtual void onDialogDismissed(Dialog* dlg) = 0;
};

class DialogBuilder : public Ref {
public:
	virtual ~DialogBuilder() {}
	static DialogBuilder* create(Node* parent, DialogEventListener* listener = nullptr);

	DialogBuilder* setTitle(const std::string& title) {
		m_strTitle = title;
		return this;
	}
	DialogBuilder* setMessage(const std::string& msg) {
		m_strMessage = msg;
		return this;
	}
	DialogBuilder* setPositiveButton(const std::string& txt, const std::string& res = "") {
		m_strPositive = txt;
		m_strPositiveRes = res;
		return this;
	}
	DialogBuilder* setNegativeButton(const std::string& txt, const std::string& res = "") {
		m_strNegative = txt;
		m_strNegativeRes = res;
		return this;
	}

	DialogBuilder* setPadding(const int& left, const int& top, const int& right, const int& bottom) {
		m_iPaddingLeft = left;
		m_iPaddingTop = top;
		m_iPaddingRight = right;
		m_iPaddingBottom = bottom;
		return this;
	}

	Dialog* build();

private:
	DialogBuilder() : m_pParent(nullptr), m_pListener(nullptr),
		m_iPaddingLeft(0), m_iPaddingTop(0), m_iPaddingRight(0), m_iPaddingBottom(0),
		m_strTitle(""), m_strMessage(""),
		m_strPositive(""), m_strPositiveRes(""),
		m_strNegative(""), m_strNegativeRes("") {
	}

private:
	Node* m_pParent;
	DialogEventListener* m_pListener;

	int m_iPaddingLeft;
	int m_iPaddingRight;
	int m_iPaddingTop;
	int m_iPaddingBottom;
	int m_iGap;

	std::string m_strTitle;
	std::string m_strMessage;
	std::string m_strPositive;
	std::string m_strPositiveRes;
	std::string m_strNegative;
	std::string m_strNegativeRes;
};

class Dialog : public LayerColor {
	friend class DialogBuilder;
public:
	virtual ~Dialog();

	void show() {	this->setVisible(true);		}
	void hide() {	this->setVisible(false); 	}
	void dismiss() {
		this->retain();
		this->removeFromParent();
		if (m_pListener)
			m_pListener->onDialogDismissed(this);
		this->release();
	}
	DialogButtonType result() { return m_eResult; }

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

private:
	Dialog(DialogEventListener* listener);
	void onPositiveButtonClicked(Ref* sender);
	void onNegativeButtonClicked(Ref* sender);

protected:
	DialogButtonType m_eResult;
	DialogEventListener* m_pListener;
};

#endif /* DIALOG_H_ */
