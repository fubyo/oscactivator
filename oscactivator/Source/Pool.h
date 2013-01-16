#ifndef __POOL_H__
#define __POOL_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include <string>
using namespace std;

struct ObjectValue
{
	void* object;
	double value;

	ObjectValue()
	{
		object = 0;
		value = 0;
	};
};

class Pool
{
	static Pool* instance;
	Pool();

	static HashMap<String, ObjectValue> map;

public:
	
	static Pool* Instance();
	bool contains(String key);
	double getValue(String key);
	void* getObject(String key);
	void reg(String key,void* object);
	void reg(String key,double value);
	void unreg(String key);
};

#endif