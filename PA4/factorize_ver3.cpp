#include<iostream>
using namespace std;
int main(int argc, char **argv){
    long long start_num = strtoll(argv[1], NULL, 10);
    long long end_num = strtoll(argv[2], NULL, 10);
    if(end_num<start_num)return 0;
    int num_factors=0;
    int primefactor_list[MAX_FACTORS]={0};
    for (long long num = start_num; num <= end_num; num++)
    {
        num_factors=0;
        factorize(num, primefactor_list, num_factors);
        //print
        cout<<num<<"=";
        for(int i = 0; i < num_factors; i++)(i!=num_factors-1)?cout<<primefactor_list[i]<<"*":cout<<primefactor_list[i];
        cout<<endl;
    }
}