#include "BaseComponent.h"

namespace Cherry::GUI {

	void BaseComponent::PreRender() {
		if (!m_Enabled)
			ImGui::BeginDisabled(true);
	}

	void BaseComponent::PostRender() {
		if (!m_Enabled)
			ImGui::EndDisabled();
	}

}