//Ӳ�����������ͷ�ļ�
//֧�֣�cuda / intel / ati
#pragma once

#ifdef	WIN32

#else

#ifndef __stdcall
#define __stdcall 
#endif


#include "typedef.hpp"

#endif


//Ӳ����������
#ifndef __ACCELERATE_TYPE__
#define __ACCELERATE_TYPE__
enum ACCELERATETYPE
{
	HARDWARE_ACCELERATE_NONE = 0, 
	HARDWARE_ACCELERATE_CUDA,
	HARDWARE_ACCELERATE_ATI,
	HARDWARE_ACCELERATE_INTEL,
	HARDWARE_ACCELERATE_NVENC,
	HARDWARE_ACCELERATE_VCE,
	SOFTWARE_ACCELERATE_SYSTEM = 100,//USE SYSTEM ENCODERS
};
#endif //__ACCELERATE_TYPE__

#ifdef __cplusplus
extern "C" {
#endif

// ���fourcc�ڵ�ǰ�Կ����������£��Ƿ����֧��Ӳ������
/* ���÷���:
	 1.createCheckFourccObj 
	 2.SetAcerType
	 3.CheckAcerFormate
	 4.destroyCheckFourccObj

	 �����2 -3 ����

*/

void * __stdcall createCheckFourccObj(void);
BOOL __stdcall SetAcerType(int nAccelerateType, const wchar_t* pszDescript , void * pCheckFourccObj);
BOOL __stdcall CheckAcerFormate(DWORD& dwFileFourCC, DWORD& dwVideoFourCC, DWORD& dwAudioFourCC,void * pCheckFourccObj);
void __stdcall destroyCheckFourccObj(void * pCheckFourccObj);

//
//���亯����ʱ����ϵͳ������滻
//
void * __stdcall createCheckFourccObjEx(void);
BOOL __stdcall SetAcerTypeEx(int nAccelerateType, const wchar_t* pszDescript , void * pCheckFourccObj);
BOOL __stdcall CheckAcerFormateEx(DWORD& dwFileFourCC, DWORD& dwVideoFourCC, DWORD& dwAudioFourCC,void * pCheckFourccObj);
void __stdcall destroyCheckFourccObjEx(void * pCheckFourccObj);

#ifdef __cplusplus
}
#endif