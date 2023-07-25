#include "GameNetSerializer.h"

GameNetSerializer::GameNetSerializer()
	: WriteOffset(0)
	, ReadOffset(0)
{
	Data.resize(1024);
}

GameNetSerializer::GameNetSerializer(const char* _Data, unsigned int _Size)
	: WriteOffset(0)
	, ReadOffset(0)
{

	Data.resize(_Size);
	memcpy_s(&Data[0], _Size, _Data, _Size);
}

GameNetSerializer::~GameNetSerializer()
{
}

void GameNetSerializer::Read(void* _Data, unsigned int _Size)
{
	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += _Size;
}

void GameNetSerializer::Write(const void* _Data, unsigned int _Size)
{
	if (WriteOffset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2);
	}

	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += _Size;

}

void GameNetSerializer::operator<<(const int _Value)
{
	Write(&_Value, sizeof(int));
}

void GameNetSerializer::operator<<(const float _Value)
{
	Write(&_Value, sizeof(float));
}

void GameNetSerializer::operator<<(const std::string& _Value)
{
	operator<<(static_cast<unsigned int>(_Value.size()));
	Write(reinterpret_cast<const void*>(&_Value[0]), static_cast<unsigned int>(_Value.size()));
}

void GameNetSerializer::operator<<(const unsigned int _Value)
{
	Write(&_Value, sizeof(unsigned int));
}

void GameNetSerializer::operator<<(const uint64_t& _Value)
{
	Write(&_Value, sizeof(uint64_t));
}

void GameNetSerializer::operator>>(std::string& _Value)
{
	int Size;
	operator>>(Size);
	if (0 >= Size)
	{
		return;
	}
	_Value.resize(Size);
	Read(&_Value[0], Size);
}

void GameNetSerializer::operator>>(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameNetSerializer::operator>>(unsigned int& _Value)
{
	Read(&_Value, sizeof(unsigned int));
}

void GameNetSerializer::operator>>(float& _Value)
{
	Read(&_Value, sizeof(float));
}

void GameNetSerializer::operator>>(uint64_t& _Value)
{
	Read(&_Value, sizeof(uint64_t));
}

void GameNetSerializer::ClearReadData()
{
	memcpy_s(&Data[0], WriteOffset, &Data[ReadOffset], WriteOffset - ReadOffset);
	WriteOffset -= ReadOffset;
	ReadOffset = 0;
}