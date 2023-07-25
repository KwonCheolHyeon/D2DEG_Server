#include "GameNetBase.h"
#include <string>

namespace GameNetDebug
{
	void GetLastErrorPrint()
	{
		DWORD error = GetLastError();
		char* message = nullptr;

		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&message,
			0,
			nullptr);

		if (nullptr != message)
		{
			std::string Text = "Code : ";
			Text += std::to_string(error);
			Text += " Message : ";
			Text += message;

			MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK);
			// 운영체제가 준건 해제헤야 한다.
			// 서버면 더더더더더더욱
			// 실행중 발생하는 릭이 가장 위험하다.
			// 힙이 비대해지기 시작합니다.
			// 램을 초과하면서 터진다.
			LocalFree(message);
		}
	}
}