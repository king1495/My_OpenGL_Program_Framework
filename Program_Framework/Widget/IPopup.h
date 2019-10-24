#pragma once
#include <string>
#include "ImGui/imgui.h"

class IPopup
{
public:
	IPopup(const std::string& _title = "Popup")
		:popupID(_title)
		, popupFlags(ImGuiWindowFlags_None)
	{};
	virtual ~IPopup() = default;

	virtual void Update() = 0;

	void Render() {
		if (ImGui::BeginPopupModal(popupID.c_str(), NULL, popupFlags)) {
			GuiUpdate();
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
	}

protected:
	std::string popupID;
	ImGuiWindowFlags popupFlags;

	virtual void GuiUpdate() = 0;
};