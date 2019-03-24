#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

int main(){
	int numele, a, b,bbsom,aasom,bsomm,bdiff,asomm,aadiff,adiff,op1piop2, abdivb, aopb1,aopb2,x,y;
    bool resta;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input >> numele;
		for(int i=0; i<numele; i++){
            vector<int> divisori;
			input >> aopb1>>aopb2;
            x=min(aopb1,aopb2);
            y=max(aopb1,aopb2);
            op1piop2=aopb1+aopb2;
            a=op1piop2/2;
            b=y-a;
            if(((a+b)==y) && (max(a,b)-min(a,b))==x && a<1000 && b< 1000){
                output<<a<<" "<<b<<" ";
            }
            else{
                for(unsigned i=5;i<max(aopb1,aopb2);i++){
                    if(max(aopb1,aopb2)%i==0){
                        divisori.push_back(i);
                    }
                }
                bdiff=(-x+sqrt(x*x+4*y))/2;
                b=(-x-sqrt(x*x+4*y))/2;
                //cout<<bdiff<<" bdiff "<<b<<" b ";
                if(x*x>4*y){
                    bsomm=abs(-x+sqrt(x*x-4*y))/2;
                    bbsom=abs(-x-sqrt(x*x-4*y))/2;
                    //cout<<bsomm<<" bsomm "<<bbsom<<" bbsomm ";
                }
                else bsomm=0;
                //cout<<endl;
                adiff=x+bdiff;
                a=x+b;
                asomm=x+bsomm;
                aadiff=x+bbsom;
                aasom=x-bbsom;
                //cout<<aadiff<<" aa diff ";
                //if((a>0 && b>0)){
                    if((a-b==x) && a*b==y && a>0 && b>0){output<<a<<" "<<b<<" ";}
                //}
                //if((aasom>0 && bbsom>0)){
                    if((adiff-bdiff==x) && adiff*bdiff==y){output<<adiff<<" "<<bdiff<<" ";}
                    else if((asomm+bsomm==x) && asomm*bsomm==y){output<<asomm<<" "<<bsomm<<" ";} 
                    else if((aadiff-bbsom==x) && aadiff*bbsom==y && aadiff>0 && bbsom>0){output<<bbsom<<" "<<aadiff<<" ";}
                    else if((aasom+bbsom==x) && aasom*bbsom==y && aasom>0 && bbsom>0){output<<max(aasom,bbsom)<<" "<<min(bbsom,aasom)<<" ";}
                //}  
            }
		}
		output << endl;
	}
	
}
