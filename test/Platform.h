//
// Created by koncord on 23.01.16.
//

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#ifdef _MSC_VER
#ifdef _M_X86
#define ARCH_X86
#endif
#endif

#ifdef __GNUC__
#ifdef __i386__
#define ARCH_X86
#endif
#endif

#if defined _WIN32 && !defined _GENFFI
#ifndef CDECL
#define CDECL __cdecl
#endif
#else
#define CDECL
#endif

#if defined __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

#if defined _WIN32
#define IMPORT_FUNCTION EXTERN __declspec(dllimport)
#define EXPORT_FUNCTION EXTERN __declspec(dllexport)
#else
#define EXPORT_FUNCTION EXTERN __attribute__ ((visibility ("default")))
#define IMPORT_FUNCTION EXTERN
#endif

#if defined _GENFFI
#define API_FUNCTION
#elif !defined _HOST
#define API_FUNCTION IMPORT_FUNCTION
#else
#define API_FUNCTION EXPORT_FUNCTION
#endif // _GENFFI

#if defined __cplusplus
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END() }
#define NOEXCEPT noexcept
#else
#define NAMESPACE_BEGIN(name)
#define NAMESPACE_END()
#define NOEXCEPT
#endif

#endif //PLATFORM_HPP
