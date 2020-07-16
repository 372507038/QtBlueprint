#include "ObjectPool.h"
#include "Object.h"


UObjectManager& UObjectManager::GetInstance()
{
	static UObjectManager Instance;
	return Instance;
}

UObjectPool& UObjectManager::GetPool(const QString& key)
{
	Q_ASSERT(!key.isEmpty());
	return GetInstance().m_Pools[key];
}

UObjectPool& UObjectManager::GetPool(const UObject* blueprint)
{
	Q_ASSERT(blueprint);
	return GetInstance().m_Pools[blueprint->GetObjectName()];
}


bool UObjectPool::Add(UObject * obj)
{
	Q_ASSERT(obj != nullptr && obj->GetObjectGuid().IsValid());

	auto ite = m_Objects.find(obj->GetObjectGuid());
	if (ite != m_Objects.end())
	{
		Q_ASSERT(false);
		return false;
	}

	m_Objects.insert(obj->GetObjectGuid(), obj);
	return true;
}

int UObjectPool::Add(QList<UObject*> objs)
{
	int count = 0;
	for (auto obj : objs)
	{
		if (Add(obj))
			count++;
	}
	return count;
}

bool UObjectPool::Remove(UObject * obj)
{
	Q_ASSERT(obj != nullptr && obj->GetObjectGuid().IsValid());

	auto ite = m_Objects.find(obj->GetObjectGuid());
	if (ite == m_Objects.end())
	{
		Q_ASSERT(false);
		return false;
	}

	m_Objects.erase(ite);
	return true;
}

bool UObjectPool::Delete(const FGuid & id)
{
	Q_ASSERT(id.IsValid());

	auto ite = m_Objects.find(id);
	if (ite == m_Objects.end())
	{
		Q_ASSERT(false);
		return false;
	}

	delete ite.value();
	m_Objects.erase(ite);
	return true;
}

UObject * UObjectPool::Find(const FGuid & id)
{
	Q_ASSERT(id.IsValid());

	auto ite = m_Objects.find(id);
	if (ite == m_Objects.end())
	{
		Q_ASSERT(false);
		return nullptr;
	}

	return ite.value();
}

QList<UObject*> UObjectPool::Find(const QList<FGuid>& ids)
{
	QList<UObject*> objs;
	for (const FGuid& id : ids)
	{
		objs.append(Find(id));
	}
	return objs;
}

UObject * UObjectPool::Find(const QString & objType)
{
	for (auto ite = m_Objects.begin(); ite != m_Objects.end(); ite++)
	{
		if (ite.value()->GetObjectType() == objType)
			return ite.value();
	}

	Q_ASSERT(false);
	return nullptr;
}

QList<UObject*> UObjectPool::Get()
{
	QList<UObject*> objs;
	for (auto ite = m_Objects.begin(); ite != m_Objects.end(); ite++)
	{
		objs.append(ite.value());
	}
	return objs;
}

void UObjectPool::Clear()
{
	auto ite = m_Objects.begin();
	while (ite != m_Objects.end())
	{
		delete ite.value();
		ite = m_Objects.erase(ite);
	}
}
