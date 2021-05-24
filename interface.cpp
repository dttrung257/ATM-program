#include "interface.h"

void Main_menu()
{
    cout << "\n====================================== Chao mung quy khach den voi chuong trinh ATM ====================================";
    cout << "\n\n==================================================== MAIN MENU ========================================================" << endl;
    cout << "\nVui long lua chon chuc nang : " << endl;
    cout << "\t1. Dang nhap" << endl;
    cout << "\t2. Dang ki" << endl;
    cout << "\t3. Thoat chuong trinh" << endl;

    Make_atm_not_empty();

    do
    {
        string response;
        cin >> response;

        if (response == "1")
        {
            system("cls");
            Dang_nhap();
            break;
        }
        else if (response == "2")
        {
            system("cls");
            Tao_tai_khoan_moi();
            system("cls");
            Main_menu();
            break;
        }
        else if (response == "3")
        {
            system("cls");
            Thoat_chuong_trinh();
            break;
        }
        else
            cout << "\nCu phap sai. Vui long chon tu 1 -> 3" << endl;

    } while (true);
}

void Dang_nhap()
{
    int n = 0;
    string so_id, ma_pin;
    cout << "\n======================================================= Dang nhap =====================================================";
    cout << "\n\n\t\t\t********  Nhap phim [T] neu quy khach muon tro ve main menu  ********";
    cout << "\n\nVui long nhap id: ";
    vector<int> a = Get_all_account_infomation();
    do
    {
        cin >> so_id;

        if (Is_int(so_id) && String_to_int(so_id) >= 10000)
        {
            if (!Is_locked_id(String_to_int(so_id)))
            {
                if (Is_duplicate_id(a, String_to_int(so_id)))
                {
                    int id = String_to_int(so_id);
                    vector<int> Thong_tin_tai_khoan = Get_account_infomation(id);

                    ofstream file("Single_Account_Info.txt");
                    if (file)
                    {
                        file << Thong_tin_tai_khoan[0] << " " << Thong_tin_tai_khoan[1] << " " << Thong_tin_tai_khoan[2] << " " << endl;
                    }
                    file.close();

                    cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Main menu  **********";
                    cout << "\n\nVui long nhap ma pin: ";
                    do
                    {
                        cin >> ma_pin;
                        if (Is_int(ma_pin) && String_to_int(ma_pin) == Thong_tin_tai_khoan[1])
                        {
                            system("cls");
                            cout << "\n\t\t\t\t\t\t DANG NHAP THANH CONG";
                            Menu();
                            break;
                        }
                        else if (ma_pin == "t" || ma_pin == "T")
                        {
                            Main_menu();
                            break;
                        }
                        else
                        {
                            cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Main menu  **********";
                            cout << "\nSai ma pin. Vui long nhap lai : ";
                            n++;
                        }
                        if (n == 5)
                        {
                            cout << "\n\n\t************** Quy khach da nhap sai ma pin 5 lan. Neu tiep tuc sai se bi khoa the ***************";
                            cout << "\nQuy khach co muon tiep tuc dang nhap (y/n): ";
                            do
                            {
                                string response;
                                cin >> response;
                                if (response == "y" || response == "Y")
                                {
                                    cout << "\n\nVui long nhap lai ma pin: ";
                                    break;
                                }
                                else if (response == "n" || response == "N")
                                {
                                    Main_menu();
                                    break;
                                }
                                else
                                    cout << "\nCu phap sai. Vui long nhap (y/n) : ";
                            } while (true);
                        }
                        if (n == 6)
                        {
                            cout << "\n***************************************************** The da bi khoa ***************************************************";
                            ofstream file("Locked_id.txt", ios::app);
                            if (file)
                            {
                                file << id << endl;
                            }
                            file.close();
                            cout << "\n\n\tCam on quy khach da su dung dich vu";
                            exit(0);
                            break;
                        }
                    } while (true);
                }
                else
                {
                    system("cls");
                    cout << "\nSo id " << so_id << " khong ton tai" << endl;
                    system("pause");
                    cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Main Menu  **********\n";
                    cout << "\n\nVui long nhap lai id : ";
                }
            }
            else
            {
                system("cls");
                cout << "\n********************************************** The so id " << String_to_int(so_id) << " da bi khoa **********************************************\n";
                system("pause");
                Main_menu();
                break;
            }
        }
        else if (so_id == "t" || so_id == "T")
        {
            system("cls");
            Main_menu();
            break;
        }
        else
        {
            cout << "\n*************************************************** So id khong hop le *************************************************\n";
            system("pause");
            cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Main Menu  **********\n";
            cout << "\n\nVui long nhap lai id : ";
        }
    } while (true);
}

void Tao_tai_khoan_moi()
{
    ifstream FILE("Account_Info.txt");
    if (FILE)
    {
        bool is_empty = (FILE.peek() == ifstream::traits_type::eof());
        if (is_empty)
        {
            ofstream FILE("Account_Info.txt", ios::app);
            {
                FILE << 0 << " " << 0 << " " << 0 << endl;
            }
        }
    }
    FILE.close();

    cout << "\n=================================================== Tao tai khoan moi ==================================================" << endl;
    cout << "\n\n\t\t\t      **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
    cout << "\nTao id moi tu 5 -> 9 chu so : ";
    string so_id;
    do
    {
        vector<int> a = Get_all_account_infomation();
        cin >> so_id;
        if (Is_int(so_id) && String_to_int(so_id) > 10000 && String_to_int(so_id) % 10000 != 0 && !Is_duplicate_id(a, String_to_int(so_id)))
        {
            cout << "\n\nId hop le. Tao id moi thanh cong";
            cout << "\n\n\t\t\t       **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
            cout << "\n\nTao ma pin moi tu 5 -> 9 chu so : ";
            string ma_pin;
            do
            {
                cin >> ma_pin;
                if (Is_int(ma_pin) && String_to_int(ma_pin) > 10000 && String_to_int(ma_pin) % 10000 != 0 && !Is_duplicate_pin(a, String_to_int(ma_pin)))
                {
                    cout << "\n\nMa pin hop le. Tao ma pin moi thanh cong";

                    int id = String_to_int(so_id);
                    int pin = String_to_int(ma_pin);

                    ofstream file("Account_Info.txt", ios::app);
                    if (file)
                    {
                        file << id << " " << pin << " " << 0 << endl;
                    }
                    file.close();

                    cout << "\n\n============================================= Tao tai khoan moi thanh cong =============================================";
                    cout << "\n\t\t\t\t\t\t So du ban dau : 0 dong\n\n";
                    system("cls");
                    Dang_nhap();
                    break;
                }
                else if (Is_duplicate_pin(a, String_to_int(ma_pin)))
                {
                    cout << "\n\n\t\t\t       **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
                    cout << "\n\nMa pin nay da ton tai. Vui long tao ma pin khac tu 5 -> 9 chu so: ";
                }
                else if (ma_pin == "t" || ma_pin == "T")
                {
                    Main_menu();
                    break;
                }
                else
                {
                    cout << "\n\n\t\t\t       **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
                    cout << "\n\nMa pin khong hop le. Vui long tao ma pin khac tu 5 -> 9 chu so: ";
                }
            } while (true);
        }
        else if (Is_duplicate_id(a, String_to_int(so_id)))
        {
            cout << "\n\n\t\t\t       **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
            cout << "\n\nId nay da ton tai. Vui long tao id khac tu 5 -> 9 chu so: ";
        }
        else if (so_id == "t" || so_id == "T")
        {
            Main_menu();
            break;
        }
        else
        {
            cout << "\n\n\t\t\t       **********  Nhap phim [T] de tro ve Main Menu  **********" << endl;
            cout << "\n\nId khong hop le. Vui long tao id khac tu 5 -> 9 chu so: ";
        }
    } while (true);
}

void Thoat_chuong_trinh()
{
    cout << "\nQuy khach co muon thoat chuong trinh (y/n) ? : ";

    do
    {
        string response;
        cin >> response;
        if (response == "y" || response == "Y")
        {
            cout << "\n\n******************************** Cam on quy khach da su dung dich vu ******************************" << endl;
            exit(0);
            break;
        }
        else if (response == "n" || response == "N")
        {
            system("cls");
            Main_menu();
            break;
        }
        else
        {
            cout << "\nCu phap sai.Vui long nhap (y/n) :";
        }

    } while (true);
}

void Menu()
{
    cout << "\n\n======================================================= MENU ===========================================================" << endl;
    cout << "Vui long chon chuc nang :" << endl;
    cout << "\t 1. Gui tien" << endl;
    cout << "\t 2. Rut tien" << endl;
    cout << "\t 3. Kiem tra so du tai khoan" << endl;
    cout << "\t 4. Kiem tra lich su giao dich" << endl;
    cout << "\t 5. Chuyen tien" << endl;
    cout << "\t 6. Doi ma pin" << endl;
    cout << "\t 7. Dang xuat" << endl;

    TaiKhoan account;

    do
    {
        string response;
        cin >> response;
        if (response == "1")
        {
            system("cls");
            account.gui_tien();
            break;
        }
        else if (response == "2")
        {
            system("cls");
            account.rut_tien();
            break;
        }
        else if (response == "3")
        {
            system("cls");
            account.kiem_tra_so_du();
            break;
        }
        else if (response == "4")
        {
            system("cls");
            account.kiem_tra_lich_su_giao_dich();
            break;
        }
        else if (response == "5")
        {
            system("cls");
            account.chuyen_tien();
            break;
        }
        else if (response == "6")
        {
            system("cls");
            account.doi_ma_pin();
            break;
        }
        else if (response == "7")
        {
            system("cls");
            Dang_xuat_tai_khoan();
            break;
        }
        else
            cout << "Cu phap sai. Vui long nhap tu 1 -> 7." << endl;
    } while (true);
}

void Dang_xuat_tai_khoan()
{
    cout << "\nQuy khach co muon dang xuat tai khoan (y/n) ? : ";

    do
    {
        string response;
        cin >> response;
        if (response == "y" || response == "Y")
        {
            system("cls");
            Main_menu();
            break;
        }
        else if (response == "n" || response == "N")
        {
            system("cls");
            Menu();
            break;
        }
        else
        {
            cout << "\nCu phap sai.Vui long nhap (y/n) :";
        }

    } while (true);
}

void Admin()
{
    cout << "\n======================================================== Admin =========================================================";
    cout << "\nSelect option : ";
    cout << "\n\t1. Check deposit and withdraw history";
    cout << "\n\t2. Check transfer history";
    cout << "\n\t3. Unlocked account";
    cout << "\n\t4. Check money in ATM";
    cout << "\n\t5. Exit\n";
    cout << "\nPlease select option: ";
    string option;
    do
    {
        cin >> option;
        if (option == "1")
        {
            system("cls");
            ifstream file("History_1.txt");
            bool is_empty = (file.peek() == ifstream::traits_type::eof());
            if (is_empty)
            {
                cout << "\n\nHas no deposit and withdraw history\n";
                system("pause");
                Menu();
            }
            else
            {
                while (file && !file.eof())
                {
                    string s;
                    getline(file, s);
                    cout << s << endl;
                }
                file.close();
            }
            system("pause");
            Admin();
            break;
        }
        else if (option == "2")
        {
            system("cls");
            ifstream file("Transfer_1.txt");
            bool is_empty = (file.peek() == ifstream::traits_type::eof());
            if (is_empty)
            {
                cout << "\n\nHas no transfer history\n";
                system("pause");
                Menu();
            }
            else
            {
                while (file && !file.eof())
                {
                    string s;
                    getline(file, s);
                    cout << s << endl;
                }
                file.close();
            }
            system("pause");
            Admin();
            break;
        }
        else if (option == "3")
        {
            system("cls");
            cout << "\nUnlocked id: ";
            string id;
            do
            {
                cin >> id;
                if (Is_locked_id(String_to_int(id)))
                {
                    vector<int> a;
                    ifstream file("Locked_id.txt");
                    while (file && !file.eof())
                    {
                        int number;
                        file >> number;
                        a.push_back(number);
                    }
                    file.close();
                    a.erase(a.begin() + a.size() - 1);

                    for (int i = 0; i < a.size(); i++)
                    {
                        if (a[i] == String_to_int(id))
                        {
                            a.erase(a.begin() + i);
                            break;
                        }
                    }

                    ofstream File("Locked_id.txt");
                    if (File)
                    {
                        for (int i = 0; i < a.size(); i++)
                        {
                            File << a[i] << endl;
                        }
                    }
                    File.close();
                    cout << "Id " << id << " is unlocked" << endl;
                    system("pause");
                    Admin();
                    break;
                }
                else
                {
                    cout << "This id does not exist or is not locked" << endl;
                    system("pause");
                    Admin();
                    break;
                }
            } while (true);
        }
        else if (option == "4")
        {
            system("cls");
            ifstream file("Money_in_atm.txt");
            bool is_empty = (file.peek() == ifstream::traits_type::eof());
            if (is_empty)
            {
                cout << "\n\nHas no money in ATM\n";
                system("pause");
                Menu();
            }
            else
            {
                cout << "\n\nMoney in ATM : \n";
                while (file && !file.eof())
                {
                    string s;
                    getline(file, s);
                    cout << s << endl;
                }
                file.close();
            }
            system("pause");
            Admin();
            break;
        }
        else if (option == "5")
        {
            cout << "\nEnd program";
            exit(0);
            break;
        }
        else
            cout << "\nPlease select option from 1 to 5 : ";
    } while (true);
}

