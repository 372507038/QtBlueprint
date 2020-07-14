/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:编译器输出行的日志
**************************************************/
#pragma once

/** (Ivy)这个类表示编译器输出行的日志(错误、警告和信息注释)，每个输出行都可以是丰富的标记化消息
This class represents a log of compiler output lines (errors, warnings, and information notes), each of which can be a rich tokenized message */
class FCompilerResultsLog
{
public:
	FCompilerResultsLog();
	virtual ~FCompilerResultsLog();
};

