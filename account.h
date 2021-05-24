#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "setting.h"
#include "interface.h"
using namespace std;

class TaiKhoan
{
private:
    int id;
    int pin;
    int so_du_tai_khoan;

public:
    TaiKhoan();
    void Luu_thong_tin();
    void kiem_tra_so_du();
    void rut_tien();
    void gui_tien();
    void gui_tien_theo_menh_gia(const int& menhgia);
    void kiem_tra_lich_su_gui_va_rut_tien();
    void kiem_tra_lich_su_chuyen_va_nhan_tien();
    void kiem_tra_lich_su_giao_dich();
    void chuyen_tien();
    void doi_ma_pin();
};

#endif // ACCOUNT_H

