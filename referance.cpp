#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include<ctime>
#include <cstdlib> // For system()
#include <cstdio>  // For remove()

using namespace std;


void clientCache(int i);
void struk(int i);
void clientDb();
void cacheAcc(int i);

int count = 0; 
int acc = 0;   
struct harga{
	int cuci_kering, setrika, ekspres, reguler; 
};

struct client {
    string nama, hp, id, tgl, paket, status;
    int berat,harga;
    long total; 
};

struct user {
    string name, pass;
    bool type; // true if manager, false if coworker
    string pin ;
    
};

// Global Arrays
user data_usr[1000];
client data_client[1000];
harga hrg;
void header() {
    cout << "===== Sumber Makmur Bantul =====" << endl;
}

// --- Account Functions ---
void buat_akun() {
	system("cls");
	bool check = false;
	string pin;
	cout << "Silahkan Masukkan " << data_usr[0].pin.length() << " digit PIN yang diberikan oleh Manager untuk membuat akun : ";
	cin >> pin;
	if(pin == data_usr[0].pin){
    cout << "=== REGISTRASI AKUN ====" << endl;
    cout << "MASUKKAN USERNAME : ";
    cin >> data_usr[acc].name;
    cout << "MASUKKAN PASSWORD : ";
    cin >> data_usr[acc].pass;
    data_usr[acc].type = false; // Default to employee
    cacheAcc(acc);
    acc++;
    system("cls");
} else {
	cout << "PIN Salah, Coba lagi!" << endl;
	buat_akun();
}
}

bool login() {
    string x, y;
    bool n = true;
    do {
        cout << "======= LOGIN AKUN =======" << endl;
        cout << "MASUKKAN USERNAME : ";
        cin >> x;
        cout << "MASUKKAN PASSWORD : ";
        cin >> y;
        for (int i = 0; i < acc; i++) {
            if (x == data_usr[i].name && y == data_usr[i].pass) {
                n = false;
                return data_usr[i].type;
            }
        }
        if (n) {
            system("cls");
            cout << "Username atau Password Salah, Coba lagi!" << endl;
        }
    } while (n);
    system("cls");
    return 0;
}

// --- File Functions ---
void struk(int i) {
    string dir = "struk/" + data_client[i].nama + ".txt";
    ofstream filestruk(dir.c_str());
    filestruk << "========================================" << endl;
    filestruk << "          Sumber Makmur Bantul" << endl;
    filestruk << "========================================" << endl;
    filestruk << "No Nota : " << data_client[i].id << endl;
    filestruk << "Nama : " << data_client[i].nama << endl;
    filestruk << "Berat : " << data_client[i].berat << endl;
    filestruk << "Paket : " << data_client[i].paket << endl;
    filestruk << "Total : " << data_client[i].total << endl;
    filestruk << "Status : " << data_client[i].status << endl;
    filestruk << "Tanggal : " << data_client[i].tgl << endl;
    filestruk << "========================================" << endl;
    filestruk.close();
}

void clientCache(int i) {
    string dir = "cache/" + data_client[i].nama + ".dat";
    ofstream filestruk(dir.c_str());
    filestruk << data_client[i].id << " " << data_client[i].nama << " " 
              << data_client[i].berat << " " << data_client[i].paket << " " << data_client[i].total << " " 
              << data_client[i].status << " " << data_client[i].tgl << " " 
              << data_client[i].hp << " " << data_client[i].harga << endl;
    filestruk.close();
}

void clientDb() {
    ofstream filestruk("db/client.dat");
    for (int i = 0; i < count; i++) {
        filestruk << data_client[i].id << " " << data_client[i].nama << " " 
                  << data_client[i].berat << " " << data_client[i].paket << " " << data_client[i].total << " " 
                  << data_client[i].status << " " << data_client[i].tgl << " " 
                  << data_client[i].hp << " " << data_client[i].harga << endl;
    }
    filestruk.close();
}

void cacheAcc(int i) {
    string dir = "cache/acc" + to_string(i) + ".env";
    ofstream cache(dir.c_str());
    cache << data_usr[i].name << " " << data_usr[i].pass << " " << data_usr[i].type;
    cache.close();
}

void account() {
    ofstream userAcc("db/.env");
    userAcc << data_usr[0].pin << endl;
    for (int i = 0; i < acc; i++) {
        userAcc << data_usr[i].name << " " << data_usr[i].pass << " " << data_usr[i].type << endl;
    }
    userAcc.close();
}

void loadData() {
    count = 0;
    acc = 0;
    ifstream loadClient("db/client.dat");
    if (loadClient.is_open()) {
        while (count < 1000 && loadClient >> data_client[count].id >> data_client[count].nama 
               >> data_client[count].berat >> data_client[count].paket >> data_client[count].total 
               >> data_client[count].status >> data_client[count].tgl 
               >> data_client[count].hp >> data_client[count].harga) {
            clientCache(count); 
            count++;
        }
        loadClient.close();
    }

    ifstream loadUser("db/.env");
    if (loadUser.is_open()) {
    	loadUser >> data_usr[0].pin;
        while (acc < 1000 && loadUser >> data_usr[acc].name >> data_usr[acc].pass >> data_usr[acc].type) {
            cacheAcc(acc);
            acc++;
        }
        loadUser.close();
    } else{
    	data_usr[0].pin = "0101";
	}
	ifstream loadHarga("db/harga.dat");
	if(loadHarga.is_open()){
    while(loadHarga >> hrg.reguler >> hrg.ekspres >> hrg.cuci_kering >> hrg.setrika){
    	
	} 
	}else {
		hrg.reguler = 6000;
        hrg.ekspres = 10000;
        hrg.cuci_kering = 5000;
        hrg.setrika = 4000;
	}
	loadHarga.close();
    
}

// --- Main Employee Functions ---
string randomId(){
	string id;
	bool verify;
	
	do{
		verify = false;
		int random = rand() % 9000 + 1000;
		id = to_string(random);
		
		for(int i = 0; i < count; i++){
			if(data_client[i].id == id){
				verify = true;
			}
		}
	} while (verify);
	return id;
}

string getTanggal(){
	time_t now = time(0);
	tm*ltm = localtime(&now);
	char buffer[80];
	strftime(buffer, 80,"%d-%m-%Y",ltm);
	return string(buffer);
}

void identitas(int n) {
    if (n != 1) return;
    
    if (count >= 1000) {
        cout << "Database Penuh!" << endl;
        system("pause");
        return;
    }

    int j = count; 
    data_client[j].status = "Proses";

    cout << "IDENTITAS PELANGGAN" << endl;
    cout << "NAMA : "; cin >> data_client[j].nama;
    cout << "NO HP : "; cin >> data_client[j].hp;
    cout << "Berat : "; cin >> data_client[j].berat;
    data_client[j].id = randomId();
	data_client[j].tgl = getTanggal();
    int t;
    cout << "+===== PAKET =====+" << endl;
    cout << "1. Reguler " << endl;
    cout << "2. Ekspres " << endl;
    cout << "3. Cuci Kering " << endl;
    cout << "4. Setrika " << endl;
    cout << "Masukkan Pilihan (1-4) : ";
    cin >> t;
    system("cls");

    if (t == 1) {
    	data_client[j].harga = hrg.reguler;
        data_client[j].total = data_client[j].berat * hrg.reguler;
        data_client[j].paket = "Reguler(3Days)";
    } else if (t == 2) {
    	data_client[j].harga = hrg.ekspres;
        data_client[j].total = data_client[j].berat * hrg.ekspres;
        data_client[j].paket = "Ekspres(1Day)";
    } else if (t == 3) {
    	data_client[j].harga = hrg.cuci_kering;
        data_client[j].total = data_client[j].berat * hrg.setrika;
        data_client[j].paket = "CuciKering(2Days)";
    } else if (t == 4) {
    	data_client[j].harga = hrg.setrika;
        data_client[j].total = data_client[j].berat * hrg.setrika;
        data_client[j].paket = "Setrika(2Days)";
    }

    struk(j);
    clientCache(j);
    
    count++; 
}

void update(int n) {
    if (n != 2) return;

    header();
    string idt;
    int targetIndex = -1;
    
    cout << "Masukkan ID Transaksi : ";
    cin >> idt;
    system("cls");

    for (int j = 0; j < count; j++) {
        if (idt == data_client[j].id) {
            targetIndex = j;
        }
    }

    if (targetIndex == -1) {
        cout << "Maaf Data dengan ID '" << idt << "' Tidak ditemukan" << endl;
        system("pause");
        return;
    }

    		cout << "Data dengan ID '" << data_client[targetIndex].id << "' : " << endl;
			cout << "Nama	: " << data_client[targetIndex].nama << endl;
			cout << "No HP	: " << data_client[targetIndex].hp << endl;
			cout << "Paket	: " << data_client[targetIndex].paket << endl;
			cout << "Status	: " << data_client[targetIndex].status << endl;
			cout << "Tanggal : " << data_client[targetIndex].tgl << endl;
			cout << "Berat	: " << data_client[targetIndex].berat << endl;
			cout << "Harga	: " << data_client[targetIndex].total << endl;
			cout << "===============================================" << endl;
    
    int input;
    cout << "1. Update Status Selesai " << endl;
    cout << "2. Hapus Client" << endl;
    cout << "3. Exit" << endl;
    cout << "Masukkan Pilihan : ";
    cin >> input;

    if (input == 1) {
        data_client[targetIndex].status = "Selesai";
        cout << "Status berhasil diupdate menjadi Selesai." << endl;
    } 
    else if (input == 2) {
        char chose;
        cout << "Apakah Anda Ingin Menghapus Data ini? (Y/N) : ";
        cin >> chose;
        if (chose == 'y' || chose == 'Y') {
            
            string dir = "cache/" + data_client[targetIndex].nama + ".dat";
            remove(dir.c_str());

            for (int k = targetIndex; k < count - 1; k++) {
                data_client[k] = data_client[k + 1];
            }
            count--; 
            cout << "Data Berhasil dihapus!!!" << endl;
        }
    }
    system("pause");
}

void data_transaksi(int n) {
    if (n != 3) return;

    if (count > 0) {
        for (int j = 0; j < count; j++) {
            cout << "-------------------------" << endl;
            cout << "Pelanggan Ke-" << j + 1 << endl;
            cout << "Nama    : " << data_client[j].nama << endl;
            cout << "ID      : " << data_client[j].id << endl;
            cout << "Paket   : " << data_client[j].paket << endl;
            cout << "Status  : " << data_client[j].status << endl;
            cout << "Berat	: " << data_client[j].berat << endl;
            cout << "Harga   : " << data_client[j].harga << endl;
            cout << "Total	: " << data_client[j].total << endl;
        }
    } else {
        cout << "Tidak Ada Data Transaksi Yang Bisa di Tampilkan !!!" << endl;
    }
    system("pause");
}

//---Manager Menu---
void keuangan(){
	long  int grandTotal;
	string sgrand;
	ofstream filestruk("db/Laporan.txt",ios::out);
	filestruk<<"-----------------------------------------------------------------------------------------"<<endl;
	filestruk<<"| No   | tanggal    | id   | Nama       | paket             | berat | harga  | total    |"<<endl;

	for(int i=0; i<count; i++){
		string sberat = to_string(data_client[i].berat),sharga = to_string(data_client[i].harga),
		stotal = to_string(data_client[i].total);
		string sno = to_string(i+1);
		int nama = 11 - data_client[i].nama.length(),paket = 17-data_client[i].paket.length();
		filestruk<<"-----------------------------------------------------------------------------------------"<<endl;
		filestruk<<"| " << i+1;
		for (int i = 1;i<=5-sno.length();i++){
			filestruk <<" ";
		}
		filestruk << "| "<<data_client[i].tgl<<" | "<<data_client[i].id<<" | ";
		filestruk <<data_client[i].nama;
		for (int i = 1;i<=nama;i++){
			filestruk <<" ";
		}	
		filestruk <<"| "<<data_client[i].paket;
		for (int i = 1;i<=paket;i++){
			filestruk <<" ";
		}
		filestruk<<" | "<<data_client[i].berat << " Kg";
		for (int i = 1;i<=3-sberat.length();i++){
			filestruk <<" ";
		}
		filestruk<<"| "<<data_client[i].harga;
		for (int i = 1;i<=7-sharga.length();i++){
			filestruk <<" ";
		}
		filestruk<<"| "<<data_client[i].total;
		for (int i = 1;i<10-stotal.length();i++){
			filestruk <<" ";
		}
		filestruk<<"|"<<endl;
		grandTotal += data_client[i].total;
		sgrand = to_string(grandTotal);
		}
	
    	filestruk<<"-----------------------------------------------------------------------------------------"<<endl;
    	filestruk<<"|				TOTAL			    |       Rp."<<grandTotal;
		for (int i = 0;i<=16-sgrand.length();i++){
			filestruk <<" ";
		}
	filestruk<<"|"<<endl;
    filestruk<<"-----------------------------------------------------------------------------------------"<<endl;
    filestruk.close();
    ifstream file("db/Laporan.txt");
    string baris;
    while(getline(file,baris)){
    	cout << baris << endl;
	}
	file.clear();
	system("pause");
}

void manageHarga(){
	int t, h;
	do{
		header();
	cout << "Harga Yang Ingin Di Ubah : "<<endl;
	cout << "1. Reguler ("<< hrg.reguler <<")"<<endl;
	cout << "2. Ekspres ("<< hrg.ekspres <<")"<<endl;
	cout << "3. Cuci Kering ("<< hrg.cuci_kering <<")"<<endl;
	cout << "4. Setrika ("<< hrg.setrika <<")"<<endl;
	cout << "5. exit"<<endl;
	cout << "Masukkan Pilihan (1-5) : ";
	cin >> t;
	system("cls");
	if(t<5){
	cout << "Masukkan Harga : ";
	cin >> h;
	cout <<endl;
}
		if(t == 1){
			
		    hrg.reguler = h;
		   
		}else if (t == 2){
			
			hrg.ekspres = h;
			
		}else if (t == 3){
			
			hrg.cuci_kering = h;
			
		}else if (t == 4){
			
			
			hrg.setrika = h;
			
		}
	}while(t<5);
	ofstream file("db/harga.dat",ios::out);
	file << hrg.reguler << " " << hrg.ekspres << " " << hrg.cuci_kering << " " << hrg.setrika;
	file.close();
}
void save();
void settings(){
	
	int a;
	int input;
	string pin;
	cout << "Silahkan Masukkan " << data_usr[0].pin.length() << " digit PIN terlebih dahulu : ";
	cin >> pin;
	do{
		system("cls");
		header();
	if(pin == data_usr[0].pin){
	cout << "1. Tambah Akun" << endl << "2. Hapus Akun"  << endl << "3. Manage Admin" << endl << "4. Save & Exit" <<endl;
	cout << "Masukkan Pilihan (1-4) : ";
	cin >> a;
	
	if(a == 1){
            buat_akun();
        } else if (a == 2){
            cout << "Daftar Akun:" << endl;
            for(int i = 0; i < acc; i++){
                cout << i+1 << ". " << data_usr[i].name << endl;
            }
            cout << "Pilih Nomor untuk dihapus (0 to cancel): ";
            cin >> input;
            
            if(input > 0 && input <= acc){
                int targetIdx = input - 1;
                for (int k = targetIdx; k < acc - 1; k++) {
                    data_usr[k] = data_usr[k + 1];
                }
                acc--; 
                cout << "Akun Berhasil dihapus!" << endl;
                save(); 
                system("pause");
            }
        } else if(a == 3) {
            int l;
            bool h;
            for(int i = 0; i < acc; i++){
                cout << i+1 << ". " << data_usr[i].name << " [Status: " << data_usr[i].type << "]" << endl;
            }
            cout << "Pilih Nomor Akun: ";
            cin >> l;
            if(l > 0 && l <= acc){
                cout << "Set Status (1 for Manager, 0 for Pegawai): ";
                cin >> h;
                data_usr[l-1].type = h;
                cout << "Data Telah Di Ubah." << endl;
                save();
                system("pause");
            }
        }
    }
	} while(a < 4);
}


void save() {
    account();
    clientDb();
    system("del /Q cache\\*");
}

int main() {
    system("mkdir db 2> NUL");
    system("mkdir cache 2> NUL");
    system("mkdir struk 2> NUL");
    
    loadData(); 

    char input;
    bool loggedIn = false, admin;

    do {
        system("cls");
        header();
        cout << "Apakah Anda Sudah Memiliki Akun? (Y/N) : " ;
        cin >> input;
		system("cls");
        if (input == 'y' || input == 'Y') {
            admin = login();
            loggedIn = true;
        } else if (input == 'n' || input == 'N') {
            buat_akun();
            admin = login();
            loggedIn = true;
        } else {
            cout << "Input salah!" << endl;
        }
    } while (!loggedIn);

    int n;
    if( admin == false){
    do {
        system("cls");
        cout << "+===== MENU PEGAWAI =====+" << endl;
        cout << "1. Input Data Pelanggan " << endl;
        cout << "2. Update Status / Hapus " << endl;
        cout << "3. Data Transaksi " << endl;
        cout << "4. Go to back" << endl;
        cout << "Masukkan Pilihan (1-4) : ";
        cin >> n;
        system("cls");
        
        if (n == 1) identitas(n);
        else if (n == 2) update(n);
        else if (n == 3) data_transaksi(n);
        else if (n == 4) save();
        
    } while (n != 4);
} else {
	do {
        system("cls");
        cout << "+===== MENU MANAGER =====+" << endl;
        cout << "1. Laporan Keuangan " << endl;
        cout << "2. Manage Harga " << endl;
        cout << "3. Settings " << endl;
        cout << "4. Save & Exit" << endl;
        cout << "Masukkan Pilihan (1-4) : ";
        cin >> n;
        system("cls");
        
        if (n == 1){
    		keuangan();
		}
        else if (n == 2) manageHarga();
        else if (n == 3) settings();
        else if (n == 4) save();
        
    } while (n != 4);
}
    return 0;
}
