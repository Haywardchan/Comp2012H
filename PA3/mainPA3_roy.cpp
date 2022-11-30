#include <iostream>
using namespace std;

// some constraints for board
const int MAX_ROW = 15, MAX_COL = 15;
const int MAX_CONSTRAINT_NUM = 15;  // constraint cannot exceed MAX_ROW/MAX_COL

// board and its size
int num_rows = 0, num_cols = 0;
char board[MAX_ROW][MAX_COL] = {{0}};

// constraints and their sizes
int num_row_constraints[MAX_ROW] = {0}, num_col_constraints[MAX_COL] = {0};
int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM] = {{0}};
int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};

/**********************************
 * Part 1: Initialize the board   *
 **********************************/

/**
 **********  Task 1  **********
 * 
 * This function reads the board size and constraints from user input,
 * store the information in global variables and init the board.
 * 
 * Don't forget to check whether row/column constraints are valid.
 * Please refer to webpage for a detailed description.
 *
 * For simplicity, we assume the user's other inputs are always valid.
 */
void get_input_board() {
    int validity = 0, count = 0, k = 0;
    char input[50];
    bool repeat = true;

    cout << "Enter the number of rows: ";
    cin >> num_rows;
    cout << "Enter the number of columns: ";
    cin >> num_cols;
    cin.ignore();
    //int i = -1;     // just use -1 for demo

    for (int i = 0; i < num_rows; i++){
        repeat = true;
        while (repeat){
            validity = 0; k = 0; num_row_constraints[i] = 0;
            for (int j = 0; j < MAX_ROW; j++){
                input[j] = 0;
            }
            cout << "Enter the number of constraints for row " << i << " (end with -1): ";
            cin.getline(input, 50, '\n');
            for (int j = 0; j < 100; j++){
                if (input[j+1]=='-'||input[j]=='-'){row_constraints[i][k+1] = '\0'; break;}
                if (input[j]!=' '){
                    row_constraints[i][k] = input[j] - '0'; k++;
                    num_row_constraints[i]++;
                    validity += input[j] - '0';
                }else{validity++;}
            }

            if (validity > num_cols){
                cout << "Invalid row constraint, please try again." << endl;
                repeat = true;
            }else{
                repeat = false;
            }
        }
    }

    for (int i = 0; i < num_cols; i++){
        repeat = true;
        while (repeat){
            validity = 0; k = 0; num_col_constraints[i] = 0;
            for (int j = 0; j < MAX_COL; j++){
                input[j] = 0;
            }
            cout << "Enter the number of constraints for column " << i << " (end with -1): ";
            cin.getline(input, 50, '\n');
            for (int j = 0; j < 100; j++){
                if (input[j+1]=='-'||input[j]=='-'){col_constraints[i][k+1] = '\0'; break;}
                if (input[j]!=' '){
                    col_constraints[i][k] = input[j] - '0'; k++;
                    num_col_constraints[i]++;
                    validity += input[j] - '0';
                }else{validity++;}
            }

            if (validity > num_rows){
                cout << "Invalid column constraint, please try again." << endl;
                repeat = true;
            }else{
                repeat = false;
            }
        }
    }
    
    // END YOUR CODES HERE
}


/**
 **********  Task 2  **********
 *
 * This function prints the board and the constraints for each row and column.
 * Constraints should be printed on the bottom of each column and on the left of each row.
 *
 * You may find an example in webpage.
 */
void print_board() {
    int max_row = 0, max_col = 0;int nob = 0;

    for (int i = 0; i < num_rows; i++){
        if (num_row_constraints[i]>max_row)max_row = num_row_constraints[i];
    }

    for (int i = 0; i < 2*max_row+5 ; i++){
    cout << " ";
    }

    for (int i = 0; i < num_cols; i++){
        cout << char(65+i) << " ";
    }cout << endl;

    for (int i = 0; i < num_rows; i++){
        if (num_row_constraints[i] < max_row){
            for (int j = 0; j < max_row-num_row_constraints[i]; j++){
                cout << "  ";
            }
        }

        for (int j = 0; j < num_row_constraints[i]; j++){
            cout << row_constraints[i][j] << " ";
        }

        if (i<10){
            cout << "|  " << i;  
        }else{
            cout << "| " << i;
        }
        

        for (int j = 0; j < num_cols; j++){
            if (board[i][j]==0){
                cout << " .";
            }else{
                cout << " X";
            }
        }cout << endl;

    }

    max_col = 0;

    for (int i = 0; i < num_cols; i++){
        if (num_col_constraints[i]>max_col)max_col = num_col_constraints[i];
    }

    for (int i = 0; i < max_col; i++){
        for (int k = 0; k < 2*max_row+5-1 ; k++){
        cout << " ";
        }

        for (int j = 0; j < num_cols; j++){
            if (num_col_constraints[j]==0||col_constraints[j][i]==0){
                cout << "  ";
            }else{
                cout << " " << col_constraints[j][i];
            }

        }cout << endl;
    }
}



/********************************
 * Part 2: User play on board   *
 ********************************/

/**
 **********  Task 3  **********
 *
 * This function will be called when user choose to set/unset a cell. 
 *
 * You need to:
 * 1. Ask user to input which cell he/she wants to modify
 * 2. Check if the user input is a valid cell(i.e., it is within the board)
 *    If invalid, keep asking the user to input.
 * 3. Set/unset the cell
 * 4. Print the new board
 */
void user_operate_board() {
    char input[50]{'\0'};
    bool repeat = true;
    int row_choice = 0;
    cin.ignore();
    while (repeat){
        for (int i = 0; i < 5; i++)input[i] = '\0';
        cout << "Enter the cell you want to modify (e.g. A 2): ";
        cin.getline(input, 50, '\n');
        if (input[4]!='\0'){
            row_choice = num_rows;
        }else if (input[3]!='\0'){
            row_choice = 10*(input[2] - '0') + (input[3] - '0');
        }else{
            row_choice = input[2] - '0';
        }
        if (((input[0] - 'A')>=num_cols)||(row_choice>=num_rows)||(input[2] == '-')){
            cout << "Invalid row or column. Try again." << endl;
        }else{
            repeat = false;
        }
    }
    if (board[row_choice][input[0]-'A'] == 1)board[row_choice][input[0]-'A'] = 0;else board[row_choice][input[0]-'A'] = 1;
}


/**
 **********  Task 4  **********
 *
 * This function will be called after user finish filling the whole board.
 * You need to check whether his/her solution is correct, 
 * i.e., follow all constraints.
 *
 * Return true if his/her solution is correct; false otherwise.
 */
bool check_whole_board_valid() {
    int count = 0, k = 0;
    bool initial = true;
    for (int i = 0; i < num_rows; i++){
        k = 0;
        if (row_constraints[i][k] == 0){
            for (int j = 0; j < num_cols; j++){
                if (board[i][j]==1)return false;
            }continue;
        }
        
        initial = true;
        count = 0;
        for (int j = 0; j < num_cols; j++){
            if (board[i][j]==1){
                count++;
                initial = false;
                if ( j == num_cols - 1){
                    if (row_constraints[i][k] != count){
                        return false;
                    }
                }
            }else if ((!initial)){
                if (board[i][j-1]==0) continue;
                if (row_constraints[i][k] != count){
                    return false;
                }else{
                count = 0;
                k++;
                }
            
            }if (( j == num_cols - 1 )&& (initial)) return false;
        }
    }

    for (int i = 0; i < num_cols; i++){
        k=0;
        if (col_constraints[i][k] == 0){
            for (int j = 0; j < num_rows; j++){
                if (board[j][i]==1)return false;
            }continue;
        }

        initial = true;
        count = 0;
        for (int j = 0; j < num_rows; j++){
            cout << col_constraints[i][k] << endl;
            if (col_constraints[i][k] == 0)continue;
            if (board[j][i]==1){
                count++;
                initial = false;
                if ( j == num_rows - 1){
                    if (col_constraints[i][k] != count){
                        return false;
                    }
                }
            }else if (!initial){
                if (board[j-1][i]==0) continue;
                if (col_constraints[i][k] != count){
                    return false;
                }else{
                    count = 0;
                    k++;
                }
                
            }if (( j == num_rows - 1 )&& (initial)) return false;
        }
    }

    return true;    // added to pass compilation

    // END YOUR CODES HERE
}


/*******************************
 * Part 3: A nonogram solver   *
 *******************************/

/**
 **********  Task 5  **********
 *
 * This function coverts a position vector of a row into a real row.
 * 
 * For example, if num_col = 8, position vector = {0, 3, 5}, 
 * row_constraint for this row is {2, 1, 1}, then the row should be:
 * [X X . X . X . .]
 * It will store the result row in variable 'result_row[]'
 *
 * You may assume the parameters given are always valid.
 */
void positions_to_row(int row_idx, const int positions[], int num_pos, char result_row[]) {
    int count = 0;
    for (int i = 0; i < num_pos; i++){
        if (i == positions[count]){
            for (int j = i; j < i+row_constraints[row_idx][count]; j++){
                result_row[j] = '1';
            }i += row_constraints[row_idx][count]-1; count++; 
        }else{result_row[i] = '0';}
    }
}


/**
 **********  Task 6  **********
 * 
 * This function checks if the given block on given row can be shifted right
 * for one cell. 
 * For example, if the position vector is {0, 4, 6}, num_col = 8
 * then the row is: [X X . . X . X .], and there are 3 blocks
 * then block_can_shift(row_idx, 0, {0, 4, 6}) = true, 
 *      block_can_shift(row_idx, 1, {0, 4, 6}) = false, since it will hit 2nd block after shift
 *      block_can_shift(row_idx, 2, {0, 4, 6}) = true.
 * 
 * More details can be found on webpage.
 */
bool block_can_shift(int row_idx, int block_idx, const int positions[], int num_pos) {
    char result_row[MAX_COL];
    positions_to_row(row_idx, positions, num_pos, result_row);
    if (result_row[positions[block_idx]+row_constraints[row_idx][block_idx]+1]=='0'||positions[block_idx]+row_constraints[row_idx][block_idx]==num_pos-1){
        return true;
    }else{return false;}
}

// this array stores all valid permutations for each row
// it's expected that num of permutations for each row should not exceed 2^(num_cols)
const int MAX_PERM = 1 << MAX_COL;     // A way to calculate 2^(num_cols)
char row_perms[MAX_ROW][MAX_PERM][MAX_COL];
// this array stores num of permutations for each row
int num_row_perms[MAX_ROW] = {0};


/**
 **********  Task 7  **********
 * 
 * This function gets all valid permutations for a row, 
 * and store all results in global variables 'row_perms' and 'num_row_perms'.
 * 
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'block_can_shift()', etc.
 * 
 */

void perm(int row_idx, int block_idx, const int positions[], int num_pos){
    int tmp_positions[MAX_COL];
    char result_row[MAX_COL];

    for (int i = 0; i < num_cols ; i++){
        tmp_positions[i] = positions[i];
    }

    while (true){
        positions_to_row(row_idx, tmp_positions, num_pos, result_row);

        for (int i = 0; i < num_cols ; i++){
            row_perms[row_idx][num_row_perms[row_idx]][i] = result_row[i];
        }num_row_perms[row_idx]++;

        if (!(block_can_shift(row_idx,block_idx,tmp_positions,num_pos)))break;
        tmp_positions[block_idx]++;
    }

    for (int i = block_idx - 1; i >= 0; i--){

        if (block_can_shift(row_idx, i, tmp_positions, num_pos)){ 
            tmp_positions[i]++;
            for (int j = i+1; j < num_row_constraints[row_idx]; j++){
                tmp_positions[j] = tmp_positions[j-1]+row_constraints[row_idx][j-1]+1;
            }
            perm(row_idx, block_idx, tmp_positions,num_pos);
            break;
        }
    }

    return;
}

void get_row_perms(int row_idx) {
    char result_row[MAX_COL];
    int positions[MAX_COL];
    int tmp_positions[MAX_COL];
    int num_pos = num_row_constraints[row_idx];
    positions[0] = 0;
    for ( int i = 1; i < num_pos; i++){
        positions[i] = positions[i-1]+row_constraints[row_idx][i-1]+1;
    }

    positions_to_row(row_idx,positions,num_pos,result_row);

    perm(row_idx, num_row_constraints[row_idx]-1,positions, num_pos);

    for (int j = 0; j <= num_row_perms[row_idx];j++){
        for (int i = 0; i < num_cols; i++){
            cout << row_perms[row_idx][j][i];
        }cout << endl;
    }
}

/**
 **********  Task 8  **********
 * 
 * This function checks if current state is valid, after 
 * we finish filling 'num_complete_rows' rows.
 *
 * For example, if num_complete_rows = 2, it will only check
 * if the first two rows (with index 0 and 1) do not 
 * break column constraints.
 *
 * Note that this function is different from 'check_whole_board_valid()'
 * in 2 ways:
 * 1. We don't check whole board here, only check the first 'num_complete_rows' rows.
 * 2. We don't (need to) check row_constraints here, only check column_constraints.
 *    This is because this function will only be called during solver, 
 *    so the rows are generated in permutation process, which must be valid.
 */
bool check_rows_valid(int num_complete_rows) {
    // START YOUR CODES HERE

    return true;    // added to pass compilation

    // END YOUR CODES HERE
}


/**
 **********  Task 9  **********
 * 
 * This function will solve the board, and store the solution
 * into board[][] directly.
 * 
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'get_row_perms()', �焝heck_rows_valid()��, etc.
 */
void solve() {
    // START YOUR CODES HERE

    // END YOUR CODES HERE
}


int main() {
    get_input_board();
    print_board();

    while (true) {
        cout << "===== Welcome to Nonogram Game =====" << endl;
        cout << "Please enter your choice:" << endl;
        cout << "Enter 'p' to print the current board." << endl;
        cout << "Enter 'm' to modify a cell." << endl;
        cout << "Enter 'c' to check your solution." << endl;
        cout << "Enter 's' to invoke solver." << endl;
        cout << "Enter 'q' to quit." << endl;
        cout << "Your choice: ";
        char input;
        cin >> input;
        if (input == 'p') {
            print_board();
        } else if (input == 'm') {
            user_operate_board();
        } else if (input == 'c') {
            if (check_whole_board_valid()) {
                cout << "Congratulations! Your solution is correct!" << endl;
            } else {
                cout << "Ahh, your solution is incorrect, try again." << endl;
            }
        } else if (input == 's') {
            cout << "Generating solution:" << endl;
            solve();
            print_board();
        } else if (input == 'q') {
            cout << "Bye!" << endl;
            break;
        } else {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return 0;
}