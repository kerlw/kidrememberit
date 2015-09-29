/*
 * GameController.h
 *
 *  Created on: 2015年5月26日
 *      Author: kerlw
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameController: public Ref {
public:
	enum class SceneType {
		eMainScene,
		eGameScene,
	};

public:
	virtual ~GameController();

	static GameController* getInstance();
	static void destroyInstance();

	void enterScene(const SceneType& eType);
	void leaveScene();

private:
	GameController();
	bool init();
};

#endif /* GAMECONTROLLER_H_ */
