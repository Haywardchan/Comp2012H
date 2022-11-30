#include <iostream>
using namespace std;
int size(string str)
{
    int i=0;
        while (str[i]!='\0')i++;
        return i;
}
bool contains(int month[], int target,int size){
    for (int i = 0; i < size; i++)
    {
        if (month[i]==target)
        {
            return true;
            break;
        }   
    } return false;
}
int return_dates_in_month(int year, int month){
    int dates_in_month;
    bool leap_year;
    if( (year%400==0 || year%100!=0) && (year%4==0))
    leap_year=true;
    else
    leap_year=false;
    int bigmonth[7]={1,3,5,7,8,10,12};
    int smallmonth[4]={4,6,9,11};
    (contains(bigmonth,month,7))?dates_in_month=31
    :(contains(smallmonth,month,4))?dates_in_month=30
    :leap_year?dates_in_month=29
    :dates_in_month=28;
    return dates_in_month;
}
int return_fd_month(int year, int month){
    int tdays_in_month, tdays_in_year;
    bool leap_year;
    if( (year%400==0 || year%100!=0) && (year%4==0))
    leap_year=true;
    else
    leap_year=false;
    //fd_month
    int bigmonth[7]={1,3,5,7,8,10,12};
    int smallmonth[4]={4,6,9,11};
    // tdays_in_year=(year-1800)*(365) + (year-1801)/4;
    tdays_in_year=0;
    for (int i = 1800; i < year; i++)
    {
        if( (i%400==0 || i%100!=0) && (i%4==0)){
            tdays_in_year+=366;
        }else tdays_in_year+=365;
    }
    
    tdays_in_month=0;
    for (int i = 1; i < month; i++)
    {
        (contains(bigmonth,i,7))?tdays_in_month+=31
        :(contains(smallmonth,i,4))?tdays_in_month+=30
        :leap_year?tdays_in_month+=29
        :tdays_in_month+=28;
    }
    return (3 + tdays_in_year + tdays_in_month) % 7;//sunday is 0
}
void print_horizontal_calendar_s(int fd_month, int dates_in_month, string weekdays_name[]){
    int num_space=0;
    for (int i = 0; i < 7; i++)
            {
                cout << weekdays_name[i] << " ";
            }
            cout<<"\n";
    for (int i = 0; i < fd_month; i++)
            {
                cout << "   ";
                num_space+=3;
            }

    for (int i = 0; i < dates_in_month; i++)
    {
        (i<9)? cout << " " << i+1 << " ":cout << i+1 << " ";
        num_space+=3;
        if (num_space % 21==0){
            cout<<"\n";
                }
            }
}
void print_3_conseq_calendar_s(int fd_month, int dates_in_month, string weekdays_name[], string month_name[], int required_month, int year,int month){
    int num_space=0, num_line=1, temp1, temp2, temp3, dates_in_1stmonth, dates_in_2ndmonth, dates_in_3rdmonth,
    fd_1stmonth, fd_2ndmonth, fd_3rdmonth;
    bool sixth_line_occupied=false;
    if (required_month==1)
    {
        dates_in_1stmonth=return_dates_in_month(year-1,12);
            fd_1stmonth=return_fd_month(year-1,12);
    }else{
        dates_in_1stmonth=return_dates_in_month(year,required_month-1);
            fd_1stmonth=return_fd_month(year,required_month-1);
    } 
    dates_in_2ndmonth=return_dates_in_month(year,required_month);
            fd_2ndmonth=return_fd_month(year,required_month);
    if (required_month==12)
    {
        dates_in_3rdmonth=return_dates_in_month(year+1,1);
            fd_3rdmonth=return_fd_month(year+1,1);
    }else{
        dates_in_3rdmonth=return_dates_in_month(year,required_month+1);
            fd_3rdmonth=return_fd_month(year,required_month+1);
    }
    for (int i = required_month-2; i < required_month+1; i++){
        if (month==-3 && required_month==1)
        {
            (i==required_month-2)?cout << month_name[11]:cout << month_name[i];
        }
        if(month==-3 && required_month==12){
            (i==required_month)?cout << month_name[0]:cout << month_name[i];
        }
        if ((month==-3 && required_month!=1 && required_month!=12) || month==-1)
        {
            cout << month_name[i];
        }
        
        
        if (month==-3 && required_month==12){
            (i==required_month)?cout << " " << year+1:cout << " " << year;
        }else if(month==-3 && required_month==1){
            (i==required_month-2)?cout << " " << year-1:cout << " " << year;
        }else if (month==-3) cout << " " << year;
        if (month==-3)
        {
            if (required_month==1)
            {
                if(i==required_month-2){
                    for (int j = 0; j < 22-size(month_name[11])-5; j++){cout << " ";}
                }else {
                    for (int j = 0; j < 22-size(month_name[i])-5; j++){cout << " ";}
                }
            }
            if (required_month==12)
            {
                if(i==required_month){
                    for (int j = 0; j < 22-size(month_name[0])-5; j++){cout << " ";}
                }else {
                    for (int j = 0; j < 22-size(month_name[i])-5; j++){cout << " ";}
                }
            }
            if(required_month!=1 && required_month!=12){
                for(int j = 0; j < 22-size(month_name[i])-5; j++){cout << " ";}
            }
        }else{
            for(int j = 0; j < 22-size(month_name[i]); j++){cout << " ";}
        } 
    }
    cout << "\n";
    for (int i = 0; i < 3; i++){
        for (int i = 0; i < 7; i++){cout << weekdays_name[i] << " ";}
        cout << " ";
    }
    cout << "\n";
    for (int i = 0; i < fd_1stmonth; i++)
            {   
                cout << "   ";
                num_space+=3;}
    for (int i = 0; i < 7-fd_1stmonth; i++)
        {
            (i<9)? cout << " " << i+1 << " ":cout << i+1 << " ";
            num_space+=3;
        }
    
    cout << " ";
    for (int i = 0; i < fd_2ndmonth; i++)
            {   
                cout << "   ";
                num_space+=3;}
    for (int i = 0; i < 7-fd_2ndmonth; i++)
        {
            (i<9)? cout << " " << i+1 << " ":cout << i+1 << " ";
            num_space+=3;
        }
    
    cout << " ";
    for (int i = 0; i < fd_3rdmonth; i++)
            {   
                cout << "   ";
                num_space+=3;}
    for (int i = 0; i < 7-fd_3rdmonth; i++)
        {
            (i<9)? cout << " " << i+1 << " ":cout << i+1 << " ";
            num_space+=3;
        }
    while (num_line<6)
    {
        temp1= 7*num_line-fd_1stmonth;
        temp3= 7*num_line-fd_3rdmonth;
        temp2= 7*num_line-fd_2ndmonth;
        num_line+=1;
        cout<<"\n";
        for (int i = temp1; i < temp1+7; i++)
            {
                (i < dates_in_1stmonth)?((i<9)? cout << " " << i+1 << " ":cout << i+1 << " "):cout<<"   ";
                num_space+=3;
                if(i<dates_in_1stmonth && num_line==6){sixth_line_occupied=true;}
            }
        cout<<" ";
        for (int i = temp2; i < temp2+7; i++)
            {
                (i < dates_in_2ndmonth)?((i<9)? cout << " " << i+1 << " ":cout << i+1 << " "):cout<<"   ";
                num_space+=3;
                if(i<dates_in_2ndmonth && num_line==6){sixth_line_occupied=true;}
            }
        cout<<" ";
        for (int i = temp3; i < temp3+7; i++)
            {
                (i < dates_in_3rdmonth)?((i<9)? cout << " " << i+1 << " ":cout << i+1 << " "):cout<<"   ";
                num_space+=3;
                if(i<dates_in_3rdmonth && num_line==6){sixth_line_occupied=true;}
            }
    }
    cout<<"\n";
    if (sixth_line_occupied)cout<<"\n";
    
}
void print_horizontal_calendar_m(int fd_month, int dates_in_month, string weekdays_name[]){
    int num_space=0;
    if(fd_month==0){fd_month=7;};
    for (int i = 0; i < 7; i++)cout << weekdays_name[(i+1)%7] << " ";
            cout<<"\n";
            fd_month-=1;

            for (int i = 0; i < fd_month; i++)
            {
                cout << "   ";
                num_space+=3;
            }

            for (int i = 0; i < dates_in_month; i++)
            {
                (i<9)? cout << " " << i+1 << " ":cout << i+1 << " ";
                num_space+=3;
                if (num_space % 21==0){
                    cout<<"\n";
                }
            }
}
void print_vertical_calendar(int fd_week,int fd_month, int dates_in_month, string weekdays_name[]){
    for (int i = 0; i < 7; i++)
            {
                // cout<<fd_month;
                while (fd_month<0)
                {
                    fd_month+=7;
                }
                (fd_week=='s')?cout << weekdays_name[i]:cout << weekdays_name[(i+1)%7];
                if (fd_month > i) cout << "   ";
                
                for (int j = 0; j < dates_in_month; j++)
                {
                    if ((j+fd_month-i) % 7==0)(j < 9)? cout << "  " << j+1:cout << " " << j+1 ;
 
                }
                cout << "\n";
            }
}
int main(){
    int year, month, dates_in_month, fd_month, required_month;
    char fd_week, orientation;
    
    // //task1
    do {
        cout << "Enter year (in range 1800-9999): ";
        cin >> year;
        } while (year<1800 || year>9999);
    //bonus part to skip step 3, 4 if month -1, -3 is inputted
    do{
        cout << "Enter month (in range 1-12): ";
        cin >> month;
    } while ((month<1 || month>12) && month!=-1 && month!=-3);
    if(month!=-1 && month!=-3)
    {
        do {
        cout << "Enter the first day of week ('s' for Sunday, 'm' for Monday): ";
        cin >> fd_week;
        } while (fd_week!='s' && fd_week!='m');

        do {
        cout << "Print horizontally (h) or vertically (v): ";
        cin >> orientation;
        } while (orientation!='h' && orientation!='v');
    }

    //testing for task 2 set up
    // year=2022;
    // month=-1;
    // fd_week='s';
    // orientation='v';
    //task2 Horizontal calendars with week starts on Sunday
    
    dates_in_month=return_dates_in_month(year, month);
    fd_month =return_fd_month(year, month);
    string month_name[12] = {"January", "February", "March", "April", "May", 
                    "June", "July", "August", "September",
                    "October", "November", "December"};
    string weekdays_name[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
    if(month!=-1 && month!=-3){
        cout << month_name[month-1] << " " << year << "\n";
        //for horizonal printing of day name
        if (orientation=='h'){
            (fd_week=='s')?print_horizontal_calendar_s(fd_month, dates_in_month, weekdays_name)
            :print_horizontal_calendar_m(fd_month,dates_in_month, weekdays_name);
        }else if(orientation=='v'){
            if(fd_week=='m')fd_month-=1;
            print_vertical_calendar(fd_week, fd_month, dates_in_month, weekdays_name);
        }
    }
    if (month==-1){
        cout << "Year " << year << "\n";
        for (int i = 2; i < 13; i+=3)
        {
            print_3_conseq_calendar_s(fd_month, dates_in_month, weekdays_name, month_name, i, year, month);
        }
    }
    if (month==-3){
        do{
            cout<<"Enter the month in the center (in range 1-12): ";
            cin>>required_month;
        }while((year==1800 && required_month==1)||(year==9999 && required_month==12));
        
            print_3_conseq_calendar_s(fd_month, dates_in_month, weekdays_name, month_name, required_month, year, month);
    }
    
}

//g++ -o main main.cpp -std=c++11 -Wall