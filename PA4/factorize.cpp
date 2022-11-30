#include<iostream>
#include<cmath>
using namespace std;
const int MAX_FACTORS=100;
const long long MAX_VALUE=1000000;
bool is_prime(const long long num);
void factorize(unsigned long long num, long long primefactor_list[MAX_FACTORS], int& num_factors);


bool is_prime(const long long num){
    for (int divisor = 2; divisor < sqrt(num); divisor++)
    {if(num % divisor==0)return false;}
    return true;
}
void factorize(unsigned long long num, long long primefactor_list[MAX_FACTORS], int& num_factors){
    int divisor = 3;
    int idx = 0; 
    if(num==1){primefactor_list[idx]=1;num_factors++;}
    while (num > 1 && num%2==0)
    {
        num/=2;
        primefactor_list[idx]=2;
        idx++;
        num_factors++;
    }
    while (num > 1 && num%3==0)
    {
        num/=3;
        primefactor_list[idx]=3;
        idx++;
        num_factors++;
    }
    while (num > 1)
    {
        if(divisor > sqrt(num)){primefactor_list[idx]=num;num_factors++;return;}
        if(num % divisor==0 && is_prime(divisor)){
                num/=divisor;
                primefactor_list[idx]=divisor;
                idx++;
                num_factors++;
                
        }else{
            divisor+=2;
        }
    }
}
int main(int argc, char **argv){
    unsigned long long start_num = strtoull(argv[1], NULL, 10);
    unsigned long long end_num = strtoull(argv[2], NULL, 10);
    if(end_num<start_num)return 0;
    int num_factors=0;
    long long primefactor_list[MAX_FACTORS]={0};
    // cout<<start_num<<" "<<end_num<<endl;
    // int x,y=0;
    // fermet(start_num,x,y);
    for (unsigned long long num = start_num; num <= end_num; num++)
    {
        num_factors=0;
        factorize(num, primefactor_list, num_factors);
        //print
        cout<<num<<"=";
        for(int i = 0; i < num_factors; i++)(i!=num_factors-1)?cout<<primefactor_list[i]<<"*":cout<<primefactor_list[i];
        cout<<endl;
    }
}