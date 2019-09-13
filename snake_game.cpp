#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<string.h>
using namespace std;
bool gameover;
const int width=20;
const int height=20;
 int n;
enum edirection{STOP=0,LEFT,RIGHT,UP,DOWN};
edirection dir;
class player_info
{
    public:
            int points;
            char naam[20];    
};
class snake_game
{
    protected:
    int x,y,fruitx,fruity,score;
    int tailx[100],taily[100];
    int ntail;
    char name[20];
    player_info p[10];
   
    public:
            void setup();
            void draw();
            void input();
            void logic();
            void read_high_score();
};
class menu:public snake_game
{
    char choice;
    
    public:
            int main_menu();
            int help();
            void high_score();
            
};
void snake_game::read_high_score()
{
    ifstream fin("score.txt");
    if(fin.is_open())
    {
        
        fin>>n;
        for(int i=0;i<n;i++)
        {
            fin>>p[i].naam;
            fin>>p[i].points;
        }
    }
}
void menu::high_score()
{
    cout<<"HIGH SCORES ARE";
    for(int i=n-1;i>=0;i--)
    {
        cout<<endl;
        cout<<(n-i)<<" "<<p[i].naam<<"\t"<<p[i].points;
    }
    cout<<endl;
    system("pause");
}
int menu::main_menu()
{
    read_high_score();
    while(1)
    {
        system("cls");
        cout<<"\n"<<"ENTER 1 FOR NEW GAME : "
        <<"\n"<<"ENTER 2 FOR HELP : "
        <<"\n"<<"ENTER 3 FOR HIGH SCORES : "
        <<"\n"<<"ENTER 4 FOR TO EXIT : "<<endl;
        fflush(stdin);
        cin>>choice;
        fflush(stdin);
        switch(choice)
        {
            case '1':
                {
                
                    setup();
                    while(!gameover)
                    {
                        draw();
                        input();
                        logic();
                        Sleep(15);
                    }
                    cout<<"NAME : "<<name<<" "<<"SCORE : "<<score;
                    if(n==10)
                    {
                        if(p[0].points<score)
                        {
                            strcpy(p[0].naam,name);
                            p[0].points=score;
                        }
                    }
                    else
                    {
                        strcpy(p[n].naam,name);
                        p[n].points=score;
                        n++;
                    }
                    for(int i=1;i<n;i++)
                    {
                        for(int j=0;j<n-i;j++)
                        {
                            if(p[j].points>p[j+1].points)
                            {
                                player_info tmp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=tmp;
                            }
                        }
                    }
                    ofstream outfile;
                    outfile.open("score.txt");
                    outfile<<n<<endl;
                    for(int i=0;i<n;i++)
                    {
                    
                        outfile<<p[i].naam<<"\t";
                        outfile<<p[i].points<<"\n";
                    }
                    outfile.close();
                    cout<<endl;
                    system("pause");
                    break;
                }
            case '2':
                if(help())
                    break;
                else
                    break;
            case '3':
                high_score();
                break;
            case '4':
                return 1;
            default:cout<<endl<<"YOU HAVE ENTERED WRONG OPTION "<<endl;
                    system("pause");
                    continue;
        }
    }
}
int menu::help()
{
    cout<<endl<<"PRESS w TO MOVE UP"
        <<endl<<"PRESS s TO MOVE DOWN"
        <<endl<<"PRESS a TO MOVE LEFT"
        <<endl<<"PRESS d TO MOVE RIGHT"
        <<endl<<"PRESS m TO QUIT"
        <<endl<<"PRESS p to pause"
        <<endl<<"TRY NOT TO EAT YOUR OWN TAIL"<<endl;
    cout<<"ENTER ANY INTEGER EXCEPT 0 TO RETURN : ";
    int retrn;
    cin>>retrn; 
} 
void snake_game::setup()
{
    gameover=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    ntail=0;
    
    fruitx=rand()%width;
    fruity=rand()%height;
    cout<<"ENTER PLAYER NAME : ";
    cin.getline(name,20);
    score=0;
    read_high_score();
}
void snake_game::draw()
{
    system("cls");
    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";
            if(i==y&&j==x)
                cout<<"O";
            else if(i==fruity&&j==fruitx)
                cout<<"F";
            else
            {
                bool print=false;
                for(int k=0;k<ntail;k++)
                {
                    
                    if(tailx[k]==j&&taily[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                    
                }
                if(!print)
                        cout<<" ";
            }
            if(j==width-1)
                cout<<"#";
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"NAME : "<<name<<endl;
    cout<<"SCORE : "<<score<<endl;
}
void snake_game::input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                if(dir!=RIGHT)
                    dir=LEFT;
                break;
            case 'd':
                if(dir!=LEFT) 
                  dir=RIGHT;
                break;
            case 'w':
                if(dir!=DOWN) 
                    dir=UP;
                break;
            case 's':
                if(dir!=UP) 
                    dir=DOWN;
                break;
            case 'm':
                gameover=true;
                break;
            case 'p':
                system("pause");
                break;
        }
    }
}
void snake_game::logic()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=x;
    taily[0]=y;
    for(int i=1;i<ntail;i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    switch(dir)
        {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }
       // if(x>width||x<0||y>height||y<0)
            //   gameover=true;
        if(x>=width)x=0;
        else if(x<0)x=width-1;
        if(y>=height)y=0;
        else if(y<0)y=height-1;
        for(int i=0;i<ntail;i++)
        {
            if(tailx[i]==x&&taily[i]==y)
            {
                gameover=true;
            }
        }
        if(x==fruitx&&y==fruity)
        {
            score+=10;
            bool fruit_gen=false;
            while(!fruit_gen)
            {
                fruitx=rand()%width;
                fruity=rand()%height;
                int i;
                for(i=0;i<ntail;i++)
                {
                    if(tailx[i]==fruitx&&taily[i]==fruity)
                        break;
                }
                if(i==ntail)
                    fruit_gen=true;
                    
            }
            ntail++;
        }
}
int main()
{
    menu m;
    m.main_menu();   
    return 0;
}
