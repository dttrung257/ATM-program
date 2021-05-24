#include "account.h"

TaiKhoan::TaiKhoan()
{
    vector<int> Thong_tin_tai_khoan = Get_single_account_infomation();

    id = Thong_tin_tai_khoan[0];
    pin = Thong_tin_tai_khoan[1];
    so_du_tai_khoan = Thong_tin_tai_khoan[2];
}

// Luu lai thong tin
void TaiKhoan::Luu_thong_tin()
{
    ofstream file("Account_Info.txt", ios::app);
    if (file)
    {
        file << id << " ";
        file << pin << " ";
        file << so_du_tai_khoan << endl;
    }
    file.close();

    ofstream File("Single_Account_Info.txt");
    if (File)
    {
        File << id << " " << pin << " " << so_du_tai_khoan << endl;
    }
    File.close();
}

// Kiem tra tai khoan
void TaiKhoan::kiem_tra_so_du()
{
    string xac_nhan;
    cout << "\nQuy khach co muon kiem tra so du khoan (y/n) ? :  ";
    do
    {
        cin >> xac_nhan;
        if (xac_nhan == "y" || xac_nhan == "Y")
        {
            system("cls");
            cout << "\n\tSo du tai khoan cua quy khach: " << so_du_tai_khoan << " dong" << endl;
            system("pause");
            Menu();
            break;
        }
        else if (xac_nhan == "n" || xac_nhan == "N")
        {
            system("cls");
            Menu();
            break;
        }
        else
            cout << "\nCu phap sai. Vui long nhap (y/n)." << endl;
    } while (true);
}

//Rut tien
void TaiKhoan::rut_tien()
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    vector<int> Thong_tin_tai_khoan = Get_single_account_infomation();
    cout << "\n\n======================================================== Rut tien ====================================================\n";
    cout << "\n\t\t\t\t**********  Nhap phim [T] tro ve menu  **********";
    cout << "\n\nMenh gia nho nhat: 10,000 dong. Vui long nhap so tien can rut: ";
    do
    {
        string response;
        cin >> response;
        if (Is_int(response) && String_to_int(response) > 0 && String_to_int(response) % 10000 == 0)
        {
            string input;
            cout << "\n\nVui long nhap ma pin de rut tien: ";
            cin >> input;
            if (String_to_int(input) == pin)
            {
                int so_tien_can_rut = String_to_int(response);
                if (so_tien_can_rut <= so_du_tai_khoan)
                {
                    if (Can_withdraw_or_transfer_money(so_tien_can_rut))
                    {
                        so_du_tai_khoan -= so_tien_can_rut;
                        Thong_tin_tai_khoan[2] = so_du_tai_khoan;
                        vector<int> so_to_duoc_chon = Greedy(so_tien_can_rut);
                        system("cls");
                        cout << "\n================================================== Rut tien thanh cong =================================================";
                        cout << "\nDa rut: " << so_tien_can_rut << " dong" << endl;
                        cout << "\nQuy khach se nhan duoc: " << endl;
                        for (int i = 0; i < 6; i++)
                        {
                            if (so_to_duoc_chon[i] > 0)
                                cout << so_to_duoc_chon[i] << " to " << Loai_tien[i] << " dong" << endl;
                        }

                        for (int i = 0; i < 6; i++)
                        {
                            if (so_to_duoc_chon[i] > 0)
                            {
                                vector<int> newSoTo = Decrease_money_in_atm(Loai_tien[i], so_to_duoc_chon[i]);
                                Save_money_to_atm(newSoTo);
                            }
                        }

                        // Luu lich su rut tien.
                        vector<int> time = Get_time();
                        ofstream file("History_1.txt", ios::app);
                        if (file)
                        {
                            file << "\n* Thoi gian: " << time[0] << "/" << time[1] << "/" << time[2] << " " << time[3] << ":" << time[4] << ":" << time[5] << "s" << endl;
                            file << "So id: " << id << " . Ma pin : Private. Rut tien: Tai khoan " << (-1) * so_tien_can_rut << " dong. Da tra ra: " << endl;
                            for (int i = 0; i < 6; i++)
                            {
                                if (so_to_duoc_chon[i] > 0)
                                    file << so_to_duoc_chon[i] << " to " << Loai_tien[i] << " dong"
                                    << endl;
                            }
                            file << endl;
                        }
                        file.close();

                        ofstream File("History_2.txt", ios::app);
                        if (File)
                        {
                            File << id << " " << (-1) * so_tien_can_rut << " ";
                            for (int i = 0; i < 6; i++)
                            {
                                File << time[i] << " ";
                            }
                            File << endl;
                        }
                        File.close();

                        Luu_thong_tin();

                        cout << "\n\nQuy khach co muon tiep tuc rut tien (y/n) ? : ";
                        do
                        {
                            cin >> response;
                            if (response == "y" || response == "Y")
                            {
                                system("cls");
                                rut_tien();
                                break;
                            }
                            else if (response == "n" || response == "N")
                            {
                                system("cls");
                                Menu();
                                break;
                            }
                            else
                                cout << "\nCu phap sai. Vui long nhap (y/n) : ";
                        } while (true);
                    }
                    else
                    {
                        cout << "\nKhong the thuc hien giao dich";
                        cout << "\n\nQuy khach co muon tiep tuc rut tien (y/n) ? : ";
                        do
                        {
                            cin >> response;
                            if (response == "y" || response == "Y")
                            {
                                system("cls");
                                rut_tien();
                                break;
                            }
                            else if (response == "n" || response == "N")
                            {
                                system("cls");
                                Menu();
                                break;
                            }
                            else
                                cout << "\nCu phap sai. Vui long nhap (y/n) : ";
                        } while (true);
                    }
                }
                else
                {
                    cout << "\nSo du tai khoan cua quy khach khong du de giao dich.";
                    cout << "\nQuy khach muon tro ve menu (y/n) ? : ";
                    do
                    {
                        cin >> response;
                        if (response == "y" || response == "Y")
                        {
                            system("cls");
                            Menu();
                            break;
                        }
                        else if (response == "n" || response == "N")
                        {
                            system("cls");
                            rut_tien();
                            break;
                        }
                        else
                            cout << "\nCu phap sai. Vui long nhap (y/n) ? : ";
                    } while (true);
                    break;
                }
            }
            else
            {
                system("cls");
                cout << "\n========================================= Ma pin sai khong the thuc hien rut tien =======================================";
                cout << "\n\t\t\t\t**********  Nhap phim [0] tro ve menu  **********";
                cout << "\n\nMenh gia nho nhat: 10,000 dong. Vui long nhap so tien can rut: ";
            }
        }
        else if (response == "t" || response == "T")
        {
            system("cls");
            Menu();
            break;
        }
        else
        {
            system("cls");
            cout << "\nSo tien nhap khong hop le" << endl;
            cout << "\n\t\t\t\t**********  Nhap phim [0] tro ve menu  **********";
            cout << "\n\nMenh gia nho nhat: 10,000 dong. Vui long nhap so tien can rut: ";
        }
    } while (true);
}

// Gui tien
void TaiKhoan::gui_tien()
{
    cout << "\n======================================================== Gui tien ======================================================";
    cout << "\n Vui long chon menh gia: ";
    cout << "\n1. 500,000 dong";
    cout << "\n2. 200,000 dong";
    cout << "\n3. 100,000 dong";
    cout << "\n4. 50,000 dong";
    cout << "\n5. 20,000 dong";
    cout << "\n6. 10,000 dong";
    cout << "\n7. Tro ve menu\n";
    string option;
    do
    {
        cin >> option;
        if (option == "1")
        {
            system("cls");
            gui_tien_theo_menh_gia(500000);
            break;
        }
        else if (option == "2")
        {
            system("cls");
            gui_tien_theo_menh_gia(200000);
            break;
        }
        else if (option == "3")
        {
            system("cls");
            gui_tien_theo_menh_gia(100000);
            break;
        }
        else if (option == "4")
        {
            system("cls");
            gui_tien_theo_menh_gia(50000);
            break;
        }
        else if (option == "5")
        {
            system("cls");
            gui_tien_theo_menh_gia(20000);
            break;
        }
        else if (option == "6")
        {
            system("cls");
            gui_tien_theo_menh_gia(10000);
            break;
        }
        else if (option == "7")
        {
            cout << "\nQuy khach muon tro ve menu (y/n) ? : ";
            do
            {
                string response;
                cin >> response;
                if (response == "y" || response == "Y")
                {
                    system("cls");
                    Menu();
                    break;
                }
                else if (response == "n" || response == "N")
                {
                    system("cls");
                    gui_tien();
                    break;
                }
                else
                    cout << "\nCu phap sai. Vui long nhap (y/n) ? : ";
            } while (true);
        }
        else
            cout << "\nCu phap sai. Vui long nhap 1 -> 7: ";
    } while (true);
}

void TaiKhoan::gui_tien_theo_menh_gia(const int& menhgia)
{
    vector<int> Thong_tin_tai_khoan = Get_single_account_infomation();
    string so_to;
    cout << "\n\n\t\t\t\t**********  Nhap phim [T] de quay lai Menu **********" << endl;
    cout << "\nVui long nhap so to " << menhgia << " dong : ";
    do
    {
        cin >> so_to;
        if (Is_int(so_to) && String_to_int(so_to) > 0 && String_to_int(so_to) < 1000)
        {
            cout << "\nVui long nhap ma pin de thuc hien gui tien: ";
            string response;
            cin >> response;
            if (String_to_int(response) == pin)
            {
                int soto = String_to_int(so_to);
                so_du_tai_khoan += menhgia * soto;
                Thong_tin_tai_khoan[2] = so_du_tai_khoan;

                system("cls");
                cout << "\n======================== "
                    << menhgia * soto << " dong da gui vao tai khoan cua quy khach ========================" << endl;
                cout << "\nSo du hien tai: " << so_du_tai_khoan << " dong" << endl;

                vector<int> newSoTo = Increase_money_in_atm(menhgia, soto);
                Save_money_to_atm(newSoTo);

                // Luu lich su gui tien.
                vector<int> time = Get_time();

                ofstream file("History_1.txt", ios::app);
                if (file)
                {
                    file << "\n# Thoi gian: " << time[0] << "/" << time[1] << "/" << time[2] << " " << time[3] << ":" << time[4] << ":" << time[5] << "s" << endl;
                    file << "So id: " << id << ". Ma pin: Private. Gui tien: Tai khoan +" << menhgia * soto << " dong. Da nhan: " << soto << " to " << menhgia << " dong." << endl;
                }
                file.close();
                ofstream File("History_2.txt", ios::app);
                if (File)
                {
                    File << id << " " << menhgia * soto << " " << soto << " " << menhgia << " ";

                    for (int i = 0; i < 6; i++)
                        File << time[i] << " ";
                    File << endl;
                }
                File.close();


                // Update so du tai khoan lai.
                Luu_thong_tin();

                cout << "\nQuy khach co tiep tuc gui tien (y/n) ? : ";
                do
                {
                    cin >> response;
                    if (response == "y" || response == "Y")
                    {
                        system("cls");
                        gui_tien();
                        break;
                    }
                    else if (response == "n" || response == "N")
                    {
                        system("cls");
                        Menu();
                        break;
                    }
                    else
                        cout << "\nCu phap sai. Vui long nhap (y/n): ";
                } while (true);
            }
            else
            {
                system("cls");
                cout << "\n======================================== Ma pin sai khong the thuc hien gui tien ======================================";
                gui_tien_theo_menh_gia(menhgia);
                break;
            }
        }
        else if (so_to == "t" || so_to == "T")
        {
            system("cls");
            gui_tien();
            break;
        }
        else
        {
            system("cls");
            cout << "\n======= Vui long nhap so to " << menhgia << " dong la so nguyen > 0 va < 1000 neu quy khach muon gui tien ===========" << endl;
            cout << "=========================== Nhap so 0 neu quy khach chon sai menh gia =========================================" << endl;
            cout << "\nVui long nhap lai lua chon : ";
        }
    } while (true);
}


void TaiKhoan::kiem_tra_lich_su_gui_va_rut_tien()
{
    int Loai_tien[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
    vector<int> a;
    ifstream file("History_2.txt");
    if (file)
    {
        bool is_empty = (file.peek() == ifstream::traits_type::eof());
        if (is_empty)
        {
            cout << "\n\nKhong co lich su rut va gui tien nao.\n\n";
        }
        else
        {
            while (file && !file.eof())
            {
                int n;
                file >> n;
                a.push_back(n);
            }
        }
    }
    file.close();

    bool Co_giao_dich = false;
    for (int i = 0; i < a.size() ; i++)
    {
        if (a[i] == id)
        {
            Co_giao_dich = true;
            break;
        }
    }
    if (Co_giao_dich)
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == id)
            {
                if (a[i + 1] > 0)
                {
                    cout << "\nThoi gian: " << a[i + 4] << "/" << a[i + 5] << "/" << a[i + 6] << " " << a[i + 7] << ":" << a[i + 8] << ":" << a[i + 9] << "s" << endl;
                    cout << "Gui tien: Tai khoan +" << a[i + 1] << " dong. Da nhan: " << a[i + 2] << " to " << a[i + 3] << " dong." << endl;
                }
                else if (a[i + 1] < 0)
                {
                    vector<int> soto = Greedy((-1) * a[i + 1]);
                    cout << "\nThoi gian: " << a[i + 2] << "/" << a[i + 3] << "/" << a[i + 4] << " " << a[i + 5] << ":" << a[i + 6] << ":" << a[i + 7] << "s" << endl;
                    cout << "Rut tien: Tai khoan " << a[i + 1] << " dong. Da tra ra: " << endl;
                    for (int i = 0; i < 6; i++)
                    {
                        if (soto[i] > 0)
                        {
                            cout << soto[i] << " to " << Loai_tien[i] << " dong " << endl;
                        }
                    }
                }
            }
        }
    }
    else
    {
        cout << "\nQuy khach chua thuc hien hoat dong rut va gui tien nao.";
    }
}

void TaiKhoan::kiem_tra_lich_su_chuyen_va_nhan_tien()
{
    vector<int> a;
    ifstream file("Transfer_2.txt");
    if (file)
    {
        bool is_empty = (file.peek() == ifstream::traits_type::eof());
        if (is_empty)
        {
            cout << "\n\nKhong co lich su chuyen va nhan tien nao.\n";
        }
        else
        {
            while (file && !file.eof())
            {
                int n;
                file >> n;
                a.push_back(n);
            }
        }
    }
    file.close();

    bool Co_giao_dich = false;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == id || ((-1) * a[i]) == id)
        {
            Co_giao_dich = true;
            break;
        }
    }
    if (Co_giao_dich)
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == id)
            {
                cout << "\nThoi gian: " << a[i + 2] << "/" << a[i + 3] << "/" << a[i + 4] << " " << a[i + 5] << ":" << a[i + 6] << ":" << a[i + 7] << "s" << endl;
                cout << "Nhan tien tu so id: " << (-1) * a[i - 1] << ". So tien nhan : " << a[i + 1] << " dong. Tai khoan + " << a[i + 1] << " dong" << endl;
            }
            else if (((-1) * a[i]) == id)
            {
                cout << "\nThoi gian: " << a[i + 3] << "/" << a[i + 4] << "/" << a[i + 5] << " " << a[i + 6] << ":" << a[i + 7] << ":" << a[i + 8] << "s" << endl;
                cout << "Chuyen tien den id: " << a[i + 1] << ". So tien chuyen : " << a[i + 2] << " dong. Tai khoan - " << a[i + 2] << " dong" << endl;
            }
        }
    }
    else
    {
        cout << "\n\nQuy khach khong co hoat dong chuyen va nhan tien nao." << endl;
    }
}

void TaiKhoan::kiem_tra_lich_su_giao_dich()
{
    cout << "\n================================================== Lich su giao dich ===================================================" << endl;
    kiem_tra_lich_su_gui_va_rut_tien();
    kiem_tra_lich_su_chuyen_va_nhan_tien();
    cout << "========================================================================================================================" << endl;
    system("pause");
    system("cls");
    Menu();
}

void TaiKhoan::chuyen_tien()
{
    vector<int> Thong_tin_tai_khoan = Get_single_account_infomation();

    cout << "\n====================================================== Chuyen tien =====================================================";
    cout << "\n\t\t\t\t**********  Nhap phim [T] de tro ve MENU  **********";
    cout << "\n\nVui long nhap id tai khoan nhan: ";
    vector<int> a = Get_all_account_infomation();
    string so_id;
    do
    {
        cin >> so_id;
        bool true_id = false;
        for (int i = 0; i < a.size(); i++)
        {
            if (i % 3 == 0 && a[i] == String_to_int(so_id))
            {
                true_id = true;
                break;
            }
        }
        if (Is_int(so_id) && true_id && String_to_int(so_id) > 10000 && String_to_int(so_id) != id)
        {
            int id = String_to_int(so_id);
            vector<int> Thong_tin_nguoi_nhan = Get_account_infomation(id);

            cout << "\nHe thong xac nhan duoc id nhan tien";
            cout << "\n\nVui long nhap so tien can chuyen: ";
            string tien_chuyen;

            do
            {
                cin >> tien_chuyen;
                if (Is_int(tien_chuyen) && String_to_int(tien_chuyen) > 0 && String_to_int(tien_chuyen) % 10000 == 0)
                {
                    if (String_to_int(tien_chuyen) > so_du_tai_khoan && Can_withdraw_or_transfer_money(String_to_int(tien_chuyen)))
                    {
                        cout << "\nSo tien trong tai khoan quy khach khong du de thuc hien chuyen tien";
                        cout << "\nQuy khach co muon tiep tuc chuyen tien (y/n): ";
                        do
                        {
                            string response;
                            cin >> response;
                            if (response == "y" || response == "Y")
                            {
                                system("cls");
                                chuyen_tien();
                                break;
                            }
                            else if (response == "n" || response == "N")
                            {
                                system("cls");
                                Menu();
                                break;
                            }
                            else
                                cout << "\nCu phap sai. Vui long nhap (y/n): ";
                        } while (true);
                    }
                    else
                    {
                            string ma_pin;
                                cout << "\nVui long nhap ma pin de thuc hien chuyen tien: ";
                                cin >> ma_pin;
                                if (String_to_int(ma_pin) == pin)
                                {
                                    int so_tien_chuyen = String_to_int(tien_chuyen);
                                        so_du_tai_khoan -= so_tien_chuyen;
                                        Thong_tin_tai_khoan[2] = so_du_tai_khoan;

                                        // Luu thong tin tai khoan chuyen tien
                                        Luu_thong_tin();

                                    Thong_tin_nguoi_nhan[2] += so_tien_chuyen;

                                    // Luu thong tin tai khoan nhan tien
                                    ofstream file("Account_Info.txt", ios::app);
                                    if (file)
                                    {
                                        file << Thong_tin_nguoi_nhan[0] << " " << Thong_tin_nguoi_nhan[1] << " " << Thong_tin_nguoi_nhan[2] << endl;
                                    }
                                    file.close();

                                    // Luu lich su
                                    vector<int> time = Get_time();
                                    ofstream File("Transfer_1.txt", ios::app);
                                    if (File)
                                    {
                                        File << "\nThoi gian: " << time[0] << "/" << time[1] << "/" << time[2] << " " << time[3] << ":" << time[4] << ":" << time[5] << "s" << endl;
                                        File << "So id: " << Thong_tin_tai_khoan[0] << " chuyen khoan " << so_tien_chuyen << " dong -> so id: " << Thong_tin_nguoi_nhan[1] << endl;
                                    }
                                    File.close();

                                    ofstream FILE("Transfer_2.txt", ios::app);
                                    if (FILE)
                                    {
                                        FILE << (-1) * Thong_tin_tai_khoan[0] << " " << Thong_tin_nguoi_nhan[0] << " " << so_tien_chuyen << " ";
                                        for (int i = 0; i < 6; i++)
                                        {
                                            FILE << time[i] << " ";
                                        }
                                        FILE << endl;
                                    }
                                    FILE.close();
                                    cout << "\n============================================== Chuyen tien thanh cong ===============================================";

                                    cout << "\n\nQuy khach co muon tiep tuc chuyen tien (y/n): ";
                                    do
                                    {
                                        string response;
                                        cin >> response;
                                        if (response == "y" || response == "Y")
                                        {
                                            system("cls");
                                            chuyen_tien();
                                            break;
                                        }
                                        else if (response == "n" || response == "N")
                                        {
                                            system("cls");
                                            Menu();
                                            break;
                                        }
                                        else
                                            cout << "\nCu phap sai. Vui long nhap (y/n): ";
                                    } while (true);
                                }
                                else
                                {
                                    cout << "\n\t\t****************** Ma pin sai. Khong the thuc hien chuyen tien **********************";
                                    chuyen_tien();
                                    break;
                                }
                    }

                }
                else
                {
                    cout << "\nSo tien chuyen khong hop le";
                    cout << "\nQuy khach co muon tiep tuc chuyen tien (y/n): ";
                    do
                    {
                        string response;
                        cin >> response;
                        if (response == "y" || response == "Y")
                        {
                            system("cls");
                            chuyen_tien();
                            break;
                        }
                        else if (response == "n" || response == "N")
                        {
                            system("cls");
                            Menu();
                            break;
                        }
                        else
                            cout << "\nCu phap sai. Vui long nhap (y/n): ";
                    } while (true);
                }
            } while (true);
        }
        else if (so_id == "t" || so_id == "T")
        {
            system("cls");
            Menu();
            break;
        }
        else if (String_to_int(so_id) == id)
        {
            cout << "\nSo id " << id << " hien dang la id cua tai khoan nay" << endl;
            cout << "\n\nKhong the thuc hien chuyen tien" << endl;
            cout << "\n\t\t\t\t**********  Nhap phim [0] de tro ve MENU  **********";
            cout << "\n\nVui long nhap id tai khoan nhan: ";
        }
        else
        {
            cout << "\nSo id " << so_id << " hien dang khong ton tai";
            cout << "\n\nQuy khach co muon tiep tuc chuyen tien (y/n): ";
            string response;
            do
            {
                cin >> response;
                if (response == "y" || response == "Y")
                {
                    system("cls");
                    chuyen_tien();
                    break;
                }
                else if (response == "n" || response == "N")
                {
                    system("cls");
                    Menu();
                    break;
                }
                else
                    cout << "\nCu phap sai. Vui long nhap (y/n): ";
            } while (true);
        }
    } while (true);
}

void TaiKhoan::doi_ma_pin()
{
    string ma_pin;
    cout << "\n====================================================== Doi ma pin =====================================================";
    cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Menu  **********";
    cout << "\n\nVui long nhap ma pin tai khoan : ";
    do
    {
        cin >> ma_pin;
        if (String_to_int(ma_pin) == pin)
        {
            vector<int> a = Get_all_account_infomation();
            string ma_pin_moi;
            cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Menu  **********";
            cout << "\nVui long nhap ma pin moi : ";
            do
            {
                cin >> ma_pin_moi;
                if (Is_int(ma_pin_moi) && String_to_int(ma_pin_moi) > 10000 && String_to_int(ma_pin_moi) % 10000 != 0 && !Is_duplicate_pin(a, String_to_int(ma_pin_moi)))
                {
                    ofstream file("Single_Account_Info.txt");
                    if (file)
                    {
                        file << id << " " << String_to_int(ma_pin_moi) << " " << so_du_tai_khoan << endl;
                    }
                    file.close();

                    int n = a.size();
                    int* arr = new int[n];
                    for (int i = 0; i < n; i++)
                    {
                        arr[i] = a[i];
                    }

                    for (int i = 0; i < n; i++)
                    {
                        if (i % 3 == 1 && arr[i] == pin)
                        {
                            arr[i] = String_to_int(ma_pin_moi);
                        }
                    }
                        
                    ofstream File("Account_Info.txt");
                    if (File)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            if (i % 3 == 0)
                            {
                                File << arr[i] << " " << arr[i + 1] << " " << arr[i + 2] << endl;
                            }
                        }
                    }
                    File.close();

                    system("cls");
                    cout << "\n\nDoi ma pin thanh cong" << endl;
                    system("pause");
                    Menu();
                }
                else if (ma_pin_moi == "t" || ma_pin_moi == "T")
                {
                    system("cls");
                    Menu();
                    break;
                }
                else
                {
                    system("cls");
                    cout << "Ma pin moi khong hop le";
                    cout << "Quy khach co muon tiep tuc doi ma pin (y/n) : ";
                    string response;
                    do
                    {
                        cin >> response;
                        if (response == "y" || response == "Y")
                        {
                            system("cls");
                            doi_ma_pin();
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
                            cout << "\n\nCu phap sai. Vui long nhap (y/n) :";
                        }
                    } while (true);
                }
            } while (true);
        }
        else if (ma_pin == "t" || ma_pin == "T")
        {
            system("cls");
            Menu();
            break;
        }
        else
        {
            system("cls");
            cout << "Sai ma pin. Khong the thuc hien doi ma pin moi";
            cout << "\n\n\t\t\t\t**********  Nhap phim [T] de tro ve Menu **********";
            cout << "\n\nVui long nhap ma pin tai khoan : ";
        }
    } while (true);
}
