#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

void doTask();
void SignUp();//1 1
void Withdrawal();//1 2
void LogIn();//2 1
void LogOut();//2 2
void InputItem();//3 1
void GetItem();//3 2
void GetSoldedItem();//3 3
void InputClothesName();//4 1
void Buy();//4 2
void GetBuyItem();//4 3
void Evaluating();//4 4
void GetStatics();//5 1
void program_exit();//6 1

//FILE* in_fp, * out_fp;

int main() 
{
	//FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
	//FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");
	doTask();


}

void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	ifstream input_file(INPUT_FILE_NAME);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<<INPUT_FILE_NAME << "'" << endl;
		return;
	}//input.txt를 발견하지 못하거나 없으면 에러 코드
	//input.txt 파일 위치 = "C:\Users\"본인 사용자명"\SE\과제3\Assignment3\Assignment3\input.txt"
	while (!input_file.eof() || !is_program_exit)
	{
		input_file >> menu_level_1 >> menu_level_2;
		cout << menu_level_1 << " " << menu_level_2 << endl;//입력 제대로 되는지 확인용 코드. 지워도됨
		switch (menu_level_1)
		{
			case 1:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						SignUp();
						break;
					}
					case 2:
					{
						Withdrawal();
						break;
					}
					default:
						break;
				}

			}
			case 2:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						LogIn();
						break;
					}
					case 2:
					{
						LogOut();
						break;
					}
					default:
						break;
				}
			}
			case 3:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						InputItem();
						break;
					}
					case 2:
					{
						GetItem();
						break;
					}
					case 3:
					{
						GetSoldedItem();
						break;
					}
					default:
						break;
				}
			}
			case 4:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						InputClothesName();
						break;
					}
					case 2:
					{
						Buy();
						break;
					}
					case 3:
					{
						GetBuyItem();
						break;
					}
					case 4:
					{
						Evaluating();
						break;
					}
					default:
						break;
				}
			}
			case 5:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						GetStatics();
						break;
					}
					default:
						break;
				}
			}
			case 6:
			{
				switch (menu_level_2)
				{
					case 1:
					{
						program_exit();
						break;
					}
				}
			}
			default:
				break;
		}
	}
	return;
}
//아래에 함수 구현