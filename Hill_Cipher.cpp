#include<iostream>
#include<cmath>
#include<string>
using namespace std;
#define N 3


int mod(int a,int b){
	if(a>0)
	return a % b;
	else if(a % b == 0)
	return 0;
	else{
	int q = -a / b;
	q++;
	return q * b + a;
	}
}



int findModuloInverse(int a,int m){
	
	a = a%m;
	for(int i=2;i<m;i++)
	if((a*i) % m == 1)
	return i;
	
}



void generateCoFactors(int a[N][N],int temp[N][N],int p,int q,int n){
	
	int i=0,j=0;
	
	for(int row=0;row<n;row++){
		for(int col=0;col<n;col++){
		if(row!=p && col!=q){
			temp[i][j++] = a[row][col];
		}
		
		if(j==n-1)
		{
			i++;
			j=0;
		}	
		}
	}
}


int findDeterminant(int a[N][N],int n){
		
		if(n==1)
		return a[0][0];
		
		int temp[N][N],D = 0;
		
		int sign = 1;
		
		for(int i = 0; i<n ; i++){
			
			generateCoFactors(a,temp,0,i,n);
			D += sign*a[0][i]*findDeterminant(temp,n-1);
			sign *= -1;
			
		}


return D;
}

void adjoint(int a[N][N],int adj[N][N]){
	
	if(N==1){
		adj[0][0] = 1;
		return;
	}
	
	
		int temp[N][N];
		int sign;
		for(int i=0;i<N;i++){
			
			for(int j=0;j<N;j++){
				generateCoFactors(a,temp,i,j,N);
				
				sign = ((i+j) % 2 == 0) ? 1:-1;
				
				adj[j][i] =  sign * findDeterminant(temp,N-1);
				
			}
	}
	
}


void inverse(int a[N][N],int inv[N][N],int adj[N][N]){
	
	int det = findDeterminant(a,N);
	if(det == 0)
	{
		cout<<"Matrix is singular"<<endl;
		return;
	}

	det = findModuloInverse(det,128);
	cout<<endl<<"inverse of determinant : "<<det<<endl;
	
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++){
	inv[i][j] = adj[i][j] * det; 
	inv[i][j] = mod(inv[i][j],128);
	}
	
	
}

void print(int a[N][N]){
	
	for(int i=0;i<N;i++)
	{
	for(int j=0;j<N;j++)
	cout<<a[i][j]<<"    ";
	cout<<endl;
	}

}

void vectorMultiply(int inv[N][N],int v[N],int vec[N],string &text){
	char temp;
	
	for(int i=0;i<N;i++){
	vec[i] = 0;
		for(int j=0;j<N;j++)
			vec[i] += v[j] * inv[i][j];
		vec[i] %= 128;
		temp = vec[i];
		text.push_back(temp);
		}
}

void isValid(string &text){
	int count=text.length();
	
	if(count % N != 0){
		int temp = 3 - (count % N);
	cout<<"N is "<<N<<", give "<<temp<<" padding characters"<<endl;
	char tem;
	while(temp--){
		cin>>tem;
		text.push_back(tem);
	}
	}
	else
	cout<<"Given string is valid"<<endl;
}

int main(){
	
	int a[N][N] = {
	{2,4,5},
	{9,2,1},
	{3, 17 ,7}
	};
	string given_text, encryptedText, decryptedText;
	cout<<"Enter the text : "<<endl;
	getline(cin,given_text);
	int adj[N][N],inv[N][N],vec[N],v[N];
	adjoint(a,adj);
	inverse(a,inv,adj);
	cout<<"Adjoint:"<<endl;
	print(adj);
	cout<<"Inverse:"<<endl;
	print(inv);
	cout<<"The determinant is : "<<findDeterminant(a,N)<<endl;

		isValid(given_text);
		cout<<given_text;
		int i=0,j=0;
		while(i<given_text.length()){
		
		v[j] = given_text[i];
		j++;
		
		if(j==N){
		vectorMultiply(a,v,vec,encryptedText);
		j=0;
			}
		i++;
		}
		
		cout<<"The encrypted text is : "<<encryptedText<<endl;
	
		i = 0; j = 0;
		while(i<encryptedText.length()){
			
			v[j] = encryptedText[i];
			j++;
			i++;
			if(j==N){
			vectorMultiply(inv,v,vec,decryptedText);
			j = 0;
			}
		}
		
		cout<<"The decrypted text is : "<<decryptedText<<endl;
	
		return 0;
}
