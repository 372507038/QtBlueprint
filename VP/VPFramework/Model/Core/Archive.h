/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:序列化数据，存档
**************************************************/
#pragma once

#include "Object.h"
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QVariant>


typedef std::function<UObject*(const UObjectInfo& info)> IArchiveCreateObject;


/**
 * (zxf)归档的基类，可用于以字节顺序中性方式进行装载，保存和垃圾回收。
 * 自定义序列化方式
 * Base class for archives that can be used for loading, saving, and garbage
 * collecting in a byte order neutral way.
 */
class FArchive : public QFile
{
public:
	virtual ~FArchive();

public:
	/** 保存所有的Objects到文件中 */
	bool SaveObjects(const QList<UObject*>& Objects);
	/** 从文件中读取数据并创建Object，需要提供接口创建Object */
	bool LoadObjects(QList<UObject*>& Objects, IArchiveCreateObject CreateObject);
};


struct FArchiveHead
{
	qint32 ObjCount;

	FArchiveHead()
		: FArchiveHead(0)
	{}
	FArchiveHead(qint32 ObjCount_)
		: ObjCount(ObjCount_)
	{}

	friend QDataStream &operator<<(QDataStream &out, const FArchiveHead &myObj)
	{
		out << myObj.ObjCount;
		return out;
	}
	friend QDataStream &operator>>(QDataStream &in, FArchiveHead &myObj)
	{
		in >> myObj.ObjCount;
		return in;
	}
};

