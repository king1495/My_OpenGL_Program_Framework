#include "stdafx.h"
#include "TestPopup.h"

void TestPopup::Update()
{
}

void TestPopup::GuiUpdate()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Dummy menu item")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

	// Testing behavior of widgets stacking their own regular popups over the modal.
	static int item = 1;
	static float color[4] = { 0.4f,0.7f,0.0f,0.5f };
	ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
	ImGui::ColorEdit4("color", color);

	if (ImGui::Button("Add another modal.."))
		ImGui::OpenPopup("Stacked 2");

	// Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which will close the popup.
	// Note that the visibility state of popups is owned by imgui, so the input value of the bool actually doesn't matter here.
	bool dummy_open = true;
	if (ImGui::BeginPopupModal("Stacked 2", &dummy_open))
	{
		ImGui::Text("Hello from Stacked The Second!");
		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
