#pragma once
#ifndef SETTING_H
#define SETTING_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

vector<int> Get_account_infomation(int id);
vector<int> Get_all_account_infomation();
vector<int> Get_single_account_infomation();
bool Is_duplicate_id(vector<int> a, const int& id);
bool Is_duplicate_pin(vector<int> a, const int& pin);
bool Is_locked_id(const int& id);

vector<int> Get_time();
bool Is_int(const string& s);
int String_to_int(const string& s);

void Make_atm_not_empty();
vector<int> Get_money_from_atm();
vector<int> Increase_money_in_atm(const int& menhgia, const int& soto);
vector<int> Decrease_money_in_atm(const int& menhgia, const int& soto);
vector<int> Greedy(const int& so_tien_can_rut);
bool Can_withdraw_or_transfer_money(const int& so_tien);
void Save_money_to_atm(vector<int> newSoTo);

#endif // SETTING_H


