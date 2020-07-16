/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-13
Description:存储所有基础对象的指针，单例对象
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
	/** 往map添加对象，已存在时返回false */
	bool Add(UObject *obj);

	/** 往map添加对象，返回添加成功个数 */
	int Add(QList<UObject*> objs);

	/** 从map移除对象，不执行delete析构，不存在时返回false */
	bool Remove(UObject *obj);

	/** 从map删除对象，执行delete析构，不存在时返回false */
	bool Delete(const FGuid& id);

	/** 在map中查找对象，不存在时返回nullpt */
	UObject* Find(const FGuid& id);

	/** 在map中查找对象，不存在时返回nullpt */
	QList<UObject*> Find(const QList<FGuid>& ids);

	/** 在map中查找对象，不存在时返回nullpt，返回第一个查找到的对象 */
	UObject* Find(const QString& objType);

	/**  获取所有Object对象 */
	QList<UObject*> Get();

	/** 清除所有对象，执行delete析构 */
	void Clear();

private:
	QMap<FGuid, UObject*> m_Objects;
};

