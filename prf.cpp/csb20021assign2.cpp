#include <bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>

using namespace std;

int random_number(void) 
{
   unsigned int random;
   FILE *fd;
   fd=fopen("/dev/urandom","r");
   fread(&random,sizeof(random),1,fd);
   fclose(fd);
   return random;
}

int PFR_func(int key, int X )
{
    fstream f_stream;
    for(int i=0;i<key;i++)
    {
        stringstream string_stream;
        string key_no;

        string_stream<<i;
        string_stream>>key_no;
        f_stream.open("file"+key_no+".txt", ios::out );

        if(!f_stream.is_open())
        {
            cout<<"error in opening the file!";
            return 0;
        }

        for(int k=0;k<X;k++)
        {
            unsigned short int number = (unsigned short int)random_number();
            f_stream<<number<<endl;
        }

        f_stream.close();
    }

    return 1;
}

int main()
{
    int key_length,x,choice,option=1;

    while(1)
    {
        cout<<"Enter 1: Key and X (default values)\nEnter 2: User input for Key and X\n";
        cout<<"Enter choices: ";
        cin>>option;
        if(option==1)
        {
            key_length=4;
            x=16;
            break;
        }
        else if(option==2)
        {
            cout<<"Enter the key(1 to 4): ";
            cin>>key_length;
            if(key_length>5){
                cout<<"wrong value of key!!\n";
                return 1;
            }
            cout<<"Enter the X(1-16): ";
            cin>>x;
            break;
        }
        else{
            cout<<"Entered wrong choice!";
        }
    }

    int key=(int)pow(2,key_length);
    int X=(int)pow(2,x);

    fstream arr;

    if(PFR_func(key, X))
    {
        cout<<"PRF values generated successfully"<<endl;
    }
    else
    {
        cout<<"generation failed !"<<endl;
    }

    while(1)
    {

        cout<<"1.User input \n2. Computer generated input(for convenience)\n3. to exit\n";
        cout<<"Enter the choice: ";
        cin>>choice;
        
        if(choice==1)
        {
            int x_value, key_value;
            unsigned short int y_value;
        
            cout<<"enter key (from 0 and "<<key-1<<") : ";
            cin>>key_value;
            if(key_value > key-1 || key_value < 0)
            {
                cout<<"wrong key(out of range)!"<<endl;
                continue;
            }
            cout<<"enter key (0 and "<<X-1<<") : ";
            cin>>x_value;
            if(x_value > (int)(X-1) || x_value < 0)
            {
                cout<<"wrong X val(out of range)!"<<endl;
                continue;
            }

            stringstream string_stream;
            string key_no;

            string_stream<<key_value;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int i=0;i<x_value;i++)
            {
                arr>>y_value;
            }

            cout<<"Y: "<<y_value<<endl;
            

            arr.close();
        }

        else if(choice==2)
        {
            int x_value = (unsigned short int)random_number(), key_value = random_number();
            unsigned short int y_value;

            stringstream string_stream;
            string key_no;

            string_stream<<key_value;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int i=0;i<x_value;i++)
            {
                arr>>y_value;
            }

            cout<<"Y: "<<y_value<<endl;

            arr.close();
        }

        else if(choice==3)
        {
            break;
        }

        else
        {
            cout<<"wrong choice enterd!"<<endl;
        }

    }

    return 0;

}