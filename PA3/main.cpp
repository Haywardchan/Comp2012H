#include <iostream>
using namespace std;

// some constraints for board
const int MAX_ROW = 15, MAX_COL = 15;
const int MAX_CONSTRAINT_NUM = 15;  // constraint cannot exceed MAX_ROW/MAX_COL

// board and its size
int num_rows = 0, num_cols = 0;
char board[MAX_ROW][MAX_COL] = {{0}};

// constraints and their sizes
int num_row_constraints[MAX_ROW] = {0}, num_col_constraints[MAX_COL] = {0};//test
int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM] = {{0}};
int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};
// int num_row_constraints[MAX_ROW]={1,3,1,2,2,2};
// int num_col_constraints[MAX_COL]={2,1,3,2,2,2};
//test case
// num_rows=5;
// num_cols=5;
// int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2},{2, 2},{0},{1, 1},{3}};
// int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1},{2, 1},{1},{2, 1},{2, 1}};
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
void WRITE_TO_FROM(char arr1[MAX_COL], char arr2[MAX_COL]){
    for (int i = 0; i < MAX_COL; i++)
    {
        arr1[i]=arr2[i];
    }
}
//no problem
void get_input_board() {
    int row_constraint_index=0, col_constraint_index=0, count_constraint=0;
    char str[30]={0};
    do
    {
        cout << "Enter the number of rows: ";
        cin >> num_rows;
        // cout << num_rows;
    } while (num_rows > MAX_ROW && num_rows < 1);
    do
    {
        cout << "Enter the number of columns: ";
        cin >> num_cols;
    } while (num_cols > MAX_COL && num_cols < 1);
    cin.ignore(100, '\n');
    // //get row constraint
    for(int i = 0; i < num_rows; i++){
        count_constraint=0;
        num_row_constraints[i]=0;
        row_constraint_index=0;
            cout << "Enter the number of constraints for row " << i << " (end with -1): ";
            cin.getline(str, 30, '\n');
            // cout<<str;
            for (int j = 0; j < 30; j++)
            {
                if(str[j]=='-'){row_constraints[i][row_constraint_index]=-1;break;}
                if(str[j]>'0'&&str[j]<='9'){
                    row_constraints[i][row_constraint_index]=str[j]-'0';
                    // cout<<"this:  "<<row_constraint_index<<": "<< row_constraints[i][row_constraint_index];
                    count_constraint++;
                    count_constraint+=row_constraints[i][row_constraint_index];
                    num_row_constraints[i]++;
                    row_constraint_index++;}
                else continue;
            }
            count_constraint--;
            if (num_cols < count_constraint){
                cout << "Invalid row constraint, please try again." << endl;
                i--;
                for (int j = 0; j < 30; j++){
                    str[j] = 0;
                }
                count_constraint=0;
            }
            // cout<< row_constraints[i][row_constraint_index]<<"count:"<<count_constraint;

    }
    for(int i = 0; i < num_cols; i++){
        count_constraint=0;
        num_col_constraints[i]=0;
        col_constraint_index=0;
            cout << "Enter the number of constraints for column " << i << " (end with -1): ";
            cin.getline(str, 30, '\n');
            // cout<<str;
            for (int j = 0; j < 30; j++)
            {
                if(str[j]=='-'){/* cout<<"break!"; */col_constraints[i][col_constraint_index]=-1;break;}
                if(str[j]>'0'&&str[j]<='9'){
                    // cout<<"this "<<str[j]<<" this";
                    col_constraints[i][col_constraint_index]=str[j]-'0';
                    // cout<<"this:  "<< col_constraints[i][col_constraint_index];
                    count_constraint++;
                    count_constraint+=col_constraints[i][col_constraint_index];
                    num_col_constraints[i]++;
                    col_constraint_index++;}
                else continue;
            }
            count_constraint--;
            if (num_rows < count_constraint){
                cout << "Invalid column constraint, please try again." << endl;
                i--;
                for (int j = 0; j < 30; j++){
                    str[j] = 0;
                }
                count_constraint=0;
            }
            // cout<< col_constraints[i][col_constraint_index]<<"count:"<<count_constraint;

    }
    // num_rows=5;
    // num_cols=5;
    // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2},{2, 2},{0},{1, 1},{3}};
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1},{2, 1},{1},{2, 1},{2, 1}};
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            board[i][j]='.';
        }
    }
    // cout<<"this:"<<num_row_constraints[0]<<"that:"<<num_row_constraints[1];

    // cout << "test : " << col_constraints[0][0];
    //print
    // for (int i = 0; i < num_rows; i++)
    // {
    //     cout<<row_constraints[i][0];
    // }
    
    //test casen
    // int num[MAX_ROW][MAX_COL]={{0,0},{0,1},{0,3},{0,4},{1,0},{1,1},{1,3},{1,4},{3,0},{3,4},{4,1},{4,2},{4,3},{2,2}};
    // for(int i=0;i<MAX_ROW;i++)board[num[i][0]][num[i][1]]='X';
    // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2},{2, 2},{0},{1, 1},{3}};
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1},{2, 1},{1},{2, 1},{2, 1}};
}

/**
 **********  Task 2  **********
 *
 * This function prints the board and the constraints for each row and column.
 * Constraints should be printed on the bottom of each column and on the left of each row.
 *
 * You may find an example in webpage.
 */
template<typename T>
int size(const T arr[]){
    return *(&arr + 1) - arr;
}
void print_board() {
    //set initial value of board for testing
    int count=0, row_constraint_index=0, col_constraint_index=0, max_row_constraint=0, max_col_constraint;
    //case 1
    // num_rows=5;
    // num_cols=5;
    // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2, -1},{2, 2, -1},{-1},{1, 1, -1},{3, -1}};
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1, -1},{2, 1, -1},{1, -1},{2, 1, -1},{2, 1, -1}};
    // //case 2
    // // num_rows=12;
    // // num_cols=12;
    // // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 1, 2, 4, -1},{5, 2, -1},{1, 1, 3, 1, -1},{2, 2, 3, -1},{4, 1, 3, -1},{1,1,8,-1},{2,1,1,1,-1},{1,2,2,3,-1},{5,4,-1},{2,1,1,-1},{2,6,-1},{3,1,1,3,-1}};
    // // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{1, 5, 1, -1},{1, 2, 3, 1, -1},{2, 2, 1, 1, -1},{2, 1, 3, 1, -1},{3, 6, -1},{4,1,1,2,-1},{3,3,1,-1},{2,1,3,-1},{1,1,1,1,1,-1},{6,2,2,-1},{2,7,1,-1},{1,2,2,1,-1}};
   
    // //find max number of the items in row constraint array
    max_row_constraint=num_row_constraints[0];
    for (int i = 0; i < num_rows; i++)
    {
        max_row_constraint=(num_row_constraints[i]>max_row_constraint)?num_row_constraints[i]:max_row_constraint;
    }
    //find max number of the items in col constraint array
    max_col_constraint=num_col_constraints[0];
    for (int i = 0; i < num_cols; i++)
    {
        max_col_constraint=(num_col_constraints[i]>max_col_constraint)?num_col_constraints[i]:max_col_constraint;
        // cout<<max_col_constraint<<" ";
    }
    //first row to print
    char b_alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < max_row_constraint*2+5; i++){cout<<" ";}
    for (int i = 0; i < num_cols; i++){cout<<b_alphabet[i]<<" ";}
    cout<<"\n";
    //print second to last row of board
    for(int i = 0; i < num_rows; i++){
        row_constraint_index=0;
        for(int j = 0; j < max_row_constraint; j++){
            // cout<<num_row_constraints[i]<<max_row_constraint-j<<"\n";
            if(num_row_constraints[i]>=max_row_constraint-j){cout<<row_constraints[i][row_constraint_index]<<" ";row_constraint_index++;}
            else{cout<<"  ";}
        }
        cout<<"| ";
        (i<10)?cout<<" "<<i:cout<<i;
        for (int k = 0; k < num_cols; k++){cout<<" "<<board[i][k];}
        cout<<"\n";
    }
    //print col constraints
    for(int i = 0; i < max_col_constraint; i++){
        for (int i = 0; i < max_row_constraint*2+5; i++){cout<<" ";}
        for (int j = 0; j < num_cols; j++){
            if(i < num_col_constraints[j]){
                cout<<col_constraints[j][i]<<" ";
            }else{cout<<"  ";}
        }
        cout<<"\n";
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
    char col;
    int row=-1;
    cout << "Enter the cell you want to modify (e.g. A 2): ";
    cin>>col>>row;
    // cout<<col<<row;
    while (col<64||col>(64+num_cols)||row<0||row>num_rows-1)
    {
        cout << "Invalid row or column. Try again." << endl;
        cout << "Enter the cell you want to modify (e.g. A 2): ";
        cin>>col>>row;
        // cout<<col<<row;
    }
    //set or unset value
    if(board[row][col-65]=='.')board[row][col-65]='X';
    else board[row][col-65]='.';
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
    int count_X=0, count_dot=0, row_constraint_index=0, col_constraint_index=0;
    bool next_must_dot=false;
    //test case
    // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2, -1},{2, 2, -1},{-1},{1, 1, -1},{3, -1}};
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1, -1},{2, 1, -1},{1, -1},{2, 1, -1},{2, 1, -1}};
    //check row constraints
    for (int j = 0; j < num_rows; j++)
    {
        row_constraint_index=0;
        next_must_dot=false;
        count_dot=0;
        count_X=0;
        for (int i = 0; i < num_cols; i++)
        {
            if (board[j][i]=='X')
            {
                if(next_must_dot)return false;
                count_X++;
                count_dot=0;
            }else if (board[j][i]=='.')
            {
                if(next_must_dot)next_must_dot=false;
                count_dot++;
                count_X=0;
            }
            if (count_X==row_constraints[j][row_constraint_index])
            {
                row_constraint_index++;
                next_must_dot=true;
            }
            //check empty row constraint
            if(row_constraints[j][0]==-1&&count_X>0)return false;
            // cout<<i<<" "<<row_constraint_index<<" "<<count_dot<<" "<<count_X<<" "<<next_must_dot<<" "<<row_constraints[j][row_constraint_index]<<"\n";
        }
        if(row_constraint_index!=num_row_constraints[j])return false;
    }
    //check col constraints
    for (int j = 0; j < num_cols; j++)
    {
        col_constraint_index=0;
        next_must_dot=false;
        count_dot=0;
        count_X=0;
        for (int i = 0; i < num_rows; i++)
        {
            if (board[i][j]=='X')
            {
                if(next_must_dot)return false;
                count_X++;
                count_dot=0;
            }else if (board[i][j]=='.')
            {
                if(next_must_dot)next_must_dot=false;
                count_dot++;
                count_X=0;
            }
            if (count_X==col_constraints[j][col_constraint_index])
            {
                col_constraint_index++;
                next_must_dot=true;
            }
            //check empty col constraint
            if(col_constraints[j][0]==-1&&count_X>0)return false;
            // cout<<i<<" "<<col_constraint_index<<" "<<count_dot<<" "<<count_X<<" "<<next_must_dot<<" "<<col_constraints[j][col_constraint_index]<<"\n";
        }
        if(col_constraint_index!=num_col_constraints[j])return false;
    }
    
    return true;    // added to pass compilation

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
void positions_to_row(int row_idx, const int positions[MAX_COL], int num_pos, char result_row[MAX_COL]) {

    //create empty dot array
    //cout << positions[0];
    for (int i = 0; i < num_cols; i++){result_row[i]='.';};
    //pos-->row_constraints
    for(int j = 0; j < num_pos; j++)
        for (int i = positions[j]; i < positions[j]+row_constraints[row_idx][j]; i++)            
            {
                result_row[i]='X';
            }
    // for (int i = 0; i < num_cols; i++)
    // {
    //     cout<<result_row[i];
    // }
    // cout<<"\n";
    return;
    
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
bool block_can_shift(int row_idx, int block_idx, const int positions[MAX_COL], int num_pos) {
    // int positions[]={0,3,8}; row_constraint={2,2,1};

    char result_row[MAX_COL]={0};


    //cout << positions[0]<<endl;
    positions_to_row(row_idx,positions,num_row_constraints[row_idx],result_row);
    // cout<<result_row<<"\n";
    //print row constraints
    // for (int i = 0; i < num_row_constraints[row_idx]; i++)
    // {
    //     cout<<row_constraints[row_idx][i]<<" ";
    // }
    // cout<<"\n";
    //check whether the right pos and right right pos are dots

    if(result_row[positions[block_idx]+row_constraints[row_idx][block_idx]]=='.'&&result_row[positions[block_idx]+row_constraints[row_idx][block_idx]+1]!='X')return true;else return false;    
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
// //no problem
void recursive_perms(int row_idx, int block_idx, int positions[MAX_COL], int& num_pos, int& num_perms, int position_arr_perms[MAX_PERM][MAX_CONSTRAINT_NUM]){
    
    int arr[MAX_COL];
    //cout<<"tesyt";

    /* cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl;
    cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl;
    cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl;
    cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl;
    cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl;
    cout<<"test: "<< boolalpha <<block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])<<endl; */



    if(!(block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])))return;//base case
    //while loop
    while( (block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])) ){
            //put position to perm
            //cout << " aaa ";
            positions[block_idx]++;
            for(int i=0; i < num_row_constraints[row_idx]; i++){
                position_arr_perms[num_perms][i]=positions[i];
                // cout<<positions[i];
            }
            num_perms++;
            for(int i=0; i < block_idx; i++){
                arr[i]=positions[i];
            }                                                                                                                         
            if(block_idx-1>=0){
                recursive_perms(row_idx, block_idx-1, positions, num_row_constraints[row_idx], num_perms, position_arr_perms);
                    for(int i = 0; i < block_idx; i++){
                        positions[i]=arr[i];
                    }  
                };
    }
}
// //no problem
void get_row_perms(int row_idx) {

    int position_arr[MAX_CONSTRAINT_NUM]={0};//test
    int starting_position_arr[MAX_CONSTRAINT_NUM]={0};
    int position_arr_perms[MAX_PERM][MAX_CONSTRAINT_NUM]={0};
    int num_perms=0;
    num_row_perms[row_idx]=0;
    //convert constraint to pos vector
    for (int i = 0; i < num_row_constraints[row_idx]; i++)
    {
        if(i==0)position_arr[i]=0;
        else {
            for (int j = 0; j < i; j++){
                position_arr[i]+=row_constraints[row_idx][j];
                // cout<<row_constraints[row_idx][j]<<" ";
                // cout<<position_arr[i]<<"\n";
            }  
            //add space
            position_arr[i]+=i;
        }
    }
    if(num_row_constraints==0){position_arr_perms[row_idx][0]=0;}
    for (int i = 0; i < num_row_constraints[row_idx]; i++)
    {
        starting_position_arr[i]=position_arr[i];
        // cout<<starting_position_arr[i];
        position_arr_perms[0][i]=position_arr[i];
    }
    num_perms++;
    //print pos vect
    // for(int i=0; i< num_row_constraints[row_idx];i++)cout<<position_arr[i]<<" ";

    //cout<<"\n";

    //find perms
    // cout<<row_idx<<" "<<num_row_constraints[row_idx]-1<<" "<<position_arr<<" "<<num_row_constraints[row_idx]<<" "<<num_perms<<" "<<position_arr_perms;
    recursive_perms(row_idx, num_row_constraints[row_idx]-1, position_arr, num_row_constraints[row_idx], num_perms, position_arr_perms);
    
    //print perms
    for (int i = 0; i < num_perms; i++)
    {
        for (int j = 0; j < num_row_constraints[row_idx]; j++)
        {
             //cout<<position_arr_perms[i][j]<<" ";
        }
        positions_to_row(row_idx, position_arr_perms[i], num_row_constraints[row_idx], row_perms[row_idx][i]);
        num_row_perms[row_idx]++;
         //cout<<"\n";
    }
    /* cout << "row " << row_idx << "num perms: " << num_perms<< " " << num_row_perms[row_idx] << endl;
     for(int i = 0; i < num_perms; i++)cout<<row_perms[row_idx][i]<<"\n"; */
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
//no problem
bool check_rows_valid(int num_complete_rows) {
    // int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM]={{2, 2},{2, 2},{0},{1, 1},{3}};
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1},{2, 1},{1},{2, 1},{2, 1}};
    
    int col_idx=0;
    int count_X=0;
    int count_dot=0;
    bool next_must_dot=0;
    int spaces[MAX_COL]={0};
    //cpt spaces
    for (int j = 0; j < num_cols; j++){
        for (int i = 0; i < num_col_constraints[j]; i++)
        {
            spaces[j]+=col_constraints[j][i];
        }
        spaces[j]+=num_col_constraints[j]-1;
        // col_constraints[j][num_col_constraints[j]]=-1;
    }
    //check col constraints
    for (int j = 0; j < num_cols; j++)
    {
        for (int i = 0; i < num_complete_rows; i++)
        {
            if (board[i][j]=='X')
            {
                if(next_must_dot)return false;
                count_X++;
                if(count_X==1&&col_idx==0){
                    // cout<<"hi"<<num_rows-i<<spaces[j]<<"\n";
                    if(num_rows-i<spaces[j])return false;
                }
                count_dot=0;
                if(col_idx==num_col_constraints[j]){col_idx++;}
            }else if (board[i][j]=='.')
            {
                if(next_must_dot)next_must_dot=false;
                count_dot++;
                count_X=0;
            }
            if (count_X==col_constraints[j][col_idx]&&col_idx<num_col_constraints[j])
            {
                col_idx++;
                next_must_dot=true;
                // cout<<"spaces"<<j<<":"<<spaces[j]<<endl;
            }
            //check empty col constraint
            if((num_col_constraints[j]==0)&&count_X>0)return false;

            if(col_idx>num_col_constraints[j])return false;
            // cout<<i<<" "<<col_idx<<" "<<count_dot<<" "<<count_X<<" "<<next_must_dot<<" "<<col_constraints[j][col_idx]<<"\n";
            
        }
        
        // if((num_rows - num_complete_rows) < spaces[j])return false;
        
        if(col_idx!=num_col_constraints[j]&&num_complete_rows==num_rows)return false;
        col_idx=0;count_dot=0;count_X=0;next_must_dot=false;
    }
    return true;    
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

void recursive_solve(int rows_idx, int num_perms){
    // int shift;
    // if(check_rows_valid(num_rows)||rows_idx==num_rows-1)return;//base case
    // get_row_perms(rows_idx);
    // WRITE_TO_FROM(board[rows_idx],row_perms[rows_idx][num_perms]);
    // while (check_rows_valid(rows_idx))
    // {
    //     rows_idx++;
    //     if(rows_idx+1<num_rows)recursive_solve(rows_idx,0);
    //     if(!check_rows_valid(rows_idx)){
    //     WRITE_TO_FROM(board[rows_idx],row_perms[rows_idx][num_perms+1]);
    //     recursive_solve(rows_idx-1,num_perms+1);
    //     }
    // }
    //get_row_perms(rows_idx);
    
    do 
    {
        /* if(rows_idx==0)
            cout <<"    test    " <<num_perms;
        WRITE_TO_FROM(board[rows_idx],row_perms[rows_idx][0]); */
        
        /* cout << "test row " << rows_idx << " perm "<<num_perms<<" : ";
        for(int j = 0; j<5;j++)
            cout << board[2][j];
        cout << endl; */
        


        /* if(1)
        {
            int a;
            print_board();
            cout << "pause ";
            cin >> a;
        }; */
        WRITE_TO_FROM(board[rows_idx],row_perms[rows_idx][num_perms]);
        if(check_rows_valid(rows_idx+1) && (rows_idx<num_rows-1))
            {
                /* if(rows_idx == 12)
                {
                    cout << "this is row " << rows_idx << "perm " << num_perms << " : " << boolalpha << check_rows_valid(rows_idx+1) << endl;
                    print_board();
                    cout << "pause ";
                    int a;
                    cin >> a;
                } ; */  
                recursive_solve(rows_idx+1,0);


            }

        if(check_rows_valid(num_rows))
        {
            return;
        };

        num_perms++;

    } while(num_perms<num_row_perms[rows_idx]);
    
    return;
}
void solve() {
    // row_constraints={{2, 2},{2, 2},{0},{1, 1},{3}};
    // col_constraints={{2, 1},{2, 1},{1},{2, 1},{2, 1}}; 
    for(int i = 0; i<num_rows;i++)
        get_row_perms(i);
    
    recursive_solve(0,0);
    // return true;


}

int main() {
    get_input_board();
    print_board();
    // char result_row[MAX_COL];int positions[]={0,4};
    // positions_to_row(0,positions,size(positions),result_row);//test
    // cout<<size(positions);
    // cout<<block_can_shift(3,0,positions,2)<<"\n";//test

    // const int test_positions[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //cout << "test_positions[0]: " << test_positions[0]<<endl;
    //cout << "test_positions[0]: " << test_positions[0]<<endl;




    /* for(int i = 0; i<num_rows;i++)
        WRITE_TO_FROM(board[i],row_perms[i][0]); */


    // get_row_perms(1);
    // get_row_perms(2);
    // get_row_perms(3);
    // get_row_perms(4);
    // get_row_perms(5);
    // cout<<num_row_perms[4];
    // cout<< check_rows_valid(5);
    // cout<<result_row<<"\n";
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