#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

//!!snake!! _____________________________________________
int gameover = 0;
int width=77;
int height=20;
int sheadx=width/2;
int sheady=height/2;
int fruitx=15;
int fruity=15;
int temp;
class highscore
 {
 public:
 int high_score;
 };
enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
edirection dir;
int score = 0;
int tailx[100];
int taily[100];
int tailsize=0;
int gametime=150;

//______________

void gameboard()
{
   for(int i =1;i<=width+2;i++)
     cout<<"#";
     cout<<endl;
	for(int t=1;t<=height-1;t++)
     {
   for(int j=1;j<=width+2;j++)
     {
	if((j==1||j==width+2)&&((t!=10&&j!=1)||(j!=(width+2)&&t!=5)))
	     cout<<"#";
	     else
	     cout<<" ";
     }
     cout<<endl;
     }
   for(int l =1;l<=width+2;l++)
     cout<<"#";

}

//__________

void draw()
{

    gotoxy(2,2);

	for(int t=1;t<=height;t++)
	{
	    for(int j=1;j<=width;j++)
	    {

		 if(j==sheadx&&t==sheady)
		    cout<<"0";
		else if(j==fruitx&&t==fruity)
		    cout<<"F";
		    else
		    {
			int print= 0;
		    for(int k=0;k<tailsize;k++)
		     if(tailx[k]==j&&taily[k]==t)
			    {
				cout<<"o";
			    print=1;
			    }
			    if(!print)
			cout<<" ";

		    }

	    }

		gotoxy(2,t+1);
	}

	gotoxy(1,t+2);
	cout<<endl<<"Score - "<<score;
	gotoxy(1,t+3);

}

//__________

void input()
{
  if(kbhit())
  {
     switch(getch())
     {
      case 'a' :
      {
	if(dir!=RIGHT||tailsize==0)
		dir = LEFT;
      }
	break;
      case 'd' :
     {
	if(dir!=LEFT||tailsize==0)
		dir = RIGHT;
     }
	break;
     case 'w' :
     {
	if(dir!=DOWN||tailsize==0)
		dir = UP;
     }
	break;
     case 's':
     {
       if(dir!=UP||tailsize==0)
		dir = DOWN;
     }
	break;
     case 'p':
	dir=STOP;
	break;
  }

  }
}

//____________

  void logic()
 {
  if(dir!=STOP)
    {
      randomize();
      int prevx=sheadx;
      int prevy=sheady;
      int tempx;
      int tempy;
    for(int i=0;i<tailsize;i++)
      {
       tempx=tailx[i];
       tempy=taily[i];
       tailx[i]=prevx;
       taily[i]=prevy;
       prevx=tempx;
       prevy=tempy;
      }
   switch(dir)
      {
	case LEFT:
		dir = LEFT;
		sheadx--;
		break;
	case RIGHT:
		dir = RIGHT;
		sheadx++;
		break;
	case UP:
		dir = UP;
		sheady--;
		break;
	case DOWN:
		dir = DOWN;
		sheady++;
		break;
      }
       if(sheadx==0||sheadx==width+1||sheady==1||sheady==height+1)
		gameover=1;
       if(sheady==6&&sheadx==0)
	       {
		 gameover=0;
		 sheadx=(width+1);
		 sheady=11;
	       }
      else if(sheadx==(width+1)&&sheady==11)
	       {
		gameover=0;
		sheady=6;
		sheadx=0;
	       }

       int grand=1;
       if(sheady==fruity&&sheadx==fruitx)
	{
	  while(grand==1)
	    {
	      fruitx=random(width-1)+2;
	      fruity=random(height-4)+2;
	      grand=0;
	       for(int k=0;k<tailsize;k++)
		if(tailx[k]==fruitx&&taily[k]==fruity)
			grand=1;
	       if(sheady==fruity&&sheadx==fruitx)
		grand=1;
		     if(grand==0)
			{
			  score+=10;
			  tailsize++;
			  if(gametime>=50)
			  gametime-=5;
			}

	    }
       }
	  for(int k=0;k<tailsize;k++)
		if(tailx[k]==sheadx&&taily[k]==sheady)
			gameover=1;
    }
 }

//________________

 void high_score()
 {
   highscore h;
    ifstream value("highscore.dat",ios::in|ios::binary);

     value.read((char*)&h,sizeof(h));
     temp=h.high_score;
     if(score>temp)
     {
     ofstream change("temp.dat",ios::out|ios::binary);
       h.high_score=score;
     change.write((char*)&h,sizeof(h));
     value.close();
     change.close();
     remove("highscore.dat");
     rename("temp.dat","highscore.dat");
	clrscr();
	gotoxy(30,13);
	 cout<<"   || gameover ||";
       gotoxy(30,15);
	 cout<<"!! New Highscore "<<h.high_score<<" !!";
     }
    else
    {
	clrscr();
	gotoxy(30,13);
	 cout<<"   || gameover ||";
	 gotoxy(30,15);
	 cout<<"   || score "<<score<<" ||";
	 gotoxy(30,16);
	 cout<<"!! Highscore "<<h.high_score<<" !!";
	 gotoxy(30,17);

    }
	getch();
 }

//______________

void main()
{

clrscr();
int tail=0,opt;
gotoxy(65,1);
cprintf("EXIT (0)");
gotoxy(35,20);
cprintf("START GAME (1)");
gotoxy(37,12);
cprintf("!! SNAKE !!");
for(int i=1;i<21;i++)
{
gotoxy(32,14);
delay(200);
for(int j=0;j<tail;j++)
{
cprintf("o");
}
cprintf("0");
tail++;
}
gotoxy(40,21);
cin>>opt;
if(opt==0)
exit(EXIT_FAILURE);
clrscr();
   gameboard();
    while(gameover==0)
    {    draw();
	input();
	logic();
	delay(gametime);
    }
    high_score();
}
//_______________________________________________________