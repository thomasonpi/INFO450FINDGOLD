#include <iostream>
#include<cstdlib>
#include<string.h>
#include<time.h>
using namespace std;

//Set size of gameBoard
const int SIZE = 8;

void fillArray(char arrayOut[SIZE][SIZE], char seedIn[SIZE*SIZE]);
void printArray(char arrayIn[SIZE][SIZE]);
void checkInput(char arrayIn[SIZE][SIZE], int maxTurns);

int main() 
{
	char goAgain = 'y';
	do
	{
	srand(time(NULL));

	//Set number of guesses and game pieces
	int numTurns = 5;
	char seedStr[SIZE * SIZE] ={'G','G','G','G','G','B'};
	
	char gameBoard[SIZE] [ SIZE];
	char blankStr[SIZE*SIZE] = {};
	char blankBoard[SIZE][SIZE];

	fillArray(blankBoard,blankStr);
	fillArray(gameBoard,seedStr);

	printArray(blankBoard);

	checkInput(gameBoard, numTurns);	

	printArray(gameBoard);
	
	cout << "Game Over" <<endl;	
	cout << "^^^^^^^^^^^^^"<<endl;
	cout << "would you like to play again? (y/n)";
	cin >> goAgain;	
	cout << endl;
	}while (goAgain == 'y' || goAgain == 'Y' );
	cout <<"Goodbye, thanks for playing!"<<endl;
	
	return 0;
}


// populates array from seedIn and shuffles by fisher-yates into arrayOut
void fillArray(char arrayOut[SIZE][SIZE], char seedIn[SIZE*SIZE])
{
	//seed then fill 1d array
	int i;

	for (i =0; i< (SIZE*SIZE); i++) 
	{
		if (seedIn[i]== 0) seedIn[i] = '*';
	}

	//shuffle 1d array
	int jCount = (SIZE*SIZE)-1;
	for (jCount; jCount >= 0; jCount--)	{
		int randI = rand() % (jCount+1);
		char temp;
		temp = seedIn[jCount];
		seedIn[jCount] = seedIn[randI];
		seedIn[randI] = temp;
	}

	// populate 2d array from 1d
	int  j;
	int count = 0;
	for (i = 0; i < SIZE; i++)	{
		for (j=0; j<SIZE; j++)
		{
		       	arrayOut[i][j] = seedIn[count];
			count++;
		}
	}
}

// steps through arrayIN and outputs each value
void printArray(char arrayIn[SIZE][SIZE])
{
	int i, j;
	cout << "  ";
	for (i=0; i < SIZE; i++) cout << i+1 << " ";
	cout << endl;
	
	for (i=0; i<SIZE; i++)
	{
		cout << i + 1 << " ";
		for (j=0; j<SIZE; j++)
		{
			cout << arrayIn[i][j];
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

// takes user input, checks against arrayIn, outputs results
void checkInput(char arrayIn[SIZE][SIZE], int maxTurns)
{
	int i;
	int guessX, guessY;
	int goldCount = 0;
	
	for(i=0;i<maxTurns;i++)
	{
		//get user guess
		cout << "pick an x: ";
		cin >> guessX;
		cout << "pick a Y: ";
		cin >> guessY;
		
		//check guess is in bounds, print error if not
		while (guessX<1 || guessX>8 || guessY<1 || guessY>8)
		{
			cout << "*picks must be between 1 and 8*"<<endl;

		cout << "pick an x: ";
		cin >> guessX;
		cout << "pick a Y: ";
		cin >> guessY;
		}
		
		// convert input to count by zero
		guessX -= 1;
		guessY -= 1; 	
		
		//show result 
		cout << "-->  " << arrayIn[guessX][guessY]<< endl;	
		
		// if gold found give bonus turn and swap G for F on board
		if(arrayIn[guessX][guessY] == 'G')
		{
			cout << "you found a gold!" <<endl;
			cout << "you got a bonus turn!" <<endl;
			goldCount++;
			i--;
			arrayIn[guessX][guessY] = 'F';
		}
		//if bomb found end game
		else if(arrayIn[guessX][guessY] == 'B')
		{
			cout << "***Boom!**"<<endl;
			break;
		}
		else arrayIn[guessX][guessY] = ' ';
		
		cout << "you have "<<maxTurns - (i+1)<<" turns left"<<endl;

	}
	cout << "you found: "<<goldCount<< " gold!"<<endl;
	cout << endl;
}
