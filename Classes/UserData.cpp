/*
 * UserData.cpp
 *
 *  Created on: 2015.09.15
 *      Author: kerlw
 */

#include "UserData.h"

#include "cocos2d.h"

USING_NS_CC;

static UserData* _instance = nullptr;

UserData* UserData::getInstance() {
	if (!_instance) {
		_instance = new UserData();
	}
	return _instance;
}

UserData::UserData() {
}

UserData::~UserData() {
}

void UserData::load() {
	if (name.length() == 0)
		return;

	UserDefault::getInstance()->getStringForKey(name.c_str());
}

void UserData::save() {
	if (name.length() == 0)
		return;

	UserDefault::getInstance()->setStringForKey(name.c_str(), "");
}
