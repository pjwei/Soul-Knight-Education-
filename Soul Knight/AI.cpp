#include "AI.h"

void melee_AI(int spc, int num) {
	//�Թ���Ϊ���Ľ�������ϵ������Ϊx������������Ϊy�������򣨼�Ĭ��ͼ������ϵ��

	int dir;							//����ѭ������
	int dx;								//���ﵽ����ж����ĺ���������
	int dy;								//���ﵽ����ж���������������
	double distance;					//���������֮��ľ���
	double cosarc;						//���ﵽ��Ҽн�����ֵ
	double sinarc;						//���ﵽ��Ҽн�����ֵ
	double arc;							//���ﵽ��Ҽнǣ���Χ [0, 2PI)
	double marc;						//�н�ƫ��ֵ
	int action;							//��Ϊ�жϲ���
	int	move;							//�ƶ��жϲ���
	int attack;							//�����жϲ���
	int	mx;								//�����ƶ�����
	int my;								//�����ƶ�����
	static int backx;					//������˾����¼
	static int backy;					//������˾����¼
	int Eleft, Eright, Etop, Ebottom;   //���ﵱǰ�ڴ������ж����ķ�������
	POINT Ecenter;                      //���ﵱǰ�ڴ��������ĵ�����

	Eleft = enemy[spc].num[num].x - map.x + enemy[spc].pic_left;
	Eright = enemy[spc].num[num].x - map.x + enemy[spc].pic_right;
	Etop = enemy[spc].num[num].y - map.y + enemy[spc].pic_top;
	Ebottom = enemy[spc].num[num].y - map.y + enemy[spc].pic_bottom;    
	Ecenter.x = (Eleft + Eright) / 2;
	Ecenter.y = (Etop + Ebottom) / 2;

	dx = character_position.x - (enemy[spc].num[num].x - map.x);
	dy = character_position.y - (enemy[spc].num[num].y - map.y);
	distance = sqrt(dx * dx + dy * dy);										  

	if (distance > 0 && enemy[spc].num[num].HP > 0) {
		cosarc = dx / distance;												  
		sinarc = dy / distance;												  	
		if (dy >= 0) arc = acos(cosarc);
		else arc = 2 * PI - acos(cosarc);	

		if (dy >= 0) enemy[spc].num[num].spin = 2 * PI - acos(cosarc) - PI / 2;
		else enemy[spc].num[num].spin = acos(cosarc) - PI / 2;
		if (enemy[spc].num[num].spin < 0) enemy[spc].num[num].spin += 2 * PI;

		if (enemy[spc].num[num].pic_x == 3)
			enemy[spc].num[num].pic_x = 0;									  //��Ϊͼ�ֻ�

		//δ�������																  
		if (!isdetected(spc, num)) {
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 2;										  //���������Ϊ

			//Լ1/2���ʽ���˼����Ϊ
			if (action == 0) {												  
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 21 + 30;		  //���˼��ʱ��30~50 * 30ms = 0.9~1.5s

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect;       //�л���վ��ͼ״̬��
				if (enemy[spc].num[num].think == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�վ��ͼ					
				}

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ
			else {															  
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 111 + 30;		  //����ƶ�ʱ��30~140 * 30ms = 0.9~4.2s
				move = rand() % 100 + 1;
				for (dir = 0; dir < 5; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 36; break;
						case 2:move = 61; break;
						case 3:move = 81; break;
						case 4:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

				//�����ʵݼ��ķ�ʽ������·�������·�����о���															  
				if (move >= 1 && move <= 35) {								  //35%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}															  
				else if (move >= 36 && move <= 60) {						  //25%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}															  
				else if (move >= 61 && move <= 80) {						  //20%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}															  
				else if (move >= 81 && move <= 95) {						  //15%������ (PI/2,3PI/4] ƫ�ΧС������
					if (rand() % 2) marc = (rand() % 5 + 11) * PI / 20;
					else marc = -(rand() % 5 + 11) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[3] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[3]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[3] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}															  
				else {														  //5%������ (3PI/4,PI] ƫ�Χ�������
					if (rand() % 2) marc = (rand() % 5 + 16) * PI / 20;
					else marc = -(rand() % 5 + 16) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[4] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[4]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[4] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}															  
				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}
																			
				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect + 2;   //�л�������ͼ״̬��
				if (enemy[spc].num[num].move == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�����ͼ
				}

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}

		//�������																  
		else {																  
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 2;										  //���������Ϊ

			if (enemy[spc].num[num].attack_time != 0) {						  //��鹥����ȴ
				if (enemy[spc].num[num].attack_cnt == enemy[spc].num[num].attack_time) {
					enemy[spc].num[num].attack_cnt = 0;
					enemy[spc].num[num].attack_time = 0;					  //������ȴ���ڽ���
				}
				else enemy[spc].num[num].attack_cnt++;						  //������ȴ���ڼ���
			}

			//Լ1/2���ʽ���˼����Ϊ
			if (action == 0) {												  
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 21 + 20;		  //���˼��ʱ��20~40 * 30ms = 0.6~1.2s

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect;       //�л���վ��ͼ״̬��
				if (enemy[spc].num[num].think == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�վ��ͼ					
				}

				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ																  
			else {															  
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 111 + 60;		  //����ƶ�ʱ��60~140 * 30ms = 1.8~4.2s
				move = rand() % 100 + 1;
				for (dir = 0; dir < 3; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 51; break;
						case 2:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

				//�����ʵݼ��ķ�ʽ������ǰ��·�������ǰ��·�����о���															  
				if (move >= 1 && move <= 50) {								  //50%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 51 && move <= 80) {						  //30%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else {													      //20%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}

				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0; 
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}
				//����������ж���Ӵ�
				if (((int)(fabs(Ecenter.x + mx - knight.center.x)) <= (60 - enemy[spc].pic_left + knight.center.x - knight.left))
					&& ((int)(fabs(Ecenter.y + my - knight.center.y)) <= (60 - enemy[spc].pic_top + knight.center.y - knight.top)))																		  	
				{
					attack = rand() % 2;

					//1/2���ʽ��й���
					if (attack == 0 && enemy[spc].num[num].attack_cnt == 0 && knight.HP >0)   
					{ 
						enemy[spc].num[num].attack_time = rand() % 31 + 40;   //���������ȴʱ��40~70 * 30ms = 1.2~2.1s														  
						if (knight.AM > 0) {
							if (enemy[spc].damage > knight.AM)knight.AM = 0;
							else knight.AM -= enemy[spc].damage;			  //������ʧ�ж�
						}
						else if (knight.HP > 0) {
							if (enemy[spc].damage > knight.HP)knight.HP = 0;
							else knight.HP -= enemy[spc].damage;			  //HP��ʧ�ж�
						}
						player_damaged = 1;									  //��ұ����ж�
																			  //��ұ�����Ч
						mciSendString(_T("close resource\\player_hurt.wav"), NULL, 0, NULL);
						mciSendString(_T("play resource\\player_hurt.wav"), NULL, 0, NULL);
																			
						armor_cnt = 0;										  //���׻ظ���ʱ����
						//��ɫ�ܵ��������
						if (mx > 0 && object[map.x + 2 * speed + knight.right][map.y + knight.top] == FLOOR
							&& object[map.x + 2 * speed + knight.right][map.y + knight.bottom] == FLOOR)
							map.x += 2 * speed;
						else if (mx < 0 && object[map.x - 2 * speed + knight.left][map.y + knight.top] == FLOOR
							&& object[map.x - 2 * speed + knight.left][map.y + knight.bottom] == FLOOR)
							map.x -= 2 * speed;
						if (my > 0 && object[map.x + knight.left][map.y + 2 * speed + knight.bottom] == FLOOR
							&& object[map.x + knight.right][map.y + 2 * speed + knight.bottom] == FLOOR)
							map.y += 2 * speed;
						else if (my < 0 && object[map.x + knight.left][map.y - 2 * speed + knight.top] == FLOOR
							&& object[map.x + knight.right][map.y - 2 * speed + knight.top] == FLOOR)
							map.y -= 2 * speed;
																			  //�����ж���·�Ƿ�����ײ
						mx = 0;
						my = 0;												  //���ƶ�
					}

					//2/3���ʻ���
					else {													  
						if (enemy[spc].num[num].back_cnt == 0) {
							backx = -mx;
							backy = -my;									  //��¼���˷���
							enemy[spc].num[num].direction_cnt = 0;			  //��������ƶ����ڼ���
							for (dir = 0; dir < 5; dir++)
								enemy[spc].num[num].direction_time[dir] = 0;  //���ǰ���������ڼ���
							enemy[spc].num[num].back_time = rand() % 21 + 20; //�������ʱ��20~40 * 30ms = 0.6~1.2s
							enemy[spc].num[num].is_cnt = 0;
							enemy[spc].num[num].think_time = 0;
							enemy[spc].num[num].move_time = 0;				  //�����������
						}
						mx = backx;
						my = backy;

						if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
							|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
							|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
							|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
						{
							mx = 0;
							my = 0;
							enemy[spc].num[num].back_cnt = 0;
							enemy[spc].num[num].back_time = 0;				  //���˹����з�����ײ����ֹ����
						}

						if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
							enemy[spc].num[num].back_cnt = 0;
							enemy[spc].num[num].back_time = 0;				  //������Ϊ���ڽ���
						}
						else enemy[spc].num[num].back_cnt++;				  //������Ϊ���ڼ���
					}
				}					

				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�										

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect + 2;
				if (enemy[spc].num[num].move == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�����ͼ
				}
				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}
	}

	else if (enemy[spc].num[num].HP <= 0) {
		enemy[spc].num[num].pic_y = 4;
		enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect;
	}

	if (enemy[spc].num[num].think == 6) enemy[spc].num[num].think = 0;
	else enemy[spc].num[num].think++;										  //˼��ʱվ��ͼ�ı����ͼ�任ʱ�����1:6
	if (enemy[spc].num[num].move == 6) enemy[spc].num[num].move = 0;
	else enemy[spc].num[num].move++;										  //�ƶ�ʱ����ͼ�ı����ͼ�任ʱ�����1:6
}

void shoot_AI(int spc, int num) 
{
	//�Թ���Ϊ���Ľ�������ϵ������Ϊx������������Ϊy�������򣨼�Ĭ��ͼ������ϵ��

	int dir;							//����ѭ������
	int dx;								//���ﵽ����ж����ĺ���������
	int dy;								//���ﵽ����ж���������������
	double distance;					//���������֮��ľ���
	double cosarc;						//���ﵽ��Ҽн�����ֵ
	double sinarc;						//���ﵽ��Ҽн�����ֵ
	double arc;							//���ﵽ��Ҽнǣ���Χ [0, 2PI)
	double marc;						//�н�ƫ��ֵ
	int action;							//��Ϊ�жϲ���
	int	move;							//�ƶ��жϲ���
	int attack;							//�����жϲ���
	int	mx;								//�����ƶ�����
	int my;								//�����ƶ�����
	static int backx;					//������˾����¼
	static int backy;					//������˾����¼
	int Eleft, Eright, Etop, Ebottom;   //���ﵱǰ�ڴ������ж����ķ�������
	POINT Ecenter;                      //���ﵱǰ�ڴ��������ĵ�����

	Eleft = enemy[spc].num[num].x - map.x + enemy[spc].pic_left;
	Eright = enemy[spc].num[num].x - map.x + enemy[spc].pic_right;
	Etop = enemy[spc].num[num].y - map.y + enemy[spc].pic_top;
	Ebottom = enemy[spc].num[num].y - map.y + enemy[spc].pic_bottom;
	Ecenter.x = (Eleft + Eright) / 2;
	Ecenter.y = (Etop + Ebottom) / 2;

	dx = character_position.x - (enemy[spc].num[num].x - map.x);
	dy = character_position.y - (enemy[spc].num[num].y - map.y);
	distance = sqrt(dx * dx + dy * dy);

	if (distance > 0 && enemy[spc].num[num].HP > 0) {
		cosarc = dx / distance;
		sinarc = dy / distance;
		if (dy >= 0) arc = acos(cosarc);
		else arc = 2 * PI - acos(cosarc);

		if (dy >= 0) enemy[spc].num[num].spin = 2 * PI - acos(cosarc) - PI / 2;
		else enemy[spc].num[num].spin = acos(cosarc) - PI / 2;
		if (enemy[spc].num[num].spin < 0) enemy[spc].num[num].spin += 2 * PI;

		if (enemy[spc].num[num].pic_x == 3)
			enemy[spc].num[num].pic_x = 0;									  //��Ϊͼ�ֻ�

		//δ�������																  
		if (!isdetected(spc, num)) {
			enemy[spc].num[num].is_cnt = 0;
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 2;										  //���������Ϊ

			//Լ1/2���ʽ���˼����Ϊ
			if (action == 0) {
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 31 + 30;		  //���˼��ʱ��30~60 * 30ms = 0.9~1.8s

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect;       //�л���վ��ͼ״̬��
				if (enemy[spc].num[num].think == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�վ��ͼ					
				}

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ
			else {
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 81 + 30;		  //����ƶ�ʱ��30~100 * 30ms = 0.9~3.0s
				move = rand() % 100 + 1;
				for (dir = 0; dir < 5; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 21; break;
						case 2:move = 41; break;
						case 3:move = 61; break;
						case 4:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

																																	//�����ʵݼ��ķ�ʽ������·�������·�����о���															  
				if (move >= 1 && move <= 20) {								  //20%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 21 && move <= 40) {						  //20%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 41 && move <= 60) {						  //20%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 61 && move <= 80) {						  //20%������ (PI/2,3PI/4] ƫ�ΧС������
					if (rand() % 2) marc = (rand() % 5 + 11) * PI / 20;
					else marc = -(rand() % 5 + 11) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[3] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[3]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[3] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else {														  //20%������ (3PI/4,PI] ƫ�Χ�������
					if (rand() % 2) marc = (rand() % 5 + 16) * PI / 20;
					else marc = -(rand() % 5 + 16) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[4] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[4]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[4] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}

				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect + 2;   //�л�������ͼ״̬��
				if (enemy[spc].num[num].move == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�����ͼ
				}

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}

		//�������																  
		else {
			enemy[spc].num[num].not_cnt = 0;
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 2;										  //���������Ϊ

			if (enemy[spc].num[num].attack_time != 0) {						  //��鹥����ȴ
				if (enemy[spc].num[num].attack_cnt == enemy[spc].num[num].attack_time) {
					enemy[spc].num[num].attack_cnt = 0;
					enemy[spc].num[num].attack_time = 0;					  //������ȴ���ڽ���
				}
				else enemy[spc].num[num].attack_cnt++;						  //������ȴ���ڼ���
			}

			//Լ1/2���ʽ���˼����Ϊ
			if (action == 0) {
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 21 + 20;		  //���˼��ʱ��20~40 * 30ms = 0.6~1.2s

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect;       //�л���վ��ͼ״̬��
				if (enemy[spc].num[num].think == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�վ��ͼ					
				}

				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ																  
			else {
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 111 + 60;		  //����ƶ�ʱ��60~140 * 30ms = 1.8~4.2s
				if (distance > 250) move = rand() % 100 + 1;				  //�������ʱ������ƶ���Ϊ
				else move = rand() % 50 + 51;								  //���־��룬��ȡ������Ϊ
				for (dir = 0; dir < 5; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 21; break;
						case 2:move = 36; break;
						case 3:move = 51; break;
						case 4:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

				//�����ʵݼ��ķ�ʽ������ǰ��·�������ǰ��·�����о���															  
				if (move >= 1 && move <= 20) {								  //20%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 21 && move <= 35) {						  //15%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 36 && move <= 50) {						 //15%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 51 && move <= 70) {						  //20%������ (PI/2,3PI/4] ƫ�ΧС������
					if (rand() % 2) marc = (rand() % 5 + 11) * PI / 20;
					else marc = -(rand() % 5 + 11) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[3] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[3]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[3] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else {														  //30%������ (3PI/4,PI] ƫ�Χ�������
					if (rand() % 2) marc = (rand() % 5 + 16) * PI / 20;
					else marc = -(rand() % 5 + 16) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[4] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[4]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[4] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}

				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}

				//����������ж���Ӵ�
				if (((int)(fabs(Ecenter.x + mx - knight.center.x)) <= (60 - enemy[spc].pic_left + knight.center.x - knight.left))
					&& ((int)(fabs(Ecenter.y + my - knight.center.y)) <= (60 - enemy[spc].pic_top + knight.center.y - knight.top)))
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;									  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;			  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 21 + 20; //�������ʱ��20~40 * 30ms = 0.6~1.2s
						enemy[spc].num[num].is_cnt = 0;
						enemy[spc].num[num].think_time = 0;
						enemy[spc].num[num].move_time = 0;				  //�����������
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;				  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;				  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;				  //������Ϊ���ڼ���				
				}

				attack = rand() % 4;

				//1/4���ʽ��й���
				if (attack == 0 && enemy[spc].num[num].attack_cnt == 0 && knight.HP >0)
				{
					enemy[spc].num[num].attack_time = rand() % 31 + 40;   //���������ȴʱ��40~70 * 30ms = 1.2~2.1s				

					enemy_shoot(spc, num);
				}

				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�

				enemy[spc].num[num].pic_y = enemy[spc].num[num].aspect + 2;
				if (enemy[spc].num[num].move == 6) {
					enemy[spc].num[num].pic_x++;							  //��ʱ����ر����л�����ͼ
				}
				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}
	}

	else if (enemy[spc].num[num].HP <= 0) {
		enemy[spc].num[num].pic_y = 4;
		enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect;
	}

	if (enemy[spc].num[num].think == 6) enemy[spc].num[num].think = 0;
	else enemy[spc].num[num].think++;										  //˼��ʱվ��ͼ�ı����ͼ�任ʱ�����1:6
	if (enemy[spc].num[num].move == 6) enemy[spc].num[num].move = 0;
	else enemy[spc].num[num].move++;										  //�ƶ�ʱ����ͼ�ı����ͼ�任ʱ�����1:6
}

void BOSS_AI(int spc, int num)
{
	//�Թ���Ϊ���Ľ�������ϵ������Ϊx������������Ϊy�������򣨼�Ĭ��ͼ������ϵ��

	int dir;							//����ѭ������
	int dx;								//���ﵽ����ж����ĺ���������
	int dy;								//���ﵽ����ж���������������
	double distance;					//���������֮��ľ���
	double cosarc;						//���ﵽ��Ҽн�����ֵ
	double sinarc;						//���ﵽ��Ҽн�����ֵ
	double arc;							//���ﵽ��Ҽнǣ���Χ [0, 2PI)
	double marc;						//�н�ƫ��ֵ
	double garc;						//�����н�
	int action;							//��Ϊ�жϲ���
	int	move;							//�ƶ��жϲ���
	int attack;							//�����жϲ���
	int	mx;								//�����ƶ�����
	int my;								//�����ƶ�����
	static int backx;					//������˾����¼
	static int backy;					//������˾����¼
	int Eleft, Eright, Etop, Ebottom;   //���ﵱǰ�ڴ������ж����ķ�������
	POINT Ecenter;                      //���ﵱǰ�ڴ��������ĵ�����
	static int angry;

	Eleft = enemy[spc].num[num].x - map.x + enemy[spc].pic_left;
	Eright = enemy[spc].num[num].x - map.x + enemy[spc].pic_right;
	Etop = enemy[spc].num[num].y - map.y + enemy[spc].pic_top;
	Ebottom = enemy[spc].num[num].y - map.y + enemy[spc].pic_bottom;
	Ecenter.x = (Eleft + Eright) / 2;
	Ecenter.y = (Etop + Ebottom) / 2;

	dx = character_position.x - (enemy[spc].num[num].x - map.x);
	dy = character_position.y - (enemy[spc].num[num].y - map.y);
	distance = sqrt(dx * dx + dy * dy);

	if (enemy[spc].num[num].HP >= enemy[spc].HP_MAX / 2) {
		enemy[spc].num[num].pic_y = 0;
		angry = 0;
	}		
	else if (enemy[spc].num[num].HP > 0) {
		enemy[spc].num[num].pic_y = 1;
		if (angry == 0) {
			mciSendString(_T("close resource\\boss_angry.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\boss_angry.wav"), NULL, 0, NULL);
			angry = 1;
		}
	}	
	else {
		enemy[spc].num[num].pic_y = 2;
		enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect;
	}

	if (distance > 0 && enemy[spc].num[num].HP > 0) {
		cosarc = dx / distance;
		sinarc = dy / distance;
		if (dy >= 0) arc = acos(cosarc);
		else arc = 2 * PI - acos(cosarc);

		if (dy >= 0) enemy[spc].num[num].spin = 2 * PI - acos(cosarc) - PI / 2;
		else enemy[spc].num[num].spin = acos(cosarc) - PI / 2;
		if (enemy[spc].num[num].spin < 0) enemy[spc].num[num].spin += 2 * PI;
																			  //δ�������																  
		if (!isdetected(spc, num)) {
			enemy[spc].num[num].is_cnt = 0;
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].not_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 3;										  //���������Ϊ

			//Լ1/3���ʽ���˼����Ϊ
			if (action == 0) {
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 11 + 30;		  //���˼��ʱ��30~40 * 30ms = 0.9~1.2s

				enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect;		  				

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ
			else {
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].not_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 81 + 30;		  //����ƶ�ʱ��30~100 * 30ms = 0.9~3.0s
				move = rand() % 100 + 1;
				for (dir = 0; dir < 5; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 21; break;
						case 2:move = 41; break;
						case 3:move = 61; break;
						case 4:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

																																	//�����ʵݼ��ķ�ʽ������·�������·�����о���															  
				if (move >= 1 && move <= 20) {								  //20%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 21 && move <= 40) {						  //20%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 41 && move <= 60) {						  //20%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 61 && move <= 80) {						  //20%������ (PI/2,3PI/4] ƫ�ΧС������
					if (rand() % 2) marc = (rand() % 5 + 11) * PI / 20;
					else marc = -(rand() % 5 + 11) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[3] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[3]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[3] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else {														  //20%������ (3PI/4,PI] ƫ�Χ�������
					if (rand() % 2) marc = (rand() % 5 + 16) * PI / 20;
					else marc = -(rand() % 5 + 16) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[4] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[4]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[4] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}

				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�

				enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect + 2;   

				if (enemy[spc].num[num].not_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].not_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].not_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}

		//�������																  
		else {
			enemy[spc].num[num].not_cnt = 0;
			if (enemy[spc].num[num].think_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].think_time) action = 0;     //����˼����Ϊ
			else if (enemy[spc].num[num].move_time != 0 && enemy[spc].num[num].is_cnt <= enemy[spc].num[num].move_time) action = 1;  //�����ƶ���Ϊ
			else action = rand() % 2;										  //���������Ϊ

			if (enemy[spc].num[num].attack_time != 0 && enemy[spc].num[num].attack_cnt <= enemy[spc].num[num].attack_time) attack = 0;     //���乥����Ϊ
			else attack = rand() % 4;										  //1/4���ʽ��й���

			if (enemy[spc].num[num].attack_time != 0) {						  //��鹥����ȴ
				if (enemy[spc].num[num].attack_cnt == enemy[spc].num[num].attack_time) {
					enemy[spc].num[num].attack_cnt = 0;
					enemy[spc].num[num].attack_time = 0;					  //������ȴ���ڽ���
				}
				else enemy[spc].num[num].attack_cnt++;						  //������ȴ���ڼ���
			}

			//Լ1/2���ʽ���˼����Ϊ
			if (action == 0) {
				enemy[spc].num[num].move = 0;								  //��ʼ���ƶ���Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].think_time = rand() % 21 + 20;		  //���˼��ʱ��20~40 * 30ms = 0.6~1.2s

				enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect;

				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].think_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].think_time = 0;						  //˼����Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //˼����Ϊ���ڼ���
			}

			//Լ1/2���ʽ����ƶ���Ϊ																  
			else {
				enemy[spc].num[num].think = 0;								  //��ʼ��˼����Ϊ����ͼ�����л�
				if (enemy[spc].num[num].is_cnt == 0)
					enemy[spc].num[num].move_time = rand() % 111 + 60;		  //����ƶ�ʱ��60~140 * 30ms = 1.8~4.2s
				if (distance > 300) move = rand() % 100 + 1;				  //�������ʱ������ƶ���Ϊ
				else move = rand() % 50 + 51;								  //���־��룬��ȡ������Ϊ
				for (dir = 0; dir < 5; dir++) {								  //���ݼ���·�������ƶ�
					if (enemy[spc].num[num].direction_time[dir] != 0 && enemy[spc].num[num].direction_cnt <= enemy[spc].num[num].direction_time[dir]) {
						switch (dir) {
						case 0:move = 1; break;
						case 1:move = 16; break;
						case 2:move = 36; break;
						case 3:move = 61; break;
						case 4:move = 100; break;
						}
						break;
					}
				}
				if (enemy[spc].num[num].back_time != 0 && enemy[spc].num[num].back_cnt <= enemy[spc].num[num].back_time) move = 0;  //����Ϊ����ʱ���ƶ�

																																	//�����ʵݼ��ķ�ʽ������ǰ��·�������ǰ��·�����о���															  
				if (move >= 1 && move <= 15) {								  //15%���������ŷ���ǰ��
					mx = (int)(enemy[spc].Espeed * cosarc);
					my = (int)(enemy[spc].Espeed * sinarc);

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[0] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[0]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[0] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 16 && move <= 35) {						  //20%������ (0,PI/4] ƫ�Χ���ǰ��
					if (rand() % 2) marc = (rand() % 5 + 1) * PI / 20;
					else marc = -(rand() % 5 + 1) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[1] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[1]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[1] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 36 && move <= 60) {						 //25%������ (PI/4,PI/2] ƫ�ΧС��ǰ��
					if (rand() % 2) marc = (rand() % 5 + 6) * PI / 20;
					else marc = -(rand() % 5 + 6) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));

					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[2] = rand() % 21 + 10; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[2]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[2] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else if (move >= 61 && move <= 80) {						  //20%������ (PI/2,3PI/4] ƫ�ΧС������
					if (rand() % 2) marc = (rand() % 5 + 11) * PI / 20;
					else marc = -(rand() % 5 + 11) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[3] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[3]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[3] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}
				else {														  //20%������ (3PI/4,PI] ƫ�Χ�������
					if (rand() % 2) marc = (rand() % 5 + 16) * PI / 20;
					else marc = -(rand() % 5 + 16) * PI / 20;

					mx = (int)(enemy[spc].Espeed * cos(arc + marc));
					my = (int)(enemy[spc].Espeed * sin(arc + marc));
					if (enemy[spc].num[num].direction_cnt == 0)
						enemy[spc].num[num].direction_time[4] = rand() % 11 + 20; //��������ƶ�ʱ��20~30 * 30ms = 0.6~0.9s
					if (enemy[spc].num[num].direction_cnt == enemy[spc].num[num].direction_time[4]) {
						enemy[spc].num[num].direction_cnt = 0;
						enemy[spc].num[num].direction_time[4] = 0;			  //�����ƶ�����
					}
					else enemy[spc].num[num].direction_cnt++;				  //�����ƶ����ڼ���
				}

				//�ϰ�ײ���ж�
				if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
					|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
					|| move == 0)
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;										  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;				  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;	  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 11 + 20;     //�������ʱ��20~30 * 30ms = 0.6~0.9s
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;					  //������Ϊ���ڼ���
				}

				//����������ж���Ӵ�
				if (((int)(fabs(Ecenter.x + mx - knight.center.x)) <= (60 - enemy[spc].pic_left + knight.center.x - knight.left))
					&& ((int)(fabs(Ecenter.y + my - knight.center.y)) <= (60 - enemy[spc].pic_top + knight.center.y - knight.top)))
				{
					if (enemy[spc].num[num].back_cnt == 0) {
						backx = -mx;
						backy = -my;									  //��¼���˷���
						enemy[spc].num[num].direction_cnt = 0;			  //��������ƶ����ڼ���
						for (dir = 0; dir < 5; dir++)
							enemy[spc].num[num].direction_time[dir] = 0;  //���ǰ���������ڼ���
						enemy[spc].num[num].back_time = rand() % 21 + 20; //�������ʱ��20~40 * 30ms = 0.6~1.2s
						enemy[spc].num[num].is_cnt = 0;
						enemy[spc].num[num].think_time = 0;
						enemy[spc].num[num].move_time = 0;				  //�����������
					}
					mx = backx;
					my = backy;

					if (object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_left + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_top + my] == IMMORTAL_OBJ
						|| object[enemy[spc].num[num].x + enemy[spc].pic_right + mx][enemy[spc].num[num].y + enemy[spc].pic_bottom + my] == IMMORTAL_OBJ)
					{
						mx = 0;
						my = 0;
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;				  //���˹����з�����ײ����ֹ����
					}

					if (enemy[spc].num[num].back_cnt == enemy[spc].num[num].back_time) {
						enemy[spc].num[num].back_cnt = 0;
						enemy[spc].num[num].back_time = 0;				  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].back_cnt++;				  //������Ϊ���ڼ���				
				}

				if (attack == 0 && knight.HP >0)
				{
					if (enemy[spc].num[num].attack_cnt == 0)
						enemy[spc].num[num].attack_time = rand() % 51 + 50;		  //�������ʱ��50~100 * 30ms = 1.5~3s

					if (enemy[spc].num[num].attack_cnt % 40 == 0)				 //����1.2s/��
					{
						if (enemy[spc].num[num].HP >= enemy[spc].HP_MAX / 2)
						{
							marc = (rand() % 7 - 3) * PI / 18;
							enemy[spc].num[num].spin += marc;
							enemy_shoot(spc, num);
							enemy[spc].num[num].spin += PI / 12;
							enemy_shoot(spc, num);
							enemy[spc].num[num].spin += PI / 12;
							enemy_shoot(spc, num);
							enemy[spc].num[num].spin -= PI / 4;
							enemy_shoot(spc, num);
							enemy[spc].num[num].spin -= PI / 12;
							enemy_shoot(spc, num);
							enemy[spc].num[num].spin += PI / 6;
							enemy[spc].num[num].spin -= marc;
						}
						else {
							marc = (rand() % 7 - 3) * PI / 18;
							for (garc = marc; garc < 2 * PI + marc; garc += PI / 12) {
								enemy[spc].num[num].spin += garc;
								enemy_shoot(spc, num);
							}				
							enemy[spc].num[num].spin -= (23 * PI / 12 + marc);
						}
					}

					if (enemy[spc].num[num].attack_cnt == enemy[spc].num[num].attack_time) {
						enemy[spc].num[num].attack_cnt = 0;
						enemy[spc].num[num].attack_time = 0;					  //������Ϊ���ڽ���
					}
					else enemy[spc].num[num].attack_cnt++;						  //������Ϊ���ڼ���									
				}

				enemy[spc].num[num].x += mx;
				enemy[spc].num[num].y += my;								  //�ƶ�

				enemy[spc].num[num].pic_x = enemy[spc].num[num].aspect + 2;
				
				if (enemy[spc].num[num].is_cnt == enemy[spc].num[num].move_time) {
					enemy[spc].num[num].is_cnt = 0;
					enemy[spc].num[num].move_time = 0;						  //�ƶ���Ϊ���ڽ���
				}
				else enemy[spc].num[num].is_cnt++;							  //�ƶ���Ϊ���ڼ���
			}

			if (enemy[spc].num[num].spin < PI) enemy[spc].num[num].aspect = LEFT;
			if (enemy[spc].num[num].spin > PI) enemy[spc].num[num].aspect = RIGHT;		//�ж����߳���
		}
	}

	if (enemy[spc].num[num].think == 6) enemy[spc].num[num].think = 0;
	else enemy[spc].num[num].think++;										  //˼��ʱվ��ͼ�ı����ͼ�任ʱ�����1:6
	if (enemy[spc].num[num].move == 6) enemy[spc].num[num].move = 0;
	else enemy[spc].num[num].move++;										  //�ƶ�ʱ����ͼ�ı����ͼ�任ʱ�����1:6
}