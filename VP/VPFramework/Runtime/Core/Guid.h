/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:全局唯一ID生成及校验
**************************************************/
#pragma once

#include <QObject>
#include <QDataStream>


/**
 * 实现全局唯一标识符。
 * Implements a globally unique identifier.
 */
struct FGuid
{
public:
    FGuid();

	/** (zxf)创建一个全局唯一标识符 * Returns a new GUID. */
	static FGuid NewGuid();

private:
	/** Holds the first component. */
	quint32 A;
	quint32 B;
	quint32 C;
	quint32 D;

public:
	bool IsValid() const
	{
		return ((A | B | C | D) != 0);
	}

public:
	friend bool operator==(const FGuid& X, const FGuid& Y)
	{
		return ((X.A ^ Y.A) | (X.B ^ Y.B) | (X.C ^ Y.C) | (X.D ^ Y.D)) == 0;
	}
	friend bool operator!=(const FGuid& X, const FGuid& Y)
	{
		return ((X.A ^ Y.A) | (X.B ^ Y.B) | (X.C ^ Y.C) | (X.D ^ Y.D)) != 0;
	}
	friend bool operator<(const FGuid& X, const FGuid& Y)
	{
		return	((X.A < Y.A) ? true : ((X.A > Y.A) ? false :
				((X.B < Y.B) ? true : ((X.B > Y.B) ? false :
				((X.C < Y.C) ? true : ((X.C > Y.C) ? false :
				((X.D < Y.D) ? true : ((X.D > Y.D) ? false : false)))))))); //-V583
	}
	quint32& operator[](qint32 Index)
	{
		switch (Index)
		{
		case 0: return A;
		case 1: return B;
		case 2: return C;
		case 3: return D;
		}
		return A;
	}

	friend QDataStream &operator<<(QDataStream &out, const FGuid &myObj)
	{
		out << myObj.A << myObj.B << myObj.C << myObj.D;
		return out;
	}
	friend QDataStream &operator>>(QDataStream &in, FGuid &myObj)
	{
		in >> myObj.A >> myObj.B >> myObj.C >> myObj.D;
		return in;
	}
};
