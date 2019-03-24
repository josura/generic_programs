#include<iostream>
#include<cstdlib>
#include<string>
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
						case (21):
							cout<<"ventuno";
							break;
						case (28):
							cout<<"ventotto";
							break;
						case (31):
							cout<<"trentuno";
							break;
						case (38):
							cout<<"trentotto";
							break;
						case (41):
							cout<<"quarantuno";
							break;
						case (48):
							cout<<"quarantotto";
							break;
						case (51):
							cout<<"cinquantuno";
							break;
						case (58):
							cout<<"cinquantotto";
							break;
						case (61):
							cout<<"sessantuno";
							break;
						case (68):
							cout<<"sessantotto";
							break;
						case (71):
							cout<<"settantuno";
							break;
						case (78):
							cout<<"settantotto";
							break;
						case (81):
							cout<<"ottantuno";
							break;
						case (88):
							cout<<"ottantotto";
							break;
						case (91):
							cout<<"novantuno";
							break;
						case (98):
							cout<<"novantotto";
							break;		
						default :
							if (x<0){
							cout<<"numero negativo, why";
						} /*  else if (x==char && x==string){
							cout<<"Perche' ?";
						}     */
						}
	/*	if ((x%10)==1){
			
		} 
		else if ((x%10)==8){
		
		} */
if (x>=20 && x<30 && x!=21 && x!=28){
	cout<<"venti";
	Switch_ten(x%10);	
}
else if (x>=30 && x<40 && x!=31 && x!=38){
	cout<<"trenta";
	Switch_ten(x%10);
}
else if  (x>=40 && x<50 && x!=41 && x!=48){
	cout<<"quaranta";
	Switch_ten(x%10);
}
else if (x>=50 && x<60 && x!=51 && x!=58){
	cout<<"cinquanta";
	Switch_ten(x%10);
}	
else if	(x>=60 && x<70 && x!=61 && x!=68){
	cout<<"sessanta";
	Switch_ten(x%10);			
}
else if  (x>=70 && x<80 && x!=71 && x!=78){
	cout<<"settanta";
	Switch_ten(x%10);
}
else if (x>=80 && x<90 && x!=81 && x!=88){
	cout<<"ottanta";
	Switch_ten(x%10);
}	
else if	(x>=90 && x<100 && x!=91 && x!=98){
	cout<<"novanta";
	Switch_ten(x%10);			
}
}

 

void Switch_thou(int x){
		/*	switch(x){
						case (108):
							cout<<"centotto";
							break;
						case (208):
							cout<<"duecentotto";
							break;
						case (308):
							cout<<"trecentotto";
							break;	
						case (408):
							cout<<"quattrocentotto";
							break;
						case (508):
							cout<<"cinquecentotto";
							break;
						case (608):
							cout<<"seicentotto";
							break;
						case (708):
							cout<<"settecentotto";
							break;		
						case (808):
							cout<<"ottocentotto";
							break;	
						case (908):
							cout<<"novecentotto";
							break;				
}     */
								
if (x>=100 && x<200){
	cout<<"cento";
	Switch_hun(x%100);
}
else if (x>=200 && x<300){
	cout<<"duecento";
	Switch_hun(x%100);
}
else if (x>=300 && x<400){
	cout<<"trecento";
	Switch_hun(x%100);
}
else if  (x>=400 && x<500){
	cout<<"quattrocento";
	Switch_hun(x%100);
}
else if (x>=500 && x<600){
	cout<<"cinquecento";
	Switch_hun(x%100);
}	
else if	(x>=600 && x<700){
	cout<<"seicento";
	Switch_hun(x%100);
}
else if  (x>=700 && x<800){
	cout<<"settecento";
	Switch_hun(x%100);
}
else if (x>=800 && x<900){
	cout<<"ottocento";
	Switch_hun(x%100);
}	
else if	(x>=900 && x<1000){
	cout<<"novecento";
	Switch_hun(x%100);
}


	
}

void Switch_tenth(int x){
if (x>=1000 && x<1100){
	cout<<"mille";
	Switch_hun(x%1000);
}	
else if (x>=2000 && x<2100){
	cout<<"duemila";
	Switch_hun(x%1000);
}
else if (x>=3000 && x<3100){
	cout<<"tremila";
	Switch_hun(x%1000);
}
else if (x>=4000 && x<4100){
	cout<<"quattromila";
	Switch_hun(x%1000);
}
else if (x>=5000 && x<5100){
	cout<<"cinquemila";
	Switch_hun(x%1000);
}
else if (x>=6000 && x<6100){
	cout<<"seimila";
	Switch_hun(x%1000);
}
else if (x>=7000 && x<7100){
	cout<<"settemila";
	Switch_hun(x%1000);
}
else if (x>=8000 && x<8100){
	cout<<"ottomila";
	Switch_hun(x%1000);
}
else if (x>=9000 && x<9100){
	cout<<"duemila";
	Switch_hun(x%1000);
}
else if (x>=1100 && x<2000){
	cout<<"mille";
	Switch_thou(x%1000);
}
else if (x>=2100 && x<3000){
	cout<<"duemila";
	Switch_thou(x%1000);
}
else if (x>=3100 && x<4000){
	cout<<"tremila";
	Switch_thou(x%1000);
}
else if  (x>=4100 && x<5000){
	cout<<"quattromila";
	Switch_thou(x%1000);
}
else if (x>=5100 && x<6000){
	cout<<"cinquemila";
	Switch_thou(x%1000);
}	
else if	(x>=6100 && x<7000){
	cout<<"seimila";
	Switch_thou(x%1000);
}
else if  (x>=7100 && x<8000){
	cout<<"settemila";
	Switch_thou(x%1000);	
}
else if (x>=8100 && x<9000){
	cout<<"ottomila";
	Switch_thou(x%1000);
}	
else if	(x>=9100 && x<10000){
	cout<<"novemila";
	Switch_thou(x%1000);
}	
}


int main(){
	char c = 'y';
	int x;
	do {
	system("cls");
	cout<<"scrivi un numero da 0 a 9999\n";
	cin >> x;
	if (x<10000){
		if (x<1000){
			if (x<100){
				if (x==0){
					cout<<"zero";
				}
				else
					 Switch_hun(x);
					 cout<<"\n";														
				}
			else {
				Switch_thou(x);
				cout<<"\n";
			}	
			}
		else {
			Switch_tenth(x);
			cout<<"\n";
		}	
		}
	else {
	cout<<"numero troppo grande, you don't speak italian right";	
	}   
	Sleep(2000);
 	cout<<endl<<"vorresti avere un altro numero scritto in lettere perche' sei scemo?"<<endl<<"y/n:\n";
 	cin>>c;
 } while (c== 'y'); 
 return 0;	
}
