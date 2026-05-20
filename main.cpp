#include <iostream>
#include <cctype>
using namespace std;


//================================== Const Var Region
const int total_data = 100;

//================================== Struct Region
struct Transaksi{
    int id;
    int jenis;           
    string deskripsi;
    double nominal;
    int tanggal[3];     
};

struct ViewData{
    const int space[7] = {3, 12, 15, 6, 2, 2, 4};
    const string metadata[7] = {
        "id", "jenis", "deskripsi", "nominal", 
        "tanggal", "bulan", "tahun"
    };
    Transaksi records[total_data];
};

//================================== Global Var Region
Transaksi data_catatan[total_data];
ViewData view_data;

string last_page;

//================================== View Utils Region
string _request_choice_view(){
    string pilihan;
    cout << "--------------------" << endl; 
    cout << "Pilihan: ";
    cin >> pilihan;
}

string _request_data_view(){
    string data;
    cout << "--------------------" << endl; 
    cout << "Input : ";
    cin >> data;
}

void _view_data_to_table(){
    //gunakan struct view data untuk diconvert output bentuk tabel
    //space untuk jarak antar column
}

//================================== Model Region
bool isdigit_validation(const string &str){
    if (str.empty()) return false;

    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
}

bool validation_menu(const string &str, int n, int m) {
    if (!isdigit_validation(str)){return false;}

    int data = stoi(str);
    if (n < data and m > data){
        return true;
    }
    
    return false;
}

bool new_record_validation(string data[]){
    for (int i=2; i<6; i++){
        if (!isdigit_validation(data[i])){
            return false;
        }
    }

    int tanggal = stoi(data[3]);
    int bulan = stoi(data[4]);
    int tahun = stoi(data[5]);
    
    if (tanggal <= 0 and tanggal > 31){return false;}
    if (bulan <= 0 and bulan > 12){return false;}
    if (tahun < 2020){return false;}

    return true;
}

void search_record(const string &str){
    int taget;
    //if (str == "1"){taget = }
}

void sort_record(const string &str){
    //pilih sort
}

//================================== View Region
string home_view(){
    cout << "\n=== PROGRAM MANAGEMENT KEUANGAN ===\n";
    cout << "1. Tampilkan Riwayat\n";
    cout << "2. Catat Transaksi Baru\n";
    cout << "3. Cari Transaksi\n";
    cout << "4. Laporan Keuangan\n";
    cout << "5. Edit Transaksi\n";
    cout << "6. Hapus Transaksi\n";
    cout << "7. Keluar\n";

    return _request_choice_view();
}

string riwayat_menu_view(){
    cout << "1. Semua Transaksi" << endl
         << "2. Pemasukan" << endl 
         << "3. Pengeluaran" << endl;

    return _request_choice_view();
}

string laporan_menu_view(){
    cout << "1. Tahun" << endl
         << "2. Bulan" << endl
         << "3. Semua" << endl;

    return _request_choice_view();
}

string laporan_request_view(string option){
    string tahun, bulan, list[2];
    if (option != "3"){
        cout << "Masukkan Tahun : ";
        cin >> tahun;
        if (option == "1"){
            list[0] = tahun;
            return "";
        }
        cout << "Masukkan Bulan : ";
        cin >> bulan;
        if (option == "2"){
            list[0] = tahun;
            list[1] = bulan;
            return "";
        }
    }
}

string sort_menu_view(){
    cout << "1. Ascending" << endl
         << "2. Descending" << endl
         << "3. Asli" << endl;

    return _request_choice_view();
}

string search_menu_view(){
    cout << "1. Tahun" << endl
         << "2. Bulan" << endl
         << "3. Hari" << endl
         << "4. Nominal" << endl;

    return _request_choice_view(); 
}

string add_record_view(string container[]){
    string jenis, deskripsi, nominal, tanggal[3];

    cout << "Id : " << "kosong" << endl;

    cout << "Jenis (1: Pemasukan, 2: Pengeluaran): ";
    cin >> container[0];

    cout << "Deskripsi : ";
    cin >> container[1];

    cout << "Nominal : ";
    cin >> container[2];

    cout << "Tanggal : ";
    cin >> container[3];

    cout << "Bulan : ";
    cin >> container[4];

    cout << "Tahun : ";
    cin >> container[5];
}

string edit_record_view(){
    string id;
    cout << "Masukkan ID yang akan dihapus: "; 
    cin >> id;

    return id;
}

string delete_record_view(){
    string id;
    cout << "Masukkan ID yang akan dihapus: "; 
    cin >> id;

    return id;
}

string error_view(){
    cout << "--------------------" << endl; 
    cout << "Masukkan Input Dengan Benar !!!";
    cout << "--------------------" << endl;

    return last_page;
}

void show_transaksi_view(){

}


//================================== Gateway Region
void add_record(){

}

void delete_record(){

}

void update_record(){

}

//================================== Mapper Region

//Opsional

//================================== Controller Region
string home_page_handler(){
    string request;
    string menu[] = {
        "ERROR", "RIWAYAT", "CATAT", "CARI",  
        "LAPORAN", "EDIT", "HAPUS", "KELUAR"
    };

    request = home_view();
    if (validation_menu(request, 1, 7)){
        return menu[stoi(request)];
    }else{
        last_page = "HOME";
        return menu[0];
    }
}

string riwayat_page_handler(){
    string request;
    string menu[] = {
        "ERROR", "SEMUA_CATATAN", 
        "PENGELUARAN", "PEMASUKAN"
    };
    
    request = riwayat_menu_view();
    if (validation_menu(request, 1, 3)){
        return menu[stoi(request)];
    }else{
        last_page = "RIWAYAT";
        return menu[0];
    }
}

string laporan_page_handler(){
    string request1, request2;
    request1 = laporan_menu_view();

    if (validation_menu(request1, 1, 3)){
        //lanjutan
    }else{
        last_page = "LAPORAN";
        return "ERROR";
    }
}

string catat_page_handler(){
    string request[6];
    add_record_view(request);

    if (new_record_validation(request)){
        add_record();
    } else {
        last_page = "CATAT";
        return "ERROR"; 
    }
}

string search_page_handler(){
    string request1, request2;
    request1 = search_menu_view();

    if (validation_menu(request1, 1, 4)){
        request2 = _request_data_view();
        //validator

    } else {
        last_page = "SEARCH";
        return "ERROR";
    }
}

string sort_page_handler(){
    string request;
    request = search_menu_view();
    if (validation_menu(request, 1, 3)){
        //eksekusi sort
    } else {
        last_page = "SORT";
        return "ERROR";
    }
}

//================================== main Region
int main() {
    string halaman = "HOME";

    while (halaman != "KELUAR"){

        if (halaman == "HOME"){
            halaman = home_page_handler();
        }

        else if (halaman == "RIWAYAT"){
            halaman = riwayat_page_handler();
        }

        else if (halaman == "LAPORAN"){
            halaman = riwayat_page_handler();
        }

        else if (halaman == "CATAT"){
            halaman = catat_page_handler();
        }

        else if (halaman == "ERROR"){
            halaman = error_view();
        }
    }

    return 0;
}