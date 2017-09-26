#pragma once

#include "constParameter.h"
#include "mapManager.h"
#include "liveConn.h"
#include "displayer.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	float _timer;

#pragma region Map
public:
	void onTouchTreasure(int& id);
	void onTouchArtgital(int& id);
private:
	bool _canCtrl;
	mapManager _map;
#pragma endregion

#pragma region message
public:
	void setupMessage();
	
private:
	displayer<eArtgitalCharacter> _message;
#pragma endregion

#pragma region Treasure
public:
	void setupTreasure();

private:
	displayer<eTreature> _treasure;
#pragma endregion


#pragma region Live Conn
private:
	void handleCommand(command next);

private:
	liveConn _liveConn;
#pragma endregion


	
};
