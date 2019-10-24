#include "stdafx.h"
#include "TestWidget.h"

TestWidget::TestWidget(const std::wstring& _title)
	:IWidget(_title)
{
	t0 = 0;

	for (int i = 0; i < 121; ++i) {
		xdata.emplace_back(radians(3.f * i));
		ydata1.emplace_back(1.f * cos(xdata[i]));
		ydata2.emplace_back(1.5f * sin(xdata[i]));
	}

	sPlotter = make_shared<ImGuiPlotter<float>>();
	sAxes1 = make_shared<ImAxes<float>>();
	sAxes2 = make_shared<ImAxes<float>>();
	sPlot1 = make_shared<ImPlot<float>>();
	sPlot2 = make_shared<ImPlot<float>>();

	sPlot1->lineColor = ImColor(1.f, 0.6f, 0.6f, 1.0f);

	sPlot2->lineColor = ImColor(0.6f, 0.6f, 1.0f, 1.0f);
	sPlot2->lineStyle = ImPlotLineStyle_None;
	sPlot2->markerStyle = ImPlotMarkerStyle_Circle;

	sPlot1->SetData(xdata, ydata1);
	sPlot2->SetData(xdata, ydata2);

	sAxes1->axesCoordType = ImPlotCoordType_Cartesian;
	sAxes1->xlim = ImVec2(0, radians(360.f));
	sAxes1->ylim = ImVec2(-2, 2);
	sAxes1->xGridOn = true;
	sAxes1->yGridOn = true;
	sAxes1->xPrecision = 1;
	sAxes1->yPrecision = 1;
	sAxes1->xtickNum = 6;
	sAxes1->ytickNum = 6;
	sAxes1->xlabel = L"X";
	sAxes1->ylabel = L"Y";
	sAxes1->AddImPlot(sPlot1);
	sAxes1->AddImPlot(sPlot2);
	
	sAxes2->axesCoordType = ImPlotCoordType_Polar;
	sAxes2->xlim = ImVec2(-2, 2);
	sAxes2->ylim = ImVec2(-2, 2);
	sAxes2->xGridOn = true;
	sAxes2->yGridOn = true;
	sAxes2->xPrecision = 1;
	sAxes2->yPrecision = 1;
	sAxes2->xtickNum = 6;
	sAxes2->ytickNum = 6;
	sAxes2->xlabel = L"X";
	sAxes2->ylabel = L"Y";
	sAxes2->AddImPlot(sPlot1);
	sAxes2->AddImPlot(sPlot2);

	sPlotter->frameSize = { 600,600 };
	sPlotter->SubPlot(2, 1);
	sPlotter->AddImAxes(sAxes1, 0);
	sPlotter->AddImAxes(sAxes2, 1);
}

void TestWidget::Update()
{
	t0++;
	for (int i = 0; i < xdata.size(); ++i) {
		xdata[i] = radians(3.f * i + t0);
		ydata1[i] = 1.f * cos(xdata[i]);
		ydata2[i] = 1.5f * sin(xdata[i]);
	}

	sAxes1->xlim = { radians(t0), radians(t0 + 360.f) };

	sPlot1->SetData(xdata, ydata1);
	sPlot2->SetData(xdata, ydata2);
}

void TestWidget::GuiUpdate()
{
	using namespace ImGuiKR;
	{
		sPlotter->Render();
	}
}
