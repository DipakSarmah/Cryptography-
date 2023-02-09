//csb20021 dipak sarmah 
//assignment to implement one time pad 


#include <iostream>
#include <linux/random.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 36
#define URANDOM_DEVICE "/dev/urandom"

static FILE *urandom;

using namespace std;

void input(string &text){
		
			ifstream plain("plaintext.txt");
			if(!plain){
				cout<<"Enter the plain text you want to encrypt: \n";
				getline(cin,text);	
				ofstream plaintext("plaintext.txt");	
				plaintext<<text;
				plaintext.close();
				return;
			}
			getline(plain,text);
			plain.close();
	
}

void display(char arr[],int size){
	for(int i=0;i<size;i++){
		cout<<arr[i];
	}	
	cout<<endl;
}

int random_number(void) {
    int c;
    do {
        c = fgetc(urandom);
        if (c == EOF) {
            fprintf(stderr, "Failed to read from %s\n", URANDOM_DEVICE);
            exit(EXIT_FAILURE);
        }
    }
    while (c >= (UCHAR_MAX + 1) / MAX * MAX);

    return c % MAX;
}


void random_gen(int myRandomData[], int text_size){

	urandom = fopen(URANDOM_DEVICE, "rb");
	if (urandom == NULL) {
		fprintf(stderr, "Failed to open %s\n", URANDOM_DEVICE);
		exit(EXIT_FAILURE);
	}
	ofstream key("key.txt");
	char hexa_string[8];
	for (int i = 0; i < text_size; i ++) {
		myRandomData[i]=random_number();
		sprintf(hexa_string,"%04X",myRandomData[i]);
		
		key<<hexa_string<<" ";
		
	}
	fclose(urandom); 
	key.close();
		
}

void encryption(char ciphertext[],int plaintext[], int key[],int text_size, char ciphercopy[]){
	 
	ofstream cipher("ciphertext.txt"); 
	char hexa_string[2];
	for(int i=0;i<text_size;i++){
		ciphertext[i]=(plaintext[i]^key[i]);
		ciphercopy[i]=(ciphertext[i]%26)+'a';
		sprintf(hexa_string,"%02X",ciphercopy[i]);
		cipher<<hexa_string<<" ";
		
	}
	cipher.close();
	
}


void decryption(char decrypt[],char ciphertext[],int key[],int text_size){
	 
	 
	for(int i=0;i<text_size;i++){
		decrypt[i]=(ciphertext[i]^key[i]);
	}
	
}
int main(){
	//taking input from the user;
	string text;
	input(text);

	int text_size;
	text_size=text.length();
	int key[text_size],plaintext_value[text_size];
	char ciphertext[text_size],ciphercopy[text_size],decrypt[text_size];
	
	//plaintext_value stores the integer value of the plain text 
	for(int i=0;i<text_size;i++){
		plaintext_value[i]=text[i];
	}
	//random number generation
	random_gen(key,text_size);
	cout<<"the plain text from the file is : \n";
	for(int i=0;i<text_size;i++){
		cout<<text[i];
	}
	cout<<endl;
	encryption(ciphertext, plaintext_value, key, text_size,ciphercopy);
	cout<<"The cipher text is: \n";
	display(ciphercopy,text_size);
	
	cout<<"The original text after decryption is: \n";
	decryption(decrypt, ciphertext, key, text_size);
	display(decrypt,text_size);
	
	return 0;
}