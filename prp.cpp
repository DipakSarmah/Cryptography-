//csb20021 dipak sarmah


#include <bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>

using namespace std;


unsigned int RandInt(void) //generating random integer
{
    unsigned int randval;
    FILE *f;

    f = fopen("/dev/random", "r");
    if(f==NULL)
    {
        cout<<"can't open the dev/random file\n";
        exit(1);
    }
    fread(&randval, sizeof(randval), 1, f);
    fclose(f);

    return randval;
}

//generates the random no. 
// the key choses the file in which the random no. will be present
// the X is the random generated no. of 2bytes stored for a function
int prp_Func(int key, int X )
{
    fstream f;
    for(int i=0;i<key;i++)
    {
        vector<bool> v(X,0);

        stringstream string_stream;
        string key_no;

        string_stream<<i;
        string_stream>>key_no;
        f.open("file"+key_no+".txt", ios::out );//creating files

        if(!f.is_open())
        {
            cout<<"error can't open the file!";
            return 0;
        }

        for(int j=0;j<X;j++)
        {
            unsigned short int num = (unsigned short int)RandInt();
            if(v[num]!=0)
            {
                while(v[num % X]!=0)
                {
                    num+=RandInt();
                }
            }
            v[num]=1;
            f<<num<<endl;
        }

        f.close();
    }

    return 1;
}



int main()
{
    int key_length,x,choice,options=1; 

    cout<<"wait for some time!!"<<endl;


    while(1)
    {
        cout<<"Enter 1: Key and X (default values)\nEnter 2: User input for Key and X\n";
        cout<<"Enter choice : ";
        cin>>options;
        if(options==1)
        {
            key_length=4;
            x=16;
            break;
        }
        else if(options==2)
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
            cout<<"Your entry is wrong!!!";
        }
    }

    int key=(int)pow(2,key_length);
    int X=(int)pow(2,x);

    fstream arr;

    if(prp_Func(key, X))
    {
        cout<<"PRP values generatered successfully!"<<endl<<endl;
    }
    else
    {
        cout<<"PRP generation failed !"<<endl<<endl;
    }

    //
    cout<<"For X -> Y "<<endl;
    while(1)
    {
        cout<<"1.User input \n2. Computer generated input(for convenience)\n3. to exit\n";
        cout<<"Enter the choice: ";
        cin>>choice;
        
        //user entry
        if(choice==1)
        {
            int num_x, key_val;
            unsigned short int num_y;
        
            cout<<"enter key (from 0 and "<<key-1<<") : ";
            cin>>key_val;
            if(key_val > key-1 || key_val < 0)
            {
                cout<<"wrong key(out of range)!"<<endl;
                continue;
            }
            cout<<"enter key (0 and "<<X-1<<") : ";
            cin>>num_x;
            if(num_x > (int)(X-1) || num_x < 0)
            {
                cout<<"wrong choice of the X val!"<<endl;
                continue;
            }

            stringstream string_stream;
            string key_no;

            string_stream<<key_val;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int i=0;i<num_x;i++)
            {
                arr>>num_y;
            }

            cout<<"The random value Y: "<<num_y<<endl;
            

            arr.close();
        }

        //computer generated entry
        else if(choice==2)
        {
            int num_x = (unsigned short int)RandInt(), key_val = RandInt();
            unsigned short int num_y;

            stringstream string_stream;
            string key_no;

            string_stream<<key_val;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int i=0;i<num_x;i++)
            {
                arr>>num_y;
            }

            cout<<"The random value Y: "<<num_y<<endl;

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


    //for the generation of the actual message from the o/p i.e the reverse of the function
    cout<<endl<<endl;
    cout<<"For Y -> X "<<endl;
    while(1)
    {
        
        cout<<"1. for your choice \n2. for computer generated choice\n3. to exit\n";
        cout<<"Enter the choice: ";
        cin>>choice;
        
        //user entry
        if(choice==1)
        {
            int num_y, key_val, val;
        
            cout<<"enter value of the key between 0 and "<<key-1<<" : ";
            cin>>key_val;
            if(key_val > key-1 || key_val < 0)
            {
                cout<<"wrong choice of key!"<<endl;
                continue;
            }
            cout<<"enter value of the key between 0 and "<<X-1<<" : ";
            cin>>val;
            if(val > (int)(X-1) || val < 0)
            {
                cout<<"wrong choice of the X val!"<<endl;
                continue;
            }

            stringstream string_stream;
            string key_no;

            string_stream<<key_val;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int num_x=0; num_x<X; num_x++)
            {
                arr>>num_y;
                if(num_y == val)
                    cout<<"The random value X: "<<num_x+1<<endl;
            }
            arr.close();
        }

        //computer generated entry
        else if(choice==2)
        {
            unsigned short int val = (unsigned short int)RandInt();
            int key_val = RandInt(), num_y;

            stringstream string_stream;
            string key_no;

            string_stream<<key_val;
            string_stream>>key_no;
            arr.open("file"+key_no+".txt", ios::in );

            for(int num_x=0; num_x<X; num_x++)
            {
                arr>>num_y;
                if(num_y == (int)val)
                    cout<<"The random value X: "<<num_x+1<<endl;
            }

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