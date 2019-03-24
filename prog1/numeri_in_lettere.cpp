#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<windows.h>

using namespace std;

void Switch_ten(int x){
switch (x){
	
						case (1):
							cout<<"uno";
							break;
						case (2):
							cout<<"due";
							break;
						case (3):
							cout<<"tre";
							break;
						case (4):
							cout<<"quattro";
							break;
						case (5):
							cout<<"cinque";
							break;
						case (6):
							cout<<"sei";
							break;
						case (7):
							cout<<"sette";
							break;
						case (8):
							cout<<"otto";
							break;
						case (9):
							cout<<"nove";
							break;
}
}

void Switch_hun(int x){
switch (x){
						case (0):
							cout<<"zero";
							break;
						case (1):
							cout<<"uno";
							break;
						case (2):
							cout<<"due";
							break;
						case (3):
							cout<<"tre";
							break;
						case (4):
							cout<<"quattro";
							break;
						case (5):
							cout<<"cinque";
							break;
						case (6):
							cout<<"sei";
							break;
						case (7):
							cout<<"sette";
							break;
						case (8):
							cout<<"otto";
							break;
						case (9):
							cout<<"nove";
							break;
						case (10):
							cout<<"dieci";
							break;
						case (11):
							cout<<"undici";
							break;
						case (12):
							cout<<"dodici";
							break;
						case (13):
							cout<<"tredici";
							break;
						case (14):
							cout<<"quattordici";
							break;
						case (15):
							cout<<"quindici";
							break;
						case (16):
							cout<<"sedici";
							break;
						case (17):
							cout<<"diciassette";
							break;
						case (18):
							cout<<"diciotto";
							break;
						case (19):
							cout<<"diciannove";
							break;
						case (x>=20 && x<30):
							cout<<"venti"<<Switch_ten(x-20);
							break;	
						case (x>=30 && x<40):
							cout<<"trenta"<<Switch_ten(x-30);
							break;	
						case (x>=40 && x<50):
							cout<<"quaranta"<<Switch_ten(x-40);
							break;	
						case (x>=50 && x<60):
							cout<<"cinquanta"<<Switch_ten(x-50);
							break;
						case (x>=60 && x<70):
							cout<<"sessanta"<<Switch_ten(x-60);
							break;	
						case (x>=70 && x<80):
							cout<<"settanta"<<Switch_ten(x-70);
							break;
						case (x>=80 && x<90):
							cout<<"ottanta"<<Switch_ten(x-80);
							break;	
						case (x>=90 && x<100):
							cout<<"novanta"<<Switch_ten(x-90);
							break;	
						}
} 

void Switch_thou(int x){
switch (x){
	 					case (x>=100 && x<200):
							cout<<"cento"<<Switch_hun(x-100);
							break;	
						case (x>=200 && x<300):
							cout<<"duecento"<<Switch_hun(x-200);
							break;	
						case (x>=300 && x<400):
							cout<<"trecento"<<Switch_hun(x-300);
							break;
						case (x>=400 && x<500):
							cout<<"quattrocento"<<Switch_hun(x-400);
							break;		
						case (x>=500 && x<600):
							cout<<"cinquecento"<<Switch_hun(x-500);
							break;
						case (x>=600 && x<700):
							cout<<"seicento"<<Switch_hun(x-600);
							break;	
						case (x>=700 && x<800):
							cout<<"settecento"<<Switch_hun(x-700);
							break;
						case (x>=800 && x<900):
							cout<<"ottocento"<<Switch_hun(x-800);
							break;	
						case (x>=900 && x<1000):
							cout<<"novecento"<<Switch_hun(x-900);
							break;
}
	
}
void Switch_tenth(int x){
switch (x){
	 					case (x>=1000 && x<2000):
							cout<<"mille"<<Switch_thou(x-1000);
							break;	
						case (x>=2000 && x<3000):
							cout<<"duemila"<<Switch_thou(x-2000);
							break;	
						case (x>=3000 && x<4000):
							cout<<"tremila"<<Switch_thou(x-3000);
							break;
						case (x>=4000 && x<5000):
							cout<<"quattromila"<<Switch_thou(x-4000);
							break;		
						case (x>=5000 && x<6000):
							cout<<"cinquemila"<<Switch_thou(x-5000);
							break;
						case (x>=6000 && x<7000):
							cout<<"seimila"<<Switch_thou(x-6000);
							break;	
						case (x>=7000 && x<8000):
							cout<<"settemila"<<Switch_thou(x-7000);
							break;
						case (x>=8000 && x<9000):
							cout<<"ottomila"<<Switch_thou(x-8000);
							break;	
						case (x>=9000 && x<10000):
							cout<<"novemila"<<Switch_thou(x-9000);
							break;
}
	
}
int main(){
	char x = 'y';
	int x;
	do {
	
	cout<<"scrivi un numero da 1 a 9999\n";
	cin >> x;
	if (x<10000){
		if (x<1000){
			if (x<100){
					 cout<<Switch_hun(x)<<"\n";														
				}
			else {
				cout<<Switch_thou(x)<<"\n";
			}	
			}
		else {
			cout<<Switch_tenth(x)<<"\n";
		}	
		}
	else {
	cout<<"numero troppo grande";	
	}   
	Sleep(3000);
 	cout<<endl<<"vorresti avere un altro numero scritto in lettere perchè sei scemo?"<<endl<<"y/n:\n";
 	cin>>x;
 } while (x== 'y'); 	
}

