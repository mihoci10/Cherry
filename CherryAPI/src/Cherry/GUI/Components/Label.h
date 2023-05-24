#pragma once

#include <Cherry/GUI/Components/BaseComponent.h>

namespace Cherry::GUI{

	class Label: public BaseComponent {
	public:
		Label() = default;
		Label(const std::string& text) : m_Text(text) {};

		inline void SetText(const std::string& text) { m_Text = text; };
		inline std::string GetText() const { return m_Text; };

		inline void SetTextColor(const ImVec4& textColor) { m_TextColor = textColor; };
		inline ImVec4 GetTextColor() const { return m_TextColor.value_or(ImGui::GetStyleColorVec4(ImGuiCol_Text)); };

		inline void SetDisabledTextColor(const ImVec4& textColor) { m_DisabledTextColor = textColor; };
		inline ImVec4 GetDisabledTextColor() const { return m_DisabledTextColor.value_or(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)); };

		virtual void Render() override;

	protected:
		virtual void PreRender() override;
		virtual void PostRender() override;

		std::string m_Text = "Label";
		std::optional<ImVec4> m_TextColor;
		std::optional<ImVec4> m_DisabledTextColor;
	};
	
}