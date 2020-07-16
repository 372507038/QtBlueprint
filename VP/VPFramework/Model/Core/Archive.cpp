#include "Archive.h"

FArchive::~FArchive()
{
}

bool FArchive::SaveObjects(const QList<UObject*>& Objects)
{
	if (!exists())
	{
		QString FilePath = fileName();
		QDir dir;
		dir.mkpath(FilePath.left(FilePath.lastIndexOf('/')));
	}

	if (!isOpen() && !open(QIODevice::ReadWrite))
	{
		Q_ASSERT(false);
		return false;
	}

	QByteArray Bytes;
	QDataStream Stream(&Bytes, QIODevice::ReadWrite);
	{
		FArchiveHead head(Objects.count());
		Stream << head; //[0]

		for (const auto& pObject : Objects)
		{
			UObjectInfo info = pObject->GetInfo();
			Stream << info; //[1]
			pObject->Serialize(Stream); //[2]
		}
	}
	seek(0);
	resize(0);
	write(Bytes);
	flush();
	return true;
}

bool FArchive::LoadObjects(QList<UObject*>& Objects, IArchiveCreateObject CreateObject)
{
	if (!isOpen() && !open(QIODevice::ReadWrite))
	{
		Q_ASSERT(false);
		return false;
	}

	seek(0);
	QByteArray Bytes = readAll();
	QDataStream Stream(&Bytes, QIODevice::ReadWrite);
	{
		FArchiveHead head;
		Stream >> head; //[0]

		Objects.clear();
		for (qint32 idx = 0; idx < head.ObjCount; idx++)
		{
			UObjectInfo info;
			Stream >> info; //[1]

			UObject *pObject = CreateObject(info);
			pObject->Deserialize(Stream); //[2]

			Objects.append(pObject);
		}
	}
	return true;
}
