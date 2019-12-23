#pragma once
#include <string>
#include "ImGui/imgui.h"

class IPopup
{
public:
	IPopup(const std::string& _title = "Popup")
		:popupID(_title), bOpen(false)
		, popupFlags(ImGuiWindowFlags_None)
	{};
	virtual ~IPopup() = default;

	virtual void Update() = 0;

	void Render() {
		if (bOpen) {
			ImGui::OpenPopup(popupID.c_str());
			bOpen = false;
		}

		if (ImGui::BeginPopupModal(popupID.c_str(), NULL, popupFlags)) {
			GuiUpdate();
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
	}

	std::string& GetName() { return popupID; }

	bool GetisActive() { return bOpen; };
	void SetisActive(const bool& _b) { bOpen = _b; };

protected:
	bool bOpen;
	std::string popupID;
	ImGuiWindowFlags popupFlags;

	virtual void GuiUpdate() = 0;
};