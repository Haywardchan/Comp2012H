#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_STRLEN = 1000;
const int NUM_CHARS_PER_LINE = 50;
const int MAX_LINES = 15;

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

int countCharacters(const char str[])
{
    int characters_count {0};
    for (int i{0}; i < MAX_STRLEN; i++){
        if (str[i]=='\0')
        break;
        characters_count++;
    }
    return characters_count;
}

int countWords(const char str[])
{
    int word_count {0};
    for (int i{0}; i<MAX_STRLEN; i++){
        if (str[i]=='\0'){
        word_count++;
        break;
        }
        else if (str[i]==' ')
        word_count++;
    }
    return word_count;
}

void swapString(char str[], const char target[], const char to[])
{
    bool match {false}, lock {false}, new_word = false;
    int j{0}, start_pos{0}, end_pos{0}, match_start_pos = 0;
    for (int k = 0; k < MAX_STRLEN; k++){
        if (str[k]=='\0')break;
        if((str[k]==' ')||k==0){
            match_start_pos = k;
            match = false;
            new_word = true;
        }
    
    for (int i{match_start_pos}; i<MAX_STRLEN; i++){
        if (target[j]==str[i]){
            j++;
            if (!lock){
            start_pos = i;
            lock = true;
            }
        }else{
            j=0;
            lock = false;
        }
        if (target[j]=='\0'){
            match = true;
            end_pos = i+1;
            break;
        }
        if (str[i]=='\0'){
            break;
        }
    }

    if ((match)&&(new_word)){
        char tmplst[MAX_STRLEN];
        int tmp_count {0};
        for (int i{end_pos}; i<MAX_STRLEN; i++){
            tmplst[tmp_count] = str[i];
            if (str[i]=='\0') break;
            tmp_count++;
        }
        tmp_count = 0;
        for (int i{start_pos}; i<MAX_STRLEN; i++){
            if (to[tmp_count]=='\0') break;
            str[i] = to[tmp_count];
            tmp_count++;
        }
        start_pos += countCharacters(to);
        for (int i{0}; i<MAX_STRLEN; i++){
            str[start_pos] = tmplst[i];
            if (tmplst[i]=='\0') break;
            start_pos++;
        }
        k+=countCharacters(to);
        new_word = false;
    }
    }
}

void encryptText(char str[], int shift)
{
    if (shift < 0){
        shift = 26-(-shift%26);
    }
    for (int i = 0; i<MAX_STRLEN ; i++){
        if (str[i] == '\0')break;
        if (int(str[i])>=65&&int(str[i])<=90){
        str[i] = char((int(str[i])-65+shift)%26+65);}
        else if (int(str[i])>=97&&int(str[i])<=122){
            str[i] = char((int(str[i])-97+shift)%26+97);
        }
    }
}

int countNumOccurences(const char str[], const char target[])
{
    int j=0, match_no = 0;
    for (int i = 0; i<MAX_STRLEN; i++){
        if (target[j]==str[i]){
            j++;
        }else{
            j=0;
        }
        if (target[j]=='\0'){
            match_no++;
            j=0;
        }
        if (str[i]=='\0'){
            break;
        }
    }
    return match_no;
}

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    int countchar = 0, remaining_length = NUM_CHARS_PER_LINE-1, mark_pos_counter = 0, end_line = 0, str_counter1 = 0, start_pos = 0;
    int mark_pos[MAX_STRLEN];
    bool lock = false;
    for (int i =0; i<MAX_STRLEN; i++){
        if (str[i]=='\0')break;
        if (!lock){start_pos = i; lock = true;}
        if (str[i]!=' '&&str[i+1]!='\0'){
            countchar++;
        }else{
            if (str[i+1]=='\0')countchar++;
            lock = false;
            if ((remaining_length - countchar) < 0){
                remaining_length = NUM_CHARS_PER_LINE-1 - countchar;
                mark_pos[mark_pos_counter] = start_pos;
                mark_pos_counter++;
            }else{
                countchar++;
                remaining_length -= countchar;
            }
            countchar = 0;
        }
    }
        mark_pos[mark_pos_counter]='\0';
        mark_pos_counter = 0;

        for (int i = 0; i < MAX_LINES; i++){

            if (mark_pos[mark_pos_counter]=='\0'){
                for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
                    if (j==0)if (str[str_counter1]==' ')str_counter1++;
                    lines[i][j] = str[str_counter1];str_counter1++;
                    if (str[str_counter1]=='\0'){
                        (lines[i][j]==' ')? lines[i][j] = '\0':lines[i][j+1] = '\0';
                        break;
                    }
                }
                end_line = i+1;
                break;
            }

            for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
                if (j==NUM_CHARS_PER_LINE-1){
                    lines[i][j] = '\0'; mark_pos_counter++; break;
                }
                if (j==0)if (str[str_counter1]==' ')str_counter1++;
                if (str_counter1!=mark_pos[mark_pos_counter]){
                    lines[i][j] = str[str_counter1];
                }else{
                    if (j==0){
                        mark_pos_counter++;
                        lines[i][j] = str[str_counter1];
                        str_counter1++;
                        continue;
                    }
                    mark_pos_counter++;
                    (lines[i][j]==' ')? lines[i][j] = '\0':lines[i][j+1] = '\0';
                    break;
                }
                str_counter1++;
            }

        }
        lines[end_line][0] = '\0';
        for (int i = 0; i < end_line; i++){
            for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
                if (lines[i][j]=='\0')break;              
            }
        }
}

void printLeftJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]{'\0'};
    bool stop_looping = false;
    convertIntoLines(str,lines);
    for (int i =0; i<MAX_LINES; i++){
        if (i!=0)cout << endl;
        for (int j=0; j<NUM_CHARS_PER_LINE; j++){
            if (lines[i][j]!='\0'){
                cout << lines[i][j];
            }else{ 
                if (lines[i+1][0]!='\0'){break;
                }else{
                    stop_looping = true; break; 
                }   
            }
        }
        if (stop_looping)break;
    }
}

void printRightJustified(const char str[])
{
    int shift = 0;
    char lines[MAX_STRLEN][NUM_CHARS_PER_LINE]{'\0'};
    convertIntoLines(str,lines);
    for (int i = 0; i<MAX_LINES; i++){
        for (int j = 0; j<NUM_CHARS_PER_LINE; j++){
            if (lines[i][j]=='\0'){
                shift = NUM_CHARS_PER_LINE - 1 - j;
                if (lines[i][j-1]==' ')shift++;
                for (int k = 0; k <= j; k++){
                    lines[i][NUM_CHARS_PER_LINE-1-k] = lines[i][NUM_CHARS_PER_LINE-1-shift-k];
                }
                for (int l = 0; l < shift; l++){
                    lines[i][l]=' ';
                }
            }
        }
        if (lines[i+1][0]=='\0')break;
    }
    for (int i =0; i<MAX_LINES; i++){
        if (i!=0)cout << endl;
        for (int j=0; j<NUM_CHARS_PER_LINE; j++){
            if (lines[i][j]=='\0')lines[i][j]=' ';
            cout << lines[i][j];
        }
        if (lines[i+1][0]=='\0')break;
    }
}

void printJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]{'\0'}, tmplst[MAX_STRLEN]{'\0'};
    int remaining_space = NUM_CHARS_PER_LINE, no_of_space = 0, loop_no = 0, shift = 0, final_space = 0;
    convertIntoLines(str,lines);
    for (int i = 0; i < MAX_LINES ; i++){
        //cout << "================" << endl;
        no_of_space = 0;
        shift = 0;

        for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
            tmplst[j]='\0';
        }

        if (lines[i+1][0]=='\0'){
            for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
                if (lines[i][j]=='\0'){lines[i][j] = ' ';}
                cout << lines[i][j];
            }
            break;           
        }

        for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
            if (lines[i][j]=='\0')break;
            tmplst[j] = lines[i][j];
        }

        for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
            if (tmplst[j]=='\0')break;
            if (tmplst[j]==' '){
                if (tmplst[j+1]=='\0')tmplst[j]='\0';
            }
            if (tmplst[j]==' '){
                no_of_space++; //cout << "Decteced space at: " << i << " " << j << endl;
            }
        }

        remaining_space = NUM_CHARS_PER_LINE;        
        remaining_space -= countCharacters(tmplst)+1;
        if (remaining_space == 0){
            for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
                if (lines[i][j]=='\0'){lines[i][j] = ' ';}
                cout << lines[i][j];
            }cout << endl;
            continue;
        }        
        //cout << "tmplst: " << tmplst << endl;


        // cout << "Countwords function output: " << countWords(tmplst) << endl; 
        //cout << "remaining space: " << remaining_space << " no of space:" << no_of_space << endl;
        if (no_of_space != 0){
        shift = remaining_space/no_of_space; //cout << "shift: " << shift << endl;
        final_space = remaining_space%no_of_space; //cout << "final space: " << final_space << endl;
        }
        if (shift==0){
            //cout << "Entering final loop" << endl;
            while (final_space>0){
                for (int j = 0; j < NUM_CHARS_PER_LINE-1; j++){
                    if (final_space == 0)break;
                    if (tmplst[j]=='\0')break;
                    if (tmplst[j]==' '){
                        loop_no = NUM_CHARS_PER_LINE-j-2;
                        for (int k = 0; k < loop_no; k++){
                            tmplst[NUM_CHARS_PER_LINE-2-k] = tmplst[NUM_CHARS_PER_LINE-2-k-1];
                        }
                        tmplst[j+1] = ' ';
                        j+=2;final_space--;
                    }
                }
                //cout << tmplst << endl;
            } 
        }else{
            //cout << "Executing non final loop" << endl;
        for (int j = 0; j < NUM_CHARS_PER_LINE-1; j++){
            if (tmplst[j]=='\0')break;
            if (tmplst[j]==' '){
                loop_no = NUM_CHARS_PER_LINE-j-2;
                for (int k = 0; k < loop_no; k++){
                    tmplst[NUM_CHARS_PER_LINE-2-k] = tmplst[NUM_CHARS_PER_LINE-2-k-shift];
                    //cout << "assigning tmplst[" << NUM_CHARS_PER_LINE-2-k << "] value of tmplst[" << NUM_CHARS_PER_LINE-2-k-shift << "]" << endl; 
                }
                for (int k = 0; k < shift; k++){
                    tmplst[j+1+k] = ' ';
                }
                j+=shift+1; //cout << j << endl; cout << tmplst << endl;
            }
        }
        }

        for (int j = 0; j < NUM_CHARS_PER_LINE; j++){
            lines[i][j] = tmplst [j];
            if (lines[i][j]=='\0'){lines[i][j] = ' ';}
            cout << lines[i][j];
        } cout << endl;
        // no_of_space = remaining_space%no_of_space;
        // remaining_space--;
    }
   // cout << "Not Implemented" << endl; // Replace this line with your implementation
}

void convertStrToPigLatin(char str[])
{
    bool done = false, yay = true;
    char tmplst1[MAX_STRLEN]{'\0'}, tmplst2[MAX_STRLEN]{'\0'}, tmp {'\0'};
    int end_pos = 0, tmplst1_size = 0, tmplst2_size = 0, fullstop = 0, remaining_size = countCharacters(str);
    for (int i = 0; i < MAX_STRLEN ; i++){
        done = false; yay = true;
        if (str[i]=='\0')break;
        if ((str[i-1]==' ')||(i==0)){
            for (int j = i ; j < MAX_STRLEN; j++){
                if (str[j+1] == ' '||str[j+1]== '.'||str[j+1]== ','){
                    fullstop = 0;
                    if (str[j+1]!=' '){(str[j+1]=='.')? fullstop = 1: fullstop = 2;}
                    end_pos = j;break;}
            }
            tmplst1_size = countCharacters(tmplst1);
            for (int j = 0; j < tmplst1_size; j++){
                tmplst1[j] = '\0';
            }

            for (int j = 0 ; j <= end_pos - i ; j++){
                tmplst1[j] = str[i+j];
            }
            tmplst1_size = countCharacters(tmplst1);
            remaining_size -= countCharacters(tmplst1);

                while (!done){
                    switch (tmplst1[0]){
                        case 'a':case 'e':case 'i':case 'o':case 'u':case 'A':case 'E':case 'I':case 'O':case 'U':
                        tmplst1[tmplst1_size] = ' ';
                        if (yay){swapString(tmplst1," ","yay");
                        }else{swapString(tmplst1," ","ay");} done = true; break;
                    }

                    if (done){
                        tmplst1_size = countCharacters(tmplst1);
                        tmplst2_size = countCharacters(tmplst2);
                        if (fullstop == 1){
                            tmplst1[tmplst1_size] = '.'; tmplst1_size++;
                        }else if (fullstop == 2){
                            tmplst1[tmplst1_size] = ','; tmplst1_size++;
                        }
                        if (remaining_size!=0){tmplst1[tmplst1_size] = ' '; tmplst1_size++;}
                        for (int j = 0; j <= tmplst1_size; j++ ){
                            tmplst2[j+tmplst2_size] = tmplst1[j];
                        }
                        tmplst2[countCharacters(tmplst2)] = '\0';
                        break;   
                    }

                    yay = false;
                    tmp = tmplst1[0];
                    for (int j = 0 ; j < tmplst1_size - 1 ; j++){
                        tmplst1[j] = tmplst1[j+1];
                    }
                    tmplst1[tmplst1_size - 1] = tmp;
                }
            }
        }
        for (int i = 0 ; i < MAX_STRLEN ; i++){
            str[i] = tmplst2[i];
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
