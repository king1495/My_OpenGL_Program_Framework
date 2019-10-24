#pragma once
#include "IProcess.h"

class TestProcess final : public IProcess
{
public:
	TestProcess() 
		:summury(0), maxNum(0)
	{};
	virtual ~TestProcess() {};

	int maxNum;
	int summury;

private:
	// IProcess을(를) 통해 상속됨
	virtual void PreProcess() override;
	virtual void MainProcess() override;
	virtual void PostProcess() override;
};