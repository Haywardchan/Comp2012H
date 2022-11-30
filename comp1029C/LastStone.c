/*
* Exercise for Lesson 2 laststone
*
* At the start of the game, the program randomly generates a certain number of
* stones in the game. The program then asks you to specify the maximum number
* of stones that you and the computer can take each turn.
*
* You and the computer take turn to take away the stones. The game stops when
* no stone is left.
*
* The player who takes the last stone loses the game.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int  range_max, range_min = 1;  // This is the range of the number of stones each turn can take
    int  stones_taken, stones_left; // This keeps track of the current stones in the game
    int  multi_factor;              // This is used by the computer to cleverly play the game

    char this_turn;                 // This remembers who is playing the current turn
                                    // 'H' means human and 'C' means computer

    // Task 1 - Ask the user to set a maximum number of stones allowed to be
    //          taken, for simplicity it should be <= 10 
    int input;
    do {
        printf("Please specify the number of stones that can be taken each turn.\nIt should be between 1 and 10: ");
        scanf("%d", &input);
        range_max = input;
    }while(!(input<=10 && input>0));
    // The rand() function is a build-in function in C 
    // Here the program randomly generates the initial number of stones,
    // restricted to be between 10 and 50
    //
    // You will learn the use of rand() later in the course
    printf("You have entered %d.\n", range_max);
    srand(time(0));
    stones_left = ((rand() % 41) + 10);
    printf("There are %d stones initially.\n", stones_left);

    // Using a while loop to read the number of stones to be taken
    // by each side alternatively

    this_turn = 'H';  // The game starts with the human's turn

    while (stones_left > 0) {
        // if the current turn is 'human'...
        if (this_turn == 'H') {
            // Task 2 - Ask for the number of stones from the player
            do {
            printf("How many stones you want to take, between %d to %d? ",range_min,range_max);
            scanf("%d", &stones_taken);
            }while(!(stones_taken<=range_max && stones_taken>=range_min));
        }

        // if the current turn is 'computer'...
        else {
            // The computer determines the number of stones to take cleverly
            multi_factor = (stones_left - 1) / (range_max + range_min);
            stones_taken = stones_left - ((range_max + range_min) * multi_factor + 1);
            if (stones_taken == 0) stones_taken = 1;
        }

        // Update the number of stones left and the maximum number of stones each turn
        stones_left = stones_left - stones_taken;
        if (stones_left < range_max)
            range_max = stones_left;

        // Task 3 - print out what happens this turn and the current status
        if (this_turn=='H'){
            printf("You have taken away %d stone(s).\n",stones_taken);
            printf("There are currently %d stones left.\n",stones_left);
            }
        else{
            printf("The computer has taken away %d stone(s).\n",stones_taken);
            printf("There are currently %d stones left.\n", stones_left);   
        }
        

        // if not yet game over, set the this_turn variable for the next player
        if (stones_left > 0) {
            if (this_turn == 'H')
                this_turn = 'C';
            else
                this_turn = 'H';
        }
    }

    // Task 4 - Print out who lose the game
    if (stones_left<=0){
        switch (this_turn)
        {
        case 'C':
            printf("The computer loses the game!\n");
            break;
        
        case 'H':
            printf("You lose the game!\n");
            break;
        }
    }
    

    printf("Bye!\n");
}
