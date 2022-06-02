//함수들 매개변수 수정, 필요없는 함수나 변수 제거

#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define MAX_STRING 32
#define MAX_ACCOUNT 100
#define MAX_ITEM 1000
#define MAX_QUANTITY 100
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
	char UserName[MAX_STRING + 1]; //이름
	char UserSSN[MAX_STRING + 1]; // 주민번호
	char UserID[MAX_STRING + 1]; //ID
	char UserPW[MAX_STRING + 1]; //password
	/*int SoldedItemPrice; */


public:
	bool check = 0; // Account가 비어있는지 확인
	void saveAcct(const char* str_username, const char* str_userssn, const char* str_userid, const char* str_userpw) {
		strcpy_s(UserName, MAX_STRING + 1, str_username);
		strcpy_s(UserSSN, MAX_STRING + 1, str_userssn);
		strcpy_s(UserID, MAX_STRING + 1, str_userid);
		strcpy_s(UserPW, MAX_STRING + 1, str_userpw);
		/*SoldedItemPrice = 0;*/
		check = 1;
	};
	//void deleteAcct() {};
	bool Find(const char* str_userid, const char* str_userpw) {
		if (strcmp(UserID, str_userid) == 0 && strcmp(UserPW, str_userpw) == 0)
			return 1;
		else return 0;
	};

	bool Find(const char* str_userid)
	{
		if (strcmp(UserID, str_userid) == 0)
			return 1;
		else return 0;
	};

	void GetIDPW(char* id, char* pw)
	{
		strcpy_s(id, MAX_STRING, UserID);
		strcpy_s(pw, MAX_STRING, UserPW);
	};

	/*void Earn(int money)
	{
		SoldedItemPrice += money;
	}*/

};

class Item {
private:
	char SellerID[MAX_STRING + 1];
	char BuyerID[MAX_QUANTITY][MAX_STRING + 1];
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded = 0;//판매된 수량 체크용, 남은 수량은 ItemQuantity에서 ItemSolded를 뺀 값 (판매 의류는 한번에 한 개만 등록한다고 가정합니다)
	int ItemRating[MAX_QUANTITY] = { 0 };

public:
	bool check = 0; //Item이 비어있는지 확인

	void AddItemInfo(const char* str_sellerid, const char* str_itemname, const char* str_itemcompany, int price, int quantity)
	{
		strcpy_s(SellerID, MAX_STRING + 1, str_sellerid);
		strcpy_s(ItemName, MAX_STRING + 1, str_itemname);
		strcpy_s(ItemCompany, MAX_STRING + 1, str_itemcompany);
		ItemPrice = price;
		ItemQuantity = quantity;
		check = 1;
	};

	int getItems(const char* str_sellerid, int num) //판매중인 의류 상품 리스트 조회 가능
	{
		if (strcmp(SellerID, str_sellerid) == 0 && (ItemQuantity - ItemSolded != 0))
		{
			fprintf_s(out_fp, "> { %s %s %d %d }*\n", ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded);
			num++;
		}
		return num;
	};

	int getSoldedItemInfo(const char* str_sellerid) //오름차순으로 정렬해서 출력하는 것도?
	{
		int num = 0;
		if (strcmp(SellerID, str_sellerid) == 0)
			if (ItemSolded != 0)
			{
				fprintf_s(out_fp, "> %s %s %s %d %d %f\n", ItemName, ItemCompany, ItemPrice, ItemSolded, ItemRating); //3.3 출력
				num++;
			}
		return num;
	};

	int getSearchItemInfo(const char* str_itemname, int num)
	{
		if (strcmp(ItemName, str_itemname) == 0)
			if (ItemQuantity - ItemSolded != 0)
			{
				fprintf_s(out_fp, "> %s %s %s %d %d %f\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, ItemRating);
				num++;
			}
		return num;
	};

	void buy(const char* str_buyerid, char* seller)
	{
		fprintf_s(out_fp, "> %s %s\n", SellerID, ItemName);
		strcpy_s(BuyerID[ItemSolded], MAX_STRING + 1, str_buyerid);
		ItemSolded++;
		strcpy_s(seller, MAX_STRING + 1, SellerID);
	}

	int getBuyItem(const char* str_buyerid, int num) 
	{
		for (int i = 0; i < MAX_QUANTITY; i++)
			if (strcmp(BuyerID[i], str_buyerid) == 0 && ItemSolded != 0)
			{
				fprintf_s(out_fp, "> { %s %s %s %d %d %f }*\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, ItemRating);
				num++;
			}
		return num;
	};

	void saveRating(const char* str_itemname, int itemrating) 
	{
		for (int i = 0; i < MAX_QUANTITY; i++) 
		{
			if (itemrating >= 1 && itemrating <= 5) {
				if (strcmp(ItemName, str_itemname) == 0)
				{
					ItemRating[i] = itemrating;

					fprintf_s(out_fp, "> %s %s %d\n", SellerID, ItemName, ItemRating[i]);
					break;
				}
			}
			else
				fprintf_s(out_fp, "> 구매만족도는 1-5사이의 정수 값만 입력이 가능합니다.\n");
		}
	};

	void getStatics(const char* str_sellerid)
	{
		float avgRating = 0;

		if (strcmp(SellerID, str_sellerid) == 0 && ItemSolded != 0)
		{
			int i = 0;

			for (int i = 0; i < ItemSolded; i++)
			{
				avgRating += ItemRating[i];
			}
			avgRating /= ItemSolded;

			fprintf_s(out_fp, "> { %s %d %f }*\n", ItemName, ItemPrice * ItemSolded, avgRating);
		}
	};
};


Account Acct[MAX_ACCOUNT];
Item Clothes[MAX_ITEM];
int my_idx, item_searched_idx;
char User[MAX_STRING + 1] = ""; //현재 사용하고 있는 User 
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
//아래에 함수 구현

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
	fprintf_s(out_fp, "1.1. 회원가입\n");
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
		fprintf_s(out_fp, "1.2. 회원탈퇴\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 회원탈퇴가 불가능합니다.\n");
	}
}

void LogIn()
{
	bool flag = 0; // 회원인지 아닌지 확인하는 flag
	char ID[MAX_STRING], PW[MAX_STRING];
	fscanf_s(in_fp, "%s %s", ID, sizeof(ID), PW, sizeof(PW));
	for (int i = 0; i < MAX_ACCOUNT; i++)
	{
		if (Acct[i].Find(ID, PW) == 1)
		{
			fprintf_s(out_fp, "2.1. 로그인\n");
			fprintf_s(out_fp, "> %s %s\n", ID, PW);
			strcpy_s(User, MAX_STRING + 1, ID);
			my_idx = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0) // 회원이 아닌 경우
	{
		fprintf_s(out_fp, "> 회원 등록이 되지 않아 로그인이 불가능합니다\n");
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
		fprintf_s(out_fp, "2.2. 로그아웃\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 로그아웃이 불가능합니다.\n");
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
		fprintf_s(out_fp, "3.1. 판매 의류 등록\n");
		fprintf_s(out_fp, "> %s %s %d %d\n", ItemName, ItemCompany, ItemPrice, ItemQuantity);
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 판매 의류 등록이 불가능합니다.\n");
	}
}

void GetItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "3.2. 등록 상품 조회\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getItems(User, num);
		}
		if(num == 0) // 등록한 상품이 없는 경우
			fprintf_s(out_fp, "> 등록한 상품이 없습니다.\n");
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 등록 상품 조회가 불가능합니다.\n");
	}
}

void GetSoldedItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "3.3. 판매 완료 상품 조회\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num += Clothes[i].getSoldedItemInfo(User);
		}
		if(num == 0) //판매 완료된 상품이 없는 경우
			fprintf_s(out_fp, "> 판매 완료된 상품이 없습니다.\n");
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 판매 완료 상품 조회가 불가능합니다.\n");
	}
}

void InputClothesName()
{
	if (strcmp(User, "") != 0)
	{
		char Name[MAX_STRING];
		int num = 0;
		fscanf_s(in_fp, "%s", Name, sizeof(Name));
		fprintf_s(out_fp, "4.1. 상품 정보 검색\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getSearchItemInfo(Name, num);
			item_searched_idx = i;
			if(num != 0) //없으면 for문을 1번만 돌아서 추가했습니다
				break;
		}
		if (num == 0)//검색 결과가 존재하지 않는 경우
		{
			fprintf_s(out_fp, "> 검색 결과가 없습니다.\n");
			item_searched_idx = -1;
		}
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 상품 정보 검색이 불가능합니다.\n");
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

				fprintf_s(out_fp, "4.2. 상품 구매\n");
				Clothes[item_searched_idx].buy(User, seller);
			
			}
			else
			{
				fprintf_s(out_fp, "> 검색한 상품이 있어야 상품 구매가 가능합니다.\n");
			}
		}
		else
		{
			fprintf_s(out_fp, "> 상품 구매는 상품 검색 후에만 가능합니다.\n");
		}
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 상품 구매가 불가능합니다.\n");
	}
}

void GetBuyItem()
{
	if (strcmp(User, "") != 0)
	{
		int num = 0;
		fprintf_s(out_fp, "4.3. 상품 구매 내역 조회\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getBuyItem(User, num);
		}
		if (num == 0) // 상품을 한 번도 구매한 적이 없는 경우
			fprintf_s(out_fp, "> 상품 구매 내역이 없습니다.\n");
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 상품 구매 내역 조회가 불가능합니다.\n");
	}
}

void Evaluating()
{
	if (strcmp(User, "") != 0)
	{
		char ItemName[MAX_STRING];
		int ItemRating;

		fscanf_s(in_fp, "%s %d", ItemName, sizeof(ItemName), &ItemRating);

		fprintf_s(out_fp, "4.4. 상품 구매만족도 평가\n");

		for (int i = 0; i < MAX_ITEM; i++)
		{
			Clothes[i].saveRating(ItemName, ItemRating);
		}
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 상품 구매 만족도 평가가 불가능합니다.\n");
	}
}

void GetStatics()
{
	if (strcmp(User, "") != 0)
	{
		fprintf_s(out_fp, "5.1. 판매 상품 통계\n");
		for (int i = 0; i < MAX_ITEM; i++)
		{
			Clothes[i].getStatics(User);
		}
	}
	else
	{
		fprintf_s(out_fp, "> 로그인하지 않아 판매 상품 통계 확인이 불가능합니다.\n");
	}
}

void program_exit()
{
	fprintf_s(out_fp, "6.1. 종료\n");
}