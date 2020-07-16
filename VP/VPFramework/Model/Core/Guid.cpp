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
	* CoCreateGuid��������RPC����UuidCreate���ú�������һ��GUID��ȫ��Ψһ��128λ�������� 
	* ������Ҫһ������Ψһ�����ֲ����������ֲ�ʽ�����е����ñ�ʶ��ʱ����ʹ��CoCreateGuid��
	* �ڷǳ�ȷ���ĳ̶��ϣ��˺�������һ��Ψһֵ-��ͬһϵͳ���κ�����ϵͳ���������Ͼ��������������� �򲻣���Ӧ������ͬ��ֵ��
	* 
	* The CoCreateGuid function calls the RPC function UuidCreate, which creates a GUID, a globally unique 128-bit integer.
	* Use CoCreateGuid when you need an absolutely unique number that you will use as a persistent identifier in a distributed environment.
	* To a very high degree of certainty, this function returns a unique value �C no other invocation, on the same or any other system (networked or not),
	* should return the same value.
	*/
	CoCreateGuid((GUID*)&Result);

	return Result;
}
