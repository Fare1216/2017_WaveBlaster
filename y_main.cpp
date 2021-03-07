/*-----�c:480 �~ ��:640-----*/

#include "DxLib.h"
#include"Resource.h"


/*-----�摜�ǂݍ��ݗp�ϐ�-----*/
int y_button[5]; //�{�^���摜
int y_back[5];   //�o�b�N�X�N���[��
int Charcter;    //�L�����N�^�[�摜
int Magic[2];    //���@�w�摜

int sum_click, sum_start; //�N���b�N����ꏊ�̉摜
int sum_time_gra[11]; //�Q�[���̎��Ԃ̉摜


typedef enum{
	TitleLeady,
	Title,
	CreditLeady,
	Credit,
	AboutLeady,
	About,
	ChargeLeady,
	Charge,
	LaserLeady,
	LaserStart,
	LaserScroll,
	LaserLastReady,
	LaserLast,
	ResaltLeady,
	Resalt,
}eScene;


int Scene = TitleLeady;

int mx;        //�}�E�Xx���W
int my;        //�}�E�Xy���W
int Mouse;     //�}�E�X�ʒu
int cflag = 0; //�N���b�N�̃t���O

int sum_count; //�N���b�N������
int sum_time = 10; //��������
int sum_tflag = 0; //���Ԃ̃t���O
int sum_sflag = 0; //�Q�[���J�n�̃t���O
int sum_x = 320, sum_y = 240, sum_max_x = 520, sum_max_y = 440; //�N���b�N����ꏊ�̍��W
int sum_time_x = 520, sum_time_y = 20; //���Ԃ̉摜��\��������W

int kf_Laser, kf_sLaser;//���[�U�[�̉摜
int kf_Back[4];//�w�i�̉摜
int Laser_x = 250, Lasers_x = 0;
int Back_x = 0;//�w�i��X���W
int Back2_x = 640;
int kf_fps = 0;//�t���[�����[�g��ǂݍ���
int i, j;//���[�v�Ŏg��
int Time = 0;//���Ԃ𑪂�

int kf_flag = 0;
int kf_clickcount = 0;
int kf_cflag = 0;

int score_1 = 0,score_10 = 0,score_100 = 0;

void sum_chage(); //�Q�[���̃��C���̊֐�
void sum_startflag(); //�N���b�N������Q�[�����X�^�[�g������֐�
void sum_timer(); //�N���b�N����Ƃ��̎���

void LaserGraph();
void kf_loadgraph();
void kf_Timer();

void Score();

void Graph(); //�摜�ǂݍ��ݗp�֐�


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	DxLib::SetWindowTextA("Wave Blaster"); //�^�C�g�����Z�b�g
	SetWindowIconID(ID_ICON); //�A�C�R�����Z�b�g

	Graph();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)){

		/*-----�}�E�X���W�@�擾-----*/
		Mouse = GetMouseInput();
		GetMousePoint(&mx, &my);


		switch (Scene){

		case TitleLeady:{

			Scene = Title;
			break;
		}

		case Title:{
			DrawGraph(   0,   0,   y_back[0],   FALSE);
			DrawGraph(  80, 380, y_button[0], FALSE);
			DrawGraph( 400, 380, y_button[1], FALSE);
			
			/*-----Start�@�I��-----*/
			if (80 <= mx && mx < 240 && 380 <= my && my < 440){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = AboutLeady;
					cflag = 1;
				}
			}
			/*-----Credit�@�I��-----*/
			if (400 <= mx && mx < 560 && 380 <= my && my < 440){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = CreditLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case CreditLeady:{

			Scene = Credit;
			break;
		}

		case Credit:{
			DrawGraph(0, 0, y_back[1], FALSE);

			/*-----�N���b�N������^�C�g����-----*/
			if (0 <= mx && mx < 640 && 0 <= my && my < 480){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = TitleLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case AboutLeady:{

			Scene = About;
			break;
		}

		case About:{
			DrawGraph(0, 0, y_back[2], FALSE);

			/*-----�N���b�N���ăQ�[���J�n-----*/
			if (0 <= mx && mx < 640 && 0 <= my && my < 480){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = ChargeLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case ChargeLeady:{
			sum_time = 10;
			sum_count = 0;
			sum_sflag = 0;

			Scene = Charge;
			break;
		}

		case Charge:{
			DrawGraph(0, 0, y_back[3], FALSE);

			if (sum_sflag == 0){
				sum_startflag();
			}
			else if (sum_sflag == 1){
				sum_chage();
				sum_timer();
			}
			if (sum_time == 0){
				Scene = LaserLeady;
			}

			break;
		}

		case LaserLeady:{

			kf_flag = 0;
			kf_cflag = 0;
			Time = 0;
			Laser_x = 250;
			Lasers_x = 0;
			kf_clickcount = sum_count;
			Back_x = 0, Back2_x = 640;

			Scene = LaserStart;
			break;
		}

		case LaserStart:{

			DrawGraph(   0,  0, kf_Back[0], TRUE); //�w�i�̕`��
			DrawGraph(   0,  0, Magic[0], TRUE);
			DrawGraph(   0,  0, Charcter, TRUE);
			if (kf_cflag == 0){
				DrawGraph(330, 30, y_button[2], FALSE);
			}
			/*-----�N���b�N���ă��[�U�[����-----*/
			if (330 <= mx && mx < 610 && 30 <= my && my < 130 && cflag == 0 && Mouse & MOUSE_INPUT_LEFT){
					kf_cflag = 1;
					cflag = 1;
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			if (kf_cflag == 1){
				LaserGraph();

				if (Laser_x <= 640){
					Laser_x += 50;
				}
				else{
					kf_flag = 1;
				}

				if (kf_flag == 1){
					kf_Timer();
					if (Time == 1){
						Time = 0;
						Scene = LaserScroll;
					}
				}
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			break;
		}

		case LaserScroll:{

			DrawGraph(Back_x, 0, kf_Back[1], TRUE); //�w�i�̕`��
			DrawGraph(Back2_x, 0, kf_Back[2], TRUE); //�w�i�̕`��

			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			LaserGraph();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			if (Lasers_x <= 320){
				Lasers_x += 50;
			}
			else if (Lasers_x > 320){

				Back_x -= 10;
				Back2_x -= 10;

				if (Back_x == -640){
					Back_x = 640;
				}
				if (Back2_x == -640){
					Back2_x = 640;
				}
				kf_Timer();
			}

			if (Time == (kf_clickcount / 30 + 1)){
				Time = 0;
				Scene = LaserLastReady;
			}

			break;
		}

		case LaserLastReady:{

			Scene = LaserLast;
			break;
		}

		case LaserLast:{
			DrawGraph(0, 0, kf_Back[3], TRUE); //�w�i�̕`��

			/*-----�N���b�N�����烊�U���g��-----*/
			if (0 <= mx && mx < 640 && 0 <= my && my < 480){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = ResaltLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case ResaltLeady:{

			Scene = Resalt;
			break;
		}

		case Resalt:{
			DrawGraph(   0,   0,   y_back[4], FALSE);
			DrawGraph(  80, 340, y_button[3], FALSE);
			DrawGraph( 400, 340, y_button[4], FALSE);

			Score();

			/*-----�^�C�g���ց@�I��-----*/
			if (80 <= mx && mx < 240 && 340 <= my && my < 400){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = TitleLeady;
					cflag = 1;
				}
			}
			/*-----������x�@�I��-----*/
			if (400 <= mx && mx < 560 && 340 <= my && my < 400){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = ChargeLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		}

	}

	DxLib_End();
	return 0;
}


void Graph(){

	/*-----Fare-----*/
	y_button[0] = LoadGraph("WaveBlaster/Start_B.png");
	y_button[1] = LoadGraph("WaveBlaster/Credit_B.png");
	y_button[2] = LoadGraph("WaveBlaster/Launch!!.png");
	y_button[3] = LoadGraph("WaveBlaster/BackT_B.png");
	y_button[4] = LoadGraph("WaveBlaster/OneMore_B.png");

	y_back[0] = LoadGraph("WaveBlaster/Title.png");
	y_back[1] = LoadGraph("WaveBlaster/Credit.png");
	y_back[2] = LoadGraph("WaveBlaster/About.png");
	y_back[3] = LoadGraph("WaveBlaster/Charge.png");
	y_back[4] = LoadGraph("WaveBlaster/Resalt.png");

	Charcter = LoadGraph("WaveBlaster/Charcter1.png");

	Magic[0] = LoadGraph("WaveBlaster/Magic_Front1.png");
	Magic[1] = LoadGraph("WaveBlaster/Magic_Under.png");

	/*-----sum-----*/
	sum_click = LoadGraph("WaveBlaster/Click!!.png");
	sum_start = LoadGraph("WaveBlaster/Start.png");

	sum_time_gra[0] = LoadGraph("WaveBlaster/0.png");
	sum_time_gra[1] = LoadGraph("WaveBlaster/1.png");
	sum_time_gra[2] = LoadGraph("WaveBlaster/2.png");
	sum_time_gra[3] = LoadGraph("WaveBlaster/3.png");
	sum_time_gra[4] = LoadGraph("WaveBlaster/4.png");
	sum_time_gra[5] = LoadGraph("WaveBlaster/5.png");
	sum_time_gra[6] = LoadGraph("WaveBlaster/6.png");
	sum_time_gra[7] = LoadGraph("WaveBlaster/7.png");
	sum_time_gra[8] = LoadGraph("WaveBlaster/8.png");
	sum_time_gra[9] = LoadGraph("WaveBlaster/9.png");
	sum_time_gra[10] = LoadGraph("WaveBlaster/10.png");

	/*-----kakifurai-----*/
	kf_sLaser = LoadGraph("WaveBlaster/Laser1.png");
	kf_Laser = LoadGraph("WaveBlaster/Laser2.png");
	kf_Back[0] = LoadGraph("WaveBlaster/wb back.png");
	kf_Back[1] = LoadGraph("WaveBlaster/wb back����.png");
	kf_Back[2] = LoadGraph("WaveBlaster/wb back.png");
	kf_Back[3] = LoadGraph("WaveBlaster/Finish.png");


}
void sum_chage(){
	if (mx>sum_x && mx<sum_max_x && my>sum_y && my<sum_max_y && Mouse & MOUSE_INPUT_LEFT && cflag == 0 && sum_tflag != 0){
			sum_count++;
			cflag = 1;	
	}
	if (Mouse & MOUSE_INPUT_LEFT){
		cflag = 1;
	}
	else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
		cflag = 0;
	}

	DrawGraph( 0, 0, Magic[0], TRUE);
	DrawGraph( 0, 0, Charcter, TRUE);
	DrawGraph( sum_x, sum_y, sum_click, FALSE);
}
void sum_startflag(){
	if (mx>sum_x && mx<sum_max_x && my>sum_y && my<sum_max_y && cflag == 0 && Mouse & MOUSE_INPUT_LEFT){
			cflag = 1;
			sum_sflag = 1;
	}
	if (Mouse & MOUSE_INPUT_LEFT){
		cflag = 1;
	}
	else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
		cflag = 0;
	}

	DrawGraph( 0, 0, Charcter, TRUE);
	DrawGraph( sum_x, sum_y, sum_start, FALSE);
}
void sum_timer(){
	if (sum_time>0){
		sum_tflag++;
	}
	if (sum_tflag == 60){
		sum_time--;
		sum_tflag = 0;
	}
	DrawGraph( sum_time_x, sum_time_y, sum_time_gra[sum_time], TRUE);
}
void LaserGraph(){
	if (Scene == LaserStart){
		DrawGraph(250, 100, kf_sLaser, TRUE);
		if (Laser_x >= 320)
			DrawGraph(320, 100, kf_Laser, TRUE);
		for (i = 1; i <= (Laser_x - 320) % 50; i++){
			if (Laser_x >= 320 + i * 50)
				DrawGraph(320 + i * 50, 100, kf_Laser, TRUE);
		}
	}
	if (Scene == LaserScroll){
		DrawGraph(0, 100, kf_Laser, TRUE);
		if (Lasers_x >= 50)
			DrawGraph(50, 100, kf_Laser, TRUE);
		if (Lasers_x >= 100)
			DrawGraph(100, 100, kf_Laser, TRUE);
		if (Lasers_x >= 150)
			DrawGraph(150, 100, kf_Laser, TRUE);
		if (Lasers_x >= 200)
			DrawGraph(200, 100, kf_Laser, TRUE);
		if (Lasers_x >= 250)
			DrawGraph(250, 100, kf_Laser, TRUE);
		if (Lasers_x >= 300)
			DrawGraph(300, 100, kf_Laser, TRUE);
		if (Lasers_x >= 320)
			DrawGraph(320, 100, kf_Laser, TRUE);
	}
}
void kf_Timer(){
	kf_fps++;
	if (kf_fps == 60){
		Time++;
		kf_fps = 0;
	}
}
void Score(){
	score_100 = sum_count / 100;
	score_10 = sum_count % 100 / 10;
	score_1 = sum_count % 10;
	DrawGraph(170, 100, sum_time_gra[score_100],TRUE);
	DrawGraph(270, 100, sum_time_gra[score_10], TRUE);
	DrawGraph(370, 100, sum_time_gra[score_1], TRUE);
}