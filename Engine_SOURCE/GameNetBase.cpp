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
			// �ü���� �ذ� ������� �Ѵ�.
			// ������ ��������������
			// ������ �߻��ϴ� ���� ���� �����ϴ�.
			// ���� ��������� �����մϴ�.
			// ���� �ʰ��ϸ鼭 ������.
			LocalFree(message);
		}
	}
}