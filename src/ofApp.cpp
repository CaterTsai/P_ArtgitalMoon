#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	ofSetFrameRate(60);


	_timer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float delta = ofGetElapsedTimef() - _timer;
	_timer += delta;

	_liveConn.update(delta);

	handleCommand(_liveConn.getCommand());

}

//--------------------------------------------------------------
void ofApp::draw()
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case 'q':
	{
		_liveConn.start();
		break;
	}
	case 'w':
	{
		_liveConn.stop();
		break;
	}
	}
}

//--------------------------------------------------------------
void ofApp::handleCommand(command next)
{
	if (next._eType == eCommand::eCommUnknow)
	{
		return;
	}

	switch (next._eType)
	{
	case eCommand::eCommUp:
	{
		cout << "UP" << endl;
		break;
	}
	case eCommand::eCommDown:
	{
		cout << "DOWN" << endl;
		break;
	}
	case eCommand::eCommLeft:
	{
		cout << "LEFT" << endl;
		break;
	}
	case eCommand::eCommRight:
	{
		cout << "RIGHT" << endl;
		break;
	}
	}
}

