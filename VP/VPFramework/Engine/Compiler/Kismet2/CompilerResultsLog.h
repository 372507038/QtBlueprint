/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:����������е���־
**************************************************/
#pragma once

/** (Ivy)������ʾ����������е���־(���󡢾������Ϣע��)��ÿ������ж������Ƿḻ�ı�ǻ���Ϣ
This class represents a log of compiler output lines (errors, warnings, and information notes), each of which can be a rich tokenized message */
class FCompilerResultsLog
{
public:
	FCompilerResultsLog();
	virtual ~FCompilerResultsLog();
};

