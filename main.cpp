	#include<iostream>
	#include<fstream>
	#include<string>
	using namespace std;
	
	void cls(){ cout << "\033[2J\033[1;1H"; } //Untuk clear Screen
	void key(){ cin.ignore();cin.get();}
	class SystemLaundry {
		friend ostream& operator <<(ostream&,const SystemLaundry&);
	    friend istream& operator >>(istream&, SystemLaundry&);
	    
	    public : 
	    	bool getLoggedIn() {
            return LoggedIn; 
        }	
        	SystemLaundry();
        
        
	    private :
			int userCount = 0;
			struct user {
				string UserName,UserPw;
				bool typeAccount;
			};
			string PIN;
			user userData[1000];
	    	void ProcessLogin();
	    	void AccLogin();
	    	void AccReg();
			void logout();
	    	bool LoggedIn = false;
	};

	class Menu{
		friend class databaseSystem;
		public :
			void Process();
			Menu();
			
		private :
			int clientCount = 0;
			void UnderConstruction();
			void inputPelanggan();
			void updateStatus();
			void dataTransaksi();
			void logout();
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
	
	class databaseSystem{
		friend class Menu;
		friend class SystemLaundry;
		public : 
		void struk(Menu& m);
		
		
		private :
		
				
			
	};
	//Constructor for default system parameter
	SystemLaundry::SystemLaundry(){
			PIN = "12345";
        	userData[userCount].UserName = "ucok";
        	userData[userCount].UserPw = "123";
        	userData[userCount].typeAccount = true;
	}
	
	Menu::Menu(){
		int cuci_kering = 5000, setrika = 4000, ekspres = 10000, reguler = 6000;
	}
	
	
	//Function
	void Menu::Process(){
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
					cls();
					UnderConstruction();
					inputPelanggan();
					break;
				case 2 :
					cls();
					UnderConstruction();
					updateStatus();
					break;
				case 3 :
					cls();
					UnderConstruction();
					dataTransaksi();
					break;
				case 4 :
					cls();
					UnderConstruction();
					logout();
					break;
				default :
					cls();
					cout << "Hanya Masukkan Pilihan 1-4 !!!" << endl;
			}
		}while(Input != 4);
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
    	//clientData[clientCount].id = getRandomId();
		//clientData[clientCount].tgl = getTanggal();
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
	
	}


	void Menu::dataTransaksi(){
	
	}

	void Menu::logout(){
	
	}
	
	void databaseSystem::struk(Menu& m) {
    	string dir = "struk/" + m.clientData[m.clientCount].nama + ".txt";
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
		} else if (!i){
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
	    	cout << "|      LOGIN AKUN       |" << endl;
	    	cout << "+=======================+" << endl;
			cout << "Masukkan Username : ";
			cin >> InName;
			cout << "Masukkan Password : ";
			cin >> InPw;
			if(userCount >= 0){
			for(int i = 0; i <= userCount ;i++){
				if(InName == userData[i].UserName && InPw == userData[i].UserPw){
					cls();
					cout << "Login Berhasil! " << endl;
					LoggedIn = true;
					break;
					} 		
				} 
			} else {
				cls();
				cout << "Username/Password salah!!\nCoba lagi!!!\n";
				key();
				cls();
				AccLogin();
			}
			cls();
			
	}while(!LoggedIn);
}
	
	void SystemLaundry::AccReg(){
		string inputPIN;
		cout << "Silahkan Masukkan 5 Digit yang diberikan oleh manager : ";
		cin >> inputPIN;	
		if(userCount >= 0 && inputPIN == PIN) {
		userCount++;
		cout << "+=======================+" << endl;
	    cout << "|     REGISTER AKUN     |" << endl;
	    cout << "+=======================+" << endl;
	    cout << "Masukkan Username : ";
	    cin >> userData[userCount].UserName;
	    cout << "Masukkan Password : ";
	    cin >> userData[userCount].UserPw;
	    cout << userCount;

		cls();
	} else {
		cout << "Error 1 : No default account detected in this app!\n";
		LoggedIn = false;
		key();
		cls();
	}
	}
	
	int main(){
		SystemLaundry In;
		cin >> In;
		if(In.getLoggedIn()){
			Menu M;
			M.Process();
		}
		return 0;
	}
	
	void Menu::UnderConstruction(){
		cout << "+=============================+\n";
		cout << "|    THIS MENU STILL UNDER    |\n";
		cout << "|         CONSTRUCTION        |\n";
		cout << "+=============================+\n";
		cout << "Press Any Key....";
		key();
	}
