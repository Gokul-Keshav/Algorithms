#include <bits/stdc++.h>
using namespace std;
char Index[30];
unordered_map<char,int> Hash;

string Decrypt(string cipher,int shift){
	int j;
	string text;

	for(int i=0;i<cipher.length();i++){
		if(cipher[i]==' ')
			text.push_back(' ');
		else{

		j = Hash.at(cipher[i]) - shift;
		if(j<0)
			j = j+26;
		text.push_back(Index[j]);
		}
	}

	return text;
}


int main ()
{	
	int j,i,shift;
	string text,cipher;
	char temp;
	for(i=65,j=0;i<91;i++,j++){
		temp = i;
		Hash.insert(make_pair(temp,j));
	}
	j=65;
	for(i=0;i<26;i++){
		temp = j;
		Index[i] = temp;
		j++;
	}


	cout<<"Enter the shift:"<<endl;
	cin>>shift;
	cout<<"Enter the text:"<<endl;
	cin.ignore();
	getline(cin,text);
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	cout<<"The given text is:"<<endl;
	cout<<text<<endl;

	for(i=0;i<text.length();i++){
		if(text[i]==' ')
			cipher.push_back(' ');
		else{
		j = Hash.at(text[i]);
		cipher.push_back(Index[(j+shift)%26]);
		}
	}
	cout<<"The caesar cipher is"<<endl;
	cout<<cipher<<endl;
	cout<<"The Decrypt is"<<endl;
	cout<<Decrypt(cipher,shift)<<endl;

  return 0;
}