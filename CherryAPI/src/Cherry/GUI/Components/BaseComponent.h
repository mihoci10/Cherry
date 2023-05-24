#pragma once

#include <Cherry/GUI/ImGuiAPI.h>

namespace Cherry::GUI{

	class BaseComponent {
	public:
		virtual ~BaseComponent() = default;

		inline void SetShow(bool show) { m_Show = show; };
		inline bool GetShow() const { return m_Show; };

		inline void SetEnabled(bool enabled) { m_Enabled = enabled; };
		inline bool GetEnabled() const { return m_Enabled; };

		virtual void Render() = 0;

	protected:
		virtual void PreRender();
		virtual void PostRender();

		bool m_Show = true;
		bool m_Enabled = true;
	};
	
}