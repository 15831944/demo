/* ### WS@H Project:NLE ### */
#ifndef UNIVERSAL_ANALYTICS_H_
#define UNIVERSAL_ANALYTICS_H_

typedef void* ua_tracker;
typedef void* ua_hit;

/*************************************************
//  Method:			ua_create_tracker
//  Description:	����һ����¼��
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	ua_tracker ��¼�߶���
//  Parameter:   	tracking_id - The tracking ID / web property ID. The format is UA-XXXX-Y.
//  Parameter:   	client_id - This anonymously identifies a particular user, device, or browser instance. this is randomly generated for each particular instance of an application install.
//  Parameter:   	app_name - Specifies the application name.
*************************************************/
ua_tracker __stdcall ua_create_tracker(const char* tracking_id, const char* client_id, const char* app_name);

/*************************************************
//  Method:			ua_create_event_hit
//  Description:	����һ�������¼�
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	ua_hit �¼�����
//  Parameter:   	category - �¼����
//  Parameter:   	action - �¼�����
//  Parameter:   	label - �¼���ǩ��NULL����û�У�
//  Parameter:   	value - �¼���ֵ��<0����û�У�
*************************************************/
ua_hit __stdcall ua_create_event_hit(const char* category, const char* action, const char* label, int value);

/*************************************************
//  Method:			ua_create_screenview_hit
//  Description:	����һ����תҳ���¼�
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	ua_hit �¼�����
//  Parameter:   	screen_name - ��ת��ҳ������
*************************************************/
ua_hit __stdcall ua_create_screenview_hit(const char* screen_name);

/*************************************************
//  Method:			ua_create_timing_hit
//  Description:	����һ����ʱ���¼�
//  Author:			chenming
//  Date:           2015/07/22
//  Returns:       	ua_hit �¼�����
//  Parameter:   	category - ��ʱ�����
//  Parameter:   	variable - ��ʱ������
//  Parameter:   	value - ʱ�䣨���룩
//  Parameter:   	label - ��ǩ����ѡ��NULL����û�У�
*************************************************/
ua_hit __stdcall ua_create_timing_hit(const char* category, const char* variable, int value, const char* label);

/*************************************************
//  Method:			ua_create_socialnetwork_hit
//  Description:	����һ���罻�¼�
//  Author:			chenming
//  Date:           2015/07/27
//  Returns:       	ua_hit �¼�����
//  Parameter:   	network - �罻��������
//  Parameter:   	action - �罻����
//  Parameter:   	target - �罻Ŀ��
*************************************************/
ua_hit __stdcall ua_create_socialnetwork_hit(const char* network, const char* action, const char* target);

/*************************************************
//  Method:			ua_create_exception_hit
//  Description:	����һ���쳣�¼�
//  Author:			chenming
//  Date:           2015/07/28
//  Returns:       	ua_hit �¼�����
//  Parameter:   	description - �쳣���������150�ַ���
//  Parameter:   	fatal - �Ƿ��ش��¹ʣ�1 or 0)
*************************************************/
ua_hit __stdcall ua_create_exception_hit(const char* description, const int fatal);

/*************************************************
//  Method:			ua_tracker_set_app_ver
//  Description:	����Ӧ�ó���汾��
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	ver_name - �汾���ַ���
*************************************************/
void __stdcall ua_tracker_set_app_ver(ua_tracker tracker, const char* ver_name);

/*************************************************
//  Method:			ua_tracker_set_language
//  Description:	����Ӧ�ó�������
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	lang_name - �����ַ���
*************************************************/
void __stdcall ua_tracker_set_language(ua_tracker tracker, const char* lang_name);

/*************************************************
//  Method:			ua_tracker_set_viewport_size
//  Description:	����Ӧ�ó������ߴ�
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	width - ��
//  Parameter:   	height - ��
*************************************************/
void __stdcall ua_tracker_set_viewport_size(ua_tracker tracker, const int width, const int height);

/*************************************************
//  Method:			ua_tracker_set_custom_dimension
//  Description:	�����Զ���ά��
//  Author:			chenming
//  Date:           2015/07/23
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	index - �Զ���ά������(1-20)
//  Parameter:   	value - ά������
*************************************************/
void __stdcall ua_tracker_set_custom_dimension(ua_tracker tracker, const int index, const char* value);

/*************************************************
//  Method:			ua_tracker_set_custom_metric
//  Description:	�����Զ���ָ��
//  Author:			chenming
//  Date:           2015/07/23
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	index - �Զ���ָ������(1-20)
//  Parameter:   	value - ָ����ֵ
*************************************************/
void __stdcall ua_tracker_set_custom_metric(ua_tracker tracker, const int index, const int value);

/*************************************************
//  Method:			ua_send_hit
//  Description:	����һ���¼�
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
//  Parameter:   	hit - ʱ�����
*************************************************/
void __stdcall ua_send_hit(ua_tracker tracker, ua_hit hit);

/*************************************************
//  Method:			ua_destroy_tracker
//  Description:	���ټ�¼����
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	tracker - ��¼����
*************************************************/
void __stdcall ua_destroy_tracker(ua_tracker tracker);

/*************************************************
//  Method:			ua_destroy_hit
//  Description:	�����¼�
//  Author:			chenming
//  Date:           2015/07/17
//  Returns:       	void __stdcall
//  Parameter:   	hit - �¼�����
*************************************************/
void __stdcall ua_destroy_hit(ua_hit hit);


#endif //UNIVERSAL_ANALYTICS_H_