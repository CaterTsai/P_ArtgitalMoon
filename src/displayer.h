#pragma once

#include "constParameter.h"

template <class T>
class displayer
{
public:
	displayer()
		:_isDisplay(false)
		, _timer(0.0)
		, _duration(1.0)
	{}

	void update(float delta)
	{
		if (_isDisplay)
		{
			_timer -= delta;
			if (_timer < 0.0)
			{
				_isDisplay = false;
			}
		}
	}

	void draw(int x, int y, int width, int height)
	{
		if (!_isDisplay)
		{
			return;
		}

		ofPushStyle();
		ofSetColor(255);
		{
			_data[_type].draw(x, y, width, height);
		}
		ofPopStyle();
	}

	void setDisplay(T type)
	{
		_type = type;
		_isDisplay = true;
		_timer = _duration;
	}

	void add(T type, string path)
	{
		ofImage img;
		if (!img.load(path))
		{
			ofLog(OF_LOG_ERROR, "[displayer::add]Load image failed" + path);
			return;
		}
		if (_data.find(type) == _data.end())
		{
			_data.insert(make_pair(type, img));
		}
	}

	void setDuration(float t)
	{
		_duration = t;
	}
private:
	bool _isDisplay;
	float _timer, _duration;
	T _type;
	map<T, ofImage> _data;
};