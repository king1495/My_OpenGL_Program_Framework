#pragma once
#include "IWidget.h"

class CurveFitTest : public IWidget
{
public:
	CurveFitTest(std::wstring _title)
		:IWidget(_title)
	{}
	virtual ~CurveFitTest() {};

	virtual void Update() override;
private:
	virtual void GuiUpdate() override;
};