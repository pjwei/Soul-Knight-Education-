#include "enemy.h"

enemy_species enemy[SPECIES];
BULLET *Ehead = NULL, *Etail = NULL;

void startup_enemy()
{
	//Ұ�� 42x30
	enemy[0].amount = 0;
	enemy[0].old_amount = 0;
	enemy[0].damage = 2;        
	enemy[0].HP_MAX = 20;
	enemy[0].Espeed = 5;
	enemy[0].pic_left = 39;
	enemy[0].pic_right = 81;
	enemy[0].pic_top = 45;
	enemy[0].pic_bottom = 75;                 //��ʼ����������
	loadimage(&enemy[0].model_vice, _T("resource\\boar_vice.jpg"), 480, 600);
	loadimage(&enemy[0].model, _T("resource\\boar.jpg"), 480, 600);               //�������ͼƬ

	//���� 34x52
	enemy[1].amount = 0;
	enemy[1].old_amount = 0;
	enemy[1].damage = 3;
	enemy[1].HP_MAX = 12;
	enemy[1].Espeed = 4;
	enemy[1].pic_left = 43;
	enemy[1].pic_right = 77;
	enemy[1].pic_top = 34;
	enemy[1].pic_bottom = 86;                 //��ʼ����������
	loadimage(&enemy[1].model_vice, _T("resource\\shooter_vice.jpg"), 480, 600);
	loadimage(&enemy[1].model, _T("resource\\shooter.jpg"), 480, 600);								//�������ͼƬ
	loadimage(&enemy[1].init_gun_left, _T("resource\\enemy_gun_left.jpg"), 72, 72);
	loadimage(&enemy[1].init_gun_right, _T("resource\\enemy_gun_right.jpg"), 72, 72);
	loadimage(&enemy[1].init_gun_vice_left, _T("resource\\enemy_gun_vice_left.jpg"), 72, 72);
	loadimage(&enemy[1].init_gun_vice_right, _T("resource\\enemy_gun_vice_right.jpg"), 72, 72);     //��������ͼƬ
	loadimage(&enemy[1].bullet, _T("resource\\enemy_bullet.jpg"), 24, 24);
	loadimage(&enemy[1].bullet_vice, _T("resource\\enemy_bullet_vice.jpg"), 24, 24);				//�����ӵ�ͼƬ
	loadimage(&enemy_bullet_burst, _T("resource\\enemy_bullet_burst.jpg"), 216, 72);
	
	//BOSS
	enemy[2].amount = 0;
	enemy[2].old_amount = 0;
	enemy[2].damage = 3;
	enemy[2].HP_MAX = 200;
	enemy[2].Espeed = 4;
	enemy[2].pic_left = 67;
	enemy[2].pic_right = 133;
	enemy[2].pic_top = 67;
	enemy[2].pic_bottom = 151;                 //��ʼ����������
	loadimage(&enemy[2].model_vice, _T("resource\\BOSS_vice.jpg"), 800, 600);
	loadimage(&enemy[2].model, _T("resource\\BOSS.jpg"), 800, 600);								//�������ͼƬ
	loadimage(&enemy[2].bullet, _T("resource\\enemy_bullet.jpg"), 24, 24);
	loadimage(&enemy[2].bullet_vice, _T("resource\\enemy_bullet_vice.jpg"), 24, 24);				//�����ӵ�ͼƬ
	loadimage(&enemy_bullet_burst, _T("resource\\enemy_bullet_burst.jpg"), 216, 72);

}

int enemy_generate(int left, int top, int right, int bottom, int spc, int range)  
{
	int amt, amount;
	int dir;

	if (range > 1)
		amount = rand() % (range - 1) + 2;   //��������Χ�������,����Ϊ2ֻ
	else if (range == 1) amount = 1;
	else amount = 0;

	for (amt = 0; amt < amount; amt++, enemy[spc].amount++) {
		while (1) {
			enemy[spc].num[enemy[spc].amount].x = left + rand() % (right - left - 120);
			enemy[spc].num[enemy[spc].amount].y = top + rand() % (bottom - top - 120);      //���λ������

			//�жϹ����ж��㷶Χ�����ϰ�
			if (object[enemy[spc].num[enemy[spc].amount].x + enemy[spc].pic_left][enemy[spc].num[enemy[spc].amount].y + enemy[spc].pic_top] == FLOOR
				&& object[enemy[spc].num[enemy[spc].amount].x + enemy[spc].pic_right][enemy[spc].num[enemy[spc].amount].y + enemy[spc].pic_top] == FLOOR
				&& object[enemy[spc].num[enemy[spc].amount].x + enemy[spc].pic_left][enemy[spc].num[enemy[spc].amount].y + enemy[spc].pic_bottom] == FLOOR
				&& object[enemy[spc].num[enemy[spc].amount].x + enemy[spc].pic_right][enemy[spc].num[enemy[spc].amount].y + enemy[spc].pic_bottom] == FLOOR)
			{
				enemy[spc].num[enemy[spc].amount].HP = enemy[spc].HP_MAX;						//HP��ʼ��
				enemy[spc].num[enemy[spc].amount].is_damaged = 0;								//�����ж���ʼ��
				enemy[spc].num[enemy[spc].amount].spin = 0;										//������ת�ǳ�ʼ��
				enemy[spc].num[enemy[spc].amount].think = 0;
				enemy[spc].num[enemy[spc].amount].move = 0;										//��ʼ����Ϊ�ֻ�����
				enemy[spc].num[enemy[spc].amount].damaged_cnt = 0;
				enemy[spc].num[enemy[spc].amount].think_time = 0;
				enemy[spc].num[enemy[spc].amount].move_time = 0;
				enemy[spc].num[enemy[spc].amount].back_time = 0;
				enemy[spc].num[enemy[spc].amount].attack_time = 0;
				enemy[spc].num[enemy[spc].amount].not_cnt = 0;
				enemy[spc].num[enemy[spc].amount].is_cnt = 0;
				enemy[spc].num[enemy[spc].amount].direction_cnt = 0;
				enemy[spc].num[enemy[spc].amount].back_cnt = 0;
				enemy[spc].num[enemy[spc].amount].attack_cnt = 0;								//��ʼ�����м�ʱ����ȴ									
				for (dir = 0; dir < 5; dir++) {
					enemy[spc].num[enemy[spc].amount].direction_time[dir] = 0;					//��ʼ����������
				}
				break;																		    //���ɳɹ�
			}
		}
	}

	return amount; //�������ɵ�����
}

void enemy_show(int spc, int num) 
{
	//��ʾ������ͼ��ÿһ֡ͼƬ���Ǳ߳�120��������
	//��ͼλ�����껻�㣺�����ڴ����е����� = �����ڵ�ͼ�е����� - ��ǰ��ͼ�ڴ����е�����
	IMAGE enemy_gun_left, enemy_gun_right, enemy_gun_vice_left, enemy_gun_vice_right;

	putimage(enemy[spc].num[num].x - map.x, enemy[spc].num[num].y - map.y, 120, 120, &enemy[spc].model_vice,
		enemy[spc].num[num].pic_x * 120, enemy[spc].num[num].pic_y * 120, NOTSRCERASE);

	if (enemy[spc].num[num].is_damaged == 1) {
		putimage(enemy[spc].num[num].x - map.x, enemy[spc].num[num].y - map.y, 120, 120, &enemy[spc].model,
			enemy[spc].num[num].pic_x * 120, enemy[spc].num[num].pic_y * 120, DSTINVERT);
		if (enemy[spc].num[num].damaged_cnt == 2) {
			enemy[spc].num[num].damaged_cnt = 0;
			enemy[spc].num[num].is_damaged = 0;
		}
		else enemy[spc].num[num].damaged_cnt++;
	}

	else {
		putimage(enemy[spc].num[num].x - map.x, enemy[spc].num[num].y - map.y, 120, 120, &enemy[spc].model,
			enemy[spc].num[num].pic_x * 120, enemy[spc].num[num].pic_y * 120, SRCINVERT);
	}

	if (spc == 1 && enemy[spc].num[num].HP > 0)
	{
		if (enemy[spc].num[num].aspect == RIGHT)
		{
			rotateimage(&enemy_gun_vice_right, &enemy[spc].init_gun_vice_right, enemy[spc].num[num].spin, BLACK, true, true);
			rotateimage(&enemy_gun_right, &enemy[spc].init_gun_right, enemy[spc].num[num].spin, WHITE, true, true);

			putimage(enemy[spc].num[num].x - map.x + 60 - enemy_gun_vice_right.getwidth() / 2, 
				enemy[spc].num[num].y - map.y + 80 - enemy_gun_vice_right.getheight() / 2, &enemy_gun_vice_right, NOTSRCERASE);
			putimage(enemy[spc].num[num].x - map.x + 60 - enemy_gun_right.getwidth() / 2, 
				enemy[spc].num[num].y - map.y + 80 - enemy_gun_right.getheight() / 2, &enemy_gun_right, SRCINVERT);
		}
		if (enemy[spc].num[num].aspect == LEFT)
		{
			rotateimage(&enemy_gun_vice_left, &enemy[spc].init_gun_vice_left, enemy[spc].num[num].spin, BLACK, true, true);
			rotateimage(&enemy_gun_left, &enemy[spc].init_gun_left, enemy[spc].num[num].spin, WHITE, true, true);

			putimage(enemy[spc].num[num].x - map.x + 60 - enemy_gun_vice_left.getwidth() / 2, 
				enemy[spc].num[num].y - map.y + 80 - enemy_gun_vice_left.getheight() / 2, &enemy_gun_vice_left, NOTSRCERASE);
			putimage(enemy[spc].num[num].x - map.x + 60 - enemy_gun_left.getwidth() / 2, 
				enemy[spc].num[num].y - map.y + 80 - enemy_gun_left.getheight() / 2, &enemy_gun_left, SRCINVERT);
		}
	}

}

int isdetected(int spc, int num)
{
	int dx;								//���ﵽ����ж����ĺ���������
	int dy;								//���ﵽ����ж���������������
	int path;							//���ﵽ���·��ģ��
	double distance;					//���ﵽ��ҵľ���
	double cos;							//���ﵽ��Ҽн�����ֵ��ͼ������ϵ��
	double sin;							//���ﵽ��Ҽн�����ֵ��ͼ������ϵ��
	int result;							//�������

	dx = character_position.x - (enemy[spc].num[num].x - map.x);
	dy = character_position.y - (enemy[spc].num[num].y - map.y);    

	distance = sqrt(dx * dx + dy * dy);
	cos = dx / distance;
	sin = dy / distance;

	//��12Ϊ�������ع��ﵽ���·���жϣ������ϰ������谭
	for (path = 12; path < (int)distance; path += 12) {
		if (object[enemy[spc].num[num].x + 60 + (int)(path * cos)][enemy[spc].num[num].y + 60 + (int)(path * sin)] == IMMORTAL_OBJ)
			break;
	}
	if (path >= (int)distance) result = 1;    //�������	
	else result = 0;						  //δ�������

	return result;							  //���ط������
}

void enemy_shoot(int spc, int num)
{
	BULLET *Blt;

	Blt = (BULLET*)malloc(sizeof(BULLET));
	Blt->spin = enemy[spc].num[num].spin;
	Blt->hit = 0;
	Blt->burst_cnt = 0;
	Blt->spc = spc;
	if (enemy[spc].num[num].aspect == RIGHT) {
		Blt->position.x = enemy[spc].num[num].x + 60 - (int)((36 * sin(Blt->spin)) + 4 * cos(Blt->spin));
		Blt->position.y = enemy[spc].num[num].y + 80 - (int)((36 * cos(Blt->spin)) - 4 * sin(Blt->spin));
	}
	if (enemy[spc].num[num].aspect == LEFT) {
		Blt->position.x = enemy[spc].num[num].x + 60 - (int)((36 * sin(Blt->spin)) - 4 * cos(Blt->spin));
		Blt->position.y = enemy[spc].num[num].y + 80 - (int)((36 * cos(Blt->spin)) + 4 * sin(Blt->spin));
	}
	Blt->next = NULL;
	if (Ehead == NULL) Ehead = Blt;
	else Etail->next = Blt;
	Etail = Blt;

}

void enemy_bullet()
{
	BULLET *Blt, *sBlt;
	int mx, my;

	for (sBlt = NULL, Blt = Ehead; Blt;)
	{
		if (Blt->hit == 0)
		{
			if (knight.HP > 0) {
				if (knight.left + map.x <= Blt->position.x && knight.right + map.x >= Blt->position.x
					&& knight.top + map.y <= Blt->position.y && knight.bottom + map.y >= Blt->position.y)
				{
					Blt->hit = 1;
				}
				else {
					for (Blt->path = EBspeed / 4; Blt->path < EBspeed; Blt->path += EBspeed / 4) {
						if (knight.left + map.x <= Blt->position.x + (int)(Blt->path * sin(Blt->spin))
							&& knight.right + map.x >= Blt->position.x + (int)(Blt->path * sin(Blt->spin))
							&& knight.top + map.y <= Blt->position.y + (int)(Blt->path * cos(Blt->spin))
							&& knight.bottom + map.y >= Blt->position.y + (int)(Blt->path * cos(Blt->spin)))
						{
							Blt->hit = 2;
							break;
						}
					}
				}
			}
		}

		if (object[Blt->position.x][Blt->position.y] == FLOOR && Blt->hit == 0)
		{
			putimage(Blt->position.x - enemy[Blt->spc].bullet.getwidth() / 2 - map.x,
				Blt->position.y - enemy[Blt->spc].bullet.getheight() / 2 - map.y, &enemy[Blt->spc].bullet_vice, NOTSRCERASE);
			putimage(Blt->position.x - enemy[Blt->spc].bullet.getwidth() / 2 - map.x,
				Blt->position.y - enemy[Blt->spc].bullet.getheight() / 2 - map.y, &enemy[Blt->spc].bullet, SRCINVERT);

			if (pause == 0) {
				Blt->position.x -= (int)(EBspeed * sin(Blt->spin));
				Blt->position.y -= (int)(EBspeed * cos(Blt->spin));
			}

			sBlt = Blt;
			Blt = Blt->next;
		}
		else {
			if (Blt->hit != 2) {
				putimage(Blt->position.x - 36 - map.x, Blt->position.y - 36 - map.y, 72, 72, &bullet_burst_vice, Blt->burst_cnt / 3 * 72, 0, NOTSRCERASE);
				putimage(Blt->position.x - 36 - map.x, Blt->position.y - 36 - map.y, 72, 72, &enemy_bullet_burst, Blt->burst_cnt / 3 * 72, 0, SRCINVERT);
			}
			else {
				putimage(Blt->position.x + (int)(Blt->path * sin(Blt->spin)) - 36 - map.x, Blt->position.y + (int)(Blt->path * cos(Blt->spin)) - 36 - map.y,
					72, 72, &bullet_burst_vice, Blt->burst_cnt / 3 * 72, 0, NOTSRCERASE);
				putimage(Blt->position.x + (int)(Blt->path * sin(Blt->spin)) - 36 - map.x, Blt->position.y + (int)(Blt->path * cos(Blt->spin)) - 36 - map.y,
					72, 72, &enemy_bullet_burst, Blt->burst_cnt / 3 * 72, 0, SRCINVERT);
			}

			if (Blt->burst_cnt == 0 && Blt->hit != 0) {

				if (knight.AM > 0) {
					if (enemy[Blt->spc].damage > knight.AM)knight.AM = 0;
					else knight.AM -= enemy[Blt->spc].damage;			  //������ʧ�ж�
				}
				else if (knight.HP > 0) {
					if (enemy[Blt->spc].damage > knight.HP)knight.HP = 0;
					else knight.HP -= enemy[Blt->spc].damage;			  //HP��ʧ�ж�
				}
				player_damaged = 1;									  //��ұ����ж�
																	  //��ұ�����Ч
				mciSendString(_T("close resource\\player_hurt.wav"), NULL, 0, NULL);
				mciSendString(_T("play resource\\player_hurt.wav"), NULL, 0, NULL);

				armor_cnt = 0;										  //���׻ظ���ʱ����
				mx = -(int)(30 * sin(Blt->spin));
				my = -(int)(30 * cos(Blt->spin));
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
			}

			if (Blt->burst_cnt == 6) {
				if (Blt == Ehead) {
					Ehead = Blt->next;
					free(Blt);
					Blt = Ehead;
				}
				else {
					sBlt->next = Blt->next;
					if (Blt == Etail) Etail = sBlt;
					free(Blt);
					Blt = sBlt->next;
				}
			}
			else {
				if (pause == 0) Blt->burst_cnt++;
				sBlt = Blt;
				Blt = Blt->next;
			}
		}
	}
}