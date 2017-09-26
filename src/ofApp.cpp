#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	ofSetFrameRate(60);

	_map.setup();
	ofAddListener(_map.artgitalEvent, this, &ofApp::onTouchArtgital);
	ofAddListener(_map.treasureEvent, this, &ofApp::onTouchTreasure);
	setupMessage();
	_timer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float delta = ofGetElapsedTimef() - _timer;
	_timer += delta;

	_map.update(delta);
	updateMessage(delta);
	_liveConn.update(delta);

	handleCommand(_liveConn.getCommand());

}

//--------------------------------------------------------------
void ofApp::draw()
{
	_map.draw(cMapPosition.x, cMapPosition.y, cMapWidth, cMapHeight);
	_map.drawMini(cMapMiniPosition.x, cMapMiniPosition.y, cMapMiniWidth, cMapMiniHeight);
	_map.drawCover(cMapPosition.x, cMapPosition.y, cMapWidth, cMapHeight);
	drawMessage();
	//Debug
	_map.drawInfo(0, 20);
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
	case OF_KEY_UP:
	{
		_map.moveMain(0, -1);
		break;
	}
	case OF_KEY_DOWN:
	{
		_map.moveMain(0, 1);
		break;
	}
	case OF_KEY_LEFT:
	{
		_map.moveMain(-1, 0);
		break;
	}
	case OF_KEY_RIGHT:
	{
		_map.moveMain(1, 0);
		break;
	}
	}
}

//--------------------------------------------------------------
void ofApp::onTouchTreasure(int & id)
{
}

//--------------------------------------------------------------
void ofApp::onTouchArtgital(int & id)
{
	if (id >= 0 && id < 10)
	{
		_map.displayTreature(id);
	}
	else if (id >= 10 && id < 14)
	{
		_map.goback();
	}
	setDisplay((eArtgitalCharacter)id);

}

#pragma region Message
//--------------------------------------------------------------
void ofApp::setupMessage()
{
	
	_message[artgitalJackie] = ofImage("images/msg/jackie.png");
	_message[artgitalAlvin] = ofImage("images/msg/alvin.png");
	_message[artgitalLeoH] = ofImage("images/msg/leoH.png");
	_message[artgitalJames] = ofImage("images/msg/james.png");
	_message[artgitalNora] = ofImage("images/msg/nora.png");
	_message[artgitalJerry] = ofImage("images/msg/jerry.png");
	_message[artgitalWill] = ofImage("images/msg/will.png");
	_message[artgitalJonathan] = ofImage("images/msg/jonathan.png");
	_message[artgitalJoey] = ofImage("images/msg/joey.png");
	_message[artgitalLeoC] = ofImage("images/msg/leoC.png");
	_message[artgitalIan] = ofImage("images/msg/ian.png");
	_message[artgitalStan] = ofImage("images/msg/stan.png");
	_message[artgitalCater] = ofImage("images/msg/cater.png");
	_message[artgitalTina] = ofImage("images/msg/tina.png");
	_message[artgitalVader] = ofImage("images/msg/vader.png");
	_message[artgitalYoncky] = ofImage("images/msg/yoncky.png");
	_message[artgitalAka] = ofImage("images/msg/aka.png");
	_message[artgitalMing] = ofImage("images/msg/ming.png");

	_isDisplay = false;
}

//--------------------------------------------------------------
void ofApp::updateMessage(float delta)
{
	if (_isDisplay)
	{
		_messageTimer -= delta;
		if (_messageTimer <= 0.0)
		{
			_isDisplay = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawMessage()
{
	if (!_isDisplay)
	{
		return;
	}

	ofPushStyle();
	{
		ofSetColor(255);
		_message[_displayType].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		_message[_displayType].draw(cMapPosition, cMapWidth, (float)cMapWidth / _message[_displayType].getWidth() * _message[_displayType].getHeight());
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::setDisplay(eArtgitalCharacter type)
{
	_isDisplay = true;
	_displayType = type;
	_messageTimer = cMessageDisplayTime;
	
}
#pragma endregion

#pragma region Live Conn
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
#pragma endregion




