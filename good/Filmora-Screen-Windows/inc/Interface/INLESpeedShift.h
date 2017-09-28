/**                                     
 * Copyright (c) 2016 Wondershare.inc   
 * All rights reserved.                 
 *                                      
 *@file  INLESpeedShift.h
 *@brief                                
 *@version 1.0                          
 *@author  yaoyj                       
 *@date    4/24/2017 14:28
 */

#ifndef _H_INLESPEEDSHIFT_H_
#define _H_INLESPEEDSHIFT_H_
                                                         
#include <Guiddef.h>                                                            
#include <objbase.h>    
#include "INLEGraphics.h"
#include "NLEType.h" 

/**
@brief ƽ������Ĺ��ɷ�ʽ
*/
enum eNLESpeedShiftAlgorithm
{
	NLE_SPEED_SHIFT_ALGORITHM_LINEAR = 0, //һ�����Խ���

	NLE_SPEED_SHIFT_ALGORITHM_SINECOSINE, //�����������߽���

	NLE_SPEED_SHIFT_ALGORITHM_PARABOLA, //���������߽���
};

//{3E258317-44F1-D6F7-D312-6B1F7FE08071}
DEFINE_GUID(CLSID_NLESpeedShift, 0x3E258317, 0x44F1, 0xD6F7, 0xD3, 0x12, 0x6B, 0x1F, 0x7F, 0xE0, 0x80, 0x71);                   
//{9223415C-5F2B-6EA1-6FBA-8DEB85C6D886}
DEFINE_GUID(IID_INLESpeedShift, 0x9223415C, 0x5F2B, 0x6EA1, 0x6F, 0xBA, 0x8D, 0xEB, 0x85, 0xC6, 0xD8, 0x86);                         
/**
@brief �ֶα��٣��ڱ��������л�ʱ����ƽ�����䷽ʽ���ɡ�
���ٹ�����֡�ʲ��䣬ͨ��ѹ��������ʱ��ʵ�ֱ���.
���ٷ�����Ƶ���Ҫ˼·Ϊ��
�Ա���ǰ��֡��Ϊx�ᣬ���ʵı����ĵ���Ϊy�ᣬ�����ٶȵı仯����֡�������ߣ�������ߵĻ��־��Ǳ��ٺ��Ӧ��֡����
*/
class INLESpeedShift :public IUnknown
{
public:
	/**
	*@brief ����ƽ�����㷨
	*@param[in] mode ƽ�����㷨ģʽ
	*
	@return ��׼����
	*/
	virtual HRESULT STDMETHODCALLTYPE SetShiftMode(eNLESpeedShiftAlgorithm mode) = 0;

	/**
	@brief ����Դ֡��
	*/
	virtual HRESULT STDMETHODCALLTYPE SetOriginFramerate(NLERational originFramerate) = 0;

	/**
	@brief ���ñ��ٵ�������
	*/
	//virtual HRESULT STDMETHODCALLTYPE SetOriginRange(NLERange range) = 0;

	/**
	@brief ������Ⱦ֡��
	*/
	virtual HRESULT STDMETHODCALLTYPE SetRenderFramerate(NLERational renderFramerate) = 0;
	
	/**
	@brief ���ݱ���������ԭʼ����ʱ��Ĺ�ϵ���ߣ����þ��������ߵĹؼ��㣬�����index������ڣ����޸�
	@param point ���߾����Ĺؼ���		

	@return ��׼����
	@remark �������xֵΪ����ǰ֡��ţ�yֵΪ���ٵı���
	*/
	virtual HRESULT STDMETHODCALLTYPE AddShiftPoint(NLEShiftPoint point) = 0;

	/**
	@brief ��ȡ��������ӵĹؼ���ĸ���
	*/
	virtual HRESULT STDMETHODCALLTYPE GetShiftPointCount(int *pCount) = 0;

	/**
	@brief ɾ��ָ���Ĺؼ���
	@param index ���������õĹؼ�������
	@return ��׼����
	@remark �������xֵΪ����ǰ֡��ţ�yֵΪ���ٵı���
	*/
	virtual HRESULT STDMETHODCALLTYPE DeleteShiftPoint(int index) = 0;

	/**
	@brief �޸Ĺؼ����ֵ���޸�����
	@param index ���������õĹؼ�������
	@return ��׼����
	@remark �������xֵΪ����ǰ֡��ţ�yֵΪ���ٵı���
	*/
	virtual HRESULT STDMETHODCALLTYPE ModifyShiftPoint(NLEShiftPoint point, int index) = 0;	

	/**
	@brief ��ȡ����������ԭʼ����ʱ��Ĺ�ϵ�����ϵĹؼ����б�
	@param pPoints ���߾����ĵ���б�
	@param nMaxPointCount pPoints���ɱ���ĵ�ĸ���
	@param pRealPointCount ʵ�ʱ���ĵ�ĸ���

	@return ��׼����
	@remark �������xֵΪ����ǰ֡��ţ�yֵΪ���ٵı���
	*/
	virtual HRESULT STDMETHODCALLTYPE GetShiftPoints(NLEShiftPoint *pPoints, int nMaxPointCount, int *pRealPointCount) = 0;

	/**
	@brief ��ȡ���ٺ�ָ����֡��ԭʼ���е�֡λ��
	@param nFrameIndex ���ٺ��֡λ��
	@param pOriginFrameIndex [out] ԭʼ���е�֡λ��

	@return ��׼����
	*/
	virtual HRESULT STDMETHODCALLTYPE GetOriginFrameIndex(int nFrameIndex, int *pOriginFrameIndex) = 0;

	/**
	@brief ��ȡԭʼ��ĳһ֡�ڱ���֮������ж�Ӧ��֡λ��
	@param nOriginFrameIndex ԭʼ����֡λ��
	@param pFrameIndex [out] ���ٺ�����е�֡λ��

	@return ��׼����
	*/
	virtual HRESULT STDMETHODCALLTYPE GetRenderFrameIndex(int nOriginFrameIndex, int *pFrameIndex) = 0;

	/**
	@brief ��ȡ���ٺ����֡��
	@param pFrameCount [out] ������֡��
	@return ��׼������
	*/
	virtual HRESULT STDMETHODCALLTYPE GetRenderFrameCount(int *pFrameCount) = 0;
};                                                                              



#endif //_H_INLESPEEDSHIFT_H_
