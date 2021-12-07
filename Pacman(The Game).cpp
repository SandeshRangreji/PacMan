#include<graphics.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<fstream>

#define wall(x,y) bar(330+(x*20),50+(y*20),330+((x+1)*20),50+((y+1)*20))
#define xcoord(x)  20*x+340
#define ycoord(y)  20*y +60
#define chkblock(x,y) thegrid[(y-60)/20][(x-340)/20]

using namespace std;

class ghost;
class pac;
int pause_game(int &page,char thegrid[][29],int lives,int level,int score);

class menu
{
    public:
     int x;
     int y;
}menu_option[5];

 struct save
 {
    int lives;
    int level;
    int score;
};

class player
{
  private:
  char name[20];

  protected:
  int level;
  int score;

  public:
  int resetplayer()
  {
      level=0;
      score=0;
  }

  int retscore()
  {
      return score;
  }

  int leaderout(int i)
  {
        char scoreboard[10];

        setcolor(10);
        settextstyle(4,HORIZ_DIR,3);
        outtextxy(250-textwidth(name)/2,(i+3)*50,name);
        setcolor(11);
        itoa(score, scoreboard,10  );
        outtextxy(950-textwidth(scoreboard)/2,(i+3)*50,scoreboard);
  }

  int save_game()
  {
      player data;
      cleardevice();
      int ub;

      char ch;
      settextstyle(8,HORIZ_DIR,6);
      setcolor(14);
      outtextxy(600-textwidth("Player Details")/2,50,"Player Details");
      setcolor(14);
      settextstyle(4,HORIZ_DIR,3);
      outtextxy(200-textwidth("Enter Your Name:")/2,150,"Enter Your Name:");
      setcolor(9);
      for(int i=0;;i++)
      {
          ch=getch();

          if(ch==8 && i!=0)
          {
              i--;
              i--;
          }
          else if(ch==13)
          {
                name[i]=0;
                break;
          }
          else   if(i>=19)
          {
              i--;
              continue;
          }
          else
          {
              name[i]=ch;
          }
        name[i+1]=0;
          cleardevice();
          setcolor(14);
          settextstyle(8,HORIZ_DIR,6);
           outtextxy(600-textwidth("Player Details")/2,50,"Player Details");
            settextstyle(4,HORIZ_DIR,3);
            outtextxy(200-textwidth("Enter Your Name:")/2,150,"Enter Your Name:");
            setcolor(9);
          outtextxy(200+textwidth("Enter Your Name:")/2,150,name);
      }

      strcpy(data.name,name);
      data.level=level;
      data.score=score;

      fstream f,f1;

      f.open("Player_Data.dat",ios::in | ios::binary);
    int i=f.fail();
    f.close();

    if(i==1)
    {
        f.open("Player_Data.dat",ios::out | ios::binary);
        f.write((char*)&data,sizeof(data));
        f.close();
    }
    else
    {
        f.open("Player_Data.dat",ios::out | ios::binary |ios::in);
        f.seekp(0,ios::end);
        f.write((char*)&data,sizeof(data));
        f.close();
    }
    i=0;
    f.open("Player_Data.dat",ios::out | ios::binary |ios::in);
    player details[11], temp ;
    f.seekp(0, ios::beg);
    while(f.read((char*)&details[i], sizeof(details[i])))
    {
        i++;
    }
    f.close();
    for(int j=0; j<i; j++)
    {
       for(int k=j;k<i; k++)
       {
           if(details[j].retscore()<details[k].retscore())
           {
               temp=details[j];
               details[j]=details[k];
               details[k]=temp;
           }
       }
    }

    if(i==11)
        i--;

    f.open("Player_Data.dat", ios::binary | ios::out);

    for(int p=0; p<i; p++)
    {
        f.write((char*)&details[p],sizeof(details[p]));
    }
    f.close();

    settextstyle(8,HORIZ_DIR,6);
    setcolor(14);
    cleardevice();
    outtextxy(600-textwidth("Game Saved!!!")/2,300,"Game Saved!!!");
  }
};

class sprite
{
  protected:
  int x;
  int y;
  int dir;

  public:
    int retx()
    {
        return x;
    }

    int rety()
    {
        return y;
    }

    int retdir()
    {
        return dir;
    }
};

class pac: public player, public sprite
{
  protected:
  int pptimer;
  int pcounter;
  int ppcounter;
  int mc;
  int lives;
  char input;
  int oldscore;
  int oldlives;
  int oldlevel;

  public:
   int drawpac();
   int movepac();
   int killpac(ghost[], int&, int&, char[][29]);
   int levelup(int &);
   int eat(char[][29]);
   int changedir(char&, char[][29],int&, int& ,int&, int&, int&);
   int pacio(char &);

   int storehistory( )
   {
       oldlives=lives;
       oldscore=score;
       oldlevel=level;
   }

   int restart()
   {
       cleardevice();

       lives=3;
       resetplayer();
   }

   pac()
   {
    x=y=dir=0;
    mc=20;
    pptimer=0;
    lives=3;
    input=0;
    level=0;
    score=0;
    ppcounter=4;
   }

   pac(int x,int y,int dir)                 //mainly used to draw pacman in menu
   {
    sprite::x=x;
    sprite::y=y;
    sprite::dir=dir;
    pptimer=0;
   }

   pac(int load_life,int load_level,int load_score,int save)
   {
        oldlives=lives=load_life;
        oldlevel=level=load_level;
        oldscore=score=load_score;
   }

   int retpptimer()
   {
       return pptimer;
   }

   int resetpac()
   {
       ppcounter=0;
       pcounter=0;
       pptimer=0;
   }

   int setpac(int x, int y)
   {
       pac::x=x;
       pac::y=y;
   }

   int pelletup()
   {
       pcounter++;
   }

   int ppelletup()
   {
       ppcounter++;
   }

   int checklevel()
   {
       if(pcounter==0 && ppcounter==0)
          return 1;
       else
          return 0;
   }
};

class ghost: public sprite
{

  int color;
  int gdep;

  public:
    int drawghost(pac&);
    int moveghost(pac&);
    int changedir(pac&, char[][29], int&, int&, int&, int&);
    int think(pac&, char[][29]);

    int setghost(int x, int y)
    {
        dir=0;
        ghost::x=x;
        ghost::y=y;
        gdep=30-color*10;

    }

    int setghostcolor(int i)
    {
        color=i;
    }

    ghost()
    {
        x=y=dir=0;
        color=20;
        gdep=0;
    }
    ghost(int x,int y,int dir,int clr)
    {
        sprite::x=x;
        sprite::y=y;
        sprite::dir=dir;
        color=clr;
        gdep=0;
    }

    int retcolor()
    {
        return color;
    }
} ;

int ghost::think(pac &pacman, char thegrid[][29])
{
    int turn;
    int prev=dir;

    if(color==2 || color==3 || rand()%5==0)
    {
        while(1)
        {
        turn=rand()%4;
        dir=turn-1;
        if(dir==0)
            dir=-2;
        if((dir==1 && chkblock(x,y-20)!='w'
            ||dir==-1 && chkblock(x,y+20)!='w'
            ||dir==2 && chkblock(x+20,y)!='w'
            ||dir==-2 && chkblock(x-20,y)!='w')&& dir!=-prev )
                break;
        }
    }

    else if(color==1)
    {

        if(pacman.retpptimer()==0)
        {

            if(pacman.retx()>x && chkblock(x+20,y)!='w'&& prev!=-2)
                dir=2;
            else if(pacman.retx()<x && chkblock(x-20,y)!='w'&& prev!=2)
                dir=-2;
            else if(pacman.rety()>y && chkblock(x,y+20)!='w'&& prev!=1)
                dir=-1;
            else if(pacman.rety()<y && chkblock(x,y-20)!='w'&& prev!=-1)
                dir=1;
            else
                while(1)
                {
                turn=rand()%4;
                dir=turn-1;
                if(dir==0)
                    dir=-2;
                if((dir==1 && chkblock(x,y-20)!='w'
                    ||dir==-1 && chkblock(x,y+20)!='w'
                    ||dir==2 && chkblock(x+20,y)!='w'
                    ||dir==-2 && chkblock(x-20,y)!='w')&& dir!=-prev )
                        break;
                }
        }

        else
        {
          if(pacman.retx()<x && chkblock(x+20,y)!='w'&& prev!=-2)
                dir=2;
            else if(pacman.retx()>x && chkblock(x-20,y)!='w'&& prev!=2)
                dir=-2;
            else if(pacman.rety()<y && chkblock(x,y+20)!='w'&& prev!=1)
                dir=-1;
            else if(pacman.rety()>y && chkblock(x,y-20)!='w'&& prev!=-1)
                dir=1;
            else
                while(1)
                {
                turn=rand()%4;
                dir=turn-1;
                if(dir==0)
                    dir=-2;
                if((dir==1 && chkblock(x,y-20)!='w'
                    ||dir==-1 && chkblock(x,y+20)!='w'
                    ||dir==2 && chkblock(x+20,y)!='w'
                    ||dir==-2 && chkblock(x-20,y)!='w')&& dir!=-prev )
                        break;
                }
        }
    }

    else if(color==0)
    {
        if(pacman.retpptimer()==0)
        {
            if(pacman.rety()>y && chkblock(x,y+20)!='w'&& prev!=1)
                dir=-1;
            else if(pacman.rety()<y && chkblock(x,y-20)!='w'&& prev!=-1)
                dir=1;
            else if(pacman.retx()>x && chkblock(x+20,y)!='w'&& prev!=-2)
                dir=2;
            else if(pacman.retx()<x && chkblock(x-20,y)!='w'&& prev!=2)
                dir=-2;
            else
                while(1)
                {
                    turn=rand()%4;
                    dir=turn-1;
                    if(dir==0)
                        dir=-2;
                    if((dir==1 && chkblock(x,y-20)!='w'
                        ||dir==-1 && chkblock(x,y+20)!='w'
                        ||dir==2 && chkblock(x+20,y)!='w'
                        ||dir==-2 && chkblock(x-20,y)!='w')&& dir!=-prev )
                            break;
                }
        }

        else
        {
            if(pacman.retx()<x && chkblock(x+20,y)!='w'&& prev!=-2)
                dir=2;
            else if(pacman.retx()>x && chkblock(x-20,y)!='w'&& prev!=2)
                dir=-2;
            else if(pacman.rety()<y && chkblock(x,y+20)!='w'&& prev!=1)
                dir=-1;
            else if(pacman.rety()>y && chkblock(x,y-20)!='w'&& prev!=-1)
                dir=1;
            else
                while(1)
                {
                turn=rand()%4;
                dir=turn-1;
                if(dir==0)
                    dir=-2;
                if((dir==1 && chkblock(x,y-20)!='w'
                    ||dir==-1 && chkblock(x,y+20)!='w'
                    ||dir==2 && chkblock(x+20,y)!='w'
                    ||dir==-2 && chkblock(x-20,y)!='w')&& dir!=-prev )
                        break;
        }
      }
   }
}

int pac::pacio(char &input)
{
    char scoreboard[10];
        outtextxy(10,80,"SCORE:");                     //prints the score
        itoa(score,scoreboard,10);
        outtextxy(170,80,scoreboard);

        outtextxy(900,80,"Lives:");

        int tempx,tempy;                                            //coordinates of the pacmen to show lives
        tempx=920 + textwidth("Lives:");
        tempy=80 + textheight("Lives:")/2;

        for(int i=1;i<=lives;i++)                                   //draws pacmen according to number of lives
        {

            int pointst[8];                      //points for the pacmen counting the lives.

            pointst[0]=tempx-2; pointst[1]=tempy; pointst[6]=tempx-2; pointst[7]=tempy;
            pointst[2]=tempx+13; pointst[3]=tempy+6; pointst[4]=tempx+13; pointst[5]=tempy-6;
            setcolor(14);
            setcolor(14);
            setfillstyle(1,14);                            //sets fill color to yellow
            fillellipse(tempx,tempy,10,10);
            setcolor(0);                                  //sets outline color to yellow
            setfillstyle(1,0);                            //sets the fill color to yellow
            fillpoly(4,pointst);

            tempx+=40;                                     //goes to the next life-showing pacman
        }

        if(kbhit())
        {
            input=getch();            //gets the direction of pacman
        }
}

int pac::changedir(char &input, char thegrid[][29],int &page, int &portalpx, int &portalpy, int &portalqx, int &portalqy)
{
    switch(input)                          //checks if given input is valid. then changes pacman's directions
            {
                case 'w': case 'W':
                    if(chkblock(x,y-20)!='w')
                        dir=1;
                    break;

                case 's': case 'S':
                    if(chkblock(x,y+20)!='w' && chkblock(x,y+20)!='=')
                        dir = -1;
                    break;

                case 'a': case 'A':
                    if(chkblock(x-20,y)!='w')
                        dir=-2;
                    break;

                case 'd': case 'D':
                    if(chkblock(x+20,y)!='w')
                        dir=2;
                    break;

                case 'p': case 'P':
                    pause_game(page,thegrid,lives,oldlevel,oldscore);
                    input=0;

                    break;

                     default:
                    break;
            }

             if(chkblock(x,y)=='p' && dir==2)
            {
                x=portalqx;
                y=portalqy;
            }

             if(chkblock(x,y)=='q' && dir==-2)
            {
                x=portalpx;
                y=portalpy;
            }

            switch(dir)                                     //checks for wall in front of pacman. stops him if there is a wall
            {
                case 1:
                    if(chkblock(x,y-20)=='w')
                        dir = 0;
                    break;

                case -1:
                    if(chkblock(x,y+20)=='w')
                        dir = 0;
                    break;

                case 2:
                    if(chkblock(x+20,y)=='w')
                        dir = 0;
                    break;

                case -2:
                    if(chkblock(x-20,y)=='w')
                        dir = 0;
                    break;
            }

            if(pptimer>0)                            //reduces the power pellet timer if it is active
                    pptimer--;
}

int ghost::changedir(pac &pacman, char thegrid[][29], int &portalpx, int &portalpy, int &portalqx, int &portalqy)
{
    if(gdep==0)
    {
        if(color==0 || color==1)
            dir=2;
        else if(color==2 || color==3)
            dir=-2;
    }

   if(gdep>=0)
      gdep--;

    switch(chkblock(x,y))
    {
      case ' ': case '.': case '*':
         break;

      case 'a': case 'A':
        dir++;
        break;

      case 'b': case 'B':
        dir-=3;
        break;

      case 'c': case 'C':
        dir+=3;
        break;

      case 'd': case 'D':
        dir--;
        break;

      case 'h': case 'H':
        think(pacman, thegrid);
        break;

      case 'u':
            if(dir==1)
                dir=-2;
                break;

      case 'v':
            if(dir==1)
                dir=2;
                break;
      case 'p':
            x=portalqx;
            y=portalqy;
            break;

      case 'q':
            x=portalpx;
            y=portalpy;
            break;
    }
}

int pac::eat(char thegrid[][29])
{
    if(chkblock(x,y)=='.' )                //if pacman is in a pellet block
    {
        score+=10;                               //updates score for eating pellets
        pcounter--;
        chkblock(x,y)=' ';             // makes pacman eat the pellets
    }

     else if(isupper(chkblock(x,y)))
     {
       score+=10;                               //updates score for eating pellets
        pcounter--;
        chkblock(x,y)=tolower(chkblock(x,y));
     }

    else if(chkblock(x,y)=='*')             //if pacman is in a power pellet block
    {
        score+=20;
        if(level<34)                            //to prevent negative power pellet duration
            pptimer=70-2*level;                 //the duration of the power pellet decreases as the level increases
        ppcounter--;
        chkblock(x,y)=' ';             // makes pacman eat the pellets
    }
}

int pac::levelup(int &page)
   {
       char levelboard[20];
       level++;

       itoa(level,levelboard,10);

        setactivepage(page);
        cleardevice();
        setcolor(12);
        setfillstyle(1,12);
        settextstyle(10,HORIZ_DIR,6);
        outtextxy(600-textwidth("level ")/2,350-textheight("level ")/2,"level ");
        outtextxy(600+textwidth("level ")/2,350-textheight("level ")/2, levelboard);      //prints the level

       setvisualpage(page);
       delay(3000);
   }

int pac::drawpac()
{
    int points[8];                                                                      //points for pacman's mouth

    switch(dir)                                                                     //makes pacman's mouth point the right way
    {
      case 2:
          points[0]=x-2; points[1]=y; points[6]=x-2; points[7]=y;
          points[2]=x+13; points[3]=y+6; points[4]=x+13; points[5]=y-6;
          break;
      case 1:
           points[0]=x; points[1]=y+2; points[6]=x; points[7]=y+2;
          points[2]=x-5; points[3]=y-13; points[4]=x+6; points[5]=y-13;
          break;
      case -1:
          points[0]=x; points[1]=y-2; points[6]=x; points[7]=y-2;
          points[2]=x-6; points[3]=y+13; points[4]=x+6; points[5]=y+13;
          break;
      case -2:
          points[0]=x+2; points[1]=y; points[6]=x+2; points[7]=y;
          points[2]=x-13; points[3]=y+6; points[4]=x-13; points[5]=y-6;
          break;

      default:
           points[0]=0; points[1]=0; points[6]=0; points[7]=0;
          points[2]=0; points[3]=0; points[4]=0; points[5]=0;
    }

    setcolor(14);                                  //sets color outline to yellow
    setfillstyle(1,14);                            //sets fill color to yellow
    fillellipse(x,y,10,10);                //draws pacman's body

    mc++;                                           //mouth counter

    if(mc>20)                                       //only draws the mouth half the time to create biting
    {
      setcolor(0);                                  //sets outline color to yellow
      setfillstyle(1,0);                            //sets the fill color to yellow
      fillpoly(4,points);                           //draws pacman's mouth
      if(mc==40)
        mc=0;                                           //resets the mouth counter
    }
}

int pac::movepac()
{
   switch(dir)                                 //to move in the correct direction
    {
      case 1:
          y--;
          break;
      case -1:
          y++;
          break;
      case -2:
          x--;
          break;
      case 2:
          x++;
          break;
    }

    drawpac();
}

int ghost::drawghost(pac &pacman)
{
   if(pacman.retpptimer()==0)
   {
      switch(color)              // to set the correct color for the ghost.
      {
            case 0:
             setcolor(12);
             setfillstyle(1,12);
             break;
            case 1:
             setcolor(11);
             setfillstyle(1,11);
             break;
            case 2:
             setcolor(13);
             setfillstyle(1,13);
             break;
            case 3:
             setcolor(10);
             setfillstyle(1,10);
             break;
     }
   }
   if((pacman.retpptimer()>2 &&pacman.retpptimer()<=4)|| (pacman.retpptimer()>6 && pacman.retpptimer()<=8) || (pacman.retpptimer()>10 && pacman.retpptimer()<=12) || (pacman.retpptimer()>14 && pacman.retpptimer()<=16) || (pacman.retpptimer()>18 && pacman.retpptimer()<=20))// for flashing when the pptimer aproaches 0
   {
       setcolor(WHITE);
       setfillstyle(1,WHITE);
   }
   else if(pacman.retpptimer()>0)   // purple color when the ghosts are eatable
   {
       setcolor(9);
       setfillstyle(1,9);
   }

    fillellipse(x,y-3,7,7);                             //draws the ghosts head
    bar(x-7,y-3,x+7,y+7);            //draws the ghosts body

    int points[16];
    points[0]=x-7,points[1]=y+7,points[2]=x-7,points[3]=y+9;   //points for the zigzag on the bottom of the ghost.
    points[4]=x-3,points[5]=y+7,points[6]=x-1,points[7]=y+9;
    points[8]=x+3,points[9]=y+7,points[10]=x+6,points[11]=y+9;
    points[12]=x+6,points[13]=y+7,points[14]=x-7,points[15]=y+7;

    fillpoly(8,points);                 // draws the zig zag

    setfillstyle(1,15);
    fillellipse(x-3,y-4,4,4);                 //draws the ghost's eyes
    fillellipse(x+3,y-4,4,4);
    setcolor(15);
    setfillstyle(1,0);
    switch(dir)                                          //makes the ghost look in the direction it is going
  {
    case 1:
      fillellipse(x-3,y-5,2,2);
      fillellipse(x+3,y-5,2,2);
     break;
  case -1:
      fillellipse(x-3,y-3,2,2);
      fillellipse(x+3,y-3,2,2);
    break;
  case 2:
      fillellipse(x-2,y-4,2,2);
      fillellipse(x+4,y-4,2,2);
      break;
  case -2:
       fillellipse(x-4,y-4,2,2);
       fillellipse(x+2,y-4,2,2);
       break;
  }
}

int ghost::moveghost(pac &pacman)
{
   switch(dir)                                 //to move in the correct direction
    {
      case 1:
          y--;
          break;
      case -1:
          y++;
          break;
      case -2:
          x--;
          break;
      case 2:
          x++;
          break;
    }

    drawghost(pacman);
}

int pac::killpac(ghost ghosts[],int &page,int &gameover, char thegrid[][29])
{

    char levelboard[20], scoreboard[20];

  for(int i=0; i<4; i++)
    {

        setcolor(BLACK);
        setfillstyle(1,BLACK);

        if((abs(x-ghosts[i].retx())<20 && abs(y-ghosts[i].rety())<20) || (abs(x-ghosts[i].retx())<21 && abs(y-ghosts[i].rety())<21 && dir==-ghosts[i].retdir()) )
        {
           if(pptimer==0)
           {
            lives--;
                for(int j=1;j<=1000;j++)
                {
                        fillellipse(x,y,j,j);
                        if(j<=20)
                            delay(50);
                        setvisualpage(1-page);
                }

                setcolor(12);
                outtextxy(600-textwidth("WASTED!!!")/2,350-textheight("WASTED!!!")/2,"WASTED!!!");
                delay(2000);

                if(lives==0)
               {
                    cleardevice();
                    gameover=1;
                    setcolor(RED);
                    setfillstyle(1,RED);
                    settextstyle(10,HORIZ_DIR,4);
                    itoa(level, levelboard, 10);
                    itoa(score, scoreboard, 10);
                    outtextxy(600-textwidth("GAME OVER")/2,200,"GAME OVER");
                    outtextxy(600-textwidth("SCORE: ")/2-20,300,"SCORE: ");
                    outtextxy(600+textwidth("SCORE: ")/2-20,300,scoreboard);
                    outtextxy(600-textwidth("LEVEL: ")/2-20,400,"LEVEL: ");
                    outtextxy(600+textwidth("LEVEL: ")/2-20,400,levelboard);
                    getch();
                    save_game();

                    getch();
                    restart();
               }

                for(int i=0; i<=32; i++)
                {
                        for(int j=0;j<=29;j++)
                        {
                            switch(thegrid[i][j])
                            {
                                case 'o':
                                setpac(340+(j*20),60+(i*20));
                                break;

                                case  '1':
                                ghosts[0].setghost(340+(j*20),60+(i*20));
                                break;

                                case  '2':
                                ghosts[1].setghost(340+(j*20),60+(i*20));
                                break;

                                case  '3':
                                ghosts[2].setghost(340+(j*20),60+(i*20));
                                break;

                                case  '4':
                                ghosts[3].setghost(340+(j*20),60+(i*20));
                                break;
                        }
                    }
                }

            }

                if(pptimer>0)
                {
                    char pos=ghosts[i].retcolor()+49;
                    setvisualpage(1-page);
                    for(int j=0;j<=13; j++)
                    {
                        fillellipse(ghosts[i].retx(),ghosts[i].rety(),j,j);
                        delay(50);
                    }
                    delay(50);
                    settextstyle(0,0,1);
                    setcolor(14);
                    outtextxy(ghosts[i].retx()-textwidth("200")/2,ghosts[i].rety()-textheight("200")/2,"200");
                    delay(50);

                    score+=200;

                    for(int k=0; k<=32; k++)
                    {
                        for(int j=0;j<=29;j++)
                        {
                            if(pos==thegrid[k][j])
                            {
                                ghosts[i].setghost(340+(j*20),60+(k*20));
                            }
                        }
                    }
            }
        }
    }
}

int drawgrid(char thegrid[][29])
{
     setcolor(9);
    setfillstyle(1,9);

    for(int i=0;i<=30;i++)
    {

        for(int j=0;j<=27;j++)
        {
            switch(thegrid[i][j])
            {
                case '.': case 'A': case 'B': case 'C': case 'D': case 'H':                                                //this part handles the pellets
                    setfillstyle(1,14);
                    bar(338+(j*20),58+(i*20),342+(j*20),62+(i*20));
                    break;

                case '*':                                                 //this part handles the power pellets
                    setfillstyle(1,14);
                    bar(335+(j*20),55+(i*20),345+(j*20),65+(i*20));
                    break;

                case  'w':
                    setcolor(9);
                    setfillstyle(1,9);
                    wall(j,i);

                    break;

                case 'p': case 'q':
                     setfillstyle(11,10);
                     wall(j,i);
                     break;

                case '=':
                      setfillstyle(2,12);
                      wall(j,i);
                      break;
            }
        }
    }
}


int instruct()
{
    pac pacman;
    cleardevice();
    setcolor(8);
    settextstyle(10,HORIZ_DIR,8);

    outtextxy(600-(textwidth("CONTROLS"))/2,0,"CONTROLS");

    setcolor(9);
    settextstyle(8,HORIZ_DIR,3);

    outtextxy(600-(textwidth("Move up    : w"))/2,100,"Move up    : w");
    outtextxy(600-(textwidth("Move down  : s"))/2,150,"Move down  : s");
    outtextxy(600-(textwidth("Move right : d"))/2,200,"Move right : d");
    outtextxy(600-(textwidth("Move left  : a"))/2,250,"Move left  : a");
    outtextxy(600-(textwidth("Pause Game : p"))/2,550,"Pause Game : p");
    outtextxy(600-(textwidth("Avoid the Ghosts!!!"))/2,350,"Avoid the ghosts!!!");

    ghost(552,400,1,0).drawghost(pacman);
    ghost(572,400,-1,1).drawghost(pacman);
    ghost(592,400,2,2).drawghost(pacman);
    ghost(612,400,-2,3).drawghost(pacman);

    setcolor(9);
    outtextxy(600-(textwidth("Collect the Pellets!!!"))/2,450,"Collect the pellets!!!");

    pac(552,500,2).drawpac();

    setfillstyle(1,14);
    for(int i=562,j=500;i<=632;i+=20)
    {
        bar(i+8,j+2,i+12,j-2);                      //draws pellets
    }

    getch();
    cleardevice();
}

int pac_menu(int x,int y,menu menu_option[],int m,int &erase1x,int &erase1y,int &erase2x,int &erase2y)
{
    char name[5][15] ={"NEW GAME","INSTRUCTIONS","LOAD GAME","LEADERBOARDS","EXIT"};
    int dir =2;
    pac(x,y,dir).drawpac();

    dir=-2;
    x=menu_option[m].x +(textwidth(name[m])) + 20;
    pac(x,y,dir).drawpac();

    erase1x=(menu_option[m].x - 40);                    //erases pacman
    erase1y=menu_option[m].y + textheight("PLAY")/2;
    erase2x=menu_option[m].x +(textwidth(name[m])) + 20;
    erase2y=menu_option[m].y + textheight("PLAY")/2;
}

int erasepac(int erase1x,int erase1y,int erase2x,int erase2y)
{
    setfillstyle(1,BLACK);
    bar(erase1x-10,erase1y-10,erase1x+10,erase1y+10);           //coordinates of block to erase left pacman in menu
    bar(erase2x-10,erase2y-10,erase2x+10,erase2y+10);           //coordinates of block to erase right pacman in menu
}

int gamemove(pac &pacman, ghost ghosts[], char &input, int &page, char thegrid[][29])
{
   int i=20;                          //20 pixels=1 block

   while(i)
    {
        setactivepage(page);          //double buffer
        setvisualpage(1-page);        //double buffer
        cleardevice();

        setcolor(WHITE);
        settextstyle(3,HORIZ_DIR,4);

        pacman.pacio(input);

        pacman.movepac();
        drawgrid(thegrid);
        ghosts[0].moveghost(pacman);
        ghosts[1].moveghost(pacman);
        ghosts[2].moveghost(pacman);
        ghosts[3].moveghost(pacman);

        if(page==1)
        delay(1);
        page=1-page;                            //double buffer

        i--;
    }
}

int load_game(pac &pacman)
{
    save game;

    fstream f;
    f.open("saved_game.dat",ios::binary | ios::in);
    f.read((char*)&game,sizeof(game));

    pac object=pac(game.lives,game.level,game.score,0);
    pacman=object;
}

int playgame(pac &pacman,ghost ghosts[], int &page)
{
    fstream reader;
    char thegrid[32][29];
    struct level
    {
        char a[32][29];
    }grid;
    int gameover=0, portalpx,portalpy, portalqx, portalqy, gridsize=sizeof(grid) ;char input=0;

     while(1)
     {
         delay(1000);
        if(gameover==1)
            break;

        cleardevice();

        pacman.levelup(page);
        pacman.resetpac();

        pacman.storehistory();

        reader.open("level.dat", ios::in | ios::binary);

			int random=rand()%5;
			reader.seekp(random*gridsize,ios::beg);

        reader.read((char*)&grid,sizeof(grid));

        reader.close();

        for(int i=0; i<32; i++)
        {
            strcpy(thegrid[i],grid.a[i]);
        }

        setvisualpage(page);

        for(int i=0; i<31; i++)
        {
            for(int j=0;j<29;j++)
            {
                switch(thegrid[i][j])
                {
                   case 'o':
                       pacman.setpac(340+(j*20),60+(i*20));
                       break;

                   case  '1':
                       ghosts[0].setghost(340+(j*20),60+(i*20));
                       break;

                   case  '2':
                       ghosts[1].setghost(340+(j*20),60+(i*20));
                       break;

                   case  '3':
                       ghosts[2].setghost(340+(j*20),60+(i*20));
                       break;

                   case  '4':
                       ghosts[3].setghost(340+(j*20),60+(i*20));
                       break;

                   case  '.': case 'H': case 'A': case 'B': case 'C': case 'D':
                       pacman.pelletup();
                       break;

                   case  '*':
                       pacman.ppelletup();
                       break;

                   case 'p':
                       portalpx=xcoord(j);
                       portalpy=ycoord(i);
                       break;

                   case 'q':
                       portalqx=xcoord(j);
                       portalqy=ycoord(i);
                       break;
                }
            }
        }

        while(1)
        {
            pacman.killpac(ghosts, page, gameover, thegrid);

            if(gameover==1)
                break;

            pacman.eat(thegrid);
            pacman.changedir(input, thegrid,page, portalpx, portalpy , portalqx, portalqy);

            for(int i=0; i<4; i++)
               ghosts[i].changedir(pacman, thegrid, portalpx, portalpy , portalqx, portalqy);

            gamemove(pacman, ghosts, input, page, thegrid);

            if(pacman.checklevel())
                break;
        }
     }
}

int save_progress(int lives,int level,int score)
{
       save game;
        game.lives=lives;
        game.level=level;
        game.score=score;

        fstream f;
        f.open("saved_game.dat",ios::binary | ios::out);
        f.write((char*)&game,sizeof(game));
        f.close();
}

int pause_game(int &page,char thegrid[][29],int lives,int level,int score)
{
    char ch;
    cleardevice();

    setvisualpage(1-page);
    int act=16002;
    int resume=0;

    while(!resume)
    {
        settextstyle(8,HORIZ_DIR,9);
        setcolor(14);
        outtextxy(600-(textwidth("PAUSE MENU"))/2,50, "PAUSE MENU");
        settextstyle(10,HORIZ_DIR,5);
        setcolor(12);

        if(act%3==0)
            setcolor(10);
        outtextxy(600-(textwidth("RESUME")/2),200,"RESUME");
        if(act%3==0)
            setcolor(12);
        if(act%3==1)
            setcolor(10);
        outtextxy(600-(textwidth("SAVE AND CONTINUE"))/2,300,"SAVE AND CONTINUE");
        if(act%3==1)
            setcolor(12);
        if(act%3==2)
            setcolor(10);
        outtextxy(600-(textwidth("EXIT"))/2,400,"EXIT");

        ch=getch();

        switch(ch)
        {
                case 's':case 'S':
                act++;
                break;

                case 'w':case'W':
                act--;
                break;

                case ' ':
                {
                    if(act%3==0)
                    {
                        resume=1;
                    }
                    else if(act%3==1)
                    {
                        save_progress(lives,level-1,score);
                        resume=1;
                    }
                    else if(act%3==2)
                    {
                        closegraph();
                    }
                }
        }

        setvisualpage(page-1);
    }
}

int leaderboards()
{
    fstream f;
    player temp;
    int i=0;

    cleardevice();
    settextstyle(4,HORIZ_DIR,5);
    setcolor(12);
    outtextxy(600-textwidth("LEADERBOARDS")/2,30,"LEADERBOARDS");
    setcolor(10);
    settextstyle(4,HORIZ_DIR,4);
    outtextxy(250-textwidth("NAME")/2,100,"NAME");
     setcolor(11);
    outtextxy(950-textwidth("SCORE")/2,100,"SCORE");
    setcolor(9);

    f.open("Player_Data.dat", ios::in | ios:: binary);

    while(f.read((char*)&temp, sizeof(temp)))
    {
        temp.leaderout(i);
        i++;
    }
    getch();
    f.close();
}

int main()
{
    pac pacman;
    ghost ghosts[4];
    for(int i=0; i<4;i++)
         ghosts[i].setghostcolor(i);
         srand(time(NULL));

    int page=0;
    int m_no;                 //indicates menu option
    menu_option[0].x=510;      menu_option[0].y=200;              //coordinates of menu options
    menu_option[1].x=460;      menu_option[1].y=300;
    menu_option[2].x=500;      menu_option[2].y=400;
    menu_option[3].x=450;      menu_option[3].y=500;
    menu_option[4].x=560;      menu_option[4].y=600;
    int menu_pac_x,menu_pac_y;
    menu_pac_x=menu_pac_y=0;
    int erase1x,erase1y,erase2x,erase2y;               //erasing pacman in menu

   char ch;
    int act=300;

    initwindow(1200,700);

    m_no=0;

    setcolor(8);
    settextstyle(10,HORIZ_DIR,8);
    outtextxy(600-(textwidth("CONTROLS"))/2,100,"CONTROLS");
    setcolor(9);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(600-(textwidth("Move up    : w"))/2,200,"Move up    : w");
    outtextxy(600-(textwidth("Move down  : s"))/2,250,"Move down  : s");
    outtextxy(625-(textwidth("Select     : space"))/2,300,"Select     : space");

    getch();

    cleardevice();

    settextstyle(10,HORIZ_DIR,5);
    menu_pac_x =menu_option[m_no].x - 40;    menu_pac_y=menu_option[m_no].y + textheight("NEW GAME")/2 ;  //pacman coordinates for menu

    pac_menu(menu_pac_x,menu_pac_y,menu_option,m_no,erase1x,erase1y,erase2x,erase2y);

    while(1)
    {
        settextstyle(8,HORIZ_DIR,9);
        setcolor(14);
        outtextxy(600-(textwidth("PACMAN"))/2,50, "PACMAN");
        settextstyle(10,HORIZ_DIR,5);
        setcolor(12);

        if(act%5==0)
            setcolor(10);
        outtextxy(600-(textwidth("NEW GAME")/2),200,"NEW GAME");
        if(act%5==0)
            setcolor(12);
        if(act%5==1)
            setcolor(10);
        outtextxy(600-(textwidth("INSTRUCTIONS"))/2,300,"INSTRUCTIONS");
        if(act%5==1)
            setcolor(12);
        if(act%5==2)
            setcolor(10);
        outtextxy(600-(textwidth("LOAD GAME"))/2,400,"LOAD GAME");
        if(act%5==2)
            setcolor(12);
        if(act%5==3)
            setcolor(10);
        outtextxy(600-(textwidth("LEADERBOARDS"))/2,500,"LEADERBOARDS");
        if(act%5==3)
            setcolor(12);
        if(act%5==4)
            setcolor(10);
        outtextxy(600-(textwidth("EXIT"))/2,600,"EXIT");
        if(act%5==4)
            setcolor(12);

        ch=getch();

        switch(ch)
        {
            case 'S':case 's':
            {
                erasepac(erase1x,erase1y,erase2x,erase2y);         //erasing previous option's pacman pointer
                m_no++;                //changing option number for drawing pacman
                if(m_no==5)            //reseting option number while going from option 5 to option 1
                    m_no=0;
                menu_pac_x=(menu_option[m_no].x - 40);
                menu_pac_y=menu_option[m_no].y + textheight("PLAY")/2;
                pac_menu(menu_pac_x,menu_pac_y,menu_option,m_no,erase1x,erase1y,erase2x,erase2y);          //drawing pacman
                act++;
                break;
            }

            case 'w':case 'W':
             {
                erasepac(erase1x,erase1y,erase2x,erase2y);
                m_no--;
                if(m_no==-1)
                    m_no=4;
                menu_pac_x=(menu_option[m_no].x - 40);
                menu_pac_y=menu_option[m_no].y + textheight("PLAY")/2;
                pac_menu(menu_pac_x,menu_pac_y,menu_option,m_no,erase1x,erase1y,erase2x,erase2y);          //drawing pacman
                act--;
                break;
            }

            case ' ':
            {
                if(act%5==0)
                {
                    playgame(pacman, ghosts, page);
                    cleardevice();

                    setvisualpage(1-page);
                }
                if(act%5==1)
                {
                    instruct();
                }
                if(act%5==2)
                {
                    load_game(pacman);
                    playgame(pacman, ghosts, page);
                }
                if(act%5==3)
                {
                    leaderboards();
                    cleardevice();
                }
                if(act%5==4)
                closegraph();

                break;
            }
        }
    }
}

