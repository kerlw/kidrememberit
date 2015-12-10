/*
 * UserData.cpp
 *
 *  Created on: 2015.09.15
 *      Author: kerlw
 */

#include "UserData.h"

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

static UserData* _instance = nullptr;

static const char* KEY_SCORE = "usr_score";
static const char* KEY_REM_FACTOR = "rem_factor";
static const char* KEY_REP_FACTOR = "rep_factor";

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

	score = 0;
	remember_time_factor = 0;
	represent_time_factor = 0;

	const std::string str = UserDefault::getInstance()->getStringForKey(name.c_str(), "");
	rapidjson::Document usr;
	usr.Parse<0>(str.c_str());
	if (usr.IsObject()) {
		if (usr.HasMember(KEY_SCORE))
			score = usr[KEY_SCORE].GetUint();
		if (usr.HasMember(KEY_REM_FACTOR))
			remember_time_factor = usr[KEY_REM_FACTOR].GetUint();
		if (usr.HasMember(KEY_REP_FACTOR))
			represent_time_factor = usr[KEY_REP_FACTOR].GetUint();
	}
}

void UserData::save() {
	if (name.length() == 0)
		return;

	rapidjson::Document usr;
	usr.SetObject();
	rapidjson::Document::AllocatorType& allocator = usr.GetAllocator();
	usr.AddMember(KEY_SCORE, score, allocator);
	usr.AddMember(KEY_REM_FACTOR, remember_time_factor, allocator);
	usr.AddMember(KEY_REP_FACTOR, represent_time_factor, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	usr.Accept(writer);
	UserDefault::getInstance()->setStringForKey(name.c_str(), buffer.GetString());
}

