#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int square_size=0;int number=0;
    int square[100][100];
    cin>>square_size;
    for(int j = 0; j < square_size;j++){
        for(int i = 0; i < square_size;i++){
            cin>>number;
            if(number!='\0'&&number!=' ')
            square[j][i]=number;
            }
    }
    int sum[100], idx=0, kkk=1;
    int permutations[100*100][2];
    for(int j = 1; j < square_size+1;j++){
        for(int i = 1; i < square_size+1;i++){
                permutations[idx][0]=i;
                permutations[idx][1]=j;
                idx++;
            }
    }
    for(int o=0; o<square_size;o++){
    for (int m = 0; m < square_size; m++)
    {
            for (int i = 0; i < square_size*square_size; i++)
            {
                for (int j = m; j < permutations[i][0]+m; j++)
                {
                        for (int k = 0; k < permutations[i][1]; k++)
                    {
                        sum[i+square_size*square_size*m*kkk]+=square[j][k];
                    }
                }
                // cout<<sum[i]<<"\n";
            }
         
    }
    //swap col
    int temp[100],tempidx=0;
    for (int k = 0; k < square_size-1; k++){
    for (int i = 0; i < square_size; i++)
    {
        temp[i]=square[i][k];
        square[i][k]=square[i][k+1];
        square[i][k+1]=temp[i];
        kkk++;
    }
    }
    
    }
    int max=sum[0];
    for (int i = 0; i < square_size*square_size*square_size; i++)
    {
        max=(sum[i]>max)?sum[i]:max;
    }
    cout<<max;
    return max;
}
// 4
// 0 -2 -7 0 9 2 -6 2
// -4 1 -4  1 -1

// 8  0 -2
// >>15
// 4
// 0 -2 -7 0 9 2 -6 2 -4 1 -4 1 -1 8 0 -2