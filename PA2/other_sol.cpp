#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_STRLEN = 1000;

// Change to 10 for testing, 50 for normal
const int NUM_CHARS_PER_LINE = 50;
//const int NUM_CHARS_PER_LINE = 10;
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

/*
    PA2
    by Chan Ho Wing

    This PA is so tiring

    22/9/2022 - removing all compile warnings 

    22/9/2022 - removed addStringPigLatin overload, split into two different functions to avoid unnecessary parameters

    22/9/2022 - all complie warnings have been removed

*/

/* Custom Functions */

// Check for characters
bool checkChar(char c, char type)
{
    // l = letter, m = misc, n = null, p = punctuation, s = space, v = vowel

    const char misc[5] = { ',', '.', ' ', ' ', '\0' };
    const char vowels[10] = { 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };
    bool letter = true;

    switch (type)
    {
        case 'l': for (int i = 0; i < 5; i++) {if (c == misc[i]) letter = false;} break;
        case 'm': for (int i = 0; i < 5; i++) {if (c == misc[i]) return true;} break;
        case 'n': if (c == '\0') return true; break;
        case 'p': for (int i = 0; i < 3; i++) {if (c == misc[i]) return true;} break;
        case 's': if (c == ' ') return true; break;
        case 'v': for (int i = 0; i < 10; i++) {if (c == vowels[i]) return true;} break;
    }
    return ((type == 'l') ? letter : false);
}


// Self implemented Copying String
void copyString(char repStr[], char str[], int repStartPos, int strStartPos, int strLen, bool addNull)
{
    for (int i = 0; i < strLen; i++) {repStr[repStartPos + i] = str[strStartPos + i];}
    if (addNull) {repStr[repStartPos + strLen] = '\0';}
}

void copyString(char repStr[], const char str[], int repStartPos, int strStartPos, int strLen, bool addNull)
{
    for (int i = 0; i < strLen; i++) {repStr[repStartPos + i] = str[strStartPos + i];}
    if (addNull) {repStr[repStartPos + strLen] = '\0';}
}

// Compare whether a string is exactly the same
bool detectSame(char str[], const char target[], int& strPos, int& targetLen)
{
    for (int i = 0; i < targetLen; i++) {if (str[strPos + i] != target[i]) return false;}
    return true;
}

bool detectSame(const char str[], const char target[], int& strPos, int& targetLen)
{
    for (int i = 0; i < targetLen; i++) {if (str[strPos + i] != target[i]) return false;}
    return true;
}

bool isStringEnd(char str[], int strPos)
{
    return (str[strPos + 1] == '\0');
}

// Fills the string array with blanks
void wipeString(char str[])
{
    for (int i = 0; i < MAX_STRLEN; i++) {str[i] = ' ';}
}

///////////// Convert into lines specific functions
void addToLine(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE], int len, int& strPos, int& lineRow, int& linePos)
{
    //cout << "add word to line called\n";
    for (int i = 0; i < len; i++) { lines[lineRow][linePos] = str[strPos]; strPos++; linePos++; }

}

void addToLine(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE], int& strPos, int& lineRow, int& linePos)
{
    //cout << "add char to line called\n";
    if (linePos > NUM_CHARS_PER_LINE) {lineRow++; linePos = 0;}
    lines[lineRow][linePos] = str[strPos]; 
    strPos++; linePos++;

}

bool checkRowEmpty(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int row)
{
    bool result = true;
    for (int i = 0; i < NUM_CHARS_PER_LINE; i++) {if (checkChar(lines[row][i], 'l') || (lines[row][i] == ',') || (lines[row][i] == '.') || (lines[row][i] == '-')) {result = false;}}
    return result;
}

int checkLineRow(char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    int line = 0;
    while (!checkRowEmpty(lines, line)) {line++;}
    return line;
}

void linesPostProcessing(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int lineRow)
{
    for (int i = 0; i < lineRow; i++)
    {
        int last = NUM_CHARS_PER_LINE;
        while (!checkChar(lines[i][last-1], 'l') && !(lines[i][last-1] == ',') && !(lines[i][last-1] == '.') && !(lines[i][last-1] == '-')) {last--;}
        lines[i][last] = '\0';
    }

}

// Think this can also be used in pig latin part
int countWordLen(const char str[], int strPos)
{
    //cout << "count word length called\n";
    int len = 0;
    while (checkChar(str[strPos + len], 'l')) {len++;}
    //cout << len << "\n";
    return len;
}

void convertRightJustified(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int lineRow)
{
    // Initialise
    char newLines[MAX_LINES][NUM_CHARS_PER_LINE];
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < NUM_CHARS_PER_LINE; j++) {newLines[i][j] = ' ';}}

    for (int i = 0; i < lineRow; i++)
    {
        int lineLen = countCharacters(lines[i]);
        int space = (i == 0) ? (NUM_CHARS_PER_LINE - lineLen - 1) :(NUM_CHARS_PER_LINE - lineLen - 1);
        for (int j = 0; j < lineLen; j++) {newLines[i][space + j] = lines[i][j];}
    }

    // Replace lines with newLines
    for (int i = 0; i < MAX_LINES; i++) {for (int j = 0; j <= NUM_CHARS_PER_LINE; j++) {lines[i][j] = ' ';}}

    for (int i = 0; i < MAX_LINES; i++) {for (int j = 0; j <= NUM_CHARS_PER_LINE; j++) {lines[i][j] = newLines[i][j];}}
    for (int i = 0; i < lineRow; i++) {lines[i][NUM_CHARS_PER_LINE - 1] = '\0';}

}

// Oh boy this is gonna be fun


int sumOfPrevious(int arr[], int arrPos)
{
    int result = 0;
    for (int i = 0; i < (arrPos); i++) {result += arr[i];}
    return result;
}

void makeWordStartArray(int arr[], int length, int oldArr[])
{
    arr[0] = 0;
    for (int i = 1; i < length; i++)
    {
        arr[i] = sumOfPrevious(oldArr, i*2);
    }
}

void makeWordLensArray(int arr[], int length, int oldArr[])
{
    for (int i = 0; i < length; i++)
    {
        arr[i] = oldArr[i*2];
    }
}

void debugPrintLines(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int lineRow)
{
    for (int i = 0; i < lineRow; i++) {cout << "Line " << i+1 << ": \""; for (int j = 0; j < NUM_CHARS_PER_LINE; j++) 
    {cout << lines[i][j];} cout << "\" \n";};
}

void debugPrintLine(char str[], int len)
{
    cout << "\"";
    for (int j = 0; j < len; j++) {cout << str[j];} 
    cout << "\"\n";
}

void printLines(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int lineRow)
{
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < ((countCharacters(lines[i]) < (NUM_CHARS_PER_LINE)) ? (countCharacters(lines[i])) : (NUM_CHARS_PER_LINE)); j++) 
    {cout << lines[i][j];} cout << "\n";};
}

void debugPrintIsSpace(char lines[MAX_LINES][NUM_CHARS_PER_LINE], int lineRow)
{
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < NUM_CHARS_PER_LINE; j++) 
    {if (lines[i][j] == ' ') {cout << "line " << i+1 << " pos " << j+1 << " is space\n";} 
    else {cout << "line " << i+1 << " pos " << j+1 << " is NOT space\n";}}};
}

bool notSpaceOrNull(char c)
{
    return (checkChar(c, 'l') || c == '-' || c == ',' || c == '.' );
}

bool notSpaceOrNullOrPunct(char c)
{
    return (checkChar(c, 'l') || c == '-' );
}


// I hate this part so much
void convertFullJustified(char lines[][NUM_CHARS_PER_LINE], int lineRow)
{
    char repLines[MAX_LINES][NUM_CHARS_PER_LINE] = { {0} };
    // init lines
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < NUM_CHARS_PER_LINE; j++) 
    {repLines[i][j] = ' ';}}
    for (int i = 0; i < lineRow; i++) {repLines[i][NUM_CHARS_PER_LINE - 1] = '\0';}
    // let's see (ok here)
    //debugPrintIsSpace(repLines, lineRow);
    //debugPrintLines(repLines, lineRow);

    // lemme see if i can bring back old code
    int linePos = 0;
    int lineCharPos = 0;
    int lineMax = lineRow - 1;

    int strLen = 0, spacesNeeded = 0, wordCount = 0, arrPos = 0;
    bool onWord = true;

    while (linePos < lineMax)
    {
        //cout << "Line " << linePos+1 << "\n==========================\n";

        strLen = countCharacters(lines[linePos]);
        spacesNeeded = NUM_CHARS_PER_LINE - strLen - 1;
        wordCount = countWords(lines[linePos]);
        int diffOfLen[NUM_CHARS_PER_LINE] = { 0 };

        // Build the differences array
        onWord = true;
        lineCharPos = 0;
        arrPos = 0;

        for (int i = 0; i < (wordCount*2-1); i++) {diffOfLen[i] = 0;}
        
        while (lineCharPos < strLen)
        {
            if (notSpaceOrNull(lines[linePos][lineCharPos])) 
            {if (!onWord) {arrPos++; onWord = true;} diffOfLen[arrPos]++; }
            else if (checkChar(lines[linePos][lineCharPos], 'm')) {if (onWord) {arrPos++; onWord = false;} diffOfLen[arrPos]++;} 
            lineCharPos++;
        }

        //cout << "diffOfLen = "; for (int i = 0; i < (wordCount*2-1); i++) {cout << diffOfLen[i] << " ";} cout << "\n";

        int newDiffOfLen[NUM_CHARS_PER_LINE] = { 0 };
        for (int i = 0; i < (wordCount*2-1); i++) {newDiffOfLen[i] = diffOfLen[i];}

        // Add Spaces
        int arrPos2 = 1;
        while (spacesNeeded > 0)
        {
            if (arrPos2 >= (wordCount*2-1)) {arrPos2 = 1;}
            newDiffOfLen[arrPos2]++;
            arrPos2 += 2;
            spacesNeeded--;
        }
        
        //cout << "newDiffOfLen = "; for (int i = 0; i < (wordCount*2-1); i++) {cout << newDiffOfLen[i] << " ";} cout << "\n";

        // Checkpoint
        // let's see (ok here)
        //debugPrintIsSpace(repLines, lineRow);
        //debugPrintLines(repLines, lineRow);

        // Rebuild the line
        int wordStartingPos[NUM_CHARS_PER_LINE] = { 0 };
        int newWordStartingPos[NUM_CHARS_PER_LINE] = { 0 };
        int wordLens[NUM_CHARS_PER_LINE] = { 0 };
        makeWordStartArray(wordStartingPos, wordCount, diffOfLen);
        makeWordStartArray(newWordStartingPos, wordCount, newDiffOfLen);
        makeWordLensArray(wordLens, wordCount, diffOfLen);

        //cout << "wordStartingPos = "; for (int i = 0; i < (wordCount); i++) {cout << wordStartingPos[i] << " ";} cout << '\n';
        //cout << "newWordStartingPos = "; for (int i = 0; i < (wordCount); i++) {cout << newWordStartingPos[i] << " ";} cout << '\n';

        //while (newLineCharPos < NUM_CHARS_PER_LINE)
        //{
        for (int i = 0; i < wordCount; i++)
        {
            // i governs the position of wordStartingPos, newStartingPos and wordLens
            for (int j = 0; j < wordLens[i]; j++)
            {
                repLines[linePos][newWordStartingPos[i] + j] = lines[linePos][wordStartingPos[i] + j];
            }
        }

        // let's see (ok here)
        //debugPrintIsSpace(repLines, lineRow);
        //debugPrintLines(repLines, lineRow);

        linePos++;
    }

    // copy the last row verbatim
    int lastStrLen = countCharacters(lines[lineRow-1]);
    for (int i = 0; i < lastStrLen; i++) {repLines[lineRow-1][i] = lines[lineRow-1][i];}
    repLines[lineRow - 1][lastStrLen] = '\0';
    //debugPrintIsSpace(repLines, lineRow);
    //debugPrintLines(repLines, lineRow);

    // copy to lines
    
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < NUM_CHARS_PER_LINE; j++) 
    {lines[i][j] = ' ';}}
    for (int i = 0; i < lineRow; i++) {for (int j = 0; j < NUM_CHARS_PER_LINE; j++) 
    {lines[i][j] = repLines[i][j];}}
    

}

int countWordsWithPunctuation(char str[])
{
    int num = 0;
    bool onWord = false;

    int strPos = 0;
    int strLen = countCharacters(str);

    while (strPos < strLen)
    {
        if (notSpaceOrNull(str[strPos]) && !onWord) {num++; onWord = true;}
        else if /*(checkChar(str[strPos], 'm') && onWord)*/(onWord) {onWord = false;} 
        strPos++;
    }

    return num;
}

// MOVE THESE TO TOP ONCE DONE
void addStringPigLatin(char newStr[], char word[], int wordLen, int& newStrPos)
{
    //cout << "Word change to Pig Latin function called\n";
    //cout << "Starting Letter: " << word[0] << "\n";
    
    bool startsWithVowel = checkChar(word[0],'v');
    int wordLenOffset = (startsWithVowel) ? 3 : 2;
    int wordPos = 0;
    int newWordLen =  wordLen + wordLenOffset;

    //if (startsWithVowel) {cout << "It's a vowel!\n";} else {cout << "It's a consonant...\n";}
    
    if (startsWithVowel)
    {
        word[wordLen] = 'y'; word[wordLen+1] = 'a'; word[wordLen+2] = 'y'; //yay
        while (wordPos < newWordLen) {newStr[newStrPos + wordPos] = word[wordPos]; wordPos++;}
        newStrPos += newWordLen;
        //debugPrintLine(word, newWordLen);
    }
    else
    {
        int wordOffset = 0;
        while (!checkChar(word[wordOffset],'v')) {wordOffset++;}
        word[wordLen] = 'a'; word[wordLen+1] = 'y'; //ay
        int wordBackLen = (wordLen - wordOffset);

        // copy back
        for (int i = 0; i < wordBackLen; i++) {newStr[newStrPos + i] = word[wordOffset + i];}
        for (int i = 0; i < wordOffset; i++) {newStr[newStrPos + wordBackLen + i] = word[i];}
        for (int i = 0; i < 2; i++) {newStr[newStrPos + wordLen + i] = word[wordLen + i];}

        newStrPos += newWordLen;
        //debugPrintLine(word, newWordLen);
    }

    //debugPrintLine(newStr, 80);
}

void addCharPigLatin(char str[], char newStr[], int& strPos, int& newStrPos)
{
    //cout << "Add character to new string function called\n";

    newStr[newStrPos] = str[strPos];
    newStrPos++;

    //debugPrintLine(newStr, 80);
}

/* Actual Tasks start */

/*
    Task 1 - Count Characters
    (Used in the later tasks)
    
    Loop through str and stop if '\0' is reached.
*/
int countCharacters(const char str[])
{
    int num = 0;
    while (!(str[num] == '\0')) {num++;}
    return num; 
}

/* 
    Task 2 - Count Words
    (Used in the later tasks)

    (How is count words relevant again)
    Thought: make an array storing the length of each word, size is countWords, stores countCharacters

    Loop 
*/
int countWords(const char str[])
{
    int num = 0;
    bool onWord = false;

    int strPos = 0;
    int strLen = countCharacters(str);

    while (strPos < strLen)
    {
        if (checkChar(str[strPos], 'l') && !onWord) {num++; onWord = true;}
        else if (checkChar(str[strPos], 'm') && onWord) {onWord = false;} 
        strPos++;
    }

    return num;
}

/*
    Task 3 - Swap String
    (Seems like one of the more difficult ones)


*/
void swapString(char str[], const char target[], const char to[])
{

    // Variables that are always initialised for most of the tasks
    int strPos = 0;
    int strLen = countCharacters(str);
    int targetLen = countCharacters(target);
    int toLen = countCharacters(to);
    int lastCheckPos = strLen - targetLen;

    char tempLeft[MAX_STRLEN] = { }, tempRight[MAX_STRLEN] = { }, repStr[MAX_STRLEN] = { }; 

    while (strPos <= lastCheckPos)
    {
        if (detectSame(str, target, strPos, targetLen))
        {
            // Reset stuff
            tempLeft[MAX_STRLEN] = { }; tempRight[MAX_STRLEN] = { }; repStr[MAX_STRLEN] = { };

            copyString(tempLeft, str, 0, 0, strPos, true);
            copyString(tempRight, str, 0, (strPos + targetLen), (strLen - strPos - targetLen), true);

            // Man this is a much better way of updating the length of the new string
            strLen = countCharacters(tempLeft) + toLen + countCharacters(tempRight);
            lastCheckPos = strLen - targetLen;
            int afterStart = strPos + toLen;

            wipeString(str);
            copyString(repStr, tempLeft, 0, 0, strPos, false);
            copyString(repStr, to, strPos, 0, toLen, false);
            copyString(repStr, tempRight, strPos + toLen, 0, (strLen - afterStart), true);
            int foo = countCharacters(repStr);
            copyString(str, repStr, 0, 0, foo, true);

            strPos += (toLen > targetLen) ? (toLen - 1) : (targetLen - 1); 
        }

        strPos++;
    }
}

/*
    Task 4 - Encrypt Text

    This one is quite easy
*/
void encryptText(char str[], int shift)
{
    // Variables that are always initialised for most of the tasks
    int strPos = 0;
    int strLen = countCharacters(str);

    // Dealing with shift
    while (shift < 0) {shift += 26;}
    shift %= 26;
    
    while (strPos < strLen)
    {
        if (('a' <= str[strPos]) && (str[strPos] <= 'z'))
        {
            int foo = (str[strPos] - 'a' + shift) % 26;
            char bar = foo + 'a';
            str[strPos] = bar;
        }
        else if (('A' <= str[strPos]) && (str[strPos] <= 'Z'))       
        {
            int foo = (str[strPos] - 'A' + shift) % 26;
            char bar = foo + 'A';
            str[strPos] = bar;
        }

        strPos++;
    }
}

/*
    Task 5 - Count Num Occurences

    This one is even easier
*/
int countNumOccurences(const char str[], const char target[])
{
    // Variables that are always initialised for most of the tasks
    int num = 0;
    int strPos = 0;
    int strLen = countCharacters(str);
    int targetLen = countCharacters(target);
    int lastCheckPos = strLen - targetLen;

    // Modified and shortened Task 3 code
    while (strPos <= lastCheckPos) {if (detectSame(str, target, strPos, targetLen)) {num++; strPos += (targetLen - 1);} strPos++;}

    return num;
}

/*
    Task 6 - Convert Into Lines

    I hate this one so much
*/
void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    
    // Variables for str
    int strPos = 0;
    int strLen = countCharacters(str);

    // Variables for lines
    int lineRow = 0;
    int linePos = 0;

    // First, deal with starting spaces
    while (checkChar(str[strPos],'s')) {strPos++;}
    bool startingNewLineCheckSpace = false;

    // Then can start loop
    while (strPos < strLen)
    { 

        int nextStrPos = strPos + 1;
        // just in case
        if (nextStrPos > MAX_STRLEN) {break;}

        /*
            Thought process:

            First check if inside word, and get the word length
            If word length exceeds spaces remaining, start new line
            else print punctuation as normal

            when end of line is reached, call function to add terminator in the correct place
        */
        if (checkChar(str[strPos], 'l') || (str[strPos] == ',') || (str[strPos] == '.') || (str[strPos] == '-')) {startingNewLineCheckSpace = false;}

        if (checkChar(str[strPos],'l')) 
        {
            int wordLen = countWordLen(str, strPos);
            if (wordLen < (NUM_CHARS_PER_LINE - linePos)) {addToLine(str, lines, wordLen, strPos, lineRow, linePos);}
            else {lineRow++; linePos = 0; addToLine(str, lines, wordLen, strPos, lineRow, linePos);}
        
        } else 
        {
            if (linePos < (NUM_CHARS_PER_LINE - 1)) 
            {
                if (startingNewLineCheckSpace)
                {
                    if (str[strPos] != ' ') {addToLine(str, lines, strPos, lineRow, linePos);} else {strPos++; continue;}
                }
                else
                {addToLine(str, lines, strPos, lineRow, linePos);}
            }
            else 
            {lineRow++; linePos = 0; startingNewLineCheckSpace = true;

                if (startingNewLineCheckSpace)
                {
                    if (str[strPos] != ' ') {addToLine(str, lines, strPos, lineRow, linePos);} else {strPos++; continue;}
                }
            }
        }
        //if (checkChar(str[strPos], 'l') || (str[strPos] == ',') || (str[strPos] == '.') || (str[strPos] == '-')) {startingNewLineCheckSpace = false;}

        if (nextStrPos > strLen) {break;}

        //cout << "loop finished\n";
    }
}

void printLeftJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE] = { };
    convertIntoLines(str, lines);
    int lineRow = checkLineRow(lines);
    linesPostProcessing(lines, lineRow);

    //cout << countCharacters(lines[0]) << countCharacters(lines[1]) << "\n";

    //cout << "Printing lines:\n=========================\n";
    for (int i = 0; i < lineRow; i++)
    {
        int j = 0;
        while (!(lines[i][j] == '\0')) { cout << lines[i][j]; j++;}
        cout << "\n";
    }
}

void printRightJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE] = { };
    convertIntoLines(str, lines);
    int lineRow = checkLineRow(lines);
    linesPostProcessing(lines, lineRow);

    convertRightJustified(lines, lineRow);

    //cout << "Printing lines:\n=========================\n";
    for (int i = 0; i < lineRow; i++)
    {
        int j = 0;
        while (!(lines[i][j] == '\0')) { cout << lines[i][j]; j++;}
        cout << "\n";
    }
}

// Ugh....
void printJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE] = { };
    convertIntoLines(str, lines);
    int lineRow = checkLineRow(lines);
    linesPostProcessing(lines, lineRow);

    convertFullJustified(lines, lineRow);

    printLines(lines, lineRow);
}

// i feel like this is easier



void convertStrToPigLatin(char str[])
{
    // gotta redo this part
    int strPos = 0, strLen = countCharacters(str);
    int newStrPos = 0; char newStr[MAX_STRLEN] = { 0 };
    int wordLen = 0, wordStartPos = 0; char word[MAX_STRLEN] = { 0 };
    bool onWord = true;
    // Check if there is space at first, if yes set to false
    if (str[0] == ' ') {onWord = false;}

    // Start the loop
    while (strPos <= strLen)
    {
        //cout << "\nCurrent String Position: " << strPos << "\nCurrent Character: " << str[strPos] << "\n";
        // Check if next char is null/space and if this char is on a word, then initiate pig latin convert, 
        // if not then just print out the current character
        if (notSpaceOrNullOrPunct(str[strPos]) && !onWord) {wordStartPos = strPos; wordLen++; onWord = true;}

        else if (notSpaceOrNullOrPunct(str[strPos]) && onWord) {wordLen++;}

        else if (!notSpaceOrNullOrPunct(str[strPos]) && onWord) 
        { 
            for (int i = 0; i < wordLen; i++) {word[i] = str[wordStartPos + i];}
            //cout << "Word found: ";
            //for (int i = 0; i < wordLen; i++) {cout << word[i];}
            //cout << "\n";
            addStringPigLatin(newStr, word, wordLen, newStrPos);
            // Wipe word
            for (int i = 0; i < wordLen; i++) {word[i] = ' ';}
            wordLen = 0;
            onWord = false;
        }
        if (!notSpaceOrNullOrPunct(str[strPos]) && !onWord) {addCharPigLatin(str, newStr, strPos, newStrPos);}

        strPos++;
    }
    newStr[newStrPos] = '\0';

    // Copy the entire line to lines
    for (int i = 0; i <= newStrPos; i++) {str[i] = ' ';}
    for (int i = 0; i <= newStrPos; i++) {str[i] = newStr[i];}

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


void encryptText(char str[], int shift)
{
    shift %= 26; // Gets both positive and negative shifts to be in the range (-26, 26).
    shift += 26; // Turn negative shifts to positive. Advances positive shifts by 26.
    shift %= 26; // Bring the positive shifts back in range, while negatives stay put.

    for (int i = 0; str[i] != '\0'; ++i)
    {
        if ('a' <= str[i] && str[i] <= 'z')
        {
            if (str[i] + shift > 'z')
                str[i] += static_cast<char>(shift - 26);
            else
                str[i] += static_cast<char>(shift);
        }
        else if ('A' <= str[i] && str[i] <= 'Z')
        {
            if (str[i] + shift > 'Z')
                str[i] += static_cast<char>(shift - 26);
            else
                str[i] += static_cast<char>(shift);
        }
    }
}

void encryptText(char str[], int shift) {
    shift = ((shift % 26) + 26) % 26;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + shift) % 26 + 'a';
        else if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + shift) % 26 + 'A';
    }
}