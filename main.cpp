	#include<iostream>
	using namespace std;
	
	void cls(){ cout << "\033[2J\033[1;1H"; } //Untuk clear Screen
	void key(){ cin.ignore();cin.get();}
	class Login {
		friend ostream& operator <<(ostream&,const Login&);
	    friend istream& operator >>(istream&, Login&);
	    
	    public : 
	    	bool getLoggedIn() {
            return LoggedIn; 
        }
	    private :
	    	string UserName,UserPw;
	    	void ProcessLogin();
	    	void AccLogin();
	    	void AccReg();
	    	bool LoggedIn = false;
	};
	
	class Menu{
		
		public :
			void Process();
			
		private :
			void UnderConstruction();
			int Input;
	};
	
	istream& operator>>(istream& input, Login& Acc){
		Acc.ProcessLogin();
	    return input;
	}
	ostream& operator<<(ostream& output,const Login& Acc){

	    return output;
	}
	
	
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
					//Untuk menu input data pelanggan
					break;
				case 2 :
					cls();
					UnderConstruction();
					//Unutk menu update status
					break;
				case 3 :
					cls();
					UnderConstruction();
					//Untuk menu Data transaksi
					break;
				case 4 :
					cls();
					UnderConstruction();
					//Logout menu
					break;
				default :
					cls();
					cout << "Hanya Masukkan Pilihan 1-4 !!!" << endl;
			}
		}while(Input != 4);
	} 
	
	
	void Login::ProcessLogin(){
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
		} else {
			cout << "Hanya Masukkan Input Y/N!\n";
			ProcessLogin();
		}
	}
	
	void Login::AccLogin(){
		string InName,InPw;
	
			cout << "+=======================+" << endl;
	    	cout << "|      LOGIN AKUN       |" << endl;
	    	cout << "+=======================+" << endl;
			cout << "Masukkan Username : ";
			cin >> InName;
			cout << "Masukkan Password : ";
			cin >> InPw;
			if(InName == UserName && InPw == UserPw){
				cls();
				cout << "Login Berhasil! " << endl;
				LoggedIn = true;
			} else{
				cls();
				cout << "Username/Password salah!!\nCoba lagi!!!\n";
				AccLogin();
			}
	}
	
	void Login::AccReg(){
		cout << "+=======================+" << endl;
	    cout << "|     REGISTER AKUN     |" << endl;
	    cout << "+=======================+" << endl;
	    cout << "Masukkan Username : ";
	    cin >> UserName;
	    cout << "Masukkan Password : ";
	    cin >> UserPw;
		cls();
	}
	
	int main(){
		Login In;
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
