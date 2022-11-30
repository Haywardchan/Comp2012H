#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_STRLEN = 1000;
const int NUM_CHARS_PER_LINE = 50;//50
const int MAX_LINES = 15;//15

int countCharacters(const char str[]);
int countWords(const char str[]);
int countNumOccurences(const char str[], const char target[]);

void swapString(char str[], const char target[], const char to[]);
void encryptText(char str[], int shift);

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE]);
void printRightJustified(const char str[]);
void printLeftJustified(const char str[]);

void convertStrToPigLatin(char word[]);
void printPigLatin(const char str[]);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes start here. Please do not modify codes above
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool isvowel(char vowel[], int target,int size){
    for (int i = 0; i < size; i++)
    {
        if (vowel[i]==target)
        {
            return true;
        }   
    } return false;
}

int countCharacters(const char str[])
{
    int i=0;
        while (str[i]!='\0')i++;
        return i;
}

int countWords(const char str[])
{
    int i=0, count=0;
    while (str[i]!='\0')
    {
        if(((str[i]>64&&str[i]<91)||(str[i]>96&&str[i]<123))&&(str[i+1]==' '||str[i+1]==','||str[i+1]=='.'||str[i+1]=='\0'))count++;
        i++;
    }return count;
}

void swapString(char str[], const char target[], const char to[])
{
    int starting_pos=0, count=0;
    bool found=false;
    char temp[MAX_STRLEN]={};
    for (int i = 0; i < countCharacters(str); i++)
    {
        for (int j = 0; j < countCharacters(target); j++)
        {
            if (target[j]==str[j+i])
            {
                
                if (count==countCharacters(target)-1)
                {
                    found=true;
                    starting_pos=i;
                    // cout<<starting_pos<<"\n";
                    break;
                    
                }
                count+=1;
            }else{break;}
            
        }
        // if (found)break;
        if(found){
            int mem=0;
            for (int k = starting_pos + countCharacters(target); k < countCharacters(str)+1 ; k++)
            {
                if (k==countCharacters(str))
                {
                    temp[mem]='\0';
                }else{
                    temp[mem]=str[k];
                }
                mem++;
                
            }
            // cout<<temp;
            mem=0;
            for (int m = starting_pos; m < (starting_pos + countCharacters(to)); m++)
            {
                str[m]=to[mem];
                mem++;
            }
            mem=0;
            // cout<<str;
            for (int i = starting_pos+countCharacters(to); i < starting_pos+countCharacters(to)+countCharacters(temp)+1; i++)
            {
                if(i==starting_pos+countCharacters(to)+countCharacters(temp)){ str[i]='\0'; }
                str[i]=temp[mem];
                mem++;
            }
            found=false;
        }
        count=0;
    }
    
}    

// 26 27 28 29 30 .. 52
// 0 1 2 3 4 5 ... 25
//  -26 -25 -24 ... -2 -1
// -52 -51 -50 .. -28 -27

//She sells seashells on the seashore.
void encryptText(char str[], int shift)
{
        char s_alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        char b_alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        for (int i = 0; i < countCharacters(str); i++)
        {
            while (shift<0)
                shift += 26;
            if ((str[i]>64&&str[i]<91)||(str[i]>96&&str[i]<123))
            {
                (str[i]>=97)?
                str[i]=s_alphabet[(str[i]+shift-97)%26]
                :str[i]=b_alphabet[(str[i]+shift-65)%26];
            }
        }
}
 
int countNumOccurences(const char str[], const char target[])
{
    int count=0, starting_pos=0, num_of_occurence=0;
    bool found=false;
    for (int i = 0; i < countCharacters(str); i++)
    {
        for (int j = 0; j < countCharacters(target); j++)
        {
            if (target[j]==str[j+i])
            {
                count+=1;
                if (count==countCharacters(target))
                {
                    found=true;
                    i+=countCharacters(target)-1;
                    starting_pos=i;
                    break;
                }
            }else{
                count=0;
                break;
                }
            
        }
        if (found){
            num_of_occurence+=1;
            // i+=countCharacters(target);
            // cout<<starting_pos<<" ";
            count=0;
            found=false;
        }
    }
    return num_of_occurence;
}

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    int pos=0, word_length=0;
     for (int j = 0; j < MAX_LINES; j++)
    {
        if (pos>=countCharacters(str)-1)
        {
            lines[j][0] = '\0';
            continue;
        }
        for (int i = 0; i < NUM_CHARS_PER_LINE; i++)
        {
            
            //remove heading spaces
            if (i==0 && str[pos]==' ')
            {
                pos+=1;
            }
            //place last char as null
            if (i==NUM_CHARS_PER_LINE-1)
            {
                lines[j][i]='\0';
                // word_length=0;
            //copy str into the line i
            }else{
                lines[j][i]=str[pos];
                pos++;
                
            }   
            // if (str[pos]==' '&&str[pos+1]==' ')
            // {
            //     pos+=1;
            // }
            //count length of word
            if(str[pos]!=' '){word_length++;}else{word_length=0;}
            // cout<<word_length<<" ";
            // if(i==NUM_CHARS_PER_LINE-2)cout<<str[pos-1]<<' '<<str[pos]<<"\n";
            //check last word and the next word is connected or not:move backward and copy the word to next line
            if (i==NUM_CHARS_PER_LINE-2 && str[pos]!=' ' && str[pos-1]!=' ')
            {
                if(word_length<NUM_CHARS_PER_LINE-1){
                    lines[j][i-word_length+1]='\0';
                    pos-=word_length;
                }
                // word_length=0;
                // cout<<"pos_char="<<str[pos]<< "\n";
                // cout<<"wordl="<<word_length<<"\n";
                // break;
            }

            if (str[pos]=='\0')
            {
                break;
            }
        } 
        if (str[pos]=='\0')
            {
                break;
            }
    }
    for (int i = 0; i < MAX_LINES; i++)
    {
        for (int j = NUM_CHARS_PER_LINE-2; j >= 0; j--)
        {
            if (lines[i][j]==' ')
            {
                lines[i][j]='\0';
                // word_length=0;
            }else break;
        }
    }
}

void printLeftJustified(const char str[])
{
    int num_of_lines=1;
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]={};
    convertIntoLines(str,lines);
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (lines[i][0]=='\0')
        {
            num_of_lines=i;
            break;
        }
    }
    
    for (int i = 0; i < num_of_lines; i++)
    {
        cout<<lines[i];
        cout<<"\n";
    }
}

void printRightJustified(const char str[])
{
    int num_of_lines=1, num_of_space=0;
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]={};
    convertIntoLines(str,lines);
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (lines[i][0]=='\0')
        {
            num_of_lines=i;
            break;
        }
    }
    
    
    for (int i = 0; i < num_of_lines; i++)
    {
        for (int j = 0; j < NUM_CHARS_PER_LINE; j++)
        {
            if (lines[i][j]=='\0')
            {
                num_of_space=NUM_CHARS_PER_LINE-j-1;
                break;
            }
        }
        for (int k = 0; k < num_of_space; k++)
        {
            cout<<' ';
        }
        cout<<lines[i];
        cout<<"\n";
    }
}

void extend_line(char lines[MAX_LINES], int &spaces){
    int pos=0;
    int loop=1;
    // cout<<"hello";
    while (spaces>0)
    {
        for (int i = 0; i < NUM_CHARS_PER_LINE; i++)
        {
            if(lines[i]==' '&&spaces>0){
                pos=i;
                cout<<pos;
                for (int j = countCharacters(lines); j > pos; j--)
                {
                    lines[j+1]=lines[j];
                }
                lines[pos+1]=' ';
                i+=loop;
                spaces--;
            }
        }
        loop++;
    }
}
void printJustified(const char str[])
{
    int num_of_lines=0;
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]={};
    int num_of_spaces[MAX_LINES]={};
    // int separated_spaces[MAX_LINES][MAX_STRLEN]={{0}};
    // int idx=0;
    convertIntoLines(str,lines);
    //find the number of lines
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (lines[i][0]=='\0')
        {
            num_of_lines=i;
            break;
        }
    }
    //print the original lines
    // for (int i = 0; i < num_of_lines; i++)
    // {
    //     cout<<lines[i];
    //     cout<<"\n";
    // }
    //find the number of spaces in each space and store in an array
    for (int i = 0; i < num_of_lines-1; i++)num_of_spaces[i]=NUM_CHARS_PER_LINE-countCharacters(lines[i])-1;
    // for (int i = 0; i < num_of_lines; i++)
    // {
    //     for (int j = 0; j < NUM_CHARS_PER_LINE; j++)
    //     {
    //         if(lines[i][j]==' ')separated_spaces[i][idx]++;
    //         cout<<separated_spaces[i][idx];
    //         if(lines[i][j]==' '&&lines[i][j+1]!=' ')idx++;
    //     }
    //     cout<<"\n";
    // }
    
    //print the array
    // for (int i = 0; i < num_of_lines; i++)cout<<num_of_spaces[i]<<" ";
    //if the str pos is '', replace it with increased num of space
    for (int i = 0; i < num_of_lines; i++)
    {
        extend_line(lines[i], num_of_spaces[i]);
    }
    
    //print the new lines
    for (int i = 0; i < num_of_lines; i++)
    {
        cout<<lines[i];
        cout<<"\n";
    }
}
void convertStrToPigLatin(char str[])
{
    char vowel[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    int index_str=0,index_temp1=0,index_temp2=0,index_temp3=0, larger_int=0;
    char temp1[MAX_STRLEN] = {0}; // before vowel
    char temp2[MAX_STRLEN] = {0}; // after vowel
    char temp3[MAX_STRLEN] = {0}; // final result
    bool no_vowel=true, have_comma=false, have_fullstop=false;

    while (str[index_str]!='\0')
    {
        if (!isvowel(vowel, str[index_str], 10)||str[index_str]=='.'||str[index_str]==',') // if vowel . ,
        {
            // cout<<index_str<<" ";
            // cout<<str;
            if (index_str<countCharacters(str))
            {
                temp2[index_temp2]=str[index_str];
                index_temp2++;
                temp2[index_temp2]='\0';
            }
            if (str[index_str]==' ')
            {
                temp1[index_temp1]=' ';
                index_temp1++;
                temp1[index_temp1]='\0';
                // temp2[index_temp2+1]='\0';
                // index_temp2++;
            }
        }else{
            no_vowel=false;
            while (str[index_str]!=' ')//&&str[index_str]!='.'&&str[index_str]!=','
            {
                temp1[index_temp1]=str[index_str];
                // temp2[index_temp2]=' ';
                // index_temp2++;
                index_temp1++;
                index_str++;
            }
            if (str[index_str]==' ')
            {
                temp1[index_temp1]=' ';
                index_temp1++;
                temp2[index_temp2]=' ';
                index_temp2++;
                temp2[index_temp2]='\0';
                // temp2[index_temp2+1]='\0';
                // index_temp2++;
            }
            if (index_str==countCharacters(str)-1)
            {
                temp2[index_temp2]=' ';
                temp2[index_temp2+1]='\0';
                break;
                // temp1[index_temp1]=' ';
                // index_temp1++;
                // temp2[index_temp2+1]='\0';
                // index_temp2++;
            }
        } 
        if(no_vowel&&str[index_str]==' '){
            temp1[index_temp1]=' ';
            index_temp1++;
        }
        if (str[index_str]==' '&&str[index_str-1]!=' '&&str[index_str]!='\0')
        {
            no_vowel=true;
        }
        index_str++;
        
    }

    // cout<<temp1<<"\n"<<temp2<<"\n";
    for (int i = 0; i < countCharacters(temp2)+1; i++)
    {
        if (temp2[i]==' '&&temp2[i-1]!=' '&&temp2[i-1]!='\0'&&temp2[i+1]!=' '&&temp2[i+1]!='\0')
        {
            temp2[i]='a';
        }
        if (i==countCharacters(temp2))
        {
            temp2[i]='\0';
        }
        // else if(temp2[i]==' ')temp2[i]='e'; 
    }
    // char temp1[MAX_STRLEN]={'I',' ','o','u','l','d',' ','i','k','e' ,' ','o', ' ','a','v','e',' ','a','n',' ','i','c','e','-','c','r','e','a','m'};
    // char temp2[MAX_STRLEN]={' ','w','a','l','a','t','a','h',' ',' '};
    // cout<<"\n"<<temp1<<"\n"<<temp2<<"\n";
    index_temp1=0,index_temp2=0,index_temp3=0;
    for(int i=0;i<countCharacters(temp2);i++)
    {
        if (temp2[index_temp2]==' '&&index_temp2<countCharacters(temp2))
        {
            
         while (temp1[index_temp1]!=' '&&temp1[index_temp1]!='\0')//&&temp1[index_temp1]!='.'&&temp1[index_temp1]!=','
            {
                if(temp1[index_temp1]!='.'&&temp1[index_temp1]!=','){
                temp3[index_temp3]=temp1[index_temp1];
                index_temp3++;
                }
                if(temp1[index_temp1]==','){
                    have_comma=true;
                }
                if (temp1[index_temp1]=='.')
                {
                    have_fullstop=true;
                }
                index_temp1++;
            }
            temp3[index_temp3]='y';
            index_temp3++;
            temp3[index_temp3]='a';
            index_temp3++;
            temp3[index_temp3]='y';
            index_temp3++;
            if(have_comma){
                 temp3[index_temp3]=',';
                index_temp3++;
                have_comma=false;
            }
            if (have_fullstop)
            {
                 temp3[index_temp3]='.';
                index_temp3++;
                have_fullstop=false;
            }
            temp3[index_temp3]=' ';
            index_temp3++;
            index_temp1++;
        }
        if (temp2[index_temp2]!=' '&&temp2[index_temp2]!='a'&&index_temp2<countCharacters(temp2)) {
            
            while (temp1[index_temp1]!=' '&&temp1[index_temp1]!='\0')//&&temp1[index_temp1]!='.'&&temp1[index_temp1]!=','
            {
                if(temp1[index_temp1]!='.'&&temp1[index_temp1]!=','){
                temp3[index_temp3]=temp1[index_temp1];
                index_temp3++;
                }
                if(temp1[index_temp1]==','){
                    have_comma=true;
                }
                if (temp1[index_temp1]=='.')
                {
                    have_fullstop=true;
                }
                index_temp1++;   
            }
            while (temp2[index_temp2]!=' '&&temp2[index_temp2]!='a'&&temp2[index_temp2]!='\0')
            {   
                temp3[index_temp3]=temp2[index_temp2];
                index_temp2++;
                index_temp3++;
            }
            temp3[index_temp3]='a';
            index_temp3++;
            temp3[index_temp3]='y';
            index_temp3++;
            if(have_comma){
                temp3[index_temp3]=',';
                index_temp3++;
                have_comma=false;
            }
            if (have_fullstop)
            {
                temp3[index_temp3]='.';
                index_temp3++;
                have_fullstop=false;
            }
            temp3[index_temp3]=' ';
            index_temp3++;
            index_temp1++;
            
        }
       
        index_temp2++;
    }
    // if (str[countCharacters(str)-1]=='.')
    //         {
    //             // cout<<true;
    //             temp3[countCharacters(temp3)-1]='.';
    //             index_temp3++;  
    //         }
    

     for (int i = 0; i < countCharacters(temp3)+1; i++)
     {
        str[i]=temp3[i];
     }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes end here. Please do not modify codes below
// ++++++++++++++++++++++++++++++++++++++++++++++++++++

void printPigLatin(const char str[])
{
    char pigLatin[MAX_STRLEN];
    for (int i = 0; i < MAX_STRLEN; ++i)
    {
        pigLatin[i] = str[i];
    }
    convertStrToPigLatin(pigLatin);
    int strLen = countCharacters(pigLatin);
    for (int i = 0; i < strLen; ++i)
    {
        if (pigLatin[i] >= 'A' && pigLatin[i] <= 'Z')
        {
            pigLatin[i] = 'a' + pigLatin[i] - 'A';
        }
    }
    cout << pigLatin << endl;
}

void printMainDisplay(const char str[])
{
    cout << str << endl
         << "===================================\n"
         << "1. Character Count\n"
         << "2. Word Count\n"
         << "3. Encrypt (Caeser Cipher)\n"
         << "4. Find and Replace String Globally\n"
         << "5. Find Frequency of String\n"
         << "6. Print Left Align Text\n"
         << "7. Print Right Align Text\n"
         << "8. Print Left-Right Align Text\n"
         << "9. Print Pig Latin\n"
         << "Please make your choice: ";
}

int main()
{
    int choice = 0;
    char str[MAX_STRLEN];

    cout << "Enter text: ";
    cin.getline(str, MAX_STRLEN, '\n');

    do
    {
        printMainDisplay(str);
        cin >> choice;
    } while (choice < 1 || choice > 9);

    if (choice == 1)
    {
        cout << "Total character count: " << countCharacters(str) << endl;
    }
    else if (choice == 2)
    {
        cout << "Total word count: " << countWords(str) << endl;
    }
    else if (choice == 3)
    {
        cout << "Enter the shift amount for the caeser cipher encryption (rotation encryption): ";
        int shift;
        cin >> shift;
        encryptText(str, shift);
        cout << str << endl;
    }
    else if (choice == 4)
    {
        cout << "Enter the string to find and replace: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << "Enter the string to replace it with: ";
        char to[MAX_STRLEN];
        cin.getline(to, MAX_STRLEN, '\n');

        swapString(str, target, to);
        cout << str << endl;
    }
    else if (choice == 5)
    {
        cout << "Enter the string to count the occurences of: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << '"' << target << '"' << " appears in the text " << countNumOccurences(str, target) << " time(s).\n";
    }
    else if (choice == 6)
    {
        printLeftJustified(str);
    }
    else if (choice == 7)
    {
        printRightJustified(str);
    }
    else if (choice == 8)
    {
        printJustified(str);
    }
    else if (choice == 9)
    {
        printPigLatin(str);
    }
}

//cat PA2txt|.\PA2_text.exe > outputfile1
//This course is an accelerated and intensive course on concepts and techniques behind object-oriented programming and data structures using an OOP language. 
//Its curriculum is designed for students with excellent programming background or substantial programming experience. 
//Topics include, functions, pointers, abstract data types and their class implementation, static and dynamic construction and destruction of objects, data member and member functions, 
//public interface and encapsulation, class hierarchies, polymorphism, inheritance and dynamic binding, standard template library, generic programming using templates.