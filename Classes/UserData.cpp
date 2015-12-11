/*
 * UserData.cpp
 *
 *  Created on: 2015.09.15
 *      Author: kerlw
 */

#include "UserData.h"

#include <algorithm>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

static UserData* _instance = nullptr;

static const char* KEY_SCORE = "usr_score";
static const char* KEY_CARD_NUMBERS = "card_numbers";
static const char* KEY_CARD_TYPES = "card_types";
static const char* KEY_REM_FACTOR = "rem_factor";
static const char* KEY_REP_FACTOR = "rep_factor";

#define MIN_CARD_NUMBERS 5
#define MAX_CARD_NUMBERS 14

#define MIN_CARD_TYPES  2
#define MAX_CARD_TYPES  9

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
//	log("load user data: %s", str.c_str());

	rapidjson::Document usr;
	usr.Parse<0>(str.c_str());
	if (usr.IsObject()) {
		if (usr.HasMember(KEY_SCORE))
			score = usr[KEY_SCORE].GetUint();
		if (usr.HasMember(KEY_CARD_NUMBERS))
			card_numbers = usr[KEY_CARD_NUMBERS].GetUint();
		if (usr.HasMember(KEY_CARD_TYPES))
			card_types = usr[KEY_CARD_TYPES].GetUint();
		if (usr.HasMember(KEY_REM_FACTOR))
			remember_time_factor = usr[KEY_REM_FACTOR].GetUint();
		if (usr.HasMember(KEY_REP_FACTOR))
			represent_time_factor = usr[KEY_REP_FACTOR].GetUint();
	}

	card_numbers = std::max(card_numbers, (uint8_t) MIN_CARD_NUMBERS);
	card_numbers = std::min(card_numbers, (uint8_t) MAX_CARD_NUMBERS);

	card_types = std::max(card_types, (uint8_t) MIN_CARD_TYPES);
	card_types = std::max(card_types, (uint8_t) (card_numbers / 3));
	card_types = std::min(card_types, (uint8_t) MAX_CARD_TYPES);
	card_types = std::min(card_types, (uint8_t) (card_numbers / 2));
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

void UserData::addScore(const uint16_t& value) {
	uint16_t new_score = score + value;
	if (new_score / 8 != score / 8) {
		remember_time_factor = 0;
		represent_time_factor = 0;
	}
	score = new_score;
}

int UserData::toTheNextDifficulty() {
	if (card_types >= MAX_CARD_TYPES && card_numbers >= MAX_CARD_NUMBERS)
		return -1;

	card_types++;
	if (card_types > MAX_CARD_TYPES || card_types > card_numbers / 2) {
		card_numbers++;
		card_types = std::max(card_numbers / 3, MIN_CARD_TYPES);
	}
	return 0;
}
