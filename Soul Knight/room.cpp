#include "room.h"
int r1_mid, r1_left, r1_down;
int r2_mid, r2_right, r2_down;
int r3_mid, r3_right, r3_down, r3_downright;
int rBOSS;

void room1_mid()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������

	deaths = 0;
	if (r1_mid == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		//�����Źر�
		obj_mark(2628, 2375, 2676, 2619, IMMORTAL_OBJ);			//������
		obj_mark(2916, 2087, 3156, 2135, IMMORTAL_OBJ);			//�Ϸ�����
		obj_mark(3400, 2375, 3443, 2619, IMMORTAL_OBJ);			//�Ҳ����
		obj_mark(2916, 2859, 3156, 2907, IMMORTAL_OBJ);			//�·�����
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		amount[0] = enemy_generate(2680, 2135, 3400, 2859, 0, 5);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2680, 2135, 3400, 2859, 1, 0);	//������ɹ��ﲢ������������
		r1_mid = 1;

	}
	if (r1_mid != -1) {
		putimage(2628 - map.x, 2348 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(2628 - map.x, 2348 - map.y, &door_col, SRCINVERT);
		putimage(3395 - map.x, 2348 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(3395 - map.x, 2348 - map.y, &door_col, SRCINVERT);
		putimage(2916 - map.x, 2055 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(2916 - map.x, 2055 - map.y, &door_row, SRCINVERT);
		putimage(2916 - map.x, 2828 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(2916 - map.x, 2828 - map.y, &door_row, SRCINVERT);
	}

	for (emy = 0; emy < amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = 0; emy < amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <=0) {		//����ȫ������������������������
		//�����ſ���
		obj_mark(2628, 2375, 2676, 2619, FLOOR);				//������
		obj_mark(2916, 2087, 3156, 2135, FLOOR);				//�Ϸ�����
		obj_mark(3400, 2375, 3443, 2619, FLOOR);				//�Ҳ����
		obj_mark(2916, 2859, 3156, 2907, FLOOR);				//�·�����
		if (r1_mid != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r1_mid = -1;											//����������
	}
}

void room1_left()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];   //���������

	deaths = 0;
	if (r1_left == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		//�����Źر�
		obj_mark(853, 2087, 1093, 2135, IMMORTAL_OBJ);			//�Ϸ�����
		obj_mark(1333, 2375, 1381, 2619, IMMORTAL_OBJ);			//�Ҳ����
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(617, 2135, 1333, 2859, 0, 7);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(617, 2135, 1333, 2859, 1, 0);
		r1_left = 1;
	}

	if (r1_left != -1) {
		putimage(1333 - map.x, 2345 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(1333 - map.x, 2345 - map.y, &door_col, SRCINVERT);
		putimage(853 - map.x, 2060 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(853 - map.x, 2060 - map.y, &door_row, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������
		//�����ſ���
		obj_mark(853, 2087, 1093, 2135, FLOOR);					//�Ϸ�����
		obj_mark(1333, 2375, 1381, 2619, FLOOR);				//�Ҳ����
		if (r1_left != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r1_left = -1;											//����������
	}
}

void room1_down()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r1_down == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(2916, 4151, 3156, 4199, IMMORTAL_OBJ);			//�ر��Ϸ�����
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(2676, 4199, 3400, 4923, 0, 5);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2676, 4199, 3400, 4923, 1, 0);
		r1_down = 1;
	}
	if (r1_down != -1) {
		putimage(2916 - map.x, 4125 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(2916 - map.x, 4125 - map.y, &door_row, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(2916, 4151, 3156, 4199, FLOOR);				//���Ϸ�����
		if (r1_down != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r1_down = -1;											//����������
	}
}

void room2_mid()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r2_mid == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		//�����Źر�
		obj_mark(2744, 2470, 2792, 2708, IMMORTAL_OBJ);			//������
		obj_mark(3044, 2172, 3293, 2220, IMMORTAL_OBJ);			//�Ϸ�����
		obj_mark(3543, 2471, 3591, 2708, IMMORTAL_OBJ);			//�Ҳ����
		obj_mark(3044, 2966, 3293, 3014, IMMORTAL_OBJ);			//�·�����

		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(2792, 2220, 3543, 2966, 0, 0);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2792, 2220, 3543, 2966, 1, 6);
		r2_mid = 1;
	}
	if (r2_mid != -1) {
		putimage(2746 - map.x, 2443 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(2746 - map.x, 2443 - map.y, &door_col, SRCINVERT);
		putimage(3546 - map.x, 2443 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(3546 - map.x, 2443 - map.y, &door_col, SRCINVERT);
		putimage(3050 - map.x, 2143 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(3050 - map.x, 2143 - map.y, &door_row, SRCINVERT);
		putimage(3050 - map.x, 2942 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(3050 - map.x, 2942 - map.y, &door_row, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		//�����ſ���
		obj_mark(2744, 2470, 2792, 2708, FLOOR);			//������
		obj_mark(3044, 2172, 3293, 2220, FLOOR);			//�Ϸ�����
		obj_mark(3543, 2471, 3591, 2708, FLOOR);			//�Ҳ����
		obj_mark(3044, 2966, 3293, 3014, FLOOR);			//�·�����
		if (r2_mid != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r2_mid = -1;										//����������
	}
}

void room2_right()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r2_right == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(4934, 2280, 5173, 2328, IMMORTAL_OBJ);				//�ر��Ϸ�����
		obj_mark(4743, 2471, 4791, 2708, IMMORTAL_OBJ);				//�ر�������
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(4791, 2328, 5318, 2852, 0, 0);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(4791, 2328, 5318, 2852, 1, 4);
		r2_right = 1;
	}
	if (r2_right != -1) {
		putimage(4941 - map.x, 2252 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(4941 - map.x, 2252 - map.y, &door_row, SRCINVERT);
		putimage(4743 - map.x, 2443 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(4743 - map.x, 2443 - map.y, &door_col, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(4934, 2280, 5173, 2328, FLOOR);				//���Ϸ�����
		obj_mark(4743, 2471, 4791, 2708, FLOOR);				//��������
		if (r2_right != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r2_right = -1;											//����������
	}
}

void room2_down()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r2_down == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(3044, 4266, 3293, 4314, IMMORTAL_OBJ);			//�ر��Ϸ�����
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(2697, 4314, 3642, 4957, 0, 0);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2697, 4314, 3642, 4957, 1, 7);
		r2_down = 1;
	}
	if (r2_down != -1) {
		putimage(3050 - map.x, 4239 - map.y, 247, 99, &door_row_vice, 0, 0, NOTSRCERASE);
		putimage(3050 - map.x, 4239 - map.y, 247, 99, &door_row, 0, 0, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(3044, 4266, 3293, 4314, FLOOR);				//���Ϸ�����
		if (r2_down != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r2_down = -1;											//����������
	}
}

void room3_mid()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r3_mid == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
																//�����Źر�
		obj_mark(2630, 2360, 2678, 2594, IMMORTAL_OBJ);			//������
		obj_mark(3075, 1902, 3323, 1950, IMMORTAL_OBJ);			//�Ϸ�����
		obj_mark(3732, 2360, 3780, 2592, IMMORTAL_OBJ);			//�Ҳ����
		obj_mark(3075, 2991, 3325, 3039, IMMORTAL_OBJ);			//�·�����

		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(2678, 1950, 3732, 2991, 0, 8);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2678, 1950, 3732, 2991, 1, 8);
		r3_mid = 1;
	}
	if (r3_mid != -1) {
		putimage(2629 - map.x, 2328 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(2629 - map.x, 2328 - map.y, &door_col, SRCINVERT);
		putimage(3722 - map.x, 2328 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(3722 - map.x, 2328 - map.y, &door_col, SRCINVERT);
		putimage(3080 - map.x, 1877 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(3080 - map.x, 1877 - map.y, &door_row, SRCINVERT);
		putimage(3080 - map.x, 2971 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(3080 - map.x, 2971 - map.y, &door_row, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
																//�����ſ���
		obj_mark(2630, 2360, 2678, 2594, FLOOR);				//������
		obj_mark(3075, 1902, 3323, 1950, FLOOR);				//�Ϸ�����
		obj_mark(3732, 2360, 3780, 2592, FLOOR);				//�Ҳ����
		obj_mark(3075, 2991, 3325, 3039, FLOOR);				//�·�����
		if (r3_mid != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r3_mid = -1;										//����������
	}
}

void room3_right()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r3_right == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(4800, 2360, 4848, 2592, IMMORTAL_OBJ);				//�ر�������
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(4848, 2106, 5592, 2835, 0, 3);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(4848, 2106, 5592, 2835, 1, 3);
		r3_right = 1;
	}
	if (r3_right != -1) {
		putimage(4800 - map.x, 2328 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(4800 - map.x, 2328 - map.y, &door_col, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(4800, 2360, 4848, 2592, FLOOR);				//��������
		if (r3_right != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r3_right = -1;											//����������
	}
}

void room3_down()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r3_down == 0) {											//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(3075, 4045, 3325, 4093, IMMORTAL_OBJ);			//�ر��Ϸ�����
		obj_mark(2780, 4347, 2828, 4581, IMMORTAL_OBJ);			//�ر�������
		obj_mark(3577, 4347, 3625, 4584, IMMORTAL_OBJ);			//�ر��Ҳ����
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(2828, 4093, 3577, 4832, 0, 5);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(2828, 4093, 3577, 4832, 1, 5);
		r3_down = 1;
	}
	if (r3_down != -1) {
		putimage(2780 - map.x, 4315 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(2780 - map.x, 4315 - map.y, &door_col, SRCINVERT);
		putimage(3578 - map.x, 4315 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(3578 - map.x, 4315 - map.y, &door_col, SRCINVERT);
		putimage(3082 - map.x, 4013 - map.y, 247, 99, &door_row_vice, 0, 0, NOTSRCERASE);
		putimage(3082 - map.x, 4013 - map.y, 247, 99, &door_row, 0, 0, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(3075, 4045, 3325, 4093, FLOOR);			//���Ϸ�����
		obj_mark(2780, 4347, 2828, 4581, FLOOR);			//��������
		obj_mark(3577, 4347, 3293, 3625, FLOOR);			//���Ҳ����
		if (r3_down != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r3_down = -1;											//����������
	}
}

void room3_downright()
{
	int emy;				//�������ѭ������
	int deaths;				//����������
	static int amount[2];	//��������
	static int series[2];	//��������

	deaths = 0;
	if (r3_downright == 0) {										//ֻ�ڵ�һ��ִ�еĹ���
		obj_mark(4812, 4347, 4860, 4584, IMMORTAL_OBJ);				//�ر�������
		mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
		mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);

		enemy[0].old_amount = enemy[0].amount;
		enemy[1].old_amount = enemy[1].amount;
		series[0] = enemy[0].old_amount;
		series[1] = enemy[1].old_amount;
		amount[0] = enemy_generate(4860, 4087, 5606, 4831, 0, 4);	//������ɹ��ﲢ������������
		amount[1] = enemy_generate(4860, 4087, 5606, 4831, 1, 4);
		r3_downright = 1;
	}
	if (r3_downright != -1) {
		putimage(4811 - map.x, 4317 - map.y, &door_col_vice, NOTSRCERASE);
		putimage(4811 - map.x, 4317 - map.y, &door_col, SRCINVERT);
	}

	for (emy = series[0]; emy < series[0] + amount[0]; emy++) {
		if (pause == 0)	melee_AI(0, emy);
		enemy_show(0, emy);
		if (enemy[0].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	for (emy = series[1]; emy < series[1] + amount[1]; emy++) {
		if (pause == 0)	shoot_AI(1, emy);
		enemy_show(1, emy);
		if (enemy[1].num[emy].HP <= 0) deaths++;				//ͳ��������������
	}

	if (deaths == amount[0] + amount[1] || knight.HP <= 0) {	//����ȫ������������������������														
		obj_mark(4812, 4347, 4860, 4584, FLOOR);				//��������
		if (r3_downright != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
		}

		r3_downright = -1;											//����������
	}
}

void BOSS_room()
{
	int dir;

	if (r3_downright == 0) {										//ֻ�ڵ�һ��ִ�еĹ���
	
		enemy[2].num[0].x = 3114;
		enemy[2].num[0].y = 2132;

		enemy[2].amount = 1;
		enemy[2].num[0].HP = enemy[2].HP_MAX;						//HP��ʼ��
		enemy[2].num[0].is_damaged = 0;								//�����ж���ʼ��
		enemy[2].num[0].spin = 0;									//������ת�ǳ�ʼ��
		enemy[2].num[0].think = 0;
		enemy[2].num[0].move = 0;									//��ʼ����Ϊ�ֻ�����
		enemy[2].num[0].damaged_cnt = 0;
		enemy[2].num[0].think_time = 0;
		enemy[2].num[0].move_time = 0;
		enemy[2].num[0].back_time = 0;
		enemy[2].num[0].attack_time = 0;
		enemy[2].num[0].not_cnt = 0;
		enemy[2].num[0].is_cnt = 0;
		enemy[2].num[0].direction_cnt = 0;
		enemy[2].num[0].back_cnt = 0;
		enemy[2].num[0].attack_cnt = 0;								//��ʼ�����м�ʱ����ȴ									
		for (dir = 0; dir < 5; dir++) {
			enemy[2].num[0].direction_time[dir] = 0;				//��ʼ����������
		}

		obj_mark(3075, 1902, 3323, 1950, IMMORTAL_OBJ);				//�Ϸ����Źر�

		r3_downright = 1;
	}

	if (rBOSS != -1) {
		putimage(3080 - map.x, 1877 - map.y, &door_row_vice, NOTSRCERASE);
		putimage(3080 - map.x, 1877 - map.y, &door_row, SRCINVERT);
	}

	if (pause == 0)	BOSS_AI(2, 0);

	putimage(enemy[2].num[0].x - map.x, enemy[2].num[0].y - map.y, 200, 200, &enemy[2].model_vice,
		enemy[2].num[0].pic_x * 200, enemy[2].num[0].pic_y * 200, NOTSRCERASE);
	if (enemy[2].num[0].is_damaged == 1) {
		putimage(enemy[2].num[0].x - map.x, enemy[2].num[0].y - map.y, 200, 200, &enemy[2].model,
			enemy[2].num[0].pic_x * 200, enemy[2].num[0].pic_y * 200, DSTINVERT);
		if (enemy[2].num[0].damaged_cnt == 2) {
			enemy[2].num[0].damaged_cnt = 0;
			enemy[2].num[0].is_damaged = 0;
		}
		else enemy[2].num[0].damaged_cnt++;
	}
	else {
		putimage(enemy[2].num[0].x - map.x, enemy[2].num[0].y - map.y, 200, 200, &enemy[2].model,
			enemy[2].num[0].pic_x * 200, enemy[2].num[0].pic_y * 200, SRCINVERT);
	}

	if (enemy[2].num[0].HP > 0) {									
		setfillcolor(RGB(36, 36, 36));
		solidrectangle(436, 54, 846, 88);
		setfillcolor(RGB(136, 33, 34));
		solidrectangle(440, 58, (int)(440 + 402 * enemy[2].num[0].HP / enemy[2].HP_MAX), 83);
		setfillcolor(RGB(221, 58, 58));
		solidrectangle(440, 62, (int)(440 + 402 * enemy[2].num[0].HP / enemy[2].HP_MAX), 79);		//��ʾBOSSѪ��
	}
	else {
		obj_mark(3075, 1902, 3323, 1950, FLOOR);				//�����Ϸ�����

		if (rBOSS != -1) {
			mciSendString(_T("close resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\door.wav"), NULL, 0, NULL);
			mciSendString(_T("play resource\\boss_dead.wav"), NULL, 0, NULL);
		}
		rBOSS = -1;
	}
}
