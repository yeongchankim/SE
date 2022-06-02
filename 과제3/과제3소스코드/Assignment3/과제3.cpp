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

		switch (menu_level_1)
		{
		case 1:
		{
			switch (menu_level_2)
			{
			case 1:
			{
				SignUp sign_up;
				sign_up.signup();
				break;
			}
			case 2:
			{
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

void program_exit()
{
	fprintf_s(out_fp, "6.1. 종료\n");
}