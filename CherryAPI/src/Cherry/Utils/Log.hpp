#pragma once

#include <Cherry/RendererAPI.h>

namespace Cherry {

	class StringFormatter {
	public:
		static std::string format(const char* text, ...) {
			va_list args;

			va_start(args, text);
			std::string result = formatInternal(text, args);
			va_end(args);

			return result;
		};
	private:
		inline static std::string formatInternal(const char* text, va_list args) {
			int nLength = _vscprintf(text, args) + 1;
			char* sMessage = new char[nLength];

			vsprintf_s(sMessage, nLength, text, args);
			std::string result = std::string(sMessage);

			delete[] sMessage;
			return result;
		}
	};

	#define CHERRY_DISPATCH_LOG(renderer, severity, description) { auto settings = renderer->GetRendererSettings(); \
			if(settings.logCallback) settings.logCallback(severity, description, Cherry::StringFormatter::format("%s in %s at line: %d", __FUNCTION__, __FILE__, __LINE__));}
	#define CHERRY_DISPATCH_LOG_LOC(renderer, severity, description, location) { auto settings = renderer->GetRendererSettings(); \
			if(settings.logCallback) settings.logCallback(severity, description, location);}

	#define CHERRY_TRACE(...)		CHERRY_DISPATCH_LOG(0, Cherry::StringFormatter::format(__VA_ARGS__))
	#define CHERRY_LOG(...)			CHERRY_DISPATCH_LOG(1, Cherry::StringFormatter::format(__VA_ARGS__))
	#define CHERRY_WARNING(...)		CHERRY_DISPATCH_LOG(2, Cherry::StringFormatter::format(__VA_ARGS__))
	#define CHERRY_ERROR(...)		CHERRY_DISPATCH_LOG(3, Cherry::StringFormatter::format(__VA_ARGS__))
	#define CHERRY_CRITICAL(...)	CHERRY_DISPATCH_LOG(4, Cherry::StringFormatter::format(__VA_ARGS__))

	#define CHERRY_THROW(...)		throw std::exception(Cherry::StringFormatter::format(__VA_ARGS__).c_str())
}