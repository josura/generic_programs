#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

template <typename T>
T min(T const& a, T const& b, T const& c) {
   return std::min(std::min(a, b), c);
}


int edit_distance(const string& A, const string& B)
{
    int NA = A.size();
    int NB = B.size();
	/*int** M=new int*[NA+1];
   	for(int i=0;i<=NB;i++)
   	 	M[i]=new int[NB+1];*/
	vector<vector<int>> M(NA + 1, vector<int>(NB + 1));
    for (int a = 0; a <= NA; ++a)
        M[a][0] = a;

    for (int b = 0; b <= NB; ++b)
        M[0][b] = b;

    for (int a = 1; a <= NA; a++)
        for (int b = 1; b <= NB; b++)
        {
            int x = M[a-1][b] + 1;
            int y = M[a][b-1] + 1;
            int z = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : 1);
            M[a][b] = min(x,y,z);
        }

    return M[A.size()][B.size()];
}


int main(){
	ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    if (input.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	if(output.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
    int char1,char2;
    while(!input.eof()){
    	cout<<"ciao ";
    	int editdis;
		input>>char1>>char2;
		string aux1,aux2;
		input>>aux1>>aux2;
		//cout<<aux1<<aux1.size()<<" "<<aux2<<aux2.size()<<endl;
		editdis=edit_distance(aux1,aux2);
		//cout<<longestcs<<endl;
		output<<editdis<<endl;
	}
    output.close();
    input.close();
    return 0;
}
