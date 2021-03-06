/*
 * UserData.h
 *
 *  Created on: 2015.09.15
 *      Author: kerlw
 */

#ifndef USERDATA_H_
#define USERDATA_H_

#include <stdint.h>
#include <string>

class UserData {
public:
	virtual ~UserData();

	static UserData* getInstance();

	void load();
	void save();

	void addScore(const uint16_t& value);

	/**
	 * @return 0 : success, -1 : no more difficulty level
	 */
	int toTheNextDifficulty();

private:
	UserData();

public:
	std::string name;
	uint16_t score;
	uint8_t card_numbers;
	uint8_t card_types;
	uint8_t represent_time_factor;
	uint8_t remember_time_factor;
};

#endif /* USERDATA_H_ */
