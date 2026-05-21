#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


//================================== Var Region
const int total_data = 100;

//================================== Struct Region
struct Transaksi{
    int id;
    int jenis;    // 1 untuk pemasukan, 2 untuk pengeluaran       
    string deskripsi;
    double nominal;
    int tanggal[3];     
};

//================================== Global Var Region
Transaksi data_catatan[total_data];

//================================== Function Region
void list_menu(){
    cout<<"1. Tampilkan Riwayat"<<endl;
    cout<<"2. Catat Transaksi Baru"<<endl;
    cout<<"3. Cari Transaksi"<<endl;
    cout<<"4. Laporan Keuangan"<<endl;
    cout<<"5. Edit Transaksi"<<endl;
    cout<<"6. Hapus Transaksi"<<endl;
    cout<<"7. Keluar"<<endl;
}

void sub_menu_1(){
    int sub_pilihan;
    char sorted;
    do{
        system("cls");
        cout<<"Sub Menu Tampilkan Riwayat"<<endl;
        cout<<"1. Tampilkan Semua Transaksi"<<endl;
        cout<<"2. Tampilkan Pemasukan"<<endl;
        cout<<"3. Tampilkan Pengeluaran"<<endl;
        cout<<"4. Kembali ke Menu Utama"<<endl;
        cout<<"Pilihan: ";
        cin>>sub_pilihan;
        if(sub_pilihan >= 1 && sub_pilihan <= 3){
            cout<<"Urutkan ? (y/n): ";
            cin>>sorted;
        }
        switch(sub_pilihan){
            case 1:
                system("cls");
                sorted == 'y' || sorted == 'Y' ? cout<<"(Terurut)..."<<endl : cout<<"(Tidak Terurut)..."<<endl;
                system("pause");
                break;
            case 2:
                system("cls");
                sorted == 'y' || sorted == 'Y' ? cout<<"(Terurut)..."<<endl : cout<<"(Tidak Terurut)..."<<endl;
                cout<<"Menampilkan Pemasukan..."<<endl;
                system("pause");
                break;
            case 3:
                system("cls");
                sorted == 'y' || sorted == 'Y' ? cout<<"(Terurut)..."<<endl : cout<<"(Tidak Terurut)..."<<endl;
                cout<<"Menampilkan Pengeluaran..."<<endl;
                system("pause");
                break;
            case 4:
                system("cls");
                cout<<"Kembali ke Menu Utama..."<<endl;
                break;
            default:
                system("cls");
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
                system("pause");
        }
    }while(sub_pilihan != 4);
}

void sub_menu_3(){
    int sub_pilihan;
    do{
        system("cls");
        cout<<"Sub Menu Cari Transaksi"<<endl;
        cout<<"1. Cari berdasarkan 1 Tahun"<<endl;
        cout<<"2. Cari berdasarkan 1 Bulan"<<endl;
        cout<<"3. Cari berdasarkan 1 Hari"<<endl;
        cout<<"4. Cari berdasarkan nominal"<<endl;
        cout<<"5. Kembali ke Menu Utama"<<endl;
        cout<<"Pilihan: ";
        cin>>sub_pilihan;
        switch(sub_pilihan){
            case 1:
                system("cls");
                cout<<"Mencari Transaksi berdasarkan 1 Tahun..."<<endl;
                system("pause");
                break;
            case 2:
                system("cls");
                cout<<"Mencari Transaksi berdasarkan 1 Bulan..."<<endl;
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"Mencari Transaksi berdasarkan 1 Hari..."<<endl;
                system("pause");
                break;
            case 4:
                system("cls");
                cout<<"Mencari Transaksi berdasarkan nominal..."<<endl;
                system("pause");
                break;
            case 5:
                system("cls");
                cout<<"Kembali ke Menu Utama..."<<endl;
                break;
            default:
                system("cls");
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
                system("pause");
        }
    }while(sub_pilihan != 5);
}

void sub_menu_4(){
    int sub_pilihan;
    do{
        system("cls");
        cout<<"Sub Menu Laporan Keuangan"<<endl;
        cout<<"1. Laporan Bulanan"<<endl;
        cout<<"2. Laporan Tahunan"<<endl;
        cout<<"3. Laporan All Time"<<endl;
        cout<<"4. Kembali ke Menu Utama"<<endl;
        cout<<"Pilihan: ";
        cin>>sub_pilihan;
        switch(sub_pilihan){
            case 1:
                system("cls");
                cout<<"Menampilkan Laporan Bulanan..."<<endl;
                system("pause");
                break;
            case 2:
                system("cls");
                cout<<"Menampilkan Laporan Tahunan..."<<endl;
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"Menampilkan Laporan All Time..."<<endl;
                system("pause");
                break;
            case 4:
                system("cls");
                cout<<"Kembali ke Menu Utama..."<<endl;
                break;
            default:
                system("cls");
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
                system("pause");
        }
    }while(sub_pilihan != 4);
}

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
//================================== main Region
int main() {
    int pilihan;
    do{
        system("cls");
        cout<<"========== Program Catatan Keuangan =========="<<endl;
        list_menu();
        cout<<"--------------------"<<endl;
        cout<<"Pilihan: ";
        cin>>pilihan;
        switch(pilihan){
            case 1:
                system("cls");
                sub_menu_1();
                system("pause");
                break;
            case 2:
                system("cls");
                catat_transaksi_baru();
                system("pause");
                break;
            case 3:
                system("cls");
                sub_menu_3();
                system("pause");
                break;
            case 4:
                system("cls");
                sub_menu_4();
                system("pause");
                break;
            case 5:
                system("cls");
                cout<<"Mengedit Transaksi..."<<endl;
                edit_transaksi();
                system("pause");
                break;
            case 6:
                system("cls");
                cout<<"Menghapus Transaksi..."<<endl;
                system("pause");
                break;
            case 7:
                system("cls");
                cout<<"Keluar dari Program. Terima kasih!"<<endl;
                break;
            default:
                system("cls");
                cout<<"Pilihan tidak valid. Silakan coba lagi."<<endl;
                system("pause");
        }
    }while(pilihan != 7);

    return 0;
}