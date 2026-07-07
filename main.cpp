	#include<iostream>
	#include<fstream>
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
        SystemLaundry(){
        	userData[userCount].UserName = "ucok";
        	userData[userCount].UserPw = "123";
	}
        
	    private :
			int userCount = 0;
			struct user {
				string UserName,UserPw;
				bool typeAccount;
			};
			string PIN = "12345";
			user userData[1000];
	    	void ProcessLogin();
	    	void AccLogin();
	    	void AccReg();
			void logout();
	    	bool LoggedIn = false;
	};

	class Menu{
		
		public :
			void Process();
			
		private :
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
			client clinetData[1000];
			harga fees[1000];
	};
			
		
	istream& operator>>(istream& input, SystemLaundry& Acc){
		Acc.ProcessLogin();
	    return input;
	}
	ostream& operator<<(ostream& output,const SystemLaundry& Acc){

	    return output;
	}
	
	class fileManagement{
		friend class Menu;
		friend class SystemLaundry;
		public : 
		
		
		
		private :

				
			
	};
	
	
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
	
	void Menu::updateStatus(){
	
	}

	void Menu::inputPelanggan(){
	
	}

	void Menu::dataTransaksi(){
	
	}

	void Menu::logout(){
	
	}


	
	void SystemLaundry::ProcessLogin(){
		char i;
		cout << "Apakah Anda Sudah Memiliki Akun? (Y/N) : ";
		cin >> i;
		cls();
		if(i == 'y' || i == 'Y'){
			AccLogin();
			LoggedIn = true;
		} else if (i == 'n' || i == 'N'){
			AccReg();
			AccLogin();
			LoggedIn = true;
		} else if (!i){
			cout << "Hanya Masukkan Input Y/N!\n";
			ProcessLogin();
		} else {
			key();
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
			for(int i = 0; i < userCount + 1;i++){
			if(InName == userData[i].UserName && InPw == userData[i].UserPw){
				cls();
				cout << "Login Berhasil! " << endl;
				LoggedIn = true;
			} 		
		}
			}else {
			cls();
			cout << "Username/Password salah!!\nCoba lagi!!!\n";
			AccLogin();
			}
		cout << "Tidak akun yang terdaftar di database!!\n";
		cout << "Silahkan Registrasi Akun terlebih dahulu!!!";
		key();
		cls();
		LoggedIn = true;
		AccReg();
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
