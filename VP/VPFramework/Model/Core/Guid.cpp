#include "Guid.h"
#include "Combaseapi.h" //(zxf) Win32 API COM

FGuid::FGuid()
	: A(0), B(0), C(0), D(0)
{
}

FGuid FGuid::NewGuid()
{
	FGuid Result;

	/*
	* (zxf) Combaseapi.h Win32 API COM
	* 
	* CoCreateGuid函数调用RPC函数UuidCreate，该函数创建一个GUID（全局唯一的128位整数）。 
	* 当您需要一个绝对唯一的数字并将其用作分布式环境中的永久标识符时，请使用CoCreateGuid。
	* 在非常确定的程度上，此函数返回一个唯一值-在同一系统或任何其他系统（联网）上均不进行其他调用 或不），应返回相同的值。
	* 
	* The CoCreateGuid function calls the RPC function UuidCreate, which creates a GUID, a globally unique 128-bit integer.
	* Use CoCreateGuid when you need an absolutely unique number that you will use as a persistent identifier in a distributed environment.
	* To a very high degree of certainty, this function returns a unique value – no other invocation, on the same or any other system (networked or not),
	* should return the same value.
	*/
	CoCreateGuid((GUID*)&Result);

	return Result;
}
