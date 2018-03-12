#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//"http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm" i have just implemented the steps in this web page. so read it before seeing this.

string toHex[16];
int s[8][4][16] = {
{
{14 , 4 , 13 , 1 ,  2, 15 , 11 , 8 ,  3, 10 ,  6, 12 ,  5 , 9 ,  0 , 7},
{0, 15   ,7 , 4  ,14 , 2,  13 , 1 , 10 , 6 , 12 ,11  , 9 , 5  , 3 , 8},
{4 , 1 , 14 , 8 , 13 , 6  , 2, 11  ,15 ,12  , 9  ,7  , 3 ,10 ,  5 , 0},
{15 ,12  , 8 , 2  , 4 , 9 ,  1 , 7  , 5 ,11 ,  3 ,14 , 10,  0  , 6, 13}
 },

{
{ 15 , 1 ,  8, 14 ,  6, 11  , 3 , 4,   9  ,7  , 2, 13  ,12 , 0 ,  5, 10},
{3, 13 ,  4  ,7 , 15 , 2  , 8, 14 , 12,  0 ,  1, 10 ,  6,  9,  11 , 5},
{0 ,14  , 7, 11,  10,  4 , 13,  1 ,  5 , 8,  12 , 6 ,  9 , 3 ,  2 ,15},
{13 , 8  ,10 , 1  , 3, 15 ,  4 , 2 , 11 , 6 ,  7 ,12 ,  0  ,5,  14,  9}
},

{
{ 10,  0 ,  9, 14 ,  6 , 3  ,15 , 5 ,  1 ,13 , 12,  7 , 11 , 4,   2 , 8},
{13 , 7 ,  0 , 9  , 3, 4,   6 ,10  , 2  ,8  , 5, 14 , 12 ,11 , 15 , 1 },
{ 13 , 6 ,  4 , 9 ,  8, 15 ,  3 , 0 , 11 , 1,   2 ,12 ,  5 ,10 , 14  ,7 },
{1, 10 , 13 , 0 ,  6 , 9 ,  8  ,7 ,  4 ,15 , 14 , 3 , 11,  5 ,  2 ,12 }
},

{
{7, 13 , 14,  3 ,  0 , 6 ,  9 ,10,   1 , 2 ,  8,  5 , 11, 12 ,  4, 15 },
{13 , 8 , 11,  5 ,  6, 15 ,  0  ,3  , 4 , 7,   2, 12 ,  1, 10 , 14 , 9 },
{10 , 6  , 9 , 0,  12, 11  , 7 ,13,  15,  1 ,  3, 14 ,  5 , 2  , 8 , 4 },
{3 ,15 ,  0 , 6 , 10 , 1 , 13 , 8 ,  9,  4  , 5 ,11,  12,  7 ,  2 ,14 }
} ,
{

{2 ,12 ,  4 , 1 ,  7 ,10,  11 , 6 ,  8 , 5 ,  3, 15  ,13 , 0 , 14,  9 },
{14, 11 ,  2, 12 ,  4 , 7 , 13  ,1,   5 , 0 , 15, 10,3 ,9 ,  8 , 6 },
{ 4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3, 0, 14},
{ 11,  8,  12,  7,   1, 14, 2, 13, 6, 15,0 , 9 , 10 , 4 ,  5 , 3}
},

{
{ 12,  1 , 10 ,15 ,  9 , 2  , 6,  8,   0, 13 ,  3 , 4,  14,  7  , 5, 11},
{10, 15,   4 , 2 ,  7 ,12  , 9 , 5 ,  6, 1 , 13, 14,   0, 11,   3,  8 },
{9, 14,  15,  5,   2 , 8,  12 , 3 ,  7 , 0 ,  4 ,10 ,  1, 13,  11 , 6 },
{4 , 3 ,  2 ,12,   9,  5 , 15, 10,  11, 14,   1 , 7 ,  6 , 0 ,  8, 13 }
},

{
{4, 11 ,  2, 14 , 15 , 0 ,  8, 13 ,  3, 12,   9 , 7 ,  5, 10 ,  6 , 1 },
{13,  0 , 11,  7 ,  4 , 9 ,  1,10 , 14 , 3,   5, 12,   2, 15,   8 , 6 },
{1 , 4,  11, 13,  12 , 3,   7, 14 , 10, 15  , 6 , 8 ,  0 , 5,   9,  2 },
{6, 11 , 13 , 8 ,  1,  4 , 10 , 7,   9 , 5,   0 ,15 , 14 , 2  , 3 ,12 }
},

{
{ 13 , 2 ,  8 , 4 ,  6 ,15 , 11  ,1 , 10 , 9 ,  3, 14 ,  5 , 0 , 12 , 7},
{1 ,15 , 13  ,8  ,10  ,3 ,  7,  4 , 12 , 5 ,  6 ,11 ,  0 ,14,   9,  2 },
{ 7, 11,   4 , 1 ,  9 ,12,  14 , 2 ,  0 , 6 , 10, 13,  15,  3  , 5 , 8},
{2,  1,  14 , 7,   4, 10 ,  8, 13 , 15, 12 ,  9 , 0 ,  3,  5,   6, 11 }
} 
};

int findRow(string a){
	if(a == "00")
	return 0;
	else if(a == "01")
	return 1;
	else if(a == "10")
	return 2;
	else
	return 3;
}

int findCol(string a){
	int number=-1;
	for(int i=0;i<16;i++){
		if(toHex[i]==a){
		number = i;
		break;
	}
	}
	return number;
}


string useStable(string a){
	
	
	int length = 0,i=0;
	string eight[8],ans="",temp,temp1;
	while(i<8){
		eight[i] = a.substr(length,6);
		i++;
		length = length + 6;
	}
	
//	for(int i=0;i<8;i++)
//	cout<<eight[i]<<endl<<endl;
	
	for(int i=0;i<8;i++){
	temp = eight[i][0];
	temp+=eight[i][5];
	
	temp1 = eight[i].substr(1,4);
	
	ans.append( toHex[s[i][findRow(temp)][findCol(temp1)]] );	
	}
	

	return ans;
	
}

string leftRotate(string s, int shift){

	reverse(s.begin(),s.begin()+shift);
	reverse(s.begin()+shift,s.end());
	reverse(s.begin(),s.end());

	return s;
}

string EXOR(string a, string b){
	
	int _a,_b;
	string answer;
	if(a.length()!=b.length())
	return "no answer possible";

	for(int i=0;i<a.length();i++){
		_a = a[i] - '0';
		_b = b[i] - '0';
		
		_a = _a ^ _b;
		_a = _a + '0';
		answer.push_back(_a);
		
	}
	
	return answer;
	
}


int main(){ 

toHex[0] = "0000";
toHex[1] = "0001";
toHex[2] = "0010";
toHex[3] = "0011";
toHex[4] = "0100";
toHex[5] = "0101";
toHex[6] = "0110";
toHex[7] = "0111";
toHex[8] = "1000";
toHex[9] = "1001";
toHex[10] = "1010";
toHex[11] = "1011";
toHex[12] = "1100";
toHex[13] = "1101";
toHex[14] = "1110";
toHex[15] = "1111";



	string text_message="0123456789ABCDEF", key="133457799BBCDFF1", 
	textMessage_bit, keyBitstream,  L, R, 
	permutedKey,C[17],D[17], 
	temp,temp1, K[16], IP, l[17],r[17],convert_to_hex="0123456789ABCDEF",tohex;
	
	for(int i=0;i<16;i++)
	tohex.push_back(convert_to_hex[i]);
	
	
	
	int pc1[8][7]={{57  ,49  ,  41 ,  33  ,  25  ,  17 ,   9},
	{1  , 58   , 50  , 42   , 34  ,  26  , 18},
	{10   , 2  ,  59  , 51   , 43  ,  35  , 27},
	{19  , 11   ,  3  , 60   , 52   , 44  , 36},
	{63  , 55 ,   47 ,  39   , 31  ,  23   ,15},
	{7   ,62   , 54  , 46   , 38   , 30  , 22},
	{14  ,  6  ,  61  , 53   , 45   , 37  , 29},
	{21  , 13    , 5  , 28  ,  20   , 12    ,4}
	},
	
	pc2[8][6]={
       {14 ,  17 ,  11 ,   24  ,   1  ,  5},
       {3  ,  28  , 15  ,   6 ,   21 ,  10},
       {23  ,  19  , 12  ,   4  ,  26 ,   8},
       {16   ,  7  , 27  ,  20  ,  13  ,  2},
       {41  ,  52 ,  31   , 37 ,   47  , 55},
       {30   , 40  , 51  ,  45  ,  33  , 48},
       {44  ,  49  , 39  ,  56  ,  34  , 53},
       {46   , 42  , 50   , 36   , 29   ,32}
        },
        
        ip[8][8]={
           {58   , 50  , 42  ,  34  ,  26 ,  18  ,  10   , 2}, 
            {60  ,  52  , 44   , 36   , 28  , 20   , 12   , 4},
            {62   , 54 ,  46  , 38   , 30 ,  22   , 14  ,  6},
            {64   , 56  , 48  ,  40   , 32 ,  24  ,  16   , 8},
            {57  ,  49 ,  41 ,   33  ,  25  , 17   ,  9   , 1},
            {59   , 51 ,  43  ,  35   , 27,   19  ,  11  ,  3},
            {61  ,  53 ,  45  ,  37  ,  29 ,  21  ,  13  ,  5},
            {63   , 55  , 47  ,  39   , 31 ,  23  ,  15  ,  7}
            },
	
	e_bit_selection[8][6] = {
	{ 32   ,  1  ,  2   ,  3   ,  4  ,  5},
	{4   ,  5  ,  6  ,   7   ,  8    ,9},
	{8   ,  9  , 10   , 11   , 12  , 13},
	{12   , 13 ,  14   , 15  ,  16  , 17},
	{16   , 17  , 18  ,  19  ,  20  , 21},
	{20   , 21 ,  22   , 23    ,24  , 25},
	{ 24  ,  25 ,  26  ,  27  ,  28 ,  29},
	{28   , 29  , 30  ,  31  ,  32  ,  1}
	},
	P[8][4] = {
	{16 ,  7 , 20 , 21 },
	{ 29 , 12 , 28  ,17},
	{ 1 , 15 , 23,  26},
	{5 , 18 , 31 , 10 },
	{ 2  , 8 , 24,  14 },
	{ 32 , 27 ,  3  , 9},
	{ 19  ,13,  30  , 6},
	{22 , 11 ,  4 , 25 }
	},
	ip_inverse[8][8] = {
	{40  ,   8  , 48  ,  16  ,  56  , 24   , 64   ,32},
	{ 39 ,    7 ,  47 ,   15 ,   55  , 23  ,  63  , 31},
	{38  ,   6  , 46  ,  14  ,  54  , 22   , 62  , 30 },
	{37  ,   5  , 45  ,  13  ,  53  , 21   , 61   ,29 },
	{ 36 ,    4 ,  44 ,   12 ,   52 ,  20  ,  60   ,28},
	{35  ,   3  , 43  ,  11  ,  51  , 19   , 59   ,27 },
	{34  ,   2  , 42  ,  10  ,  50   ,18    ,58   ,26 },
	{33  ,   1  , 41  ,   9  ,  49  , 17   , 57  , 25 }
	};
	
	int numberOfshifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1},length;
	
	
	// all the above declarations are used in the des encrypting procedure
	
	cout<<"Enter the message"<<endl;
	//getline(cin,text_message);
	
	cout<<"Enter the key"<<endl;
	//getline(cin,key);
	
	//construct text the hex to binary array
	//for(int i=0;i<16;i++)
	//toHex.push_back(bitset<4>(i).to_string());
	
	for(int i=0;i<text_message.length();i++){
	
		if(text_message[i]>='A' && text_message[i]<='F')
		textMessage_bit.append( toHex[text_message[i]-'A'+10] );
		else if(text_message[i]>='0' && text_message[i]<='9')			// here i convert the given hex into binary
		textMessage_bit.append( toHex[text_message[i]-'0'] );
		else{
		cout<<"useless character detected in text, terminating......"<<endl;
		goto terminate;
			}
	
	}
	
	for(int i=0;i<key.length();i++){
	
		if(key[i]>='A' && key[i]<='F')
		keyBitstream.append( toHex[key[i]-'A'+10] );
		else if(key[i]>='0' && key[i]<='9')							// here i convert the given key into binary
		keyBitstream.append( toHex[key[i]-'0'] );
		else{
		cout<<"useless character detected in key, terminating......"<<endl;
		goto terminate;
			}
	
	}
	
	L = textMessage_bit.substr(0,32);		// divide the text message bit into half. But its never used in the below program :}
	R = textMessage_bit.substr(32,32);
	cout<<"Length "<<textMessage_bit.length()<<endl;
	cout<<"L : "<<L<<endl;
	cout<<"R : "<<R<<endl;
	cout<<"Given message : "<<textMessage_bit<<endl;
	
	for(int i=0;i<8;i++){
		for(int j=0;j<7;j++){
			permutedKey.push_back(keyBitstream[pc1[i][j]-1]);		//permute the key using pc1 table
		}
	}
	
	C[0] = permutedKey.substr(0,28);
	D[0] = permutedKey.substr(28,28);
	
	cout<<"Permuted Key : "<<permutedKey<<endl;
	cout<<"permuted key length : "<<permutedKey.length()<<endl;		//just for debugging

//	cout<<"C0 : "<<C[0]<<endl;
//	cout<<"D0 : "<<D[0]<<endl;
		
	for(int i=1;i<17;i++){
		C[i] = leftRotate(C[i-1],numberOfshifts[i-1]);
		D[i] = leftRotate(D[i-1],numberOfshifts[i-1]);		//the rotating thing...u will know this if u read that des theory
		
	}
	
	cout<<"The shifts is "<<endl;
	
	for(int i=0;i<17;i++){
		cout<<"C"<<i<<" : "<<C[i]<<endl;		//this too is for debugging purpose
		cout<<"D"<<i<<" : "<<D[i]<<endl;
		cout<<endl<<endl;
	}
	
	for(int i=0;i<16;i++){
            temp = "";
            temp.append(C[i+1]);
            temp.append(D[i+1]);
            
            for(int j=0;j<8;j++){					// here i build the damn 16 keys :}
                    for(int k=0;k<6;k++){
                    
            K[i].push_back(temp[pc2[j][k]-1]);
                    
                    }               
            }
            temp = "";
     }
	
	
	for(int i=0;i<16;i++)
	cout<<"K"<<i+1<<" : "<<K[i]<<endl<<endl;
	
	for(int i=0;i<8;i++){
    for(int j=0;j<8;j++)							//permute the text message bits using ip table
    IP.push_back(textMessage_bit[ip[i][j]-1]);        
            }
	
	cout<<"IP : "<<IP<<endl;
	
	l[0] = IP.substr(0,32);
	r[0] = IP.substr(32,32);
	
	cout<<"L0 : "<<l[0]<<endl;
	cout<<"R0 : "<<r[0]<<endl;	
	
						
	//useStable(K[15]);

	//here begins the construction for 16  l and r..actually 17 l and r
	for(int i=1;i<17;i++){
		temp = "";
		temp1 = "";
	
		l[i] = r[i-1]; //ln ...i.e  ln = Rn-1
		temp = l[i];
		//this is the beginning of the function that deals with Kn and Rn-1
		for(int j=0;j<8;j++){
			for(int k=0;k<6;k++)
			temp1.push_back(temp[e_bit_selection[j][k]-1]);
			}
			
		temp1 = EXOR(temp1,K[i-1]);			//temp and temp1 are temporary strings
		temp1 = useStable(temp1);
		temp = "";
		
		for(int x=0;x<8;x++){
			for(int y=0;y<4;y++){
				temp.push_back(temp1[P[x][y]-1]);
			}
		}
		
		r[i] = EXOR(l[i-1],temp); // Rn = Ln-1 exor function(Kn,Rn-1);
		
			
	} 
	
	cout<<"L16 : "<<l[16]<<endl;
	cout<<"R16 : "<<r[16]<<endl;
	
	temp = "";
	temp =  r[16];		//reverse l16 and r16
	temp += l[16];
	cout<<"r16+l16 : "<<temp<<endl;

	temp1 = "";
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
		temp1.push_back(temp[ip_inverse[i][j]-1]); //finally permute with the ip inverse table
	}
	
	cout<<"ip inverse : "<<temp1<<endl;
	//convert the bits into hex.
	temp = "";
	length = 0;			
	while(length<temp1.length()){
		for(int i=0;i<16;i++){
			if(toHex[i] == temp1.substr(length,4)){
				temp.push_back(tohex[i]);
			}
		}
		length = length + 4;
	}
	cout<<endl<<"**************************"<<endl;
	cout<<"THE ENCRYPTED HEX IS : "<<temp<<endl;   //THE END
	cout<<"**************************"<<endl;
	
	
	terminate:
	getchar();
    return 0;
}
