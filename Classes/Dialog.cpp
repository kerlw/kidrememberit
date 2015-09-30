/*
 * Dialog.cpp
 *
 *  Created on: 2015.09.28
 *      Author: kerlw
 */

#include "Dialog.h"

#include "ui/UIScale9Sprite.h"

static const char* kDefaultDialogBackground = "dialog_bg.png";
static const char* kDefaultDialogButton = "dialog_btn.png";

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
		return false;

	Dialog* pRet = new (std::nothrow) Dialog();
	if (!pRet)
		return nullptr;

	pRet->autorelease();




	return pRet;
}
