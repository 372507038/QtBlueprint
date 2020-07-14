/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:���л����ݣ��浵
**************************************************/
#pragma once

#include "Object.h"
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QVariant>


typedef std::function<UObject*(const UObjectInfo& info)> IArchiveCreateObject;


/**
 * (zxf)�鵵�Ļ��࣬���������ֽ�˳�����Է�ʽ����װ�أ�������������ա�
 * �Զ������л���ʽ
 * Base class for archives that can be used for loading, saving, and garbage
 * collecting in a byte order neutral way.
 */
class FArchive : public QFile
{
public:
	virtual ~FArchive();

public:
	/** �������е�Objects���ļ��� */
	bool SaveObjects(const QList<UObject*>& Objects);
	/** ���ļ��ж�ȡ���ݲ�����Object����Ҫ�ṩ�ӿڴ���Object */
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

