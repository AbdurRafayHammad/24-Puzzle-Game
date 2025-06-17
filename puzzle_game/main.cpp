#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include<string>

using namespace std;

const string rest = "\033[0m";
const string blue = "\033[34m";
const string cyan = "\033[36m";
const string yellow = "\033[33m";
const string green = "\033[32m";
const string red = "\033[31m";

void print_path(); // Function to print the game board
char getkey(); // Function to get user input for moves
void init(); // Function to initialize the game board
void goal(); // Function to generate the goal state
bool Is_Solvable(); // Function to check if the current board state is solvable
bool is_goal(); // Function to check if the current board state matches the goal state
int* legal_moves(int* init_state); // Function to find legal moves
void make_move(int* init_state, char move); // Function to make a move on the board
void displayMenu(); // Function to display the game menu
void cerdit(); // Function to display credits
void instruction(); // Function to display game instructions
void countMoves(); // Function to count the number of moves made
void print_move(char move); // Function to print the move made
void store_moves(const char* moves, int num_moves); // Function to store moves in a file

int a[5][5];
int row = 5, col = 5;

const int maxmove = 100;
void print_goal_state()
{
    cout << "                                                           " << endl;
    cout << green << "|---------------------------------------|" << endl;
    cout << red << "|*          5x5 puzzle game!             *|" << endl;
    cout << red << "|*         goal board puzzle             *|" << endl;
    cout << green << "|---------------------------------------|" << endl;

    cout << rest << "+---+---+---+---+---+" << endl;
    int num = 1; // Start with number 1
    for (int x = 0; x < 5; x++)
    {
        if (x > 0)
        {
            cout << rest << "+---+---+---+---+---+" << endl;
        }
        for (int y = 0; y < 5; y++)
        {
            cout << cyan << "| ";
            if (num <= 24)
            {
                cout << yellow << num;
                if (num < 10)
                {
                    cout << yellow << " ";
                }
                num++;
            }
            else
            {
                cout << yellow << "  ";
            }
        }
        cout << cyan << "|" << endl;
    }

    cout << rest << "+---+---+---+---+---+" << endl;
}


int main()
{
    char choice;

    while (true)
    {
        system("cls"); // Clear the console screen
        displayMenu();
        cin >> choice;
        char moves[maxmove];
        int no_of_moves = 0;

        // Handle user choices
        if (choice == '1')
        {
            system("cls");
            print_goal_state();
            init();
            print_path();

            char d;

            while (!is_goal())
            {
                cout << "Enter a move (u for up / l for left / d for down / r for right): "; // Prompt for input
                d = getkey();
                make_move((int*)a, d);


                print_move(d); // Print the move after each move
                /* countMoves();*/
                print_path();
            }

            cout << "You are a winner!" << endl;

            countMoves();
        }
        else if (choice == '2')
        {
            system("cls");
            cerdit();
            int op;
            cin >> op;
            if (op == 1)
            {
                continue;
            }
            else
            {
                continue;
            }
        }
        else if (choice == '3')
        {
            system("cls");
            instruction();
            int op;
            cin >> op;
            if (op == 1)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else if (choice == '4')
        {
            cout << endl << "End of the program." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    system("pause");
    return 0;
}

void displayMenu()
{
    system("cls");
    cout << green << "|---------------------------------------|" << endl;
    cout << red << "|*          5x5 puzzle game!           *|" << endl;
    cout << green << "|---------------------------------------|" << endl;

    cout << blue << "|----------------------------------------|" << endl;
    cout << blue << "|* Welcome to the 5x5 puzzle game!      *|" << endl;
    cout << rest << "|* 1. Start a new game                  *|" << endl;
    cout << rest << "|* 2. View the credits                  *|" << endl;
    cout << rest << "|* 3. Instruction                       *|" << endl;
    cout << rest << "|* 4. Quit the program                  *|" << endl;
    cout << blue << "|* Please enter your choice:            *|" << endl;
    cout << blue << "|----------------------------------------|" << endl;
}

void cerdit()
{
    cout << green << "|---------------------------------------|" << endl;
    cout << red << "|*          5x5 puzzle game!           *|" << endl;
    cout << green << "|---------------------------------------|" << endl;

    cout << blue << "|----------------------------------------|" << endl;
    cout << blue << "|* Welcome to the 5x5 puzzle game!      *|" << endl;
    cout << rest << "|* NAME: ABDUR RAFAY                    *|" << endl;
    cout << blue << "|----------------------------------------|" << endl;
    cout << rest << "|* Press any key to continue            *|" << endl;
    cout << blue << "|----------------------------------------|" << endl;
}

void instruction()
{
    cout << " ----------------------------------------------------------------------" << endl;
    cout << "|     Swap the blank spaces with the numbers until all the numbers     | " << endl;
    cout << "|               are placed in the ascending order.                     | " << endl;
    cout << " ----------------------------------------------------------------------" << endl;
}

void print_path()
{
    cout << "                                                           " << endl;
    cout << green << "|---------------------------------------|" << endl;
    cout << red << "|*         5x5 puzzle game!            *|" << endl;
    cout << green << "|---------------------------------------|" << endl;

    cout << rest << "+---+---+---+---+---+" << endl;
    for (int x = 0; x < 5; x++)
    {
        if (x > 0)
        {
            cout << rest << "+---+---+---+---+---+" << endl;
        }
        for (int y = 0; y < 5; y++)
        {
            cout << cyan << "| ";
            if (a[x][y] == 0)
            {
                cout << yellow << "  ";
            }
            else
            {
                cout << yellow << a[x][y];
                if (a[x][y] < 10)
                {
                    cout << yellow << " ";
                }
            }
        }
        cout << cyan << "|" << endl;
    }

    cout << rest << "+---+---+---+---+---+" << endl;

    // Read moves from the file
   // Read moves from the file
    ifstream inputFile("moves.txt");
    if (inputFile.is_open())
    {
        char move;
        cout << "Moves performed so far: ";
        while (inputFile >> move)
        {
            print_move(move);
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file 'moves.txt'." << endl;
    }
}




char getkey()
{
    char key;
    cin >> key;
    return key;
}

void init()
{
    // Clear the contents of the moves.txt file
    ofstream clearFile("moves.txt", ios::trunc);
    clearFile.close();

    // Seed the random number generator
    srand(time(0));

    // Generate a random initial state
    int numbers[24];
    for (int i = 0; i < 24; ++i)
    {
        numbers[i] = i + 1;
    }

    // Randomize the initial state
    int randomIndex;
    for (int i = 0; i < 24; ++i)
    {
        randomIndex = rand() % (24 - i) + i; // Generate a random index from i to 23
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }

    int k = 0;
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (k < 24)
            {
                a[x][y] = numbers[k++];
            }
            else
            {
                a[x][y] = 0; // Set the last element as 0 (empty space)
                row = x;
                col = y;
            }
        }
    }
}

void goal()
{
    // Initialize a 1D array to store numbers
    int goalState[25];

    // Assign numbers in increasing order
    for (int i = 0; i < 24; ++i)
    {
        goalState[i] = i + 1;
    }
    goalState[24] = 0; // Set the last element as 0 (empty space)

    // Shuffle the goal state
    int randomIndex;
    for (int i = 0; i < 24; ++i)
    {
        randomIndex = (i * 13 + 7) % (24 - i);
        int temp = goalState[i];
        goalState[i] = goalState[randomIndex];
        goalState[randomIndex] = temp;
    }

    // Ensure the shuffled state is solvable
    while (!Is_Solvable())
    {
        // Reshuffle until a solvable state is achieved
        for (int i = 0; i < 24; ++i)
        {
            randomIndex = (i * 13 + 7) % (24 - i);
            int temp = goalState[i];
            goalState[i] = goalState[randomIndex];
            goalState[randomIndex] = temp;
        }
    }

    // Assign the shuffled state to the puzzle
    int k = 0;
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            a[x][y] = goalState[k++];
        }
    }
}

bool Is_Solvable()
{
    int inversions = 0;
    int flattened[25]; // Flatten the puzzle into a 1D array
    int k = 0;

    // Flatten the puzzle into a 1D array
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            flattened[k++] = a[x][y];
        }
    }

    // Count inversions
    for (int i = 0; i < 24; i++)
    {
        for (int j = i + 1; j < 25; j++)
        {
            if (flattened[i] && flattened[j] && flattened[i] > flattened[j])
            {
                inversions++;
            }
        }
    }

    // Check if the number of inversions is even or odd
    if (inversions % 2 == 0)
    {
        return true; // Solvable
    }
    else
    {
        return false; // Not solvable
    }
}

bool is_goal()
{
    // Define the goal state
    int goal_state[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 0} // 0 represents the empty space
    };

    // Compare the current state with the goal state
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (a[x][y] != goal_state[x][y])
            {
                return false; // Current state doesn't match the goal state
            }
        }
    }

    return true; // Current state matches the goal state
}

int* legal_moves(int* init_state)
{
    int emptyIndex = -1;
    // Find the index of the empty space (0)
    for (int i = 0; i < 25; ++i)
    {
        if (init_state[i] == 0)
        {
            emptyIndex = i;
            break;
        }
    }

    // Initialize an array to store legal moves
    int* moves = new int[4];
    int numMoves = 0;

    // Check if moves are possible in each direction (up, down, left, right)
    int row = emptyIndex / 5;
    int col = emptyIndex % 5;

    // Check if the empty space can move up
    if (row > 0)
    {
        moves[numMoves++] = emptyIndex - 5;
    }

    // Check if the empty space can move down
    if (row < 4)
    {
        moves[numMoves++] = emptyIndex + 5;
    }

    // Check if the empty space can move left
    if (col > 0)
    {
        moves[numMoves++] = emptyIndex - 1;
    }

    // Check if the empty space can move right
    if (col < 4)
    {
        moves[numMoves++] = emptyIndex + 1;
    }

    // Resize the moves array to the actual number of moves
    int* legalMoves = new int[numMoves];
    for (int i = 0; i < numMoves; ++i)
    {
        legalMoves[i] = moves[i];
    }

    delete[] moves;

    return legalMoves;
}

void make_move(int* init_state, char move)
{
    int* moves = legal_moves(init_state);
    int emptyIndex = -1;

    // Find the index of the empty space (0)
    for (int i = 0; i < 25; ++i)
    {
        if (init_state[i] == 0)
        {
            emptyIndex = i;
            break;
        }
    }

    // Perform the move based on user input
    switch (move)
    {
    case 'u':
        for (int i = 0; i < 4; ++i)
        {
            if (emptyIndex - 5 == moves[i])
            {
                // Swap the empty space with the number above it
                int temp = init_state[emptyIndex];
                init_state[emptyIndex] = init_state[moves[i]];
                init_state[moves[i]] = temp;
                break;
            }
        }
        break;

    case 'd':
        for (int i = 0; i < 4; ++i)
        {
            if (emptyIndex + 5 == moves[i])
            {
                // Swap the empty space with the number below it
                int temp = init_state[emptyIndex];
                init_state[emptyIndex] = init_state[moves[i]];
                init_state[moves[i]] = temp;
                break;
            }
        }
        break;

    case 'l':
        for (int i = 0; i < 4; ++i)
        {
            if (emptyIndex - 1 == moves[i])
            {
                // Swap the empty space with the number to the left
                int temp = init_state[emptyIndex];
                init_state[emptyIndex] = init_state[moves[i]];
                init_state[moves[i]] = temp;
                break;
            }
        }
        break;

    case 'r':
        for (int i = 0; i < 4; ++i)
        {
            if (emptyIndex + 1 == moves[i])
            {
                // Swap the empty space with the number to the right
                int temp = init_state[emptyIndex];
                init_state[emptyIndex] = init_state[moves[i]];
                init_state[moves[i]] = temp;
                break;
            }
        }
        break;

    default:
        cout << "Invalid move! Please enter 'u' (up), 'd' (down), 'l' (left), or 'r' (right)." << endl;
    }
    // Store the move in the moves.txt file
    ofstream movesFile("moves.txt", ios_base::app);
    movesFile << move;
    movesFile.close();

    delete[] moves;

}

void countMoves()
{
    // Read moves from the file and count the number of moves
    ifstream inputFile("moves.txt");
    if (inputFile.is_open())
    {
        int count = 0;
        char move;
        while (inputFile >> move)
        {
            ++count;
        }
        cout << "Total moves performed: " << count << endl;
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file 'moves.txt'." << endl;
    }
}

void print_move(char move)
{
    cout << "Move: ";
    switch (move)
    {
    case 'u':
        cout << "Up";
        break;
    case 'd':
        cout << "Down";
        break;
    case 'l':
        cout << "Left";
        break;
    case 'r':
        cout << "Right";
        break;
    default:
        cout << "Invalid move";
        break;
    }
    cout << endl;
}