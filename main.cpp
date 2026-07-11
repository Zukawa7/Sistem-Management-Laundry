#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstring>
#include <cstdlib>
using namespace std;

class Menu;
class SystemLaundry;

void cls(){ cout << "\033[2J\033[1;1H"; } //Untuk clear Screen
void key(){ cin.ignore();cin.get();}

class databaseSystem {
    public : 
        void struk(Menu& m);
        void loadData(Menu& m, SystemLaundry& s);
        void clientDb(Menu& m);
        void accountDb(SystemLaundry& s);
};

class SystemLaundry {
    friend class databaseSystem; 
    friend ostream& operator <<(ostream&,const SystemLaundry&);
    friend istream& operator >>(istream&, SystemLaundry&);
    
    public : 
        bool getLoggedIn() {
            return LoggedIn; 
        }    
        SystemLaundry(Menu& m);
        int userCount = 0;
        
    private :
        struct user {
            string UserName,UserPw;
        };
        string PIN;
        user userData[1000];
        void ProcessLogin();
        void AccLogin();
        void AccReg();
        bool LoggedIn = false;
};

class Menu{
    friend class databaseSystem;
    public :
        void Process(SystemLaundry& s);
        Menu();
        int clientCount = 0;
        
    private :
        void UnderConstruction();
        string randomId();
        void inputPelanggan();
        void updateStatus();
        void dataTransaksi();
        void logout(SystemLaundry& s);
        int Input;
        struct client {
            string nama, hp, id, tgl, paket, status;
            int berat,harga;
            long total; 
        };
        struct harga{
            int cuci_kering, setrika, ekspres, reguler; 
        };
        client clientData[1000];
        harga fees;
};
        
istream& operator>>(istream& input, SystemLaundry& Acc){
    Acc.ProcessLogin();
    return input;
}
ostream& operator<<(ostream& output,const SystemLaundry& Acc){
    return output;
}

//Funciont File Local Database
void databaseSystem::clientDb(Menu& m) {
    ofstream filestruk("client.dat");
    for (int i = 0; i < m.clientCount; i++) {
        filestruk << m.clientData[i].id << " " << m.clientData[i].nama << " " 
                  << m.clientData[i].berat << " " << m.clientData[i].paket << " " << m.clientData[i].total << " " 
                  << m.clientData[i].status << " " << m.clientData[i].tgl << " " 
                  << m.clientData[i].hp << " " << m.clientData[i].harga << endl;
    }
    filestruk.close();
}

void databaseSystem::accountDb(SystemLaundry& s) {
    ofstream userAcc("account.dat");
    for (int i = 0; i <= s.userCount; i++) {
        if(!s.userData[i].UserName.empty()) {
            userAcc << s.userData[i].UserName << " " << s.userData[i].UserPw << endl;
        }
    }
    userAcc.close();
}

void databaseSystem::loadData(Menu& m, SystemLaundry& s) {
    ifstream loadClient("client.dat");
    if (loadClient.is_open()) {
        m.clientCount = 0;
        while (m.clientCount < 1000 && loadClient >> m.clientData[m.clientCount].id >> m.clientData[m.clientCount].nama 
            >> m.clientData[m.clientCount].berat >> m.clientData[m.clientCount].paket >> m.clientData[m.clientCount].total 
            >> m.clientData[m.clientCount].status >> m.clientData[m.clientCount].tgl 
            >> m.clientData[m.clientCount].hp >> m.clientData[m.clientCount].harga) {
            m.clientCount++;
        }
        loadClient.close();
    }

    ifstream loadUser("account.dat");
    if (loadUser.is_open()) {
        s.userCount = 0;
        while (s.userCount < 1000 && loadUser >> s.userData[s.userCount].UserName >> s.userData[s.userCount].UserPw) {
            s.userCount++;
        }
        loadUser.close();
        if(s.userCount > 0) s.userCount--; 
    } 
}    

//Constructor for default system parameter
SystemLaundry::SystemLaundry(Menu& m){
    PIN = "12345";
    userData[0].UserName = "ucok";
    userData[0].UserPw = "123";
    
    databaseSystem db;
    db.loadData(m, *this);
}

Menu::Menu(){
    fees.cuci_kering = 5000; 
    fees.setrika = 4000;
    fees.ekspres = 10000;
    fees.reguler = 6000;
}

//Function Login & Menu
void Menu::Process(SystemLaundry& s){
    do{
        cls();
        cout << "+===== MENU PEGAWAI =====+" << endl;
        cout << "1. Input Data Pelanggan " << endl;
        cout << "2. Update Status / Hapus " << endl;
        cout << "3. Data Transaksi " << endl;
        cout << "4. Go to back" << endl;
        cout << "Masukkan Pilihan (1-4) : ";
        cin >> Input;
        cls();
        switch (Input) {
            case 1 :
                inputPelanggan();
                break;
            case 2 :
                updateStatus();
                break;
            case 3 :
                dataTransaksi();
                break;
            case 4 :
                logout(s);
                break;
            default :
                cout << "Hanya Masukkan Pilihan 1-4 !!!" << endl;
                key();
        }
    }while(Input != 4);
}

string Menu::randomId(){
    string id;
    bool verify;
    do{
        verify = false;
        int random = rand() % 9000 + 1000;
        id = to_string(random);
    
        for(int i = 0; i < clientCount; i++){
            if(clientData[i].id == id){
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

void Menu::inputPelanggan(){
    if (clientCount >= 1000) {
        cout << "Database Penuh....!" << endl;
        key();
        cls();
        return;
    }
    
    clientData[clientCount].status = "Proses";

    cout << "IDENTITAS PELANGGAN" << endl;
    cout << "NAMA : "; cin >> clientData[clientCount].nama;
    cout << "NO HP : "; cin >> clientData[clientCount].hp;
    cout << "Berat : "; cin >> clientData[clientCount].berat;
    clientData[clientCount].id = randomId();
    clientData[clientCount].tgl = getTanggal();
    int i;
    cout << "+===== PAKET =====+" << endl;
    cout << "1. Reguler " << endl;
    cout << "2. Ekspres " << endl;
    cout << "3. Cuci Kering " << endl;
    cout << "4. Setrika " << endl;
    cout << "Masukkan Pilihan (1-4) : ";
    cin >> i;
    cls();

    if (i == 1) {
        clientData[clientCount].harga = fees.reguler;
        clientData[clientCount].total = clientData[clientCount].berat * fees.reguler;
        clientData[clientCount].paket = "Reguler(3Days)";
    } else if (i == 2) {
        clientData[clientCount].harga = fees.ekspres;
        clientData[clientCount].total = clientData[clientCount].berat * fees.ekspres;
        clientData[clientCount].paket = "Ekspres(1Day)";
    } else if (i == 3) {
        clientData[clientCount].harga = fees.cuci_kering;
        clientData[clientCount].total = clientData[clientCount].berat * fees.cuci_kering;
        clientData[clientCount].paket = "CuciKering(2Days)";
    } else if (i == 4) {
        clientData[clientCount].harga = fees.setrika;
        clientData[clientCount].total = clientData[clientCount].berat * fees.setrika;
        clientData[clientCount].paket = "Setrika(2Days)";
    }
    databaseSystem db;
    db.struk(*this);
    clientCount++; 
}    

void Menu::updateStatus(){
    string id;
    int targetIndex = -1;
    
    cout << "Masukkan ID Transaksi : ";
    cin >> id;
    cls();

    for (int i = 0; i < clientCount; i++) {
        if (id == clientData[i].id) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        cout << "Maaf Data dengan ID '" << id << "' Tidak ditemukan" << endl;
        key();
        return;
    } else {
        cout << "Data dengan ID '" << clientData[targetIndex].id << "' : " << endl;
        cout << "Nama    : " << clientData[targetIndex].nama << endl;
        cout << "No HP   : " << clientData[targetIndex].hp << endl;
        cout << "Paket   : " << clientData[targetIndex].paket << endl;
        cout << "Status  : " << clientData[targetIndex].status << endl;
        cout << "Tanggal : " << clientData[targetIndex].tgl << endl;
        cout << "Berat   : " << clientData[targetIndex].berat << endl;
        cout << "Harga   : " << clientData[targetIndex].total << endl;
        cout << "===============================================" << endl;
    
        int input;
        cout << "1. Update Status Selesai " << endl;
        cout << "2. Hapus Client" << endl;
        cout << "3. Exit" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> input;

        if (input == 1) {
            clientData[targetIndex].status = "Selesai";
            cout << "Status berhasil diupdate menjadi Selesai." << endl;
            key();
        } 
        else if (input == 2) {
            char chose;
            cout << "Apakah Anda Ingin Menghapus Data ini? (Y/N) : ";
            cin >> chose;
            if (chose == 'y' || chose == 'Y') {
                for (int i = targetIndex; i < clientCount - 1; i++) {
                    clientData[i] = clientData[i + 1];
                }
                clientCount--; 
                cout << "Data Berhasil dihapus!!!" << endl;
                key();
            }
        }
    }
}

void Menu::dataTransaksi(){
     if (clientCount > 0) {
        for (int i = 0; i < clientCount; i++) {
            cout << "-------------------------" << endl;
            cout << "Pelanggan Ke-" << i + 1 << endl;
            cout << "Nama    : " << clientData[i].nama << endl;
            cout << "ID      : " << clientData[i].id << endl;
            cout << "Paket   : " << clientData[i].paket << endl;
            cout << "Tanggal : " << clientData[i].tgl << endl;
            cout << "Status  : " << clientData[i].status << endl;
            cout << "Berat   : " << clientData[i].berat << endl;
            cout << "Harga   : " << clientData[i].harga << endl;
            cout << "Total   : " << clientData[i].total << endl;
        }
     } else {
        cout << "Tidak Ada Data Transaksi Yang Bisa di Tampilkan !!!" << endl;
     }
     cout << "Tekan enter untuk melanjutkan....";
     key();
}

void Menu::logout(SystemLaundry& s){
    databaseSystem db;
    db.accountDb(s);
    db.clientDb(*this);
    cout << "Data Berhasil Disimpan ke Database!\n";
    key();
}
    
void databaseSystem::struk(Menu& m) {
    string dir = m.clientData[m.clientCount].nama + ".txt";
    ofstream filestruk(dir.c_str());
    filestruk << "========================================" << endl;
    filestruk << "          Sumber Makmur Bantul" << endl;
    filestruk << "========================================" << endl;
    filestruk << "No Nota : " << m.clientData[m.clientCount].id << endl;
    filestruk << "Nama : " << m.clientData[m.clientCount].nama << endl;
    filestruk << "Berat : " << m.clientData[m.clientCount].berat << endl;
    filestruk << "Paket : " << m.clientData[m.clientCount].paket << endl;
    filestruk << "Total : " << m.clientData[m.clientCount].total << endl;
    filestruk << "Status : " << m.clientData[m.clientCount].status << endl;
    filestruk << "Tanggal : " << m.clientData[m.clientCount].tgl << endl;
    filestruk << "========================================" << endl;
    filestruk.close();
}

void SystemLaundry::ProcessLogin(){
    char i;
    cout << "Apakah Anda Sudah Memiliki Akun? (Y/N) : ";
    cin >> i;
    cls();
    if(i == 'y' || i == 'Y'){
        AccLogin();
    } else if (i == 'n' || i == 'N'){
        AccReg();
        AccLogin();
    } else {
        cout << "Hanya Masukkan Input Y/N!\n";
        key();
        cls();
        ProcessLogin();
    }
}
    
void SystemLaundry::AccLogin(){
    string InName,InPw;
    do{
        cout << "+=======================+" << endl;
        cout << "|       LOGIN AKUN      |" << endl;
        cout << "+=======================+" << endl;
        cout << "Masukkan Username : ";
        cin >> InName;
        cout << "Masukkan Password : ";
        cin >> InPw;
        
        bool found = false;
        for(int i = 0; i <= userCount ; i++){
            if(InName == userData[i].UserName && InPw == userData[i].UserPw){
                cls();
                cout << "Login Berhasil! " << endl;
                LoggedIn = true;
                found = true;
                key();
                break;
            }         
        } 
        if(!found) {
            cls();
            cout << "Username/Password salah!!\nCoba lagi!!!\n";
            key();
            cls();
        }
    } while(!LoggedIn);
}
    
void SystemLaundry::AccReg(){
    string inputPIN;
    cout << "Silahkan Masukkan 5 Digit yang diberikan oleh manager : ";
    cin >> inputPIN;    
    if(inputPIN == PIN) {
        userCount++;
        cout << "+=======================+" << endl;
        cout << "|      REGISTER AKUN     |" << endl;
        cout << "+=======================+" << endl;
        cout << "Masukkan Username : ";
        cin >> userData[userCount].UserName;
        cout << "Masukkan Password : ";
        cin >> userData[userCount].UserPw;
        cls();
    } else {
        cout << "PIN Salah!\n";
        LoggedIn = false;
        key();
        cls();
    }
}
    
int main(){
    Menu M;
    SystemLaundry In(M); 
    cin >> In;
    if(In.getLoggedIn()){
        M.Process(In);
    }
    return 0;
}


