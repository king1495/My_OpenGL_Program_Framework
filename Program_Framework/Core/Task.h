#pragma once
#include "OpenGLCore.h"
#include "Widget/CurveFitTest.h"

class Task final : public OpenGLCore
{
public:
	Task() {};
	virtual ~Task() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void GuiRender() override;
	virtual void Destroy() override;

private:
	std::unique_ptr<GUI> pGUI;
};