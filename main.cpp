
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

int player1[3][3];	//player1 answers
int player2[3][3];	//player2 answers
int enterYN[3][3];	//entry slot is empty; yes or no 
int p1win_count=0, p2win_count=0;	//total count of p1 and p2 wins
int matchcount=1;	//current match number

char difficulty;	//difficulty of computer ai
char gametype;		//game type; player vs player or computer vs player
char arrow_one=16, arrow_two=32, arrow_three; 		//variables to show whose turn it is
char tick[3][3];	//player1 and player2 answers
char button1[3][3]=	{	//character buttons to play game with
						{'q','w','e'},
						{'a','s','d'},
						{'z','x','c'}
					};
char button2[3][3]=	{	//numeric pad button to play game with
						{'7','8','9'},
						{'4','5','6'},
						{'1','2','3'}
					};

void instruction();		//function to show instructions about the game
void heading();			//function to show heading showing tic tac toe
void gui();		//gui function to display game

int pvp(int&, int&, char&, char&, char&);	//function for player vs player game
int pvc(int&, int&, char&, char&, char&);	//function for player vs computer game

int playerwon(int &win1, int &win2);	//function for calculating who wins
int ai(int);	//fuction to decide the moves for computer



//=======================================================================================================
	
int main()
{	
	system("COLOR f0");		//white background and black text
	system("title TIC TAC TOE");
	
	instruction();	
	menu:	//when ESC is pressed go here
	
	int p1win=0, p2win=0;	//player1 and player2 win/lose variables 
	int back=0;	//go back to menu variable
	p1win_count=0;
	p2win_count=0;
	matchcount=1;
	
	system("cls");
	heading();

	cout<<endl<<"GAME TYPE: "<<endl<<endl;
	cout<<"1. Player VS Player."<<endl;
	cout<<"2. Player VS Computer."<<endl;
	
	while(1)	//get input for game type
	{
		gametype=getch();
		if(gametype=='1' || gametype=='2')
			break;
		else
			cout<<"\a";
	}
		
	system("cls");
	
	if(gametype=='2')
	{
		heading();

		cout<<endl<<"GAME DIFFICULTY: "<<"\t\t(ESC) Back to Main Menu"<<endl<<endl;
		cout<<"1. Easy"<<endl;
		cout<<"2. Medium"<<endl;	
		cout<<"3. Hard"<<endl;	
		cout<<"4. Impossible"<<endl;
		
		while(1)	//get input for game difficulty
		{
			difficulty=getch();
			if(difficulty=='1' || difficulty=='2'|| difficulty=='3' || difficulty=='4')
				break;
			else if(difficulty==27)	//when ESC is pressed
				goto menu;
			else
				cout<<"\a";
		}
	
		system("cls");
	}

	do
	{
		for(int i=0; i<3; i++)	//all values are set to default after each game
		{
			for(int j=0; j<3; j++)		
			{
				tick[i][j]=32;
				player1[i][j]=0;
				player2[i][j]=0;
				enterYN[i][j]=0;
			}
		}
		arrow_one=16;
		arrow_two=32;
		
		gui();		//calling gui function to display game

		if(gametype=='1')	//runs player vs player function
			back= pvp(p1win, p2win, arrow_one, arrow_two, arrow_three);
		
		else if(gametype=='2')	//runs player vs computer function
			back= pvc(p1win, p2win, arrow_one, arrow_two, arrow_three);
		
		if (back==10)	//if 10 is returned from pvp/pvc function, goto menu
			goto menu;
		
		if(p1win==1)	//if p1 wins a match
		{
			p1win_count++;
			if(gametype=='1')
				cout<<endl<<"\t\tPlayer 1 wins Match "<<matchcount;
			else if(gametype=='2')
				cout<<endl<<"\t\tPlayer wins Match "<<matchcount;
		
		}
		else if(p2win==1)	//if p2 wins a match
		{
			p2win_count++;
			if(gametype=='1')
				cout<<endl<<"\t\tPlayer 2 wins Match "<<matchcount;
			else if(gametype=='2')
				cout<<endl<<"\t\tComputer wins Match "<<matchcount;
		
		}
		else	//if match is a draw
			cout<<endl<<"\t\tMatch "<<matchcount<<" is a Draw";			
		
		p1win=0;
		p2win=0;
		
		cout<<endl<<endl;
		system("pause");
		system("CLS");
		
		matchcount++;	//next match
		
	}while(p1win_count<3 && p2win_count<3);
	
	if(p1win_count==3)	//if p1 wins 3 game
	{
		if(gametype=='1')
			cout<<endl<<"\tPLAYER 1 WINS!";
		else if(gametype=='2')
			cout<<endl<<"\tPLAYER WINS!";
	}
	else if(p2win_count==3)	//if p2 wins 5 game
	{
		if(gametype=='1')
			cout<<endl<<"\tPLAYER 2 WINS!";			
		else if(gametype=='2')
			cout<<endl<<"\tCOMPUTER WINS!";		
	}
	cout<<endl<<endl;
		
		
	cout<<"Play Again? (Y/N)"<<endl;
	while(1)	//play again or not
	{
	char again;
	again=getch();
	if(again=='y' || again=='Y')
		goto menu;
	else if(again=='n' || again=='N')
		return 0;
	else
		cout<<"\a";
	}	
}

//=======================================================================================================

void instruction()
{
	char b1=179, b2=196, b3=197;	//variables to display lines of game
	
	system("cls");
	heading();
	
	//instructions display
	cout<<endl<<endl<<"INSTRUCTIONS: "<<endl;
	cout<<"Play with a friend or computer by taking turns."<<endl;
	cout<<"The first one to reach 3 wins is the Winner."<<endl;
	cout<<"Player 1 is represented by (o)."<<endl;
	cout<<"Player 2 is represented by (x)."<<endl;
	cout<<"Use the following keys to choose your entry:"<<endl<<endl;
	
	cout<<"\t 7 "<<b1<<" 8 "<<b1<<" 9"<<"\t\t"<<" q "<<b1<<" w "<<b1<<" e "<<endl;
	cout<<"\t"<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<"\t\t"<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<endl;
	cout<<"\t 4 "<<b1<<" 5 "<<b1<<" 6"<<"\tor\t"<<" a "<<b1<<" s "<<b1<<" d "<<endl;
	cout<<"\t"<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<"\t\t"<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<endl;
	cout<<"\t 1 "<<b1<<" 2 "<<b1<<" 3"<<"\t\t"<<" z "<<b1<<" x "<<b1<<" c "<<endl<<endl;
	cout<<"\tNumpad Keys\t       Alphabet Keys"<<endl<<endl;
	
	system("PAUSE");
	system("CLS");
	
}

//=======================================================================================================

void heading()
{
	char b1=219, b2=220, b3=223;		//block character to make a solid black box
	
	//tic tac toe box display
	cout<<'\t'<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2<<b2;	
	cout<<endl<<"\t"<<b1<<" TIC TAC TOE "<<b1<<endl;
	cout<<'\t'<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<b3<<endl;
}

//=======================================================================================================

void gui()		//displaying tick tac toe box to play
{
	char b1=179, b2=196, b3=197;	//variables to display lines of game
	
	heading();
	cout<<"\t    MATCH "<<matchcount<<endl;
	
	cout<<endl;
	for(int i=0; i<3; i++)		//loop to display tic tac toe box
	{
		cout<<"\t   ";
		for(int j=0; j<3; j++)
		{
			if(j==0)
				cout<<tick[i][j]<<" "<<b1;
			else if(j==1)
					cout<<" "<<tick[i][j]<<" "<<b1;
			else
				cout<<" "<<tick[i][j];
				
		}
		if(i==0)
		{	
			if(gametype=='1')
				cout<<"\t\t"<<arrow_one<<" Player 1 (o) = "<<p1win_count;	//shows p1 turn and wins
			else if(gametype=='2')
				cout<<"\t\t"<<arrow_one<<" Player   (o) = "<<p1win_count;	//shows p1 turn and wins	
		}
		if(i==2)
			cout<<"\t\t  (i) Instructions";
			
		cout<<endl;
		if(i<2)
		{
			cout<<"\t  "<<b2<<b2<<b2<<b3<<b2<<b2<<b2<<b3<<b2<<b2<<b2;
			if(i==0)
			{	
				if(gametype=='1')
					cout<<"\t\t"<<arrow_two<<" Player 2 (x) = "<<p2win_count;	//shows p2 turn and wins
				else if(gametype=='2')
					cout<<"\t\t"<<arrow_two<<" Computer (x) = "<<p2win_count;	//shows p2 turn and wins
			}
			if(i==1)
				cout<<"\t\t  (ESC) Main Menu";
			
			cout<<endl;
		}
	}
	cout<<endl;
		
}

//=======================================================================================================


int pvp(int &p1, int &p2, char &one, char &two, char &three)
{
	char input;		//entered character
	int turn=0;		//total turns done	
	
do
	{
		spacefilled:	//slot is not empty
		int error=0;	//variable to tell if entered character is not equal to buttons to play
		input=getch();	//enter your character
		
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(input==button1[i][j] || input==button2[i][j])		//if entered character matches buttons to play
				{
					if(enterYN[i][j]==0)	//if entry slot is empty
					{
						enterYN[i][j]=1;	
						if(turn%2==0)		//if turn is even, player1 (o) turn
						{
							tick[i][j]='o';
							player1[i][j]=1;
						}	
						else if(turn%2==1)	//if turn is odd, player2 (x) turn
						{
							tick[i][j]='x';
							player2[i][j]=1;
						}
						
					}
					else					//if entry slot is occupied
					{
						cout<<"\a";			//bell if character is repeated
						goto spacefilled;
					}
				}
				
				else		//if entered character does not match with the buttons to play
					error++;
								
			}
		}
		playerwon(p1,p2);	//computes who wins
		
		if(input=='i')		//if i is pressed instructions are shown
		{
			instruction();
		}
		if(input==27)		//if ESC is pressed go back
		{
			return 10;
		}		
		system("CLS");
		
		if(error!=9)		//if there is no error or character matches the buttons to play
		{
			turn++;			//turn changed to other player
			three=two;
			two=one;
			one=three;			
		}
		else
			cout<<"\a";
		
		gui();				//display gui
		
				
	}while(turn<9 && p1!=1 && p2!=1);	//do until its a draw or a player wins
}


//=======================================================================================================


int pvc(int &p1, int &p2, char &one, char &two, char &three)
{
	char input;		//entered character for p1
	int turn=0;		//total turns done
		
	
do
	{
		out:
		int error=0;	//variable to tell if entered character is not equal to buttons to play
		
		if(turn%2==0)
		{
			input=getch();	//enter your character	
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					if(input==button1[i][j] || input==button2[i][j])		//if entered character matches buttons to play
					{
						if(enterYN[i][j]==0)	//if entry slot is empty
						{
							enterYN[i][j]=1;							
							tick[i][j]='o';
							player1[i][j]=1;					
						}
						else					//if entry slot is occupied
						{
							cout<<"\a";			//bell if character is repeated
							goto out;
						}
					}
					
					else		//if entered character does not match with the buttons to play
						error++;
									
				}
			}
		}
		else if(turn%2==1)	//if turn is odd, its computer's turn
		{
			ai(turn);
			Sleep(800);
		}
		playerwon(p1,p2);	//computes who wins
			
		if(input=='i')	//if i is pressed instructions are shown
		{
			instruction();
		}
		if(input==27)	//if ESC is pressed go back
		{
			return 10;
		}		
		system("CLS");
		
		if(error!=9)		//if there is no error or character matches the buttons to play
		{
			turn++;			//turn changed to other player
			three=two;
			two=one;
			one=three;			
		}
		else
			cout<<"\a";
		
		gui();				//display gui
		
	cout<<turn<<endl;	
	
	}while(turn<9 && p1!=1 && p2!=1);	//do until its a draw or a player wins
}


//=======================================================================================================

int playerwon(int &win1, int &win2)
{
	int p1=0;	//number of correct character in rows, columns, diagonal for player1
	int p2=0;	//number of correct character in rows, columns, diagonal for player2
	
	//checking rows
	for(int i=0; i<3; i++)
	{
		int p1=0;
		int p2=0;
		for(int j=0; j<3; j++)
		{
			if(player1[i][j]==1)
				p1++;
			if(p1==3)	//if in any row all 3 entries are same, p1 wins 
			{
				win1=1;
				return 0;
			}
			if(player2[i][j]==1)
				p2++;
			if(p2==3)	//if in any row all 3 entries are same, p2 wins
			{
				win2=1;
				return 0;
			}
		}
	}
	
	//checking columns
	for(int i=0; i<3; i++)
	{
		int p1=0;
		int p2=0;
		for(int j=0; j<3; j++)
		{
			if(player1[j][i]==1)
				p1++;
			if(p1==3)	//if in any column all 3 entries are same, p1 wins
			{
				win1=1;
				return 0;
			}
			if(player2[j][i]==1)
				p2++;
			if(p2==3)	//if in any column all 3 entries are same, p2 wins
			{
				win2=1;
				return 0;
			}	
		}
	}
	
	//checking diagonal1
	p1=0;
	p2=0;
	for(int i=0; i<3; i++)
	{
		if(player1[i][i]==1)
			p1++;
		if(player2[i][i]==1)
			p2++;
	}
	if(p1==3)	//if in first diagonal all 3 entries are same, p1 wins
	{
		win1=1;
		return 0;
	}
	if(p2==3)	//if in first diagonal all 3 entries are same, p2 wins
	{
		win2=1;
		return 0;
	}
	
	//checking diagonal2
	p1=0;
	p2=0;
	for(int i=0; i<3; i++)
	{
		if(player1[2-i][i]==1)
			p1++;
		if(player2[2-i][i]==1)
			p2++;
	}
	if(p1==3)	//if in second diagonal all 3 entries are same, p1 wins
	{
		win1=1;
		return 0;
	}
	if(p2==3)	//if in second diagonal all 3 entries are same, p2 wins
	{
		win2=1;
		return 0;
	}
}

//=======================================================================================================

int ai(int turn)
{
	int x=0;		//number of characters in rows
	int y=0;		//number of characters in columns
	int z1=0, z2=0;	//number of characters in diagonals
	int w=0;		//computer winning desire variable
	
	
	if(turn==1)	//if computer's first turn	
	{
		if (player1[1][1]==1)	//if p1 entered in the center
		{
			if(difficulty=='2' || difficulty=='3' || difficulty=='4')	//for medium, hard, impossible
			{
				int j=1, k=1;
				srand(time(0));
					
				while(j==1 || k==1)	//computer will randomize at corners
				{						
					j=rand()%3;
					k=rand()%3;
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;
			}
			else	//for easy
			{
				int j=10, k=10;
				srand(time(0));
					
				while(j==k || (j==0 && k==2) || (j==2 && k==0))	//computer will randomize at sides
				{						
					j=rand()%3;
					k=rand()%3;
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;
			}
		}
		if (player1[0][0]==1 || player1[2][2]==1 || player1[2][0]==1 || player1[0][2]==1)	//if p1 entered at corners
		{
			if(difficulty=='3' || difficulty=='4')	//for hard, impossible
			{		
				player2[1][1]=1;	//computer will choose center
				enterYN[1][1]=1;
				tick[1][1]='x';
				return 0;
			}
			else	//for easy and medium
			{
				int j=10, k=10;
				srand(time(0));
					
				while(player1[j][k]==1 || j>5 || k>5)	//computer will randomize anywhere
				{						
					j=rand()%3;
					k=rand()%3;
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;
			}
		}
		if (player1[0][1]==1 || player1[1][0]==1 || player1[2][1]==1 || player1[1][2]==1)	//if p1 entered at sides
		{
			if(difficulty=='2' || difficulty=='3' || difficulty=='4')	//for medium, hard, impossible
			{			
				player2[1][1]=1;	//computer will choose center
				enterYN[1][1]=1;
				tick[1][1]='x';
				return 0;
			}
			else	//for easy
			{
				int j=10, k=10;
				srand(time(0));
					
				while(player1[j][k]==1 || j>5 || k>5)	//computer will randomize anywhere
				{						
					j=rand()%3;
					k=rand()%3;
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;
			}
		}
	}
	if(turn>=3)	//if first wave of turn is completed
	{
		//computer desire to win by checking rows
		for(int i=0; i<3; i++)
		{
			w=0;
			for(int j=0; j<3; j++)
			{
				if(player2[i][j]==1)	//if computer has entered
				{
					w++;
				}
			}
			if(w==2)
			{
				for(int k=0; k<3; k++)
				{
					if(enterYN[i][k]==0)	//if slot is empty
					{
						player2[i][k]=1;
						enterYN[i][k]=1;
						tick[i][k]='x';
						return 0;
		
					}
				}
			}			
		}
		
		
		//computer desire to win by checking columns
		for(int j=0; j<3; j++)
		{
			w=0;
			for(int i=0; i<3; i++)
			{
				if(player2[i][j]==1)	//if computer has entered

				{
					w++;
				}
			}
			if(w==2)
			{
				for(int k=0; k<3; k++)
				{
					if(enterYN[k][j]==0)	//if slot is empty

					{
						player2[k][j]=1;
						enterYN[k][j]=1;
						tick[k][j]='x';
						return 0;
					}
				}
			}
		}
		
		//computer desire to win by checking diagonal 1
		w=0;
		for(int i=0; i<3; i++)
		{
			if(player2[i][i]==1)	//if computer has entered
				w++;
}
		if(w==2)	
		{
			for(int k=0; k<3; k++)
			{
			if(enterYN[k][k]==0)	//if slot is empty
				{
					player2[k][k]=1;
					enterYN[k][k]=1;
					tick[k][k]='x';
					return 0;
				}
			}
		}
		
		//computer desire to win by checking diagonal 2
		w=0;
		for(int i=0; i<3; i++)
		{
		if(player2[2-i][i]==1)	//if computer has entered
				w++;
		}
		if(w==2)
		{
			for(int k=0; k<3; k++)
			{
				if(enterYN[2-k][k]==0)	//if slot is empty
				{
					player2[2-k][k]=1;
					enterYN[2-k][k]=1;
					tick[2-k][k]='x';
					return 0;
				}
			}
		}
		
		
		
		
		
		
		//computer desire to defend by checking rows
		for(int i=0; i<3; i++)
		{
			x=0;
			for(int j=0; j<3; j++)
			{
				if(player1[i][j]==1)
				{
					x++;
				}
			}
			if(x==2)
			{
				for(int k=0; k<3; k++)
				{
					if(enterYN[i][k]==0)
					{
						player2[i][k]=1;
						enterYN[i][k]=1;
						tick[i][k]='x';
						return 0;
		
					}
				}
			}			
		}
		
		//computer desire to defend by checking columns
		for(int j=0; j<3; j++)
		{
			y=0;
			for(int i=0; i<3; i++)
			{
				if(player1[i][j]==1)
				{
					y++;
				}
			}
			if(y==2)
			{
				for(int k=0; k<3; k++)
				{
					if(enterYN[k][j]==0)
					{
						player2[k][j]=1;
						enterYN[k][j]=1;
						tick[k][j]='x';
						return 0;
					}
				}
			}
		}
		
		//computer desire to defend by checking diagonal 1 and 2
		for(int i=0; i<3; i++)
		{
			if(player1[i][i]==1)
				z1++;
			if(player1[2-i][i]==1)
				z2++;
		}
		if(z1==2)	
		{
			for(int k=0; k<3; k++)
			{
			if(enterYN[k][k]==0)
				{
					player2[k][k]=1;
					enterYN[k][k]=1;
					tick[k][k]='x';
					return 0;
				}
			}
		}
		else if(z2==2)
		{
			for(int k=0; k<3; k++)
			{
				if(enterYN[2-k][k]==0)
				{
					player2[2-k][k]=1;
					enterYN[2-k][k]=1;
					tick[2-k][k]='x';
					return 0;
				}
			}
		}
		
		
	
	if(difficulty=='4')	//for impossible
	{	
		//if turn is 3 and player 1 has already entered at center		
		if(turn==3 && player1[1][1]==1)
		{
			int j=1, k=1;
				srand(time(0));
					
				while(j==1 || k==1)	//computer will randomize at corners
				{						
					j=rand()%3;
					k=rand()%3;
					if(enterYN[j][k]==1)
					{
						j=1;
						k=1;
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';				
				return 0;			
		}
		
		//if turn is 3 and player 1 has already entered at any 2 diagonal corner
		else if(turn==3 && (player1[0][0]==1 && player1[2][2]==1 || player1[2][0]==1 && player1[0][2]==1))
		{
			int j=10, k=10;
				srand(time(0));
					
				while(j==k || (j==0 && k==2) || (j==2 && k==0))	//computer will randomize at sides
				{						
					j=rand()%3;
					k=rand()%3;
					if(enterYN[j][k]==1)
					{
						j=10;
						k=10;
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;
		}		
		
		
		//if turn is 3 and player1 has already entered at any 2 closest sides
		else if(turn==3 && player1[1][0]==1 && player1[0][1]==1)
		{
			player2[0][0]=1;
			enterYN[0][0]=1;
			tick[0][0]='x';
			return 0;		
		}
		else if(turn==3 && player1[0][1]==1 && player1[1][2]==1)
		{
			player2[0][2]=1;
			enterYN[0][2]=1;
			tick[0][2]='x';
			return 0;		
		}
		else if(turn==3 && player1[1][0]==1 && player1[2][1]==1)
		{
			player2[2][0]=1;
			enterYN[2][0]=1;
			tick[2][0]='x';
			return 0;		
		}
		else if(turn==3 && player1[1][2]==1 && player1[2][1]==1)
		{
			player2[2][2]=1;
			enterYN[2][2]=1;
			tick[2][2]='x';
			return 0;		
		}
	
		
		//if turn is 3 and player has entered once at a side and once at a corner which is not adjescent
		else if(turn==3)
		{	
			if(player1[0][1]==1 && (player1[2][0]==1 || player1[2][2]==1))
			{	
				int j=2, k=2;
				srand(time(0));
				
				while(j==2 || enterYN[j][k]==1)
				{
					j=rand()%3;
					k=rand()%3;
					if(player1[2][0]==1)
					{
						if(j==1 && k==0)
							j=2;	
					}
					else if(player1[2][2]==1)
					{
						if(j==1 && k==2)
							j=2;	
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;			
			}
			if(player1[1][0]==1 && (player1[0][2]==1 || player1[2][2]==1))
			{			
				int j=2, k=2;
				srand(time(0));
				
				while(k==2 || enterYN[j][k]==1)
				{
					j=rand()%3;
					k=rand()%3;
					if(player1[0][2]==1)
					{
						if(j==0 && k==1)
							k=2;	
					}
					else if(player1[2][2]==1)
					{
						if(j==2 && k==1)
							k=2;	
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;			
			}
			if(player1[1][2]==1 && (player1[0][0]==1 || player1[2][0]==1))
			{
				int j=0, k=0;
				srand(time(0));
				
				while(k==0 || enterYN[j][k]==1)
				{
					j=rand()%3;
					k=rand()%3;
					if(player1[0][0]==1)
					{
						if(j==0 && k==1)
							k=0;	
					}
					else if(player1[2][0]==1)
					{
						if(j==2 && k==1)
							k=0;	
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;			
			}
			if(player1[2][1]==1 && (player1[0][0]==1 || player1[0][2]==1))
			{
				int j=0, k=0;
				srand(time(0));
				
				while(j==0 || enterYN[j][k]==1)
				{
					j=rand()%3;
					k=rand()%3;
					if(player1[0][0]==1)
					{
						if(j==1 && k==0)
							j=0;	
					}
					else if(player1[0][2]==1)
					{
						if(j==1 && k==2)
							j=0;	
					}
				}
				player2[j][k]=1;
				enterYN[j][k]=1;
				tick[j][k]='x';
				return 0;			
			}
		}
	}
	
	
		//computer's choice if all other possiblities fail
		int j=10, k=10;
		srand(time(0));
					
		while(enterYN[j][k]==1 || j>5 || k>5)	//computer will randomize anywhere
		{						
			j=rand()%3;
			k=rand()%3;
		}
		player2[j][k]=1;
		enterYN[j][k]=1;
		tick[j][k]='x';
		return 0;

	
	}
	cout<<endl<<"AI Breakdown Error"<<endl;
	system("Pause");
		
}

//=======================================================================================================

