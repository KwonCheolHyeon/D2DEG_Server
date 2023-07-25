#pragma once
#include <vector>
#include <string>

// Ό³Έν :
class GameNetSerializer
{
public:
	// constrcuter destructer
	GameNetSerializer();
	GameNetSerializer(const char* _Data, unsigned int _Size);
	~GameNetSerializer();

	// delete Function
	//GameNetSerializer(const GameNetSerializer& _Other) = delete;
	//GameNetSerializer(GameNetSerializer&& _Other) noexcept = delete;
	//GameNetSerializer& operator=(const GameNetSerializer& _Other) = delete;
	//GameNetSerializer& operator=(GameNetSerializer&& _Other) noexcept = delete;


	unsigned int GetReadOffSet()
	{
		return ReadOffset;
	}

	void ReadOffsetReset()
	{
		ReadOffset = 0;
	}

	unsigned int GetWriteOffSet()
	{
		return WriteOffset;
	}

	void WriteOffsetReset()
	{
		WriteOffset = 0;
	}

	void Reset()
	{
		WriteOffset = 0;
		ReadOffset = 0;
	}

	const std::vector<unsigned char>& GetData() {
		return Data;
	}

	unsigned char* GetDataPtr() {
		return &Data[0];
	}

	const char* GetDataConstPtr() {
		return reinterpret_cast<const char*>(&Data[0]);
	}


	template<typename Type>
	Type GetDataPtrConvert() {
		return reinterpret_cast<Type>(&Data[0]);
	}

	void Write(const void* Data, unsigned int _Size);

	void Read(void* Data, unsigned int _Size);

	void ClearReadData();

	void operator<<(const std::string& _Value);
	void operator<<(const int _Value);
	void operator<<(const unsigned int _Value);
	void operator<<(const uint64_t& _Value);
	void operator<<(const float _Value);

	template<typename T>
	void WriteEnum(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void WriteUserData(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}


	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(uint64_t& _Value);
	void operator>>(float& _Value);

	template<typename T>
	void ReadEnum(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void ReadUserData(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

protected:

private:
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;
	std::vector<unsigned char> Data;

};

