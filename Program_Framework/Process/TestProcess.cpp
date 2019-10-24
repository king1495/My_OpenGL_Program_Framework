#include "stdafx.h"
#include "TestProcess.h"

void TestProcess::PreProcess()
{
	maxLoop = maxNum;
}

void TestProcess::MainProcess()
{
	summury += currentLoop;
}

void TestProcess::PostProcess()
{
	std::cout << "Result : " << summury << std::endl;
}
