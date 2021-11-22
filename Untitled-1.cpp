
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
struct Contact
{
    unsigned long long mobile;
    string email;
};

struct Penulis
{
    unsigned long long id = 0;
    string nama = "";
    string judulbuku = "";
    double beban_biaya = 0;
    int tahun_masuk;
    Contact contact;
};

struct Pembayaran
{
public:
    unsigned long long id;
    double jumlah;
};

vector<Penulis> list_pns;
vector<Pembayaran> payment;

Penulis current;

void merge(vector<Penulis>& array, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    vector<Penulis> leftArray;
    vector<Penulis> rightArray;
    for (auto i = 0; i < subArrayOne; i++)
        leftArray.push_back(array[left + i]);
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray.push_back(array[mid + 1 + j]);

    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne].id <= rightArray[indexOfSubArrayTwo].id)
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];

        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSortAlgoritm(int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSortAlgoritm(begin, mid);
    mergeSortAlgoritm(mid + 1, end);
    merge(list_pns, begin, mid, end);
}

void swap(Penulis* a, Penulis* b)
{
    Penulis t = *a;
    *a = *b;
    *b = t;
}

int partition(int low, int high)
{
    double pivot = list_pns[high].beban_biaya;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (list_pns[j].beban_biaya > pivot)
        {
            i++;
            swap(&list_pns[i], &list_pns[j]);
        }
    }
    swap(&list_pns[i + 1], &list_pns[high]);
    return (i + 1);
}

void quickSortAlgoritm(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSortAlgoritm(low, pi - 1);
        quickSortAlgoritm(pi + 1, high);
    }
}

void shellSortAlgoritm(int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            Penulis temp = list_pns[i];
            int j;
            for (j = i; j >= gap && list_pns[j - gap].beban_biaya > temp.beban_biaya; j -= gap)
                list_pns[j] = list_pns[j - gap];
            list_pns[j] = temp;
        }
    }
}

void PRINT_MENU_PROGRAM()
{
    cout << "1. Input Penulis        	\n";
    cout << "2. Tampil Detil Penulis 	\n";
    cout << "3. Pembayaran Penerbit   	\n";
    cout << "4. Hapus Data Penulis   	\n";
    cout << "5. Sorting Laporan Pembayaran\n";
    cout << "6. Search Laporan Pembayaran\n";
    cout << "7. Keluar\n";
    cout << "------------------------------------------------------------------------------------------------------------\n";
    cout << "Masukkan angka untuk masuk ke menu [1 - 4]: ";
}
void PRINT_BANNER_PROGRAM()
{
    system("cls");
    cout << "============================================================================================================\n";
    cout << "\t\t\tSISTEM PENERBITAN BUKU PENULIS \n";
    cout << "------------------------------------------------------------------------------------------------------------\n";
}
bool CEK_PENULIS_ADA(unsigned long long id)
{
    bool ret = false;
    for (Penulis pns : list_pns)
    {
        if (pns.id == id)
        {
            ret = true;
            current = pns;
            break;
        }
    }
    return ret;
}
bool CEK_ID_TERPAKAI(unsigned long long id)
{
    bool ret_value = false;
    for (Penulis pns : list_pns)
    {
        if (pns.id == id)
        {
            ret_value = true;
            goto end_of_func;
        }
    }
    ret_value = false;
end_of_func:
    return ret_value;
}
double READ_TOTALBAYAR_PENERBIT(unsigned long long id)
{
    double return_value = 0;
    for (Pembayaran p : payment)
    {
        if (p.id == id)
        {
            return_value += p.jumlah;
        }
    }
    return return_value;
}

void CREATE_PENULIS()
{
    PRINT_BANNER_PROGRAM();

    unsigned long long _id;
    string _nama;
    string _judulbuku;
    double _biaya;
    int _thn_masuk;
    unsigned long long _mobile;

    string _email;
new_input:
    cout << "INPUT DATA PENULIS BARU\n";
    cout << "------------------------------------------------------------------------------------------------------------\n";
re_input:
    cout << "ID Penulis		: ";
    string str_input;
    unsigned long long d;
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> d)
        {
            if (ss.eof())
            {
                bool test = CEK_ID_TERPAKAI(d);
                if (test)
                {
                    cout << "          ERROR: ID" << d << "' Sudah terdaftar gunakan ID lain" << endl;
                    goto re_input;
                }
                _id = d;
                break;
            }
        }
        cout << "          ERROR: ID HARUS BERUPA ANGKA" << std::endl;
        goto re_input;
    }
re_input_nama:
    cout << "Nama Penulis		: ";
    getline(cin, _nama);
    if (_nama == "")
    {
        cout << "          ERROR: nama penulis tidak boleh kosong" << endl;
        goto re_input_nama;
    }
re_input_judulbuku:
    cout << "Judul Buku		: ";
    getline(cin, _judulbuku);
    if (_judulbuku == "")
    {
        cout << "\t ERROR: Judul buku tidak boleh kosong" << endl;
        goto re_input_judulbuku;
    }
enter_tahun_masuk:
    cout << "Tahun Buku Terbit	: ";
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> _thn_masuk)
        {
            if (ss.eof())
            {
                if (_thn_masuk > 2021)
                {
                    cout << "          ERROR: Tahun terbit tidak boleh lebih dari 2021";
                    goto enter_tahun_masuk;
                }
                else
                {
                    break;
                }
            }
        }
        cout << "          ERROR: Tahun terbit tidak valid";
        goto enter_tahun_masuk;
    }

    cout << "\nInformasi Kontak" << endl;
    cout << "------------------------------" << endl;
re_input_email:
    {
        cout << "Email			: ";
        getline(cin, _email);
        if (_email == "")
        {
            cout << "\t ERROR: Email tidak boleh kosong" << endl;
            goto re_input_email;
        }
    }
re_input_mobile:
    cout << "Nomor Ponsel\t\t: ";
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> _mobile)
        {
            if (ss.eof())
            {
                break;
            }
        }
        cout << "          ERROR: nomor HP harus berupa angka [0..9]" << endl;
        goto re_input_mobile;
    }

re_input_biaya:
    cout << "\n\nBiaya Penerbit      : Rp.";
    double biaya;
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> biaya)
        {
            if (ss.eof())
            {
                _biaya = biaya;
                break;
            }
        }
        cout << "          ERROR: Nominal biaya harus berupa angka desimal [0..9]" << std::endl;
        goto re_input_biaya;
    }
    cout << "\nSimpan '" << _nama << "' (Y/N) ";
    char key = _getch();
    if (key == 'Y' || key == 'y')
    {
        Penulis baru;
        baru.nama = _nama;
        baru.judulbuku = _judulbuku;
        baru.id = _id;
        baru.beban_biaya = _biaya;
        baru.tahun_masuk = _thn_masuk;

        Contact c;
        c.mobile = _mobile;
        c.email = _email;

        baru.contact = c;

        list_pns.push_back(baru);
        cout << "\n\nData Penulis berhasil disimpan. Input Lagi? [Y/N] -> ";
        char pressed_key = _getch();
        if (pressed_key == 'y' || pressed_key == 'Y')
        {
            cout << endl;
            PRINT_BANNER_PROGRAM();
            goto new_input;
        }
    }
}
void READ_PENULIS()
{
    PRINT_BANNER_PROGRAM();

    double _total;
    int index;

    cout << "REQUEST DETAIL INFORMATION - By ID" << endl;
re_input:
    cout << "Masukkan ID Penulis\t: ";
    string str_input;
    unsigned long long d;
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> d)
        {
            if (ss.eof())
            {
                bool exist = CEK_PENULIS_ADA(d);
                if (exist)
                {
                    break;
                }
                else
                {
                    cout << "Data penulis dengan ID '" << d << " tidak ditemukan, cari lagi? [Y/N] ..." << endl;
                    char key = _getch();
                    if (key == 'Y' || key == 'y')
                    {
                        goto re_input;
                    }
                    else
                    {
                        goto exit_sub;
                    }
                }
            }
        }
        cout << "          ERROR: ID YANG DIINPUT HARUS BERUPA ANGKA" << std::endl;
        goto re_input;
    }
    _total = 0;
    index = 1;
    cout << "Nama Penulis\t\t: " << current.nama << endl;
    cout << "Judul Buku\t\t: " << current.judulbuku << endl;
    cout << "Program / Thn\t\t: " << current.tahun_masuk << endl;
    cout << "Email\t\t\t: " << current.contact.email << endl;
    cout << "Nomer Handphone\t\t: 0" << current.contact.mobile << endl;
    cout << "Biaya Penerbit\t\t: " << put_money(current.beban_biaya) << endl
        << endl;
    cout << "\nRiwayat Pembayaran Penerbit" << endl;
    cout << "------------------------------------------------" << endl;
    cout << setw(6) << "Urut" << setw(15) << "Jml. Bayar" << setw(30) << endl;
    cout << "------------------------------------------------" << endl;
    for (Pembayaran pmt : payment)
    {
        if (pmt.id == current.id)
        {
            cout << setw(6) << index << setw(15) << put_money(pmt.jumlah) << setw(30);
            _total += pmt.jumlah;
            index++;
        }
    }
    cout << setw(6) << "TOTAL " << setw(12) << put_money(_total) << endl;
    cout << setw(6) << "SISA  " << setw(12) << put_money(current.beban_biaya - _total) << endl;
exit_sub:
    char k = _getch();
}
void UPDATE_PEMBAYARAN_PENERBITAN()
{
    PRINT_BANNER_PROGRAM();
    cout << "INPUT PEMBAYARAN PENERBIT" << endl;
    cout << "===========================================" << endl;

re_input:
    cout << "ID Penulis                      : ";
    string str_input;
    unsigned long long d;
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> d)
        {
            if (ss.eof())
            {
                bool exist = CEK_PENULIS_ADA(d);
                if (exist)
                {
                    break;
                }
                else
                {
                    cout << "Data penulis dengan ID '" << d << " tidak ditemukan, cari lagi? [Y/N] ..." << endl;
                    char key = _getch();
                    if (key == 'Y' || key == 'y')
                    {
                        goto re_input;
                    }
                    else
                    {
                    }
                }
            }
        }
        cout << "          ERROR: ID HARUS BERUPA ANGKA / KARAKTER [0..9]" << std::endl;
        goto re_input;
    }
    cout << "\nData Ditemukan" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "ID Penulis                 : " << current.id << endl;
    cout << "Nama                       : " << current.nama << endl;

    double total = READ_TOTALBAYAR_PENERBIT(current.id);
    double sisa = current.beban_biaya - total;

    cout << "Jumlah yang harus dibayar  : " << put_money(sisa) << endl;
re_input_biaya:
    cout << "Jumlah Pembayaran          : Rp.";
    double biaya;
    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> biaya)
        {
            if (ss.eof())
            {
                if (biaya > sisa || biaya == 0)
                {
                    cout << "          ERROR: Jumlah pembayaran tidak boleh nol / maksimal adalah Rp." << put_money(sisa) << endl;
                    goto re_input_biaya;
                }
                else
                {
                    Pembayaran baru;
                    baru.id = current.id;
                    baru.jumlah = biaya;
                    payment.push_back(baru);
                    cout << "--------------------------------------------" << endl;
                    cout << "SUCCESS: Pembayaran berhasil disimpan, tekan tombol apapun untuk kembali ke menu utama" << endl;
                    break;
                }
            }
        }
        cout << "          ERROR: Input harus berupa angka desimal [0..9]" << std::endl;
        goto re_input_biaya;
    }
    _getch();
}
void DELETE_PENULIS()
{
    PRINT_BANNER_PROGRAM();
    cout << "HAPUS DATA PENULIS" << endl;
re_input:
    cout << "Masukkan ID Penulis yang ingin dihapus\nID : ";

    int index = 0;
    string str_input;
    unsigned long long id;

    while (getline(cin, str_input))
    {
        stringstream ss(str_input);
        if (ss >> id)
        {
            if (ss.eof())
            {
                bool exist = CEK_PENULIS_ADA(id);
                if (exist)
                {
                    break;
                }
                else
                {
                    cout << "Data penulis dengan ID '" << id << " tidak ditemukan, cari lagi? [Y/N] ..." << endl;
                    char key = _getch();
                    if (key == 'Y' || key == 'y')
                    {
                        goto re_input;
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }
        cout << "          ERROR: ID YANG DIINPUT HARUS BERUPA ANGKA" << std::endl;
        goto re_input;
    }
    for (Penulis pns : list_pns)
    {
        if (pns.id == id)
        {
            list_pns.erase(list_pns.begin() + index);
            cout << "DATA PENULIS ID: " << put_money(id) << " berhasil dihapus\n";
            break;
        }
        index += 1;
    }
    cout << "Tekan tombol apapun untuk kembali ke menu utama ...";
    _getch();
}
void READ_DAFTAR_PENULIS()
{
mulai:
    PRINT_BANNER_PROGRAM();

    int counter = 1;
    cout << "\t\t\tLaporan Pembayaran Penerbitan Penulis" << endl;
    cout << "------------------------------------------------------------------------------------------\n";
    cout << setw(5) << "No." << setw(12) << "ID Penulis" << setw(20) << "Nama Penulis" << setw(20) << "Biaya Penerbit" << setw(15) << "Terbayar" << setw(15) << "Sisa" << endl;
    cout << "------------------------------------------------------------------------------------------\n";
    double t_biaya = 0;
    double t_bayar = 0;
    double t_sisa = 0;
    for (Penulis pns : list_pns)
    {
        double terbayar = READ_TOTALBAYAR_PENERBIT(pns.id);
        double sisa = pns.beban_biaya - terbayar;

        t_biaya += pns.beban_biaya;
        t_bayar += terbayar;
        t_sisa += sisa;
        cout << setw(5) << put_money(counter) << setw(12) << put_money(pns.id) << setw(20) << pns.nama << setw(20) << put_money(pns.beban_biaya) << setw(15) << put_money(terbayar) << setw(15) << put_money(sisa) << endl;
        counter++;
    }
    cout << "------------------------------------------------------------------------------------------\n";
    cout << setw(5) << "TOTAL" << setw(52) << put_money(t_biaya) << setw(15) << put_money(t_bayar) << setw(15) << put_money(t_sisa) << endl;
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "Urutkan " << endl;
    cout << " 1. Ascending Merge Sort By ID" << endl;
    cout << " 2. Descending Quick Sort By Biaya Penerbit" << endl;
    cout << " 3. Ascending Shell Sort By Biaya Penerbit" << endl;
    cout << " 4. Kembali" << endl;
    cout << "Masukkan pilihan : ";
    int pilihan;
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
        mergeSortAlgoritm(0, list_pns.size() - 1);
        goto mulai;
        break;
    case 2:
        quickSortAlgoritm(0, list_pns.size() - 1);
        goto mulai;
        break;
    case 3:
        shellSortAlgoritm(list_pns.size());
        goto mulai;
        break;
    case 4:
        break;
    }
}
int main()
{
begin_program:
    PRINT_BANNER_PROGRAM();
    PRINT_MENU_PROGRAM();
read_key:
    char key;
    key = _getch();
    switch (key)
    {
    case '1':
        CREATE_PENULIS();
        goto begin_program;
    case '2':
        READ_PENULIS();
        goto begin_program;
    case '3':
        UPDATE_PEMBAYARAN_PENERBITAN();
        goto begin_program;
    case '4':
        DELETE_PENULIS();
        goto begin_program;
    case '5':
        READ_DAFTAR_PENULIS();
        goto begin_program;
    case '6':
        READ_DAFTAR_PENULIS();
        goto begin_program;
    case '7':
        exit(0);
    default:
        goto read_key;
    }
}