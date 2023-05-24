#include "Label.h"

namespace Cherry::GUI {

	void Label::Render()
	{
		if (!m_Show)
			return;

		PreRender();

		ImGui::Text(m_Text.c_str());

		PostRender();
	}

	void Label::PreRender()
	{
		BaseComponent::PreRender();

		if (m_TextColor.has_value())
			ImGui::PushStyleColor(ImGuiCol_Text, m_TextColor.value());

		if (m_DisabledTextColor.has_value())
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, m_DisabledTextColor.value());
	}

	void Label::PostRender()
	{
		if (m_DisabledTextColor.has_value())
			ImGui::PopStyleColor();

		if (m_TextColor.has_value())
			ImGui::PopStyleColor();

		BaseComponent::PostRender();
	}

}