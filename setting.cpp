#include "setting.h"

bool Is_int(const string& so_to)
{
    int i = 0;
    while (so_to[i] != '\0')
    {
        if (so_to[i] < '0' || so_to[i] > '9')
            return false;
        i++;
    }
    return true;
}

int String_to_int(const string& so_to)
{
    int result = 0;
    for (int i = 0; i < so_to.size(); i++)
        result = result * 10 + (so_to[i] - '0');
    return result;
}

vector<int> Get_time()
{
    vector<int> a;
    time_t now = time(0);
    tm* t = localtime(&now);

    a.push_back(t->tm_mday);
    a.push_back(t->tm_mon + 1);
    a.push_back(t->tm_year + 1900);
    a.push_back(t->tm_hour);
    a.push_back(t->tm_min);
    a.push_back(t->tm_sec);

    return a;
}


vector<int> Get_all_account_infomation()
{
    vector<int> a;
    ifstream file("Account_Info.txt");
    while (file && !file.eof())
    {
        int n;
        file >> n;
        a.push_back(n);
    }
    file.close();
    a.erase(a.begin() + a.size() - 1);
    return a;
}

vector<int> Get_account_infomation(int id)
{
    vector<int> a = Get_all_account_infomation();
    vector<int> Thong_tin_tai_khoan;
    for (int i = a.size() - 2; i >= 0; i--)
    {
        if (i % 3 == 0 && a[i] == id)
        {
            Thong_tin_tai_khoan.push_back(a[i]);
            Thong_tin_tai_khoan.push_back(a[i + 1]);
            Thong_tin_tai_khoan.push_back(a[i + 2]);
            break;
        }
    }
    return Thong_tin_tai_khoan;
}

vector<int> Get_single_account_infomation()
{
    vector<int> Thong_tin_tai_khoan;
    ifstream file("Single_Account_Info.txt");
    while (file && !file.eof())
    {
        int n;
        file >> n;
        Thong_tin_tai_khoan.push_back(n);
    }
    file.close();
    return Thong_tin_tai_khoan;
}

bool Is_locked_id(const int& id)
{
    vector<int> a;
    ifstream file("Locked_id.txt");
    while (file && !file.eof())
    {
        int n;
        file >> n;
        a.push_back(n);
    }
    file.close();
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == id)
        {
            return true;
            break;
        }
    }
    return false;
}

bool Is_duplicate_id(vector<int> a, const int& id)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (i % 3 == 0 && a[i] == id)
        {
            return true;
            break;
        }
    }
    return false;
}

bool Is_duplicate_pin(vector<int> a, const int& pin)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (i % 3 == 1 && a[i] == pin)
        {
            return true;
            break;
        }
    }
    return false;
}


vector<int> Greedy(const int& so_tien_can_rut)
{
    vector<int> SoTo = Get_money_from_atm();
    vector<int> res;
    Get_money_from_atm();
    int n = so_tien_can_rut;
    int nam_tram = n / 500000;
    int n1 = (nam_tram < SoTo[0]) ? nam_tram : SoTo[0];
    res.push_back(n1);
    n -= (n1 * 500000);

    int hai_tram = n / 200000;
    int n2 = (hai_tram < SoTo[1]) ? hai_tram : SoTo[1];
    res.push_back(n2);
    n -= (n2 * 200000);

    int mot_tram = n / 100000;
    int n3 = (mot_tram < SoTo[2]) ? mot_tram : SoTo[2];
    res.push_back(n3);
    n -= (n3 * 100000);

    int nam_muoi = n / 50000;
    int n4 = (nam_muoi < SoTo[3]) ? nam_muoi : SoTo[3];
    n -= (n4 * 50000);
    res.push_back(n4);

    int hai_muoi = n / 20000;
    int n5 = (hai_muoi < SoTo[4]) ? hai_muoi : SoTo[4];
    n -= (n5 * 20000);
    res.push_back(n5);

    int muoi_nghin = n / 10000;
    int n6 = (muoi_nghin < SoTo[5]) ? muoi_nghin : SoTo[5];
    res.push_back(n6);

    return res;
}

bool Can_withdraw_or_transfer_money(const int& so_tien)
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    vector<int> so_to_duoc_chon = Greedy(so_tien);
    int res = 0;
    for (int i = 0; i < 6; i++)
    {
        res += (so_to_duoc_chon[i] * Loai_tien[i]);
    }
    if (res == so_tien)
        return true;
    return false;
}

void Make_atm_not_empty()
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    ifstream file("Money_in_atm.txt");
    bool is_empty = (file.peek() == ifstream::traits_type::eof());
    if (is_empty)
    {
        ofstream file("Money_in_atm.txt", ios::app);
        {
            for (int i = 0; i < 6; i++)
                file << 0 << " " << Loai_tien[i] << endl;
        }
    }
}

vector<int> Get_money_from_atm()
{
    vector<int> SoTo;
    vector<int> a;
    ifstream file("Money_in_atm.txt");
    while (file && !file.eof())
    {
        int n;
        file >> n;
        a.push_back(n);
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (i % 2 == 0)
        {
            SoTo.push_back(a[i]);
        }
    }
    return SoTo;
}

vector<int> Increase_money_in_atm(const int& menhgia, const int& n)
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    vector<int> newSoTo = Get_money_from_atm();
    int type = 0;
    for (int i = 0; i < 6; i++)
    {
        if (Loai_tien[i] == menhgia)
            type = i;
    }
    int so_to_moi = newSoTo[type] + n;
    newSoTo[type] = so_to_moi;
    return newSoTo;
}

vector<int> Decrease_money_in_atm(const int& menhgia, const int& n)
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    vector<int> newSoTo = Get_money_from_atm();
    int type = 0;
    for (int i = 0; i < 6; i++)
    {
        if (Loai_tien[i] == menhgia)
            type = i;
    }
    int so_to_moi = newSoTo[type] - n;
    newSoTo[type] = so_to_moi;
    return newSoTo;
}

void Save_money_to_atm(vector<int> newSoTo)
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    ofstream file("Money_in_atm.txt");
    for (int i = 0; i < 6; i++)
    {
        file << newSoTo[i] << " " << Loai_tien[i] << endl;
    }
    file.close();
}
