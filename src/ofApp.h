#pragma once

#include "ofMain.h"

#include "liveConn.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	void handleCommand(command next);

private:
	liveConn _liveConn;
	float _timer;
};
