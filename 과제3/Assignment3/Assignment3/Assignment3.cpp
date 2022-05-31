#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define MAX_STRING 32
#define MAX_ACCOUNT 100//������ �̿밡���� ������ ���� �ִ밪
#define MAX_ITEM 1000//������ ��ϰ����� �Ǹ� ��ǰ�� �ִ� ������
#define MAX_QUANTITY 100//�Ǹ� ��ϰ����� �ִ� ����
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

FILE* in_fp, * out_fp;

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
class State
{
private:
	int menu_level_1;
	int menu_level_2;
public:
	void set_current_state(int a, int b)
	{
		menu_level_1 = a;
		menu_level_2 = b;
	}
	int get_level1()
	{
		return menu_level_1;
	}
	int get_level2()
	{
		return menu_level_2;
	}
};
class Account {
private:
	char UserName[MAX_STRING + 1];
	char UserSSN[MAX_STRING + 1];
	char UserID[MAX_STRING + 1];
	char UserPW[MAX_STRING + 1];
	int SoldedItemPrice;
	float AvgRating;


public:
	bool check = 0; // Account�� ����ִ��� Ȯ��
	void saveAcct(const char* str1, const char* str2, const char* str3, const char* str4) {
		strcpy_s(UserName, MAX_STRING + 1, str1);
		strcpy_s(UserSSN, MAX_STRING + 1, str2);
		strcpy_s(UserID, MAX_STRING + 1, str3);
		strcpy_s(UserPW, MAX_STRING + 1, str4);
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

	bool Find(const char* str1)
	{
		if (strcmp(UserID, str1) == 0)
			return 1;
		else return 0;
	};

	void GetIDPW(char* temp1, char* temp2)
	{
		strcpy_s(temp1, MAX_STRING, UserID);
		strcpy_s(temp2, MAX_STRING, UserPW);
	};

	void Earn(int money)
	{
		SoldedItemPrice += money;
	}

	//void getStatics() {};
};

class Item {
private:
	char SellerID[MAX_STRING + 1];
	char BuyerID[MAX_QUANTITY][MAX_STRING + 1];
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded = 0;//�Ǹŵ� ���� üũ��, ���� ������ ItemQuantity���� ItemSolded�� �� ��
	float ItemRating[MAX_QUANTITY];

public:
	bool check = 0; //Item�� ����ִ��� Ȯ��

	void AddItemInfo(const char* str1, const char* str2, const char* str3, int x, int y)
	{
		strcpy_s(SellerID, MAX_STRING + 1, str1);
		strcpy_s(ItemName, MAX_STRING + 1, str2);
		strcpy_s(ItemCompany, MAX_STRING + 1, str3);
		ItemPrice = x;
		ItemQuantity = y;
		for (int i = 0; i < MAX_QUANTITY; i++)
			ItemRating[i] = 0;//���� 0���� �ʱ�ȭ
		check = 1;
	};
	int getItems(const char* str1, int num)
	{
		if (strcmp(SellerID, str1) == 0)
		{
			fprintf_s(out_fp, "> { %s %s %d %d }*\n", ItemName, ItemCompany, ItemPrice, ItemQuantity);
			num++;
		}
		return num;
	};
	int getSoldedItemInfo(const char* str1, int num)
	{
		if (strcmp(SellerID, str1) == 0)
			if (ItemQuantity - ItemSolded == 0)
			{
				fprintf_s(out_fp, "> %s %s %s %d %d %f\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemSolded, ItemRating);
				num++;
			}
		return num;
	};
	int getSearchItemInfo(const char* str1, int num)
	{
		if (strcmp(ItemName, str1) == 0)
			if (ItemQuantity - ItemSolded != 0)
			{
				fprintf_s(out_fp, "> %s %s %s %d %d %f\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, ItemRating);
				num++;
			}
		return num;
	};
	int buy(const char* str1, char* seller)
	{
		fprintf_s(out_fp, "> %s %s\n", SellerID, ItemName);
		strcpy_s(BuyerID[ItemSolded], MAX_STRING + 1, str1);
		ItemSolded++;
		strcpy_s(seller, MAX_STRING + 1, SellerID);
		return ItemPrice;
	}
	//void updateItemInfo() {};
	int getBuyItem(const char* str1, int num) {
		for (int i = 0; i < MAX_QUANTITY; i++)
			if (strcmp(BuyerID[i], str1) == 0)
			{
				fprintf_s(out_fp, "> { %s %s %s %d %d %f }*\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, ItemRating);
				num++;
			}
		return num;
	};
	bool saveRating(const char * str1, const char * str2, float num)
	{
		bool is = false;//��ǰ��� ���� Ž������ ��ǰ���� ��ġ�ϴ����� ǥ��
		if(strcmp(ItemName, str1)==0)
			for (int i = 0; i < MAX_QUANTITY; i++)
				if (strcmp(BuyerID[i], str2) == 0)//������ ã��
				{
					ItemRating[i] = num;
					fprintf_s(out_fp, "> { %s %s %f }*\n", SellerID, ItemName, ItemRating[i]);
					is = true;//ã�Ƽ� ������
					break;
				}
		return is;
	};

};


Account Acct[MAX_ACCOUNT];
Item Clothes[MAX_ITEM];
int my_idx, item_searched_idx;
char User[MAX_STRING + 1] = ""; //���� ����ϰ� �ִ� User 
State current_state;
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
		current_state.set_current_state(menu_level_1, menu_level_2);
		fprintf_s(out_fp, "\n");
	}
	return;
}
//�Ʒ��� �Լ� ����

void SignUp()
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
			num = Clothes[i].getSoldedItemInfo(User, num);
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
				int money;
				fprintf_s(out_fp, "4.2. ��ǰ ����\n");
				money = Clothes[item_searched_idx].buy(User, seller);
				for (int i = 0; i < MAX_ACCOUNT; i++)
				{
					if (Acct[i].Find(seller))
						Acct[i].Earn(money);
				}
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
		char Item_Name[MAX_STRING];
		float rate;
		bool flag = false;
		fscanf_s(in_fp, "%s %f", Item_Name, sizeof(Item_Name),&rate);
		fprintf_s(out_fp, "4.4. ��ǰ ���Ÿ����� ��\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			flag = Clothes[i].saveRating(Item_Name, User, rate);
			if(flag == true)
				break;
		}
		if(!flag)
			fprintf_s(out_fp, ">�ش� ��ǰ�� �������� �ʾ� ���Ÿ����� �򰡰� �Ұ����մϴ�.\n");
	}
	else
	{
		fprintf_s(out_fp, "> �α������� �ʾ� ��ǰ ���Ÿ����� �򰡰� �Ұ����մϴ�.\n");
	}
}

void GetStatics()
{
}

void program_exit()
{
	fprintf_s(out_fp, "6.1. ����\n");
}