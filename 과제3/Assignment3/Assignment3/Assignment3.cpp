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

class Account {
private:
	char UserName[MAX_STRING + 1];
	char UserSSN[MAX_STRING + 1];
	char UserID[MAX_STRING + 1];
	char UserPW[MAX_STRING + 1];
	int SoldedItemPrice;
	float AvgRating;

public:
	bool check = 0;

	void saveAcct(const char* str1, const char* str2, const char* str3, const char* str4) {
		strcpy_s(UserName, MAX_STRING + 1, str1);
		strcpy_s(UserSSN, MAX_STRING, str2);
		strcpy_s(UserID, MAX_STRING, str3);
		strcpy_s(UserPW, MAX_STRING, str4);
		SoldedItemPrice = 0;
		AvgRating = 0;
		check = 1;
	};
	//void deleteAcct() {};
	bool Find(const char* str1, const char* str2) {
		if (strcmp(UserID, str1) == 0 && strcmp(UserPW, str2) == 0)
			return 1;
		else return 0;
	};
	void GetIDPW(char* temp1, char* temp2)
	{
		strcpy_s(temp1, MAX_STRING, UserID);
		strcpy_s(temp2, MAX_STRING, UserPW);
	}
	//void getStatics() {};

};

FILE* in_fp, * out_fp;
Account Acct[100];
int my_idx = -1;
int main()
{
	errno_t input = fopen_s(&in_fp, INPUT_FILE_NAME, "r");
	errno_t ouput = fopen_s(&out_fp, OUTPUT_FILE_NAME, "w");

	doTask();

}

void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;
	while (!is_program_exit)
	{
		fscanf_s(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

		cout << menu_level_1 << " " << menu_level_2 << endl;//�Է� ����� �Ǵ��� Ȯ�ο� �ڵ�. ��������
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
			break;
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
			break;
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
			break;
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
			break;
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
				break;
		}
		case 6:
		{
			switch (menu_level_2)
			{
				case 1:
				{
					program_exit();
					is_program_exit = 1;
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
//�Ʒ��� �Լ� ����

void SignUp()
{
	char name[MAX_STRING], SSN[MAX_STRING], ID[MAX_STRING], PW[MAX_STRING];
	fscanf_s(in_fp, "%s %s %s %s", name, sizeof(name), SSN, sizeof(SSN), ID, sizeof(ID), PW, sizeof(PW));
	for (int i = 0; i < 100; i++)
	{
		if (Acct[i].check == 0)
		{
			Acct[i].saveAcct(name, SSN, ID, PW);
			break;
		}
	}
	fprintf_s(out_fp, "1.1. ȸ������\n");
	fprintf_s(out_fp, "> %s %s %s %s\n", name, SSN, ID, PW);
}

void Withdrawal()
{
	if (my_idx >= 0)
	{
		char ID[MAX_STRING], PW[MAX_STRING];
		Acct[my_idx].GetIDPW(ID, PW);
		Acct[my_idx].check = 0;
		my_idx = -1;
		fprintf_s(out_fp, "1.2. ȸ��Ż��\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ȸ��Ż�� �Ұ����մϴ�.\n");
	}
}

void LogIn()
{
	bool flag = 0; // ȸ������ �ƴ��� Ȯ���ϴ� flag
	char ID[MAX_STRING], PW[MAX_STRING];
	fscanf_s(in_fp, "%s %s", ID, sizeof(ID), PW, sizeof(PW));
	for (int i = 0; i < 100; i++)
	{
		if (Acct[i].Find(ID, PW) == 1)
		{
			fprintf_s(out_fp, "2.1. �α���\n");
			fprintf_s(out_fp, "> %s %s\n", ID, PW);
			my_idx = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0) // ȸ���� �ƴ� ���
	{
		fprintf_s(out_fp, "> ȸ�� ����� ���� �ʾ� �α����� �Ұ����մϴ�\n");
	}
}

void LogOut()
{
	if (my_idx >= 0)
	{
		char ID[MAX_STRING], PW[MAX_STRING];
		Acct[my_idx].GetIDPW(ID, PW);
		my_idx = -1;
		fprintf_s(out_fp, "2.2. �α׾ƿ�\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� �α׾ƿ��� �Ұ����մϴ�.\n");
	}
}

void InputItem()
{
}

void GetItem()
{
}

void GetSoldedItem()
{
}

void InputClothesName()
{
}

void Buy()
{
}

void GetBuyItem()
{
}

void Evaluating()
{
}

void GetStatics()
{
}

void program_exit()
{
	fprintf_s(out_fp, "6.1. ����\n");
}