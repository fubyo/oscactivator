#include "Pool.h"

ScopedPointer<Pool> Pool::instance = 0;
HashMap<String, ObjectValue> Pool::map;

Pool::Pool()
{

}

ScopedPointer<Pool> Pool::Instance()
{
	if (!instance)
		instance = new Pool();
    return instance;
}

bool Pool::contains(String key)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	bool result =  map.contains(key);
	return result;
}

double Pool::getValue(String key)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	return map[key].value;
}

void* Pool::getObject(String key)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	return map[key].object;
}

void Pool::reg(String key, void* object)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	ObjectValue newItem;
	newItem.object = (void*) object;
	newItem.value = 0;

	map.set(key, newItem);
}

void Pool::reg(String key, double value)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	ObjectValue newItem;
	newItem.object = 0;
	newItem.value = value;

	map.set(key, newItem);
}

void Pool::unreg(String key)
{
	const GenericScopedLock<DummyCriticalSection> myScopedLock(map.getLock());

	map.remove(key);
}