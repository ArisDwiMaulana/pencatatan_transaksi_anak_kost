#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//================================== Config Region
const int total_data = 100;
const int total_column = 5;
const string metadata[total_column] = {
    "id", "jenis", "deskripsi", "nominal", "tanggal"
};
const int space_data[total_column] = {3, 12, 30, 10, 14};

const string month[] = {
    "Januari", "Februari", "Maret", "April", 
    "Mei", "Juni", "Juli", "Agustus",
    "September", "Oktober", "November", "Desember"
};

//================================== Struct Region
struct Transaksi{
    int id;
    int jenis;    // 1 untuk pemasukan, 2 untuk pengeluaran       
    string deskripsi;
    int nominal;
    int tanggal[3];     
};

//================================== Utils Region
int check_menu(string pilihan){
    if (pilihan.empty() || pilihan.length() > 1){
        return -1;
    }

    if (isdigit(pilihan[0])){
        return stoi(pilihan);
    }

    return -1;
}

string to_date_view(Transaksi data){
    string date_str = "";
    
    date_str += to_string(data.tanggal[2]) + " ";   
    date_str += month[data.tanggal[1]] + " ";       
    date_str += to_string(data.tanggal[0]);
    
    return date_str;
}

string _generate_separator(){
    string result = "+";
    for (int val : space_data) {
        result += string(val + 2, '-') + "+";
    }
    return result;
}

string _center(const string& str, int width) {
    if (str.length() >= width) return str;
    int padding = width - str.length();
    int left_pad = padding / 2;
    int right_pad = padding - left_pad;
    return string(left_pad, ' ') + str + string(right_pad, ' ');
}

string _left(const string& str, int width) {
    if (str.length() >= width) return str;
    return str + string(width - str.length(), ' ');
}

void to_table(Transaksi data[], int &total){
    string sep = _generate_separator();

    cout << sep << endl;

    cout << "|";
    for (int i = 0; i < total_column; i++) {
        cout << " " << _center(metadata[i], space_data[i]) << " |";
    }
    cout << endl;

    cout << sep << endl;

    for (int i = 0; i < total; i++) {
        cout << "|";
        for (int j = 0; j < total_column; j++) {
            string val = "";
        
            switch (j) {
                case 0: val = to_string(data[i].id); break;
                case 1: val = (data[i].jenis == 1) ? "Pemasukan" : "Pengeluaran"; break;
                case 2: val = data[i].deskripsi; break;
                case 3: val = to_string(data[i].nominal); break;
                case 4: val = to_date_view(data[i]); break;
            }
            
            cout << " " << _left(val, space_data[j]) << " |";
        }
        cout << endl;
    }

    cout << sep << endl;
}

//================================== File Region
void id_terakhir(int *id_terakhir){
    ifstream file("src/data.csv");
    if(file.fail()){
        cout<<"Gagal membuka file!"<<endl;
        return;
    }
    string baris, barisTerakhir;
    *id_terakhir = 0;
    while (getline(file, baris)) {
        if (!baris.empty()) {
            barisTerakhir = baris; // Selalu perbarui dengan baris terbaru
        }
    }
    file.close();
    *id_terakhir = stoi(barisTerakhir.substr(0, barisTerakhir.find(",")));
}

void catat_transaksi_baru(){
    int total_transaksi = 0;
    id_terakhir(&total_transaksi);
    if(total_transaksi == 100){
        cout<<"Jumlah transaksi sudah mencapai batas maksimum (100)."<<endl;
        return;
    }else{
        ofstream file("src/data.csv", ios::app);
        if(file.fail()){
            cout<<"Gagal membuka file!"<<endl;
            return;
        }
        Transaksi temp;
        temp.id = total_transaksi + 1;
        cout<<"Masukkan Jenis Transaksi (1 untuk Pemasukan, 2 untuk Pengeluaran): ";
        cin>>temp.jenis;
        cin.ignore();
        cout<<"Masukkan Deskripsi: ";
        getline(cin, temp.deskripsi);
        cout<<"Masukkan Nominal: ";
        cin>>temp.nominal;
        for(int i=0; i<3; i++){
            if(i == 0){
                cout<<"Masukkan Tahun (YYYY): ";
                cin>>temp.tanggal[i];
            }
            else if(i == 1){
                cout<<"Masukkan Bulan (MM): ";
                cin>>temp.tanggal[i];
            }
            else{
                cout<<"Masukkan Tanggal (DD): ";
                cin>>temp.tanggal[i];
            }
        }
        file<<temp.id<<","<<temp.jenis<<","<<temp.deskripsi<<","<<temp.nominal<<","<<temp.tanggal[0]<<","<<temp.tanggal[1]<<","<<temp.tanggal[2]<<endl;
        file.close();
    }
    
}

void load_data(Transaksi temp[], int *data_terisi){
    ifstream file("src/data.csv");
    if(file.fail()){
        cout<<"Gagal membuka file!"<<endl;
        return;
    }
    string baris;
    int index = 0;
    while (getline(file, baris) && index < total_data) {
        if (!baris.empty()) {
            stringstream ss(baris);
            string id_str, jenis_str, deskripsi_str, nominal_str, tahun_str, bulan_str, tanggal_str;
            getline(ss, id_str, ',');
            getline(ss, jenis_str, ',');
            getline(ss, deskripsi_str, ',');
            getline(ss, nominal_str, ',');
            getline(ss, tahun_str, ',');
            getline(ss, bulan_str, ',');
            getline(ss, tanggal_str);
            
            temp[index].id = stoi(id_str);
            temp[index].jenis = stoi(jenis_str);
            temp[index].deskripsi = deskripsi_str;
            temp[index].nominal = stod(nominal_str);
            temp[index].tanggal[0] = stoi(tahun_str);
            temp[index].tanggal[1] = stoi(bulan_str);
            temp[index].tanggal[2] = stoi(tanggal_str);
            
            index++;
        }
    }
    *data_terisi = index;
    file.close();
}

bool cari_id_transaksi(int id_transaksi){
    ifstream file("src/data.csv");
    if(file.fail()){
        cout<<"Gagal membuka file!"<<endl;
        return false;
    }
    string baris;
    while (getline(file, baris)) {
        if (!baris.empty()) {
            stringstream ss(baris);
            string id_str;
            getline(ss, id_str, ',');
            int id = stoi(id_str);
            if (id == id_transaksi) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}   

void edit_transaksi(){
    int id_transaksi;
    cout<<"Masukkan ID Transaksi yang ingin diedit: ";
    cin>>id_transaksi;
    bool found = cari_id_transaksi(id_transaksi); 
    if (!found) {
        cout<<"Transaksi tidak ditemukan atau tidak bisa membuka file!"<<endl;
    }else{
        Transaksi temp[100];
        int data_terisi;
        load_data(temp, &data_terisi);
        ofstream file("src/data.csv");
        if(file.fail()){
            cout<<"Gagal membuka file!"<<endl;
            return;
        }
        for(int i=0; i<data_terisi; i++){
            if(temp[i].id == id_transaksi){
                cout<<"Transaksi ditemukan. Silakan masukkan data baru."<<endl;
                cout<<"Masukkan Jenis Transaksi (1 untuk Pemasukan, 2 untuk Pengeluaran): ";
                cin>>temp[i].jenis;
                cin.ignore();
                cout<<"Masukkan Deskripsi: ";
                getline(cin, temp[i].deskripsi);
                cout<<"Masukkan Nominal: ";
                cin>>temp[i].nominal;
                for(int j=0; j<3; j++){
                    if(j == 0){
                        cout<<"Masukkan Tahun (YYYY): ";
                        cin>>temp[i].tanggal[j];
                    }
                    else if(j == 1){
                        cout<<"Masukkan Bulan (MM): ";
                        cin>>temp[i].tanggal[j];
                    }
                    else{
                        cout<<"Masukkan Tanggal (DD): ";
                        cin>>temp[i].tanggal[j];
                    }
                }
            }
            file<<temp[i].id<<","<<temp[i].jenis<<","<<temp[i].deskripsi<<","<<temp[i].nominal<<","<<temp[i].tanggal[0]<<","<<temp[i].tanggal[1]<<","<<temp[i].tanggal[2]<<endl;
        }
        file.close();
    }
}

void hapus_transaksi(){
    int id_transaksi;
    cout<<"Masukkan ID Transaksi yang ingin dihapus: ";
    cin>>id_transaksi;
    bool found = cari_id_transaksi(id_transaksi);
    if (!found) {
        cout<<"Transaksi tidak ditemukan atau tidak bisa membuka file!"<<endl;
    } else {
        Transaksi temp[100];
        int data_terisi;
        load_data(temp, &data_terisi);
        ofstream file("src/data.csv");
        if(file.fail()){
            cout<<"Gagal membuka file!"<<endl;
            return;
        }
        int jumlah_dihapus = 0;
        for(int i=0; i<data_terisi; i++){
            if(temp[i].id != id_transaksi){
                file<<temp[i].id - jumlah_dihapus<<","<<temp[i].jenis<<","<<temp[i].deskripsi<<","<<temp[i].nominal<<","<<temp[i].tanggal[0]<<","<<temp[i].tanggal[1]<<","<<temp[i].tanggal[2]<<endl;
            }else{
                jumlah_dihapus++;
            }
        }
        file.close();
    }
}

//================================== Sub Menu 1 Region
int list_sub_menu_1(){
    string pilihan;

    cout <<"Sub Menu Tampilkan Riwayat"<<endl
         <<"1. Tampilkan Semua Transaksi"<<endl
         <<"2. Tampilkan Pemasukan"<<endl
         <<"3. Tampilkan Pengeluaran"<<endl
         <<"4. Kembali ke Menu Utama"<<endl
         <<"-------------------" << endl;

    cout<<"Pilihan: ";
    getline(cin, pilihan);

    return check_menu(pilihan);
}

bool is_sorted(){
    string urutkan;
    cout<<"Urutkan ? (y/n): ";
    getline(cin, urutkan);

    if (urutkan == "y" || urutkan == "Y"){
        return true;
    }

    return false;
}

void sort_record(Transaksi data[], int size){
    int minIndex = -1;

    for (int i = 0; i < size; i++){
        minIndex = i;
        for (int j = i + 1; j < size; j++){
            if (data[minIndex].tanggal > data[j].tanggal){
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Transaksi temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
        }
    }
}

void filter_pilihan(const int pilihan, bool sorted){
    int total_temp = 0;

    Transaksi temp[total_data]; 
    load_data(temp, &total_temp);

    if (pilihan == 0 && !sorted) {
        to_table(temp, total_temp);
        return;
    }

    int total_result = 0;
    Transaksi result[total_data];

    for (int i = 0; i < total_temp; i++) {
        if (pilihan == 0 || temp[i].jenis == pilihan) {
            result[total_result] = temp[i];
            total_result++;
        }
    }

    if (sorted) {
        sort_record(result, total_result);
    }
    
    to_table(result, total_result);
}

void sub_menu_1(){
    int pilihan;
    bool sorted;
    do{
        system("cls");
        
        pilihan = list_sub_menu_1();

        if (pilihan >= 1 && pilihan <= 3){
            sorted = is_sorted();
            if (sorted){cout<<"(Terurut)..."<<endl;}
            else{cout<<"(Tidak Terurut)..."<<endl;}
        }

        system("cls");
        switch(pilihan){
            case 1:
                filter_pilihan(0, sorted);
                break;
            case 2:
                cout<<"Menampilkan Pemasukan..."<<endl;
                filter_pilihan(1, sorted);
                break;
            case 3:
                cout<<"Menampilkan Pengeluaran..."<<endl;
                filter_pilihan(2, sorted);
                break;
            case 4:
                cout<<"Kembali ke Menu Utama..."<<endl;
                return;
            default:
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
        }
        system("pause");
    }while(pilihan != 4);
}

//================================== Sub Menu 3 Region
int input_search(string massage){
    string request;

    cout << "---------------" << endl;
    cout << "Masukkan " << massage << " : ";
    getline(cin, request);

    if (isdigit(request[0])){
        return stoi(request);
    }
    return -1;
}

int list_sub_menu_3(){
    string pilihan;

    cout<<"Sub Menu Cari Transaksi"<<endl
        <<"1. Cari berdasarkan 1 Tahun"<<endl
        <<"2. Cari berdasarkan 1 Bulan"<<endl
        <<"3. Cari berdasarkan 1 Hari"<<endl
        <<"4. Cari berdasarkan nominal"<<endl
        <<"5. Kembali ke Menu Utama"<<endl
        <<"-------------------" << endl;

    cout<<"Pilihan: ";
    getline(cin, pilihan);

    return check_menu(pilihan);
}

void filter_search(int &h, int &b, int &t, int &n){
    int total_temp = 0;
    Transaksi temp[total_data];
    load_data(temp, &total_temp);

    int total_result = 0;
    Transaksi result[total_data];

    for (int i=0; i < total_temp; i++){
        bool filter = true;

        if (t != -1 && temp[i].tanggal[0] != t){
            filter = false;
        }

        if (b != -1 && temp[i].tanggal[1] != b){
            filter = false;
        }

        if (h != -1 && temp[i].tanggal[2] != h){
            filter = false;
        }

        if (n != -1 && temp[i].nominal != n){
            filter = false;
        }

        if (filter){
            result[total_result] = temp[i];
            total_result += 1;
        }
    }

    to_table(result, total_result);
}

void sub_menu_3(){
    int pilihan;

    do{
        system("cls");
        pilihan = list_sub_menu_3();

        int hari = -1, bulan = -1, tahun = -1, nominal = -1;
        bool proses_filter = false;

        system("cls");
        switch(pilihan){
            case 1: {
                cout << "Mencari Transaksi berdasarkan Tahun..." << endl;
                tahun = input_search("tahun");
                proses_filter = true;
                break;
            }
            case 2: {
                cout << "Mencari Transaksi berdasarkan Bulan..." << endl;
                bulan = input_search("bulan");
                tahun = input_search("tahun");
                proses_filter = true;
                break;
            }
            case 3: {
                cout << "Mencari Transaksi berdasarkan Hari..." << endl;
                hari = input_search("hari");
                bulan = input_search("bulan");
                tahun = input_search("tahun");
                proses_filter = true;
                break;
            }
            case 4: {
                cout << "Mencari Transaksi berdasarkan nominal..." << endl;
                nominal = input_search("nominal");
                proses_filter = true;
                break;
            }
            case 5:
                cout << "Kembali ke Menu Utama..." << endl;
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (proses_filter) {
            filter_search(hari, bulan, tahun, nominal); 
        }
        system("pause");
    } while(pilihan != 5);
}

//================================== Sub Menu 4 Region
void tampilkan_laporan(int pemasukan, int pengeluaran, int sisa){
    cout << "============================" << endl
         << "Pemasukan   : " << pemasukan << endl
         << "Pengeluaran : " << pengeluaran << endl
         << "Sisa Saldo  : " << sisa << endl
         << "============================" << endl;
}

void filter_laporan(int pilihan, int b, int t){
    int total_temp = 0, pemasukan = 0, pengeluaran = 0;
    Transaksi temp[total_data]; 
    load_data(temp, &total_temp);

    for (int i = 0; i < total_temp; i++) {
        if (pilihan != 3) {
            if (t != -1 && temp[i].tanggal[0] != t) continue;
            if (b != -1 && temp[i].tanggal[1] != b) continue;
        }

        if (temp[i].jenis == 1) {
            pemasukan += temp[i].nominal;
        } else {
            pengeluaran += temp[i].nominal;
        }
    }

    tampilkan_laporan(pemasukan, pengeluaran, pemasukan - pengeluaran);
}

int list_sub_menu_4(){
    string pilihan;

    cout<<"Sub Menu Laporan Keuangan"<<endl
        <<"1. Laporan Bulanan"<<endl
        <<"2. Laporan Tahunan"<<endl
        <<"3. Laporan All Time"<<endl
        <<"4. Kembali ke Menu Utama"<<endl
        <<"-------------------" << endl;

    cout<<"Pilihan: ";
    getline(cin, pilihan);

    return check_menu(pilihan);
}

void sub_menu_4(){
    int pilihan;
    do{
        system("cls");
        pilihan = list_sub_menu_4();

        int bulan = -1, tahun = -1;
        bool proses_filter = false;

        system("cls");
        switch(pilihan){
            case 1:
                cout<<"Menampilkan Laporan Bulanan..."<<endl;
                bulan = input_search("bulan");
                tahun = input_search("tahun");
                proses_filter = true;
                break;
            case 2:
                cout<<"Menampilkan Laporan Tahunan..."<<endl;
                tahun = input_search("tahun");
                proses_filter = true;
                break;
            case 3:
                cout<<"Menampilkan Laporan All Time..."<<endl;
                proses_filter = true;
                break;
            case 4:
                cout<<"Kembali ke Menu Utama..."<<endl;
                return;
            default:
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
        }
        if (proses_filter) {
            filter_laporan(pilihan, bulan, tahun); 
        }
        system("pause");
    } while(pilihan != 4);
}

//================================== main Region
int list_menu(){
    string pilihan;

    cout<<"========== Program Catatan Keuangan =========="<<endl
        <<"1. Tampilkan Riwayat"<<endl
        <<"2. Catat Transaksi Baru"<<endl
        <<"3. Cari Transaksi"<<endl
        <<"4. Laporan Keuangan"<<endl
        <<"5. Edit Transaksi"<<endl
        <<"6. Hapus Transaksi"<<endl
        <<"7. Keluar"<<endl
        <<"-------------------" << endl;

    cout<<"Pilihan: ";
    getline(cin, pilihan);

    return check_menu(pilihan);
}

int main() {
    int pilihan;
    do{
        system("cls");

        pilihan = list_menu();
        
        switch(pilihan){
            case 1:
                sub_menu_1();
                break;
            case 2:
                catat_transaksi_baru();
                break;
            case 3:
                sub_menu_3();
                break;
            case 4:
                sub_menu_4();
                break;
            case 5:
                cout<<"Mengedit Transaksi..."<<endl;
                edit_transaksi();
                break;
            case 6:
                cout<<"Menghapus Transaksi..."<<endl;
                hapus_transaksi();
                break;
            case 7:
                cout<<"Keluar dari Program. Terima kasih!"<<endl;
                break;
            default:
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
        }
        system("pause");
    }while(pilihan != 7);

    return 0;
}