#pragma once
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

FILE* in_fp, * out_fp;

#define MAX_STRING 32
#define MAX_ACCOUNT 100
#define MAX_ITEM 100
#define MAX_QUANTITY 100
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

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

	int getItems(const char* str_sellerid, int num, char* name, char* company_name, int *price, int *quantity, int *itemsolded) //판매중인 의류 상품 리스트 조회 가능
	{
		if (strcmp(SellerID, str_sellerid) == 0 && (ItemQuantity - ItemSolded != 0))
		{
			strcpy_s(name, MAX_STRING + 1, ItemName);
			strcpy_s(company_name, MAX_STRING + 1, ItemCompany);
			price = &ItemPrice;
			quantity = &ItemQuantity;
			itemsolded = &ItemSolded;
			num++;
		}
		return num;
	};

	int getSoldedItemInfo(const char* str_sellerid, int num, char* name, char* company_name, int* price, int* quantity, int* itemsolded, float* avg) //오름차순으로 정렬해서 출력하는 것도?
	{
		float avgRating = 0;
		if (strcmp(SellerID, str_sellerid) == 0)
			if (ItemSolded == ItemQuantity)
			{
				for (int i = 0; i < ItemSolded; i++)
				{
					avgRating += ItemRating[i];
				}
				avgRating /= ItemSolded;
				strcpy_s(name, MAX_STRING + 1, ItemName);
				strcpy_s(company_name, MAX_STRING + 1, ItemCompany);
				price = &ItemPrice;
				quantity = &ItemQuantity;
				itemsolded = &ItemSolded;
				avg = &avgRating;
				num++;
			}
		return num;
	};

	int getSearchItemInfo(const char* str_itemname, int num, char* ID, char* name, char* company, int* price, int* quantity, int* solded, float* rating)
	{
		float avgRating = 0;
		if (strcmp(ItemName, str_itemname) == 0)
			if (ItemQuantity - ItemSolded != 0)
			{
				for (int i = 0; i < ItemSolded; i++)
				{
					avgRating += ItemRating[i];
				}
				if (ItemSolded != 0)
					avgRating /= ItemSolded;
				strcpy_s(ID, MAX_STRING + 1, SellerID);
				strcpy_s(name, MAX_STRING + 1, ItemName);
				strcpy_s(company, MAX_STRING + 1, ItemCompany);
				price = &ItemPrice;
				quantity = &ItemQuantity;
				solded = &ItemSolded;
				rating = &avgRating;
				num++;
			}
		return num;
	};

	void buy(const char* str_buyerid, char* ID, char* name)
	{
		strcpy_s(BuyerID[ItemSolded], MAX_STRING + 1, str_buyerid);
		ItemSolded++;
		strcpy_s(ID, MAX_STRING + 1, SellerID);
		strcpy_s(name, MAX_STRING + 1, ItemName);
	}

	int getBuyItem(const char* str_buyerid, int num, char* ID, char* name, char* company, int* price, int* quantity, int* solded, float* rating)
	{
		float avgRating = 0;
		for (int i = 0; i < MAX_QUANTITY; i++)
			if (strcmp(BuyerID[i], str_buyerid) == 0 && ItemSolded != 0)
			{
				for (int i = 0; i < ItemSolded; i++)
				{
					avgRating += ItemRating[i];
				}
				if (ItemSolded != 0)
					avgRating /= ItemSolded;
				strcpy_s(ID, MAX_STRING + 1, SellerID);
				strcpy_s(name, MAX_STRING + 1, ItemName);
				strcpy_s(company, MAX_STRING + 1, ItemCompany);
				price = &ItemPrice;
				quantity = &ItemQuantity;
				solded = &ItemSolded;
				rating = &avgRating;
				num++;
			}
		return num;
	};

	void saveRating(const char* str_itemname, int itemrating, char* ID)
	{
		for (int i = 0; i < MAX_QUANTITY; i++)
		{
			if (itemrating >= 1 && itemrating <= 5) {
				if (strcmp(ItemName, str_itemname) == 0)
				{
					ItemRating[i] = itemrating;
					strcpy_s(ID, MAX_STRING + 1, SellerID);
					break;
				}
			}
		}
	};

	void getStatics(const char* str_sellerid, char* name, int* price, int* solded, float* rating)
	{
		float avgRating = 0;

		if (strcmp(SellerID, str_sellerid) == 0 && ItemSolded != 0)
		{
			for (int i = 0; i < ItemSolded; i++)
			{
				avgRating += ItemRating[i];
			}
			avgRating /= ItemSolded;

			strcpy_s(name, MAX_STRING + 1, ItemName);
			price = &ItemPrice;
			solded = &ItemSolded;
			rating = &avgRating;
		}
	};
};

Account Acct[MAX_ACCOUNT];
Item Clothes[MAX_ITEM];
int my_idx, item_searched_idx;
char User[MAX_STRING + 1] = ""; //현재 사용하고 있는 User 
State current_state;

class SignUpUI
{
public:
	char UserName[MAX_STRING]; //이름
	char UserSSN[MAX_STRING]; // 주민번호
	char UserID[MAX_STRING]; //ID
	char UserPW[MAX_STRING]; //password

	void signup()
	{
		fscanf_s(in_fp, "%s %s %s %s", UserName, sizeof(UserName), UserSSN, sizeof(UserSSN), UserID, sizeof(UserID), UserPW, sizeof(UserPW));
	}

	void print()
	{
		fprintf_s(out_fp, "1.1. 회원가입\n");
		fprintf_s(out_fp, "> %s %s %s %s\n", UserName, UserSSN, UserID, UserPW);
	}
};

class SignUp
{
public:
	void signup()
	{
		SignUpUI signinui;
		signinui.signup();

		for (int i = 0; i < MAX_ACCOUNT; i++)
		{
			if (Acct[i].check == 0)
			{
				Acct[i].saveAcct(signinui.UserName, signinui.UserSSN, signinui.UserID, signinui.UserPW);
				break;
			}
		}

		signinui.print();
	}
};

class LogInUI
{
public:
	char UserID[MAX_STRING]; //ID
	char UserPW[MAX_STRING]; //password
	void login()
	{
		fscanf_s(in_fp, "%s %s",  UserID, sizeof(UserID), UserPW, sizeof(UserPW));
	}

	void print()
	{
		fprintf_s(out_fp, "2.1. 로그인\n");
		fprintf_s(out_fp, "> %s %s\n", UserID, UserPW);
	}
};

class LogIn
{
public:
	void login()
	{
		LogInUI loginui;
		loginui.login();
		for (int i = 0; i < MAX_ACCOUNT; i++)
		{
			if (Acct[i].Find(loginui.UserID, loginui.UserPW) == 1)
			{
				strcpy_s(User, MAX_STRING + 1, loginui.UserID);
				my_idx = i;
				loginui.print();
				break;
			}
		}
	}

};

class WithdrawalUI
{
public:
	void print(char* ID)
	{
		fprintf_s(out_fp, "1.2. 회원탈퇴\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
};

class Withdrawal
{
public:
	void withdrawal()
	{
		char ID[MAX_STRING], PW[MAX_STRING];
		Acct[my_idx].GetIDPW(ID, PW);
		Acct[my_idx].check = 0;
		my_idx = -1;
		WithdrawalUI withdrawalui;
		withdrawalui.print(ID);
	}
};

class LogOutUI
{
public:
	void print(char * ID)
	{
		fprintf_s(out_fp, "2.2. 로그아웃\n");
		fprintf_s(out_fp, "> %s \n", ID);
	}
};

class LogOut
{
public:
	void logout()
	{
		char ID[MAX_STRING], PW[MAX_STRING];
		Acct[my_idx].GetIDPW(ID, PW);
		strcpy_s(User, MAX_STRING + 1, "");
		my_idx = -1;
		LogOutUI logoutui;
		logoutui.print(ID);
	}
};

class AddItemUI
{
public:
	char ItemName[MAX_STRING];
	char ItemCompany[MAX_STRING];
	int ItemPrice = 0;
	int ItemQuantity = 0;

	void additem()
	{
		fscanf_s(in_fp, "%s %s %d %d", ItemName, sizeof(ItemName), ItemCompany, sizeof(ItemCompany), &ItemPrice, &ItemQuantity);
	}

	void print()
	{
		fprintf_s(out_fp, "3.1. 판매 의류 등록\n");
		fprintf_s(out_fp, "> %s %s %d %d\n", ItemName, ItemCompany, ItemPrice, ItemQuantity);
	}
};

class AddItem
{
public:
	void additem()
	{
		AddItemUI additemui;
		additemui.additem();
		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (Clothes[i].check == 0)
			{
				Clothes[i].AddItemInfo(User, additemui.ItemName, additemui.ItemCompany, additemui.ItemPrice, additemui.ItemQuantity);
				break;
			}
		}
		additemui.print();
	}
};

class GetItemUI
{
public:
	char ItemName[MAX_ITEM][MAX_STRING + 1];
	char ItemCompany[MAX_ITEM][MAX_STRING + 1];
	int ItemPrice[MAX_ITEM];
	int ItemQuantity[MAX_ITEM];
	int ItemSolded[MAX_ITEM] = { 0 };
	void print(int num)
	{
		fprintf_s(out_fp, "3.2. 등록 상품 조회\n");
		for (int i = 0; i < num; i++)
			fprintf_s(out_fp, "> { %s %s %d %d }\n", ItemName[i], ItemCompany[i], ItemPrice[i], ItemQuantity[i] - ItemSolded[i]);
	}
};

class GetItem
{
public:
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded = 0;
	
	void getitem()
	{
		GetItemUI getitemui;
		int num = 0;
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getItems(User, num, getitemui.ItemName[num], getitemui.ItemCompany[num], &getitemui.ItemPrice[num], &getitemui.ItemQuantity[num], &getitemui.ItemSolded[num]);
		}

		getitemui.print(num);
	}
};

class GetSoldedItemUI
{
public:
	char SellerID[MAX_ITEM][MAX_STRING + 1];
	char ItemName[MAX_ITEM][MAX_STRING + 1];
	char ItemCompany[MAX_ITEM][MAX_STRING + 1];
	int ItemPrice[MAX_ITEM];
	int ItemQuantity[MAX_ITEM];
	int ItemSolded[MAX_ITEM];
	float avgRating[MAX_ITEM];

	void print(int num)
	{
		fprintf_s(out_fp, "3.3. 판매 완료 상품 조회\n");
		for (int i = 1; i <= num; i++)
			fprintf_s(out_fp, "> %s %s %d %d %f\n", ItemName[i], ItemCompany[i], ItemPrice[i], ItemSolded[i], avgRating[i]);
	}
};

class GetSoldedItem
{
public:
	char SellerID[MAX_STRING + 1];
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded;
	float avgRating;
	void getsoldedItem()
	{
		GetSoldedItemUI getsoldeditemui;
		int num = 0;
		for (int i = 0; i < MAX_ITEM; i++)
		{
			num = Clothes[i].getSoldedItemInfo(User, num, ItemName, ItemCompany, &ItemPrice, &ItemQuantity, &ItemSolded, &avgRating);
		}
	}
};

class GetItemInfoUI
{
public:
	char ItemName[MAX_STRING];

	void inputclothesname()
	{
		fscanf_s(in_fp, "%s", ItemName, sizeof(ItemName));
	}
	void print(char* SellerID, char* ItemName, char* ItemCompany, int ItemPrice, int ItemQuantity, int ItemSolded, float avgRating)
	{
		fprintf_s(out_fp, "4.1. 상품 정보 검색\n");
		fprintf_s(out_fp, "> %s %s %s %d %d %f\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, avgRating);
	}
};

class GetItemInfo
{
public:
	char SellerID[MAX_STRING + 1];
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded;
	float avgRating;

	void showclothesinfo()
	{
		GetItemInfoUI getiteminfoui;
		if (strcmp(User, "") != 0)
		{
			getiteminfoui.inputclothesname();
			int num = 0;

			for (int i = 0; i < MAX_ITEM; i++)
			{
				num = Clothes[i].getSearchItemInfo(getiteminfoui.ItemName, num, SellerID, ItemName, ItemCompany, &ItemPrice, &ItemQuantity, &ItemSolded, &avgRating);
				item_searched_idx = i;
				if (num != 0) //없으면 for문을 1번만 돌아서 추가했습니다
					break;
			}
			getiteminfoui.print(SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity, ItemSolded, avgRating);
		}
	}
};

class BuyItemUI
{
public:
	void print(char* SellerID, char* ItemName)
	{
		fprintf_s(out_fp, "4.2. 상품 구매\n");
		fprintf_s(out_fp, "> %s %s\n", SellerID, ItemName);
	}
};
class BuyItem
{
public:
	char SellerID[MAX_STRING];
	char ItemName[MAX_STRING];

	void buy()
	{
		BuyItemUI buyitemui;

		if (strcmp(User, "") != 0)
		{
			int level1 = current_state.get_level1();
			int level2 = current_state.get_level2();
			if (level1 == 4 && level2 == 1)
			{
				if (item_searched_idx >= 0)
				{
					Clothes[item_searched_idx].buy(User, SellerID, ItemName);
					buyitemui.print(SellerID, ItemName);
				}
			}
		}
	}
};

class GetBuyItemUI
{
public:
	char SellerID[MAX_ITEM][MAX_STRING + 1];
	char ItemName[MAX_ITEM][MAX_STRING + 1];
	char ItemCompany[MAX_ITEM][MAX_STRING + 1];
	int ItemPrice[MAX_ITEM];
	int ItemQuantity[MAX_ITEM];
	int ItemSolded[MAX_ITEM];
	float avgRating[MAX_ITEM];

	void print(int num)
	{
		fprintf_s(out_fp, "4.3. 상품 구매 내역 조회\n");
		for (int i = 0; i < num; i++)
			fprintf_s(out_fp, "> { %s %s %s %d %d %f }*\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, avgRating);
	}
};

class GetBuyItem
{
public:
	char SellerID[MAX_STRING + 1];
	char ItemName[MAX_STRING + 1];
	char ItemCompany[MAX_STRING + 1];
	int ItemPrice;
	int ItemQuantity;
	int ItemSolded;
	float avgRating;

	GetBuyItemUI getbuyitemui;
	void getBuyItem()
	{
		if (strcmp(User, "") != 0)
		{
			int num = 0;

			for (int i = 0; i < MAX_ITEM; i++)
			{
				num = Clothes[i].getBuyItem(User, num, SellerID, ItemName, ItemCompany, &ItemPrice, &ItemQuantity, &ItemSolded, &avgRating);
				strcpy_s(getbuyitemui.SellerID[num], MAX_STRING + 1, SellerID);
				strcpy_s(getbuyitemui.ItemName[num], MAX_STRING + 1, ItemName);
				strcpy_s(getbuyitemui.ItemCompany[num], MAX_STRING + 1, ItemCompany);
				getbuyitemui.ItemPrice[num] = ItemPrice;
				getbuyitemui.ItemQuantity[num] = ItemQuantity;
				getbuyitemui.ItemSolded[num] = ItemSolded;
				getbuyitemui.avgRating[num] = avgRating;
			}
			getbuyitemui.print(num);
		}
	}

};

class EvaluateUI
{
public:
	char ItemName[MAX_STRING];
	int ItemRating;

	void evaluating()
	{
		fscanf_s(in_fp, "%s %d", ItemName, sizeof(ItemName), &ItemRating);
	}
	void print(char* SellerID)
	{
		fprintf_s(out_fp, "4.4. 상품 구매만족도 평가\n");
		fprintf_s(out_fp, "> %s %s %d\n", SellerID, ItemName, ItemRating);
	}
};

class Evaluate
{
public:
	char SellerID[MAX_STRING + 1];

	void evaluate()
	{
		EvaluateUI evaluatingui;
		if (strcmp(User, "") != 0)
		{
			evaluatingui.evaluating();

			for (int i = 0; i < MAX_ITEM; i++)
			{
				Clothes[i].saveRating(evaluatingui.ItemName, evaluatingui.ItemRating, SellerID);
			}
			evaluatingui.print(SellerID);
		}
	}
};

class SoldedItemStaticsUI
{
public:
	void print1()
	{
		fprintf_s(out_fp, "5.1. 판매 상품 통계\n");
	}
	void print2(char* ItemName, int ItemPrice, int ItemSolded, float avgRating)
	{
		fprintf_s(out_fp, "> { %s %d %f }*\n", ItemName, ItemPrice * ItemSolded, avgRating);
	}
};

class SoldedItemStatics
{
public:
	char ItemName[MAX_STRING];
	int ItemPrice;
	int ItemSolded;
	float avgRating;
	void getStatics()
	{
		if (strcmp(User, "") != 0)
		{
			SoldedItemStaticsUI getstaticsui;
			getstaticsui.print1();
			for (int i = 0; i < MAX_ITEM; i++)
			{
				Clothes[i].getStatics(User, ItemName, &ItemPrice, &ItemSolded, &avgRating);
				getstaticsui.print2(ItemName, ItemPrice, ItemSolded, avgRating);
			}
		}
	}
};
