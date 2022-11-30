bool check_rows_valid(int num_complete_rows) {
    // int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM]={{2, 1, -1},{2, 1, -1},{1, -1},{2, 1, -1},{2, 1, -1}};
    int col_idx=0;
    int count_X=0;
    int count_dot=0;
    bool next_must_dot=0;
    //check col constraints
    for (int j = 0; j < num_cols; j++)
    {
        for (int i = 0; i < num_complete_rows; i++)
        {
            if (board[i][j]=='X')
            {
                if(next_must_dot)return false;
                count_X++;
                count_dot=0;
                if(col_constraints[j][col_idx]==-1){col_idx++;}
            }else if (board[i][j]=='.')
            {
                if(next_must_dot)next_must_dot=false;
                count_dot++;
                count_X=0;
            }
            if (count_X==col_constraints[j][col_idx])
            {
                col_idx++;
                next_must_dot=true;
            }
            //check empty col constraint
            if(col_constraints[j][0]==-1&&count_X>0)return false;
            if(col_idx>num_col_constraints[j])return false;
            // cout<<i<<" "<<col_idx<<" "<<count_dot<<" "<<count_X<<" "<<next_must_dot<<" "<<col_constraints[j][col_idx]<<"\n";
        }
        if(col_idx!=num_col_constraints[j]&&num_complete_rows==num_rows)return false;
        col_idx=0;count_dot=0;count_X=0;next_must_dot=false;
    }
    return true;    
}