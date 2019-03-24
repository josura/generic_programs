77/*
 * Creare due array di interi, A e B, con elementi e lunghezza casuale, se tutti gli elementi
 * di A sono distinti calcolare una matrice mxn contenente il prodotto AxB altrimenti restituire
 * la matrice identità.
 *
 */
 
 #include <iostream>
 #include <ctime>
 #include <cstdlib>
 
 using namespace std;
 
 template<typename T>
inline bool elementidistintiarr(T *arr,int n){
	for(int i=0;i<n-1;i++){
		for(int j=1;j<n;j++){
			if(arr[i]==arr[j])
				return false;
		}
	}
	return true;
}

int ** matrixVect(int *arr1,int *arr2,int n, int m){
	int**mat=new int*[n];
	for(int i=0;i<m;i++){
		mat[i]=new int;
		for(int j=0;j<m;j++){
			if(elementidistintiarr(arr1, n))
				mat[i][j]=arr1[i] * arr2[j]; 
			else mat[i][j]= (i==j) ? 1 : 0;
		}
	}
	return mat;		
}
 
 // core
 int get_random_int(int min, int max);
 int *random_int_array(int size, int min, int max);
 bool check_duplicates(int *array, int size);
 int **identity_matrix(int size);
 int **matrix_multiplication(int *matrix_1, int *matrix_2, int h, int w);
 
 // extra
 void print_array(int *array, int size);
 void print_matrix(int **matrix, int h, int w = 0);
 
 int main()
 {
        srand(time(NULL));
         
        int     n = get_random_int(1, 3), *A,
                m = get_random_int(1, 3), *B;
               
        A = random_int_array(n, 1, 3);
        cout << "A: "; print_array(A, n); cout << endl;
       
        B = random_int_array(m, 1, 3);
        cout << "B: "; print_array(B, m); cout << endl;
        
        cout<<"cross product under \n";
        print_matrix(matrixVect(A,B,n,m),n,m);
       
        /*if(check_duplicates(A, m)) {
                cout << "La matrice A ha duplicati, stampo la matrice identita'" << endl;
                print_matrix(identity_matrix(m * n), m * n);
        } else {
                cout << "Moltiplicazione AxB" << endl;
                print_matrix(matrix_multiplication(A, B, m, n), m, n);
        }*/
         
        return 0;
 }
 
 int get_random_int(int min, int max)
 {
        max -= min - 1;
        return int(rand() % max + min);
 }
 
 int *random_int_array(int size, int min, int max)
 {
        int *new_array = new int[size];
        for(int i = 0; i < size; i++) {
                new_array[i] = get_random_int(min, max);
        }
        return new_array;
 }
 
 bool check_duplicates(int *array, int size)
 {
        for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                        if(i == j) continue;
                        if(*(array + i) == *(array + j)) return true;
                }
        }
        return false;
 }
 
 int **identity_matrix(int size)
 {
        int **matrix = new int*[size];
         
        for(int i = 0; i < size; i++) {
                matrix[i] = new int[size];
                for(int j = 0; j < size; j++)
                        matrix[i][j] = i == j ? 1 : 0;
        }
       
        return matrix;
 }
 
 int **matrix_multiplication(int *matrix_1, int *matrix_2, int h, int w)
 {
        int **matrix = new int*[h];
       
        for(int i = 0; i < h; i++) {
                matrix[i] = new int[w];
                for(int j = 0; j < w; j++) {
                        matrix[i][j] = matrix_1[i] * matrix_2[j];
                }
        }
       
        return matrix;
 }
 
 void print_array(int *array, int size)
 {
        for(int i = 0; i < size; i++) {
                if(!i) cout << '[';
                cout << *(array + i) << (i == size-1 ? ']' : '\t');
        }
        return;
 }
 
 void print_matrix(int **matrix, int h, int w)
 {
         if(!w) w = h;
         for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                        cout << matrix[i][j] << '\t';
                }
                cout << endl;
         }
         return;
 }
