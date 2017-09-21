#ifndef SOUL_KNIGHT
#define SOUL_KNIGHT


#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib,"Winmm.lib")


#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c) & 0x8000 ? 1 : 0)  //�����ж�
#define window_width   1280 
#define window_height  720                  //���ڴ�С
#define speed          14                   //����ƶ��ٶ�
#define EBspeed        15                   //�����ӵ��ƶ��ٶ�
#define RIGHT          0					//��ɫ�����ң�
#define LEFT           1                    //��ɫ������
#define VK_Z           0x5A					//z����
#define VK_X           0x58					//x����
#define KEY_ESC        27					//ESC ASCII��
#define KEY_RIGHT      77					//�ҷ���� ASCII��
#define KEY_LEFT       75                   //����� ASCII��
#define PI             3.1415926536			//Բ����
#define FLOOR          1					//�ذ�ȿ�����λ��
#define GATEWAY        2					//������
#define CRYSTAL        3					//ˮ�����Ʒ�Χ
#define IMMORTAL_OBJ   0					//ǽ�ڵȲ�������/�ƻ���Ʒ
#define SPECIES        3					//��������
#define WEAPONS        2					//��������
#define STAGE		   4					//�ؿ�����


typedef struct weapon {
	char *name;			//��������
	int damage;			//����������
	int cost;			//��������
	int swift;			//��������
	int Bspeed;			//�ӵ��ƶ��ٶ�
	double accuracy;	//������׼��
	double spin;		//������ת��
	IMAGE left;			//���ͼ��
	IMAGE right;		//�Ҳ�ͼ��
	IMAGE v_left;		//����ڱ�ͼ
	IMAGE v_right;		//�Ҳ��ڱ�ͼ
} Weapon;				//������Ϣ�ṹ��

typedef struct player {
	const int HP_MAX = 7;	//HP����
	const int AM_MAX = 6;	//AM����
	const int MP_MAX = 200;	//MP����
	int left;				//�����ж���������꣨���ڣ�
	int right;				//�����ж����Ҳ����꣨���ڣ�
	int top;				//�����ж��㶥�����꣨���ڣ�
	int bottom;				//�����ж���ײ����꣨���ڣ�
	POINT center;			//�����ж������ĺ������꣨���ڣ�
	int HP;					//��ǰHP
	int AM;					//��ǰAM
	int MP;					//��ǰMP
	int aspect;				//���ﳯ��
	int weapon_number;		//��ǰЯ���������
} Player;					//������Ϣ�ṹ��

typedef struct enemy_status {
	int x;					//��ͼ��׼������
	int y;					//��ͼ��׼������
	int pic_x;				//����ͼ��
	int pic_y;				//����ͼ��
	double spin;			//Զ�̹���������ת��
	int think;				//˼����Ϊʱ���������
	int move;				//�ƶ���Ϊʱ���������
	int think_time;			//˼������ʱ��
	int move_time;			//�ƶ�����ʱ��	
	int direction_time[5];	//���������ʱ��
	int back_time;			//���˳���ʱ��
	int attack_time;		//������ȴʱ��
	int not_cnt;			//δ����״̬��ʱ�����
	int is_cnt;				//����״̬��ʱ�����
	int direction_cnt;		//������ʱ�����
	int back_cnt;			//����ʱ�����
	int attack_cnt;			//������ȴʱ�����
	int aspect;				//���ﳯ��
	int HP;					//��ǰѪ��
	int is_damaged;			//�����ж�
	int damaged_cnt;		//����Ӳֱʱ��
} enemy_status;				//����������Ϣ�ṹ��

typedef struct enemy_species {
	int amount;				//��������
	int old_amount;			//�����ڹ�������
	enemy_status num[50];	//ͬ�ֵĹ�����
	int pic_left;			//ͼƬ�й���ͼ���ͼƬ�߿�������
	int pic_right;			//ͼƬ�й���ͼ���ͼƬ�߿��Ҳ����
	int pic_top;			//ͼƬ�й���ͼ���ͼƬ�߿򶥲�����
	int pic_bottom;			//ͼƬ�й���ͼ���ͼƬ�߿�ײ�����
	int HP_MAX;				//HP����
	int damage;				//������
	int Espeed;				//�ƶ��ٶ�
	IMAGE model;
	IMAGE model_vice;
	IMAGE init_gun_left;
	IMAGE init_gun_right;
	IMAGE init_gun_vice_left;
	IMAGE init_gun_vice_right;
	IMAGE bullet;
	IMAGE bullet_vice;
} enemy_species;			//��������ṹ��

typedef struct bullet
{
	POINT position;			//�ӵ����ĵ�����
	double spin;			//�ӵ������
	int Bspeed;				//�ӵ��ƶ��ٶ�
	int hit;				//�ӵ����е������
	int path;				//�ӵ�����·��ģ��
	int burst_cnt;			//�ӵ�ը��Ч����ʱ
	int spc;				//�����ӵ���������
	struct bullet *next;
}BULLET;					//�洢�ӵ���Ϣ������


VOID CALLBACK timer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void start_menu();						//��ʼ�������
void pause_menu();						//��ͣ�������
void pause_back();						//��ͣ�������
void startup_music();					//���ֳ�ʼ��
void startup_menu_show();				//�˵���ʼ��
void startup_map_show();				//��ͼ��ʼ��
void startup_status_show();				//����״̬��ʼ��
void startup_weapon_show();				//������ʼ��
void startup_character_show();			//�����ʼ��
void map_show();						//��ͼ��ʾ���
void character_show();					//������ʾ���
void transform();						//���ش��Ͷ���
int auto_aiming();						//�Զ���׼���
void bullet_show();						//�ӵ���ʾ���
void status_show();						//״̬����ʾ
void armor_recover();					//���׻ظ�
void operate_control();					//������Ƽ��̲������
void operate_select();					//�˵�ѡ����̲������
void startup_enemy();					//������Ϣ��ʼ��
void obj_mark(int left, int top, int right, int bottom, int obj);  //��ָ�������ڵĵ�ͼ������Ϊָ����Ʒ����
int enemy_generate(int left, int top, int right, int bottom, int spc, int range);  //��ָ�������ڵ��ʵ�λ���������ָ����Χ�����ڵ�ָ���������
void enemy_show(int spc, int num);		//������ʾ���
void enemy_shoot(int spc, int num);		//��������ж�
void enemy_bullet();					//�����ӵ���ʾ���
int isdetected(int spc, int num);		//�жϹ����Ƿ������
void melee_AI(int spc, int num);		//��ս����AI
void shoot_AI(int spc, int num);		//Զ�̹���AI
void BOSS_AI(int spc, int num);			//�������AI
void room1_mid();						//�ؿ�1�м䷿��
void room1_left();						//�ؿ�1��෿��
void room1_down();						//�ؿ�1�·�����
void room2_mid();						//�ؿ�2�м䷿��
void room2_right();						//�ؿ�2�Ҳ෿��
void room2_down();						//�ؿ�2�·�����
void room3_mid();						//�ؿ�3�м䷿��
void room3_right();						//�ؿ�3�Ҳ෿��
void room3_down();						//�ؿ�3�·�����
void room3_downright();					//�ؿ�3���·���
void BOSS_room();						//BOSS����


#endif // !SOUL_KNIGHT

