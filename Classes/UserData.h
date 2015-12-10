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

private:
	UserData();

public:
	std::string name;
	uint16_t score;
	uint8_t represent_time_factor;
	uint8_t remember_time_factor;
};

#endif /* USERDATA_H_ */
