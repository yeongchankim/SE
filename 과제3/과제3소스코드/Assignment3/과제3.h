#pragma once
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

FILE* in_fp, * out_fp;

#define MAX_STRING 32
#define MAX_ACCOUNT 100
#define MAX_ITEM 1000
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

		fprintf_s(out_fp, "1.1. 회원가입\n");
		fprintf_s(out_fp, "> %s %s %s %s\n", UserName, UserSSN, UserID, UserPW);
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

	int getSoldedItemInfo(const char* str_sellerid, int num) //오름차순으로 정렬해서 출력하는 것도?
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
				fprintf_s(out_fp, "> %s %s %d %d %f\n", ItemName, ItemCompany, ItemPrice, ItemSolded, avgRating); //3.3 출력
				num++;
			}
		return num;
	};

	int getSearchItemInfo(const char* str_itemname, int num)
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
				fprintf_s(out_fp, "> %s %s %s %d %d %f\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, avgRating);
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
				fprintf_s(out_fp, "> { %s %s %s %d %d %f }*\n", SellerID, ItemName, ItemCompany, ItemPrice, ItemQuantity - ItemSolded, avgRating);
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

class SignUpUI
{
public:
	char UserName[MAX_STRING + 1]; //이름
	char UserSSN[MAX_STRING + 1]; // 주민번호
	char UserID[MAX_STRING + 1]; //ID
	char UserPW[MAX_STRING + 1]; //password

	void signup()
	{
		fscanf_s(in_fp, "%s %s %s %s", UserName, sizeof(UserName), UserSSN, sizeof(UserSSN), UserID, sizeof(UserID), UserPW, sizeof(UserPW));
	}
};

class SignUp
{
public:
	char UserName[MAX_STRING + 1]; //이름
	char UserSSN[MAX_STRING + 1]; // 주민번호
	char UserID[MAX_STRING + 1]; //ID
	char UserPW[MAX_STRING + 1]; //password

	void signup()
	{
		SignUpUI sui;
		sui.signup();
		strcpy_s(sui.UserName, MAX_STRING, UserName);
		strcpy_s(sui.UserSSN, MAX_STRING, UserSSN);
		strcpy_s(sui.UserID, MAX_STRING, UserID);
		strcpy_s(sui.UserPW, MAX_STRING, UserPW);
		for (int i = 0; i < MAX_ACCOUNT; i++)
		{
			if (Acct[i].check == 0)
			{
				Acct[i].saveAcct(UserName, UserSSN, UserID, UserPW);
				break;
			}
		}
	}
};