#include<iostream>
#include<queue>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<windows.h>
#include<algorithm>
#include<list>
#include<conio.h>
#include<Wincon.h>
using namespace std;
#define N 40
// try increase marginal ghost speeds after level ups
// add/increase levels.... depending upon scores. 
// add critria of lives in pac man
// consider not adding seperate fruits but rather use dots as the points for ther pac man and keep removing them from the grid
// check fruit file for number of fuits
// make all ghosts into one file and 2 lists rather than multiple lists while optimizing
class pacman
{
   public:
   char matrix[N][N];
   char input;
   bool eat;
   int ghost_count,row,col,score,speed;
   vector<int> vgr,vgc,mul,rand_check_r,rand_check_c,fruitr,fruitc,vr,vc;
   pacman(){
   	speed=200;
   	score=0;
  	row=0;
   	col=0;
   	input='a';//initialize initial position of the pac man
   	vr.push_back(38);
   	vc.push_back(38);
	ghost_count=10;     // workong for 1 ghost
   }
   void readFruit();
   void initialize();  
   void display(); 
   void initiaizeGhosts();
   void moveGhost();
   void clearScreen();
   void ghostCoords();
   void takeInputs();
   void random(int *, int *);	
   char continousMove(char );     //
   void pacMove(char ch);
};
// horizontal se mar raha ee... vertical se nai mar raha
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);

void pacman::pacMove(char ch)
{	
	int xr,xc,x,r,c;
	xr=vr.front();
	xc=vc.front();
	if(ch=='w')
	{ r=xr-1;               // up
	  c=xc; }
	
	if(ch=='s')
	{ r=xr+1;               //down
	  c=xc; }
	
	if(ch=='a')
	{ r=xr;                //left
	  c=xc-1;}
	  
	if(ch=='d')
	{ r=xr;                 //right
	  c=xc+1;}  

	if(matrix[r][c]!=(char)219 && matrix[r][c]!=(char)232)      // 219 == walls    232== ghosts
	 {	  
	 
	     if(matrix[r][c]==(char)232)     // to kill if interact  with ghosts
	     {
	        Beep(1800,50);
	     	cout<<"Game Over!!"<<endl;
	     	exit(0);
		 }
		if(matrix[r][c]==(char)234)
		 {
		    Beep(700,50);
		    score++;
		     /*if(score==10)
		     {
		     	cout<<"You Won!!";
		     	exit(0);
			 }*/
		    fruitr.erase(std::remove(fruitr.begin(), fruitr.end(), r));
		    fruitc.erase(std::remove(fruitc.begin(), fruitc.end(), c));
		 	// add code here to remove the fruit from the vector		 
		 }
		   vr.push_back(r);
		   vc.push_back(c);
		   vr.erase(vr.begin());
		   vc.erase(vc.begin());			 
		//matrix[r][c]=(char)233;                        /// poorana head position remove nahi kiya ee
	 }
	else
	{
	    Beep(900,50);
		cout<<"Game Over"<<endl;
		exit(0);
	}
}

char pacman::continousMove(char input)
{
	if(GetAsyncKeyState('W')&1)
	{
		input='w';
	}
	else if(GetAsyncKeyState('A')&1)
	{
		input='a';
	}
	else if(GetAsyncKeyState('D')&1)
	{
		input='d';
	}
	else if(GetAsyncKeyState('S')&1)
	{
		input='s';
	}
	else if(GetAsyncKeyState('P')&1)
	{		
		system("pause");
	}
	return input;
}

void pacman::takeInputs()
{    
   	  input=continousMove(input);
	 if(input=='a')
   	  {
   	    pacMove(input);  //left
	  }
	  else if(input=='d')
	  {
	  	pacMove(input);    //right
	  }
   	  else if(input=='s')
   	  {
   	     pacMove(input); 	//down
	  }
	  else if(input=='w')
	  {
	  	 pacMove(input);   //up
	  }	    	
}

void pacman::clearScreen()
{
    COORD top_left= {0, 0};
	SetConsoleCursorPosition(hout,top_left);
}

void pacman::random(int *r,int *c)
{
	 *r=1+rand()%33;
     *c=1+rand()%33;
}

void pacman::moveGhost()
{ 
     while(1)
    {
        takeInputs();
    	for (int i=0; i<vgr.size(); i++)
    	{
    		if(i%2==0)
    		{
    			if(matrix[vgr[i]+mul[i]][vgc[i]]==(char)219  || matrix[vgr[i]+mul[i]][vgc[i]]==(char)232)     // vertical move
    			{
    				if (matrix[vgr[i]+mul[i]][vgc[i]]==(char)234)
    				{
    					cout<<"Game over";
    					exit(0);
					}
					else{					
    				mul[i]=mul[i]*-1;}
				}
				vgr[i]+=mul[i];		
			}
			else
			{				
    			if(matrix[vgr[i]][vgc[i]+mul[i]]==(char)219 || matrix[vgr[i]][vgc[i]+mul[i]]==(char)232)     // horizontal move
    			{
    				if(matrix[vgr[i]][vgc[i]+mul[i]]==(char)234)
    				{
    					cout<<"Game over";
    					exit(0);
					}
					else{
						mul[i]=mul[i]*-1;}
				}
				vgc[i]+=mul[i];
			}
		}		
		initialize();
		clearScreen();		
		display(); 
	    Sleep(speed);   	
	}  
}

void pacman::initiaizeGhosts()
{	
    int r,c;
    for (int i=0; i<N; i++)
    {
    	rand_check_r.push_back(0);
    	rand_check_c.push_back(0);
	}    
    
	int size=ghost_count;
	while(ghost_count>0)
	{
	    random(&r,&c);
       while(rand_check_r[r]==1 || rand_check_c[c]==1 || matrix[r][c]==(char)219 || matrix[r-1][c]==(char)219||matrix[r][c-1]==(char)219||matrix[r+1][c]==(char)219 || matrix[r][c+1]==(char)219 || matrix[r][c]==(char)234) 
		  {
		  	 random(&r,&c);
		  }	  
     
	   vgr.push_back(r);
	   vgc.push_back(c);
	   rand_check_r[r]=1;
	   rand_check_c[c]=1;
	   mul.push_back(1);
	   ghost_count--;
	}	
}
void pacman::readFruit()
{
	fstream fin;
	char ch;
	int r,c;
	// fruit ko vector main daalo aur sirf ek baar file se nikalo 
	fin.open("fruit.txt",ios::in);
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin>>r>>ch>>c;
			fruitr.push_back(r);
			fruitc.push_back(c);			
		}
		fin.close();
	}
}

void pacman::initialize()
{
	fstream fin;
	char ch;
	int r,c;
	// fruit ko vector main daalo aur sirf ek baar file se nikalo 
	for(int i=0; i<fruitr.size(); i++)
	{
		matrix[fruitr.front()][fruitc.front()]=(char)234;
		fruitr.push_back(fruitr.front()); fruitc.push_back(fruitc.front());
		fruitr.erase(fruitr.begin());
		fruitc.erase(fruitc.begin());		
	}
	
	for(int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
	       if( i==0 || j==0 || i==N-1 || j==N-1)
	       {
	       	  matrix[i][j]=(char)219;     // walls boundary
		   }		   	
		   else if(matrix[i][j]!=(char)234)
		   {
		   	matrix[i][j]=(char)249;        /// grains
		   }	
		}
	}
	
	fin.open("walls.txt",ios::in);

	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin>>r>>ch>>c;
			matrix[r][c]=(char)219;	      		
		}
		fin.close();
	}      
	matrix[vr.front()][vc.front()]=(char)233;    // initial pac man
	for (int i=0; i<vgr.size(); i++)
    {
		matrix[vgr[i]][vgc[i]]=(char)232;
	}	
}

void pacman::display() 
{  
     cout<<"\t     Score = "<<score<<endl;
    for (int i=0; i<N; i++)
	 {
		for (int j=0; j<N; j++)
		{
			if (matrix[i][j]==(char)234)
			{
				SetConsoleTextAttribute(hout,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout<<matrix[i][j];
			}
			else if(matrix[i][j]==(char)232)
			{
				SetConsoleTextAttribute(hout,FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout<<matrix[i][j];				
			}
		     else if(matrix[i][j]==(char)233)
		     {
		        	SetConsoleTextAttribute(hout,47 | FOREGROUND_INTENSITY);
				cout<<matrix[i][j];					
			 }
			else
			{
			   SetConsoleTextAttribute(hout,FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout<<matrix[i][j];	   		   		
			}	      
		}
		cout<<endl;
	}
}
int main()
{    
    SetConsoleTitle("Pacman");
	system("cls");
	srand(time(0));
	CONSOLE_CURSOR_INFO ci; 
    ci.dwSize=100;
    ci.bVisible=1000;
    //system("color 3E");
    SetConsoleTextAttribute(hout,30 | FOREGROUND_RED | FOREGROUND_INTENSITY);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 100;                          //INDEX OF THE FONT IN THE SYSTEM FONT TABLE
    cfi.dwFontSize.X = 15;                  // Width of each character in the font
    cfi.dwFontSize.Y = 15;                 // Height
    cfi.FontFamily = FF_DONTCARE;          // Arial or Courier etc 
    cfi.FontWeight = 1000;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &cfi);   // if parameter is true the font info is set font  max window size...if is false then current window size.
	SetConsoleCursorInfo(hout,&ci);	
	pacman obj;
	obj.readFruit();
	obj.initialize();	
	obj.initiaizeGhosts();
	int time=5;
	while(time)
	{
		cout<<"Game Starts in "<<time<<" seconds";
        time--;
		Sleep(1000);
		system("cls");
	}	 
    obj.display();
   	system("cls");
	obj.moveGhost();		
	return 0;
}
