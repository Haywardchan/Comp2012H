#include <iostream> 
using namespace std; 

char month_name[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char week_name[7][3] = {"Su","Mo","Tu","We","Th","Fr","Sa"};

bool leap(int year) 
{
    bool result;

    result = (year%4 != 0) ? false          
            : ((year%100 != 0) ? true
                :((year%400 != 0) ? false : true
                 )
              );
    return result;
    };

int length_of_name(char const s[]);

int length_of_name(char const s[])
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int initial_week(int day,char ms)// cal day of the week //m: mon=0 - sun=6 ; s: sun=0 - sat=6
{
    int result;

    switch(ms) 
    {
        case 's':
            result = (day+3)%7 ;
            break;
        case 'm':
            result = (day+2)%7 ;
            break;
    }
    return result;
}

int num_day_of_mth(int yr, int mth)
{
    int result;

    switch(mth)
    {
        case 1: case 3: case 5: case 7: case 8: case 10:  case 12:
            result = 31;
            break;    
        case 4: case 6: case 9: case 11:
            result = 30;
            break;
        case 2:
            if (leap(yr))
                    result = 29;
            else
                    result = 28;
            break; 
    }
    return result;
}

void hori_calendar(int yr,int mth, int init_week, int num_mth,bool repeat) // print horizontal calendar // yr,mth:initial year, month ; init_week : day of the week of 1st of that month ; num_mth : print how many month (continous)
{
    int day[3][6][7]; //which month,which line,which day on that line //intialize with all value = 0
    int year[3]; //store the year of each month
    int new_init_week = init_week;
    int init_mth = mth; //initial month for whole year calenadar
    int tempyr = 0;

    if ((repeat) && (mth==13))
        return ;

    for (int i=0 ;i < num_mth; ++i)  //initialize the array of date and month
        for (int j=0; j < 6; ++j)
            for (int k = 0; k < 7; ++k)
                day[i][j][k] = 0;

    for (int i=0 ;i < num_mth; ++i) // create the array of date and month // and year **new add
        {
        year[i] = yr;
        int no_day = 1;
        init_week = new_init_week;  
            for (int j=0; j < 6; ++j)
                {
                    if (no_day > (num_day_of_mth(yr,mth)))
                        break;
                    for (int k = init_week; k < 7; ++k)
                        {
                            day[i][j][k] = no_day++;
                            if (no_day > (num_day_of_mth(yr,mth)))
                                {
                                    new_init_week = ((k + 1) % 7);
                                    break;
                                }
                        }
                    init_week = 0;
                }
        mth = mth + 1;
        if (mth > 12)
            {
                mth = 1;
                yr++;
            } ;
             
        }
     
    for (int i=init_mth-1; i< num_mth+init_mth-1; ++i) //print the month title
    {
        if(repeat)
            {
                cout.width(22); cout << left << month_name[i];
            }
        else
            {
                cout << month_name[i%12] << " " << year[tempyr++];
                cout.width(22-length_of_name(month_name[i%12])-5);
                cout << "";
            }
    };
    cout << endl; //go to next line after printing title

    cout.width(0);//print the week title
    for(int i=0; i < num_mth; ++i)//print the week title
    {
        for(int j=0 ;j < 7; ++j)
        {
            cout << week_name[j] << " ";
        }
        cout << " ";
    }

    cout << endl; //go to next line after printing title

    for (int j=0 ;j < 6; ++j)     // print the date
        {
            if (((day[0][5][0]==0)&&(day[1][5][0]==0)&&(day[2][5][0]==0))&&(j==5))
                continue;
            for (int i=0 ;i < num_mth; ++i)
                {
                    for (int k=0 ;k < 7; ++k)
                        {
                            cout.width(2) ;
                            if (day[i][j][k]!= 0)
                                cout << right <<day[i][j][k];
                            else
                                cout <<"  ";
                            cout <<" ";
                        }
                    cout << " ";

                }
        cout << endl;
        }
    if(repeat)
        {
            cout << endl;
            init_mth +=3;
            hori_calendar(yr,init_mth,new_init_week,num_mth,repeat);
        }

    return ;
};

int vert_calendar(int yr,int mth, int init_week)
{
    int count = 1 ;
    int start_date = 7-init_week+1;
    if(start_date == 8)
        start_date = 1;
    int day = start_date;

    cout << month_name[mth-1] <<" "<< yr << endl ;
    for(int i = 0; i<7; ++i)
        {
            cout << week_name[i] << " " ;
            if ((i < init_week) && (day < start_date+init_week))
                cout << "   ";
            while (day <= num_day_of_mth(yr,mth))
                {
                    cout.width(2); cout << day << " ";
                    day += 7;
                }
            if ((i+1)<init_week)
                day = start_date + i + 1 ;
            else if ((i+1)==init_week)
                    {   
                        day = 1; start_date=1 ; 
                    }
            else
                day = start_date + count++ ;
                
            cout << endl;

        }
return 0;

};

int main() 
{
    int in_yr, in_mth ; 
    int yearfrom1800, dayfrom1800 ;
    int temp_year = 1800, temp_mth = 1; //just for cal no. of day, not meaningful
    int init_week; 
    int num_mth = 1; //number of month to be print in one row
    char in_ms, in_hv;
    bool whole_year = false;
    

    do
    { 
        cout << "Enter year (in range 1800-9999): ";    cin >> in_yr ;
    } while ((in_yr < 1800) || (in_yr > 9999));
    do
    {
        cout << "Enter month (in range 1-12): ";    cin >> in_mth ;
    } while ((((in_mth < 1) || (in_mth > 12)) && !((in_mth == -3) || (in_mth == -1))));
    if( (in_mth >= 1) && (in_mth <= 12) )
        {
            do
            {
                cout << "Enter the first day of week ('s' for Sunday, 'm' for Monday): "; cin >> in_ms;
            } while ((in_ms!='s')&&(in_ms!='m')) ;
            do
            {
                cout << "Print horizontally (h) or vertically (v): "; cin >> in_hv;
            } while ((in_hv!='h')&&(in_hv!='v'));

        }
    else if(in_mth==-3)
            {   
                num_mth = 3;
                in_hv ='h';
                in_ms ='s';
                switch(in_yr)
                {
                    case 1800 :
                        do
                            {
                                cout << "Enter the month in the center (in range 1-12): "; cin >> in_mth;
                            }while((in_mth < 2) || (in_mth > 12));
                        break;
                    case 9999 :
                        do
                            {
                                cout << "Enter the month in the center (in range 1-12): "; cin >> in_mth;
                            }while((in_mth < 1) || (in_mth > 11));
                        break;
                    default :
                        do
                            {
                                cout << "Enter the month in the center (in range 1-12): "; cin >> in_mth;
                            }while((in_mth < 1) || (in_mth > 12));

                };
                if(--in_mth==0)
                    {in_mth=12; in_yr--;};
                
            }
    else 
        {
            num_mth = 3;
            in_hv = 'h';
            in_ms ='s';
            in_mth = 1 ;
            whole_year = true;
            cout << "Year " << in_yr <<endl;
        };

    yearfrom1800 = in_yr - 1800;       //12- cal total no. of day from 1 Jan 1800
    dayfrom1800 = yearfrom1800*365;
    while (temp_year < in_yr) // cal no. of day by counting leap year // cal no. of day from 1Jan 1800
    {
        if (temp_year%4 != 0) 
            temp_year++;
        else if (temp_year%100 != 0)
            {
                dayfrom1800++;
                temp_year++;
            }
        else if (temp_year%400 != 0)
            temp_year++;
        else
            {
                dayfrom1800++;
                temp_year++;
            }
    }

    while (temp_mth < in_mth)
    {
        switch(temp_mth)
        {
            case 1: case 3: case 5: case 7: case 8: case 10:
                dayfrom1800 += 31;
                temp_mth ++;
                break;    
            case 4: case 6: case 9: case 11:
                dayfrom1800 += 30;
                temp_mth ++;
                break;
            case 2:
                if (leap(in_yr))
                    {   
                        dayfrom1800 += 29;
                        temp_mth ++;
                    }
                else
                    {
                        dayfrom1800 += 28;
                        temp_mth ++; 
                    }
                break;
        }
    }
    //cout << dayfrom1800 << endl ;
    init_week = initial_week(dayfrom1800,in_ms);
    
    if(in_ms == 'm')
     {
          week_name[0][0] = 'M' ; week_name[0][1] = 'o' ;
          week_name[1][0] = 'T' ; week_name[1][1] = 'u' ;
          week_name[2][0] = 'W' ; week_name[2][1] = 'e' ;
          week_name[3][0] = 'T' ; week_name[3][1] = 'h' ;
          week_name[4][0] = 'F' ; week_name[4][1] = 'r' ;
          week_name[5][0] = 'S' ; week_name[5][1] = 'a' ;
          week_name[6][0] = 'S' ; week_name[6][1] = 'u' ;
     };

    switch (in_hv)
    {
    case 'h':
        hori_calendar(in_yr,in_mth,init_week,num_mth,whole_year);
        break;
    case 'v':
        vert_calendar(in_yr,in_mth,init_week);
        break;
    };


    return 0 ;
}