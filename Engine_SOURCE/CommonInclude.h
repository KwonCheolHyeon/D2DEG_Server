#pragma once
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <type_traits>
#include <Windows.h>

#define arraysize(a) (sizeof(a) / sizeof(a[0]))

// Enable enum flags:
// https://www.justsoftwaresolutions.co.uk/cplusplus/using-enum-classes-as-bitfields.html

template<typename E>
struct enable_bitmask_operators
{
	static constexpr bool enable = false;
};

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	return static_cast<E>
		(
			static_cast<underlying>(lhs) | static_cast<underlying>(rhs)
			);
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	lhs = static_cast<E>
		(
			static_cast<underlying>(lhs) | static_cast<underlying>(rhs)
			);

	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	return static_cast<E>
		(
			static_cast<underlying>(lhs) & static_cast<underlying>(rhs)
			);
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	lhs = static_cast<E>
		(
			static_cast<underlying>(lhs) & static_cast<underlying>(rhs)
			);

	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	rhs = static_cast<E>
		(
			~static_cast<underlying>(rhs)
			);

	return rhs;
}

template<typename E>
constexpr bool has_flag(E lhs, E rhs)
{
	return (lhs & rhs) == rhs;
}

#ifdef _DEBUG
#include <chrono>
#include <thread>
#define DEBUG_PRINT_INTERVAL_MS 500 // 0.5 second interval
#define DEBUG_PRINT(fmt, ...) \
		do { \
		    static auto lastPrintTime = std::chrono::system_clock::now(); \
		    auto currentTime = std::chrono::system_clock::now(); \
		    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastPrintTime).count() >= DEBUG_PRINT_INTERVAL_MS) { \
		        char Text[256]; \
		        sprintf_s(Text, fmt "\n", __VA_ARGS__); \
		        OutputDebugStringA(Text); \
		        lastPrintTime = currentTime; \
		    } \
		    std::this_thread::yield(); \
		} while (0)

#define MSG_BOX(title, text) do { \
        WCHAR wtext[MAX_PATH]; \
        WCHAR wtitle[MAX_PATH]; \
        MultiByteToWideChar(CP_UTF8, 0, text, -1, wtext, MAX_PATH); \
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, MAX_PATH); \
		WCHAR wmsg[MAX_PATH*2]; \
        wsprintf(wmsg, L"%s\n\nFile: %S\nLine: %d", wtext, __FILE__, __LINE__); \
        MessageBox(NULL, wmsg, wtitle, MB_OK); \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#define MSG_BOX(title, text) ((void)0)
#endif

//#include "yaMath.h"
