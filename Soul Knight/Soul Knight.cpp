/*
*    Soul Knight Project
*	 Team production only for study and communication.
*	 Team member: Pengjin Wei, Qi Shao, Zefan Lu, Hhengjie Zhang.
*    This file was created by Pengjin Wei on 6/5/2017.
*/

#include "Soul Knight.h"

int object[6074][5260] = { 0 };

Weapon weapon[WEAPONS];
Player knight;              

int timer_1, timer_2, timer_3;
int pause, trans;
int Stage = 1;

void main()
{
	HWND hwnd = GetHWnd();   //��ȡ������
	MSG msg;

	initgraph(window_width, window_height);     //������Ϸ����
	srand((unsigned)time(NULL));

	startup_music();                            //���ֳ�ʼ��
	startup_menu_show();                        //��ʼ����ͣ�˵���ʼ��
	startup_map_show();                         //��ͼ��ʼ��
	startup_weapon_show();						//������Ϣ��ʼ��
	startup_status_show();                      //����״̬��ʼ��
	startup_enemy();							//������Ϣ��ʼ��
	startup_character_show();				    //�����ʼ��
	start_menu();								//��ʾ��ʼ����

	timer_1 = SetTimer(hwnd, 1, 30, (TIMERPROC)timer);     //��ʱ��1�� ����30ms
	timer_2 = SetTimer(hwnd, 2, 30, (TIMERPROC)timer);
	timer_3 = SetTimer(hwnd, 2, 100, (TIMERPROC)timer);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}          //��ʱ���ص���Ϣ����
}

VOID CALLBACK timer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (idEvent == timer_1)
	{
		if (trans == 0)
		{
			cleardevice();
			map_show();
			character_show();
			bullet_show();
			enemy_bullet();
			status_show();
			if (pause == 1)
				pause_menu();
			if (pause == 0) {
				pause_back();
				if (knight.HP > 0) {
					operate_control();
					armor_recover();
				}
			}
		}	
	}
	if (idEvent == timer_2)
	{	
		if (trans == 0)
			operate_select();
	}
	if (idEvent == timer_3)
	{
		if (trans == 1) 
			transform();
	}
}
