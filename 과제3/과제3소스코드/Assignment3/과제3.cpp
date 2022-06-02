//�Լ��� �Ű����� ����, �ʿ���� �Լ��� ���� ����

#include<iostream>
#include<fstream>
#include<string.h>
#include "����3.h"
using namespace std;



void doTask();

void program_exit();//6 1

int main()
{
	errno_t input = fopen_s(&in_fp, INPUT_FILE_NAME, "r");
	errno_t ouput = fopen_s(&out_fp, OUTPUT_FILE_NAME, "w");

	doTask();

}

void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int former_menu_level_1 = 0, former_menu_level_2 = 0;
	int is_program_exit = 0;
	while (!is_program_exit)
	{
		former_menu_level_1 = menu_level_1;
		former_menu_level_2 = menu_level_2;

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
				//SignUp();
				SignUp sign_up;
				sign_up.signup();
				break;
			}
			case 2:
			{
				//Withdrawal();
				Withdrawal withdrawal;
				withdrawal.withdrawal();
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
				LogIn login;
				login.login();
				break;
			}
			case 2:
			{
				LogOut logout;
				logout.logout();
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
				AddItem additem;
				additem.additem();
				break;
			}
			case 2:
			{
				GetItem getitem;
				getitem.getitem();
				break;
			}
			case 3:
			{
				GetSoldedItem getsoldeditem;
				getsoldeditem.getsoldedItem();
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
				GetItemInfo getiteminfo;
				getiteminfo.showclothesinfo();
				break;
			}
			case 2:
			{
				BuyItem buyitem;
				buyitem.buy();
				break;
			}
			case 3:
			{
				GetBuyItem getbuyitem;
				getbuyitem.getBuyItem();
				break;
			}
			case 4:
			{
				Evaluate evaluate;
				evaluate.evaluate();
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
				SoldedItemStatics soldeditemstatics;
				soldeditemstatics.getStatics();
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
		current_state.set_current_state(menu_level_1, menu_level_2);
		fprintf_s(out_fp, "\n");
	}
	return;
}
//�Ʒ��� �Լ� ����

/*void SignUp()
{
	char name[MAX_STRING], SSN[MAX_STRING], ID[MAX_STRING], PW[MAX_STRING];
	fscanf_s(in_fp, "%s %s %s %s", name, sizeof(name), SSN, sizeof(SSN), ID, sizeof(ID), PW, sizeof(PW));
	for (int i = 0; i < MAX_ACCOUNT; i++)
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
	//if (my_idx >= 0) 
	if (strcmp(User, "") != 0)
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
	for (int i = 0; i < MAX_ACCOUNT; i++)
	{
		if (Acct[i].Find(ID, PW) == 1)
		{
			fprintf_s(out_fp, "2.1. �α���\n");
			fprintf_s(out_fp, "> %s %s\n", ID, PW);
			strcpy_s(User, MAX_STRING + 1, ID);
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
	//if (my_idx >= 0)
	if (strcmp(User, "") != 0)
	{
		char ID[MAX_STRING], PW[MAX_STRING];
		Acct[my_idx].GetIDPW(ID, PW);
		strcpy_s(User, MAX_STRING + 1, "");
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
	if (strcmp(User, "") != 0)
	{
		char ItemName[MAX_STRING], ItemCompany[MAX_STRING];
		int ItemPrice = 0, ItemQuantity = 0;
		fscanf_s(in_fp, "%s %s %d %d", ItemName, sizeof(ItemName), ItemCompany, sizeof(ItemCompany), &ItemPrice, &ItemQuantity);
		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (Clothes[i].check == 0)
			{
				Clothes[i].AddItemInfo(User, ItemName, ItemCompany, ItemPrice, ItemQuantity);
				break;
			}
		}
		fprintf_s(out_fp, "3.1. �Ǹ� �Ƿ� ���\n");
		fprintf_s(out_fp, "> %s %s %d %d\n", ItemName, ItemCompany, ItemPrice, ItemQuantity);
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� �Ǹ� �Ƿ� ����� �Ұ����մϴ�.\n");
	}
}

void GetItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "3.2. ��� ��ǰ ��ȸ\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getItems(User, num);
		}
		if(num == 0) // ����� ��ǰ�� ���� ���
			fprintf_s(out_fp, "> ����� ��ǰ�� �����ϴ�.\n");
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��� ��ǰ ��ȸ�� �Ұ����մϴ�.\n");
	}
}

void GetSoldedItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "3.3. �Ǹ� �Ϸ� ��ǰ ��ȸ\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getSoldedItemInfo(User,num);
		}
		if(num == 0) //�Ǹ� �Ϸ�� ��ǰ�� ���� ���
			fprintf_s(out_fp, "> �Ǹ� �Ϸ�� ��ǰ�� �����ϴ�.\n");
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� �Ǹ� �Ϸ� ��ǰ ��ȸ�� �Ұ����մϴ�.\n");
	}
}

void InputClothesName()
{
	if (strcmp(User, "") != 0)
	{
		char Name[MAX_STRING];
		int num = 0;
		fscanf_s(in_fp, "%s", Name, sizeof(Name));
		fprintf_s(out_fp, "4.1. ��ǰ ���� �˻�\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getSearchItemInfo(Name, num);
			item_searched_idx = i;
			if(num != 0) //������ for���� 1���� ���Ƽ� �߰��߽��ϴ�
				break;
		}
		if (num == 0)//�˻� ����� �������� �ʴ� ���
		{
			fprintf_s(out_fp, "> �˻� ����� �����ϴ�.\n");
			item_searched_idx = -1;
		}
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��ǰ ���� �˻��� �Ұ����մϴ�.\n");
	}
}

void Buy()
{
	if (strcmp(User, "") != 0)
	{
		int level1 = current_state.get_level1();
		int level2 = current_state.get_level2();
		char seller[MAX_STRING + 1];
		if (level1 == 4 && level2 == 1)
		{
			if (item_searched_idx >= 0)
			{

				fprintf_s(out_fp, "4.2. ��ǰ ����\n");
				Clothes[item_searched_idx].buy(User, seller);
			
			}
			else
			{
				fprintf_s(out_fp, "> �˻��� ��ǰ�� �־�� ��ǰ ���Ű� �����մϴ�.\n");
			}
		}
		else
		{
			fprintf_s(out_fp, "> ��ǰ ���Ŵ� ��ǰ �˻� �Ŀ��� �����մϴ�.\n");
		}
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��ǰ ���Ű� �Ұ����մϴ�.\n");
	}
}

void GetBuyItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "4.3. ��ǰ ���� ���� ��ȸ\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getBuyItem(User, num);
		}
		if (num == 0) // ��ǰ�� �� ���� ������ ���� ���� ���
			fprintf_s(out_fp, "> ��ǰ ���� ������ �����ϴ�.\n");
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��ǰ ���� ���� ��ȸ�� �Ұ����մϴ�.\n");
	}
}

void Evaluating()
{
	if (strcmp(User, "") != 0)
	{
		char ItemName[MAX_STRING];
		int ItemRating;

		fscanf_s(in_fp, "%s %d", ItemName, sizeof(ItemName), &ItemRating);

		fprintf_s(out_fp, "4.4. ��ǰ ���Ÿ����� ��\n");

		for (int i = 0; i < MAX_ITEM; i++)
		{
			Clothes[i].saveRating(ItemName, ItemRating);
		}
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��ǰ ���� ������ �򰡰� �Ұ����մϴ�.\n");
	}
}

void GetStatics()
{
	if (strcmp(User, "") != 0)
	{
		fprintf_s(out_fp, "5.1. �Ǹ� ��ǰ ���\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			Clothes[i].getStatics(User);
		}
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� �Ǹ� ��ǰ ��� Ȯ���� �Ұ����մϴ�.\n");
	}
}*/

void program_exit()
{
	fprintf_s(out_fp, "6.1. ����\n");
}