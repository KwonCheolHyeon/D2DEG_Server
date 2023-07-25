#include "GameNetString.h"

GameNetString::GameNetString()
{
}

GameNetString::~GameNetString()
{
}



std::wstring GameNetString::AnsiToUniCodeReturn(const std::string& Text)
{
	std::wstring UniCode = L"";
	AnsiToUniCode(Text, UniCode);
	return UniCode;
}

void GameNetString::AnsiToUniCode(const std::string& _Text, std::wstring& _Out)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}

	_Out.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
}

// u8""

void GameNetString::UniCodeToUTF8(const std::wstring& _Text, std::string& _Out)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}

	_Out.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], static_cast<int>(_Out.size()), nullptr, nullptr);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}

}

void GameNetString::AnsiToUTF8(const std::string& _Text, std::string& _Out)
{
	std::wstring WString;

	AnsiToUniCode(_Text, WString);
	UniCodeToUTF8(WString, _Out);
}

std::string GameNetString::AnsiToUTF8Return(const std::string& _Text)
{
	std::wstring WString;
	std::string Result;

	AnsiToUniCode(_Text, WString);
	UniCodeToUTF8(WString, Result);

	return Result;
}

std::wstring GameNetString::StringToWStringReturn(const std::string& _Text)
{
	std::wstring Return;

	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}

	Return.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}

	return Return;
}


bool GameNetString::UTF8ToUniCode(const std::string& _UTF8, std::wstring& _UniCode)
{
	_UniCode.clear();

	int32_t Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_UTF8.c_str(),
		static_cast<int32_t>(_UTF8.size()),
		nullptr, // �̺κ��� nullptr�� �־��ָ� ��ȯ �Լ��� �����ϴ°� �ƴϰ�. ��ȯ���̸� üũ�ϴ� �Լ��� �����Ѵ�.
		0
	);

	if (0 >= Len)
	{
		GameNetDebug::GetLastErrorPrint();
		return false;
	}

	_UniCode.resize(Len);

	Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_UTF8.c_str(),
		static_cast<int32_t>(_UTF8.size()),
		&_UniCode[0],
		Len
	);

	if (0 >= Len)
	{
		GameNetDebug::GetLastErrorPrint();
		return false;
	}

	return true;
}

std::wstring GameNetString::UTF8ToUniCodeReturn(const std::string& _UTF8)
{
	std::wstring Return;
	UTF8ToUniCode(_UTF8, Return);
	return Return;
}

std::string GameNetString::UniCodeToAnsiReturn(const std::wstring& _UniCode)
{
	std::string Return;
	UniCodeToAnsi(_UniCode, Return);
	return Return;
}

bool GameNetString::UniCodeToAnsi(const std::wstring& _UniCode, std::string& _AnsiString)
{
	//_In_ UINT CodePage,
//	_In_ DWORD dwFlags,
//	_In_NLS_string_(cchWideChar) LPCWCH lpWideCharStr,
//	_In_ int cchWideChar,
//	_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR lpMultiByteStr,
//	_In_ int cbMultiByte,
//	_In_opt_ LPCCH lpDefaultChar,
//	_Out_opt_ LPBOOL lpUsedDefaultChar

	int32_t Len = WideCharToMultiByte(
		CP_ACP,
		0,
		_UniCode.c_str(),
		static_cast<int32_t>(_UniCode.size()),
		nullptr,
		0,
		nullptr,
		nullptr
	);


	if (0 >= Len)
	{
		GameNetDebug::GetLastErrorPrint();
		return false;
	}

	_AnsiString.resize(Len);

	Len = WideCharToMultiByte(
		CP_ACP,
		0,
		_UniCode.c_str(),
		static_cast<int32_t>(_UniCode.size()),
		&_AnsiString[0],
		static_cast<int32_t>(_AnsiString.size()),
		nullptr,
		nullptr
	);

	return true;
}

std::string GameNetString::UTF8ToAnsiReturn(const std::string& _UTF8)
{
	std::wstring UniCode;
	if (false == UTF8ToUniCode(_UTF8, UniCode))
	{
		MsgBoxAssert("UTF8 => Ansi ConvertError");
	}
	std::string Return;
	if (false == UniCodeToAnsi(UniCode, Return))
	{
		MsgBoxAssert("UniCode => Ansi ConvertError");
	}
	return Return;
}

std::string GameNetString::Replace(const std::string& _Text, const std::string_view& _OldText, const std::string_view& _ChangeText)
{

	size_t FindIndex = _Text.find(_OldText);

	if (FindIndex == std::string::npos)
	{
		return _Text;
	}

	std::string Text = _Text;
	Text = Text.replace(FindIndex, _OldText.size(), _ChangeText);
	return Text;

	// ".FBX"
	// ".UserFBX"
}