#include<iostream>
using namespace std;
//Prime factorization using Sieve O(logn)
//create a same size array to store the smallest prime factor for every number
long long MAX_VALUE=1000000;
const int MAX_FACTORS=10000;
int primefactor_list[MAX_FACTORS]={0};
//sieve of eratostenes
void erato_sieve(int sf[]){
    sf[1]=1;
    for (int i = 2; i < MAX_VALUE; i++) sf[i]=i;    //set all non 1 arrays as its own value
    for (int i = 4; i < MAX_VALUE; i+=2) sf[i]=2;   //set value of all multiples of 2 and not 2 to be 2 (remove even numbers)
    for (int i = 3; i < MAX_VALUE; i+=3)sf[i]=3; 
    for (int i = 3; i*i < MAX_VALUE; i++)
    {
        if(sf[i]==i){                               //if prime then
            for (int j = i*i; j < MAX_VALUE; j+=i)  //set all multiples of the odd numbers to be the factor of smaller factors
            {if(sf[j]==j)sf[j]=i;}
        }
    }
}
//factorize the number by dividing the smallest prime factor each time
void factorize(long long num, int &num_factors, int sf[]){
    num_factors=0;
    while (num>1)
    {
        primefactor_list[num_factors]=sf[num];
        num/=sf[num];
        num_factors++;
    }
    return;
}

int main(int argc, char **argv){
    int num_factors=0;
    int sf[MAX_VALUE]={0};
    long long start_num = strtoll(argv[1], NULL, 10);
    long long end_num = strtoll(argv[2], NULL, 10);
    MAX_VALUE=end_num;
    if(end_num<start_num)return 0;
    erato_sieve(sf);
    factorize(start_num,num_factors, sf);
    cout<<start_num<<"=";
    for(int i = 0; i < num_factors; i++)(i!=num_factors-1)?cout<<primefactor_list[i]<<"*":cout<<primefactor_list[i];
    cout<<endl;
}