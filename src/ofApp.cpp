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
	setupTreasure();
	_timer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float delta = ofGetElapsedTimef() - _timer;
	_timer += delta;

	_map.update(delta);
	_message.update(delta);
	_treasure.update(delta);
	_liveConn.update(delta);

	handleCommand(_liveConn.getCommand());

}

//--------------------------------------------------------------
void ofApp::draw()
{
	_map.draw(cMapPosition.x, cMapPosition.y, cMapWidth, cMapHeight);
	_map.drawMini(cMapMiniPosition.x, cMapMiniPosition.y, cMapMiniWidth, cMapMiniHeight);
	_map.drawCover(cMapPosition.x, cMapPosition.y, cMapWidth, cMapHeight);
	_message.draw(cMapPosition.x, cMapPosition.y, cMessageWidth, cMessageHeight);
	_treasure.draw(cMapPosition.x, cMapPosition.y, cTreatureWidth, cTreatureHeight);

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
	_treasure.setDisplay((eTreature)id);
	_map.getTreature(id);
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

	_message.setDisplay((eArtgitalCharacter)id);

}

#pragma region Message
//--------------------------------------------------------------
void ofApp::setupMessage()
{
	_message.add(artgitalJackie, "images/msg/jackie.png");
	_message.add(artgitalAlvin, "images/msg/alvin.png");
	_message.add(artgitalLeoH, "images/msg/leoH.png");
	_message.add(artgitalJames, "images/msg/james.png");
	_message.add(artgitalNora, "images/msg/nora.png");
	_message.add(artgitalJerry, "images/msg/jerry.png");
	_message.add(artgitalWill, "images/msg/will.png");
	_message.add(artgitalJonathan, "images/msg/jonathan.png");
	_message.add(artgitalJoey, "images/msg/joey.png");
	_message.add(artgitalLeoC, "images/msg/leoC.png");
	_message.add(artgitalIan, "images/msg/ian.png");
	_message.add(artgitalStan, "images/msg/stan.png");
	_message.add(artgitalCater, "images/msg/cater.png");
	_message.add(artgitalTina, "images/msg/tina.png");
	_message.add(artgitalVader, "images/msg/vader.png");
	_message.add(artgitalYoncky, "images/msg/yoncky.png");
	_message.add(artgitalAka, "images/msg/aka.png");
	_message.add(artgitalMing, "images/msg/ming.png");
	_message.setDuration(cMessageDisplayTime);
}
#pragma endregion

#pragma region Treature
//--------------------------------------------------------------
void ofApp::setupTreasure()
{
	_treasure.add(treatrue1, "images/treasure/1.png");
	_treasure.add(treatrue2, "images/treasure/2.png");
	_treasure.add(treatrue3, "images/treasure/3.png");
	_treasure.add(treatrue4, "images/treasure/4.png");
	_treasure.add(treatrue5, "images/treasure/5.png");
	_treasure.setDuration(cTreatureDisplayTime);
}
#pragma endregion


#pragma region Live Conn
//--------------------------------------------------------------
void ofApp::handleCommand(command next)
{
	if (next._eType == eCommand::eCommUnknow || !_canCtrl)
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




