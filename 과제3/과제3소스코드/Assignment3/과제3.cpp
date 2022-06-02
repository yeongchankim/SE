//함수들 매개변수 수정, 필요없는 함수나 변수 제거

#include<iostream>
#include<fstream>
#include<string.h>
#include "과제3.h"
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

		cout << menu_level_1 << " " << menu_level_2 << endl;//입력 제대로 되는지 확인용 코드. 지워도됨
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
//아래에 함수 구현

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
			num = Clothes[i].getSoldedItemInfo(User,num);
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
}*/

void program_exit()
{
	fprintf_s(out_fp, "6.1. 종료\n");
}