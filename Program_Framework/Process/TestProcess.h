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
	// IProcess��(��) ���� ��ӵ�
	virtual void PreProcess() override;
	virtual void MainProcess() override;
	virtual void PostProcess() override;
};