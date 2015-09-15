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

	void load();
	void save();

private:
	UserData();

public:
	std::string name;
	uint16_t score;
};

#endif /* USERDATA_H_ */
