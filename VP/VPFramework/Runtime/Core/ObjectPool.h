/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-13
Description:�洢���л��������ָ�룬��������
**************************************************/
#pragma once

#include "Guid.h"
#include <QMap>

class UObject;
class UObjectPool;


#define VPPOOL(KEY)					(UObjectManager::GetPool(KEY))
#define VPPOOL_FIND(KEY, OBJ, TYPE) (dynamic_cast<TYPE*>(VPPOOL(KEY).Find(OBJ)));

class UObjectManager
{
private:
	UObjectManager() {}

public:
	static UObjectManager& GetInstance();
	static UObjectPool& GetPool(const QString& key);
	static UObjectPool& GetPool(const UObject* blueprint);

private:
	QMap<QString, UObjectPool> m_Pools;
};


class UObjectPool
{
public:
	/** ��map��Ӷ����Ѵ���ʱ����false */
	bool Add(UObject *obj);

	/** ��map��Ӷ��󣬷�����ӳɹ����� */
	int Add(QList<UObject*> objs);

	/** ��map�Ƴ����󣬲�ִ��delete������������ʱ����false */
	bool Remove(UObject *obj);

	/** ��mapɾ������ִ��delete������������ʱ����false */
	bool Delete(const FGuid& id);

	/** ��map�в��Ҷ��󣬲�����ʱ����nullpt */
	UObject* Find(const FGuid& id);

	/** ��map�в��Ҷ��󣬲�����ʱ����nullpt */
	QList<UObject*> Find(const QList<FGuid>& ids);

	/** ��map�в��Ҷ��󣬲�����ʱ����nullpt�����ص�һ�����ҵ��Ķ��� */
	UObject* Find(const QString& objType);

	/**  ��ȡ����Object���� */
	QList<UObject*> Get();

	/** ������ж���ִ��delete���� */
	void Clear();

private:
	QMap<FGuid, UObject*> m_Objects;
};

