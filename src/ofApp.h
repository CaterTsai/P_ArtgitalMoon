#pragma once

#include "constParameter.h"
#include "mapManager.h"
#include "liveConn.h"

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
	void updateMessage(float delta);
	void drawMessage();
	void setDisplay(eArtgitalCharacter type);
	
private:
	bool _isDisplay;
	float _messageTimer;
	eArtgitalCharacter _displayType;
	map<eArtgitalCharacter, ofImage> _message;
#pragma endregion

#pragma region Treasure
public:
	void setupTreasure();
	void updateTreasure(float delta);
	void drawTreasure();
	void setTreasureDisplay(int treasure);

private:
	bool _isTreasureDisplay;
	float _treasureTimer;
	eArtgitalCharacter _displayType;
	map<eArtgitalCharacter, ofImage> _message;
#pragma endregion


#pragma region Live Conn
private:
	void handleCommand(command next);

private:
	liveConn _liveConn;
#pragma endregion


	
};
