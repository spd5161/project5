#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct transition
{
	char state; //current state
	char readChar; //if read in char
	char nextState; //move to this state
	char writeChar; //write this char
	char move; //move direction
};

int main()
{
	string fname;
	cout << "Enter the name of the input file: ";
	cin >> fname;
	ifstream fin(fname); //input string and state machine;

	int startIndex = 49; //read input string into tape array at this index
	char tape[100]; //tape array
	for (int i = 0; i < 100; i++)
	{
		tape[i] = 'B';
	}

	//Tape is initialized
	string tapeTemp; //temporary tape input
	getline(fin, tapeTemp);
	int len = tapeTemp.length();
	int count = 0;
	for (int i = startIndex; i < (startIndex + len); i++) //build tape array
	{
		tape[i] = tapeTemp[count];
		count++;
	}
	int tapeLen = count;

	//state transitions are stored in array of strucures
	count = 0;
	string inputState; //state being read from file
	struct transition stateArray[30]; //array of states
	struct transition *statePtr = &stateArray[count];

	while (!fin.eof()) //reading states from file
	{
		getline(fin, inputState);
		statePtr->state = inputState[0];
		statePtr->readChar = inputState[1];
		statePtr->nextState = inputState[2];
		statePtr->writeChar = inputState[3];
		statePtr->move = inputState[4];

		count++;
		statePtr = &stateArray[count];
	}

	fin.close();

	//Turing Machine Simulator
	int numStates = count;
	bool stateFound = true; //determines if a state is found
	char curState = '0'; //current state
	char readVal; //value read by machine
	char moveDi; //move direction
	char haltState; //halt state of machine
	statePtr = &stateArray[0];
	int stateCount = 0; //state count when searching for next state
	int tapeCount = startIndex; //position on tape

								//Tape starts at 40 length = 5 highlights position 40 tape =
	cout << "Tape starts at " << startIndex << ", length = " << tapeLen << ", highlights postion " << startIndex << ", tape = " << endl;

	for (int i = (startIndex - 1); i <= (startIndex + tapeLen); i++) //print start tape
	{
		if (i == startIndex)
		{
			cout << "|" << tape[i] << "| ";
		}
		else
		{
			cout << tape[i] << " ";
		}
	}
	cout << endl << endl;

	while (stateFound == true) //while not in halt state
	{
		readVal = tape[tapeCount]; //read in vaalue from tape
		stateCount = 0;
		while (stateCount < numStates) //check for state to transition to
		{
			if ((curState == statePtr->state) && (readVal == statePtr->readChar)) //if current state and value read
			{
				stateFound = true;
				tape[tapeCount] = statePtr->writeChar;
				moveDi = statePtr->move;
				break;
			}
			else //state not found
			{
				haltState = statePtr->nextState;
				stateFound = false;
			}
			stateCount++;
			statePtr = &stateArray[stateCount];
		}

		if (stateFound == false)// break if halt state
			break;

		if (moveDi == 'L') //move left
		{
			tapeCount--;
		}
		else if (moveDi == 'R') //move right
		{
			tapeCount++;
		}

		curState = statePtr->nextState;
	}

	//when machine halts, display all non blank charactrs from left to right

	cout << "Execution halts in state " << haltState << endl;
	cout << "Tape starts at " << startIndex << ", length = " << tapeLen << ", highlights postion " << tapeCount << ", tape = " << endl;

	for (int i = (startIndex - 1); i <= (startIndex + tapeLen); i++) //print final tape
	{
		if (i == (tapeCount))
		{
			cout << "|" << tape[i] << "| ";
		}
		else
		{
			cout << tape[i] << " ";
		}
	}
	cout << endl;

	system("pause");
	return 0;
}
