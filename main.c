#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Pattern_struct {
    char* pat;  //string pattern - exs: "hello", "-ell-", "-----"
    int count;  //frequency of pattern in the current word list
    int changes;//number of occurences of new letter in this pattern
} Pattern;


//-------------------------------------------------------------------
// TODO - Task II: write addWord() function, which adds a new word to
//      a dynamic heap-allocated array of C-strings; heap-space must  
//      be allocated for the new word inside this function, then copy  
//      the chars from newWord to the newly allocated heap-space; if
//      adding the new word pushes numWords above maxWords, then 
//      realloate the words array with double the capacity
//      parameters: 
//          char*** words - array of C-strings passed-by-pointer
//              note: *words is an array of pointers
//                    **words is an array of chars
//                    ***words is a char  
//                    (*words)[0] is the 1st C-string in the array
//                    (*words)[1] is the 2nd C-string in the array
//                    (*words)[0][0] is 1st char of 1st C-string
//                    (*words)[1][2] is 3rd char of 2nd C-string
//                    etc.
//          int* numWords - current # of words in *words array
//               note: numWords will increase by 1 here, 
//                     so it is passed-by-pointer
//          int* maxWords - current capacity of *words array
//               note: maxWords may increase by x2 here, 
//                     so it is passed-by-pointer
//          char* newWord - C-string word to be added to words
//               note: newWord is a C-string, automatically a pointer
//-------------------------------------------------------------------
void addWord(char*** words, int* numWords, int* maxWords, char* newWord) {
    char** newWords = NULL;
    char* freshWord = (char*)malloc( ((strlen(newWord) + 1) * sizeof(char))); //allocate memory for the new word
    strcpy(freshWord, newWord);


    if ( ((*numWords) + 1) > (*maxWords) ){
        newWords = (char**)malloc( ((*maxWords) * 2) * sizeof(char*) ); //create a new array with double the size

        for (int i = 0; i < (*numWords); ++i){ //copy over the words from the old words array to the new one
            newWords[i] = (*words)[i];
        }

        (*maxWords) = (*maxWords) * 2;
        free(*words);
        (*words) = newWords;
    }

    (*words)[(*numWords)] = freshWord;
    (*numWords) ++;

}

//Parameters wordList, capacity and Words added will be directly edited in the helper function addWord. Only longest word is directly edited in this function
void loadWordList(char*** wordList, char* fileName, int* capacity, int* wordsAdded, int* wordsRead, int correctLength, char* longestWord){
    FILE* myFile = NULL;
    myFile = fopen(fileName, "r");

    char tempWord[30] = {'\0'};
    char* fixedWord = NULL;

    if (myFile == NULL){
        printf("File could not be opened.\n");
        return;
    }
    while(fscanf(myFile, "%s", tempWord) == 1){
        (*wordsRead)++;
        if (strlen(tempWord) == correctLength){ //Only the word to the word list if it's the correct length
            addWord(wordList, wordsAdded, capacity, tempWord);
        }
        if (strlen(tempWord) > strlen(longestWord)){ //Only change the longest word if temp word's length is greater than the length of the current longest word
            strcpy(longestWord, tempWord);
        }
    }

    fclose(myFile);
}

//-------------------------------------------------------------------
// TODO - Task V: write the strNumMods() function, which
//      returns count of character differences between two strings;
//      includes extra characters in longer string if different lengths
// Exs: str1 = magic, str2 = magic, returns 0
//      str1 = wands, str2 = wants, returns 1
//      str1 = magic, str2 = wands, returns 4
//      str1 = magic, str2 = mag, returns 2
//      str1 = magic, str2 = magicwand, returns 4
//      str1 = magic, str2 = darkmagic, returns 8
//-------------------------------------------------------------------
int strNumMods(char* str1, char* str2) {
    int difference = 0;
    if (strcmp(str1, str2) == 0){
        return 0;
    }

    if (strlen(str1) > strlen(str2)){
        for (int i = 0 ; i < strlen(str2); i++){
            if (str2[i] != str1[i]){
                difference++;
            }
        }
        difference += (strlen(str1) - strlen(str2));
    } else {
        for (int i = 0; i < strlen(str1); i++){
            if (str1[i] != str2[i]){
                difference++;
            }
        }
        difference += (strlen(str2) - strlen(str1));
    }
    return difference; //modify this
}

//If the two strings are the same return the length of the string
//If one string is bigger than the either. first compare the characters of the the shorter string with the longer string. If all the characters match then the difference is the length of the shorter string
//If the strings are the same size then we will compare the characters of both string until we find the different character
int strDiffInd(char* str1, char* str2) {
    int diff = 0;
    if (strcmp(str1,str2) == 0){
        diff = strlen(str1);
        return diff;
    } 

    if (strlen(str1) < strlen(str2)){//str 1 is smaller than string 2
        for(int i = 0; i < strlen(str1); ++i){
            if (str1[i] != str2[i]){
                return i;
            }
        }
        diff = strlen(str1);
        return diff;
    } else if (strlen(str2) < strlen(str1)) {//str 2 is smaller than string 1
        for(int i = 0; i < strlen(str2); ++i){
            if (str2[i] != str1[i]){
                return i;
            }
        }
        diff = strlen(str2);
        return diff;
    }

    //strings are the same size
    for(int i = 0; i < strlen(str1);++i){
        if (str1[i] != str2[i]){
            return i;
        }
    }
}

//Prints game settubg
void printGameSettings(int wordSize, int numGuesses, bool statsMode, bool wordListMode, bool letterListMode, bool patternListMode){
    printf("Game Settings:\n");
    printf("  Word Size = %d\n", wordSize);
    printf("  Number of Guesses = %d\n", numGuesses);

    if (statsMode == true){ 
        printf("  View Stats Mode = ON\n");
    } else {
        printf("  View Stats Mode = OFF\n");
    }

    if (wordListMode == true){
        printf("  View Word List Mode = ON\n");
    } else {
        printf("  View Word List Mode = OFF\n");
    }

    if (letterListMode == true){
        printf("  View Letter List Mode = ON\n");
    } else {
        printf("  View Letter List Mode = OFF\n");
    }

    if (patternListMode == true){
        printf("  View Pattern List Mode = ON\n");
    } else {
        printf("  View Pattern List Mode = OFF\n");
    }

}

void createPatternArray(char*** wordList, int listSize, int wordSize, Pattern** patterns, int* numPatterns, int* patternsCap, char guess, char* guesses){

    (*patterns) = (Pattern*)malloc((*patternsCap) * sizeof(Pattern));
    int numChanges = 0;
    Pattern* newPatterns = NULL;

    for(int i = 0; i < listSize; i++){//This for loop iterates through each word in wordList
        char* patternString = (char*)malloc((wordSize + 1) * sizeof(char));
        numChanges = 0;

        for (int j = 0; j < wordSize; ++j){ //This for loop iterates through each character in a word
            if ((*wordList)[i][j] == guess){ //compares it to our current guess
                patternString[j] = guess;
                numChanges++;
            } else {
                patternString[j] = '-';
            }

            for (int k = 0; k < 26; k++){ //Loops through the characters previously guessed and compares it to the current character we're at as we iterate through the characters in the word of the for loop we're currently in
                if(guesses[k] == (*wordList)[i][j]){
                    patternString[j] = guesses[k];
                }
            }
        }

        patternString[wordSize] = '\0';//adding a null character to the end of pattern string

        if(numPatterns == 0){//we currently don't have any patterns so add it.
            (*patterns)[(*numPatterns)].count = 0;
            (*patterns)[(*numPatterns)].changes = 0;
            (*patterns)[(*numPatterns)].pat = patternString;
            (*patterns)[(*numPatterns)].count += 1;
            (*patterns)[(*numPatterns)].changes = numChanges;
            (*numPatterns)++;
        } else {
            for(int j = 0; j < (*numPatterns); j++){ //iterate through each pattern we have
                if (strcmp(patternString, ((*patterns)[j].pat) ) == 0){//We already have that pattern
                    ((*patterns)[j]).count += 1;
                    free(patternString);
                    patternString = NULL;
                    break;
                }
            }
            if (patternString != NULL){
                if( ((*numPatterns) + 1) > (*patternsCap)){//We need to grow the array
                    newPatterns = (Pattern*)malloc(((*patternsCap) * 2) * sizeof(Pattern));//Copy over elements
                    for(int j = 0; j < (*numPatterns); j++){ 
                        newPatterns[j] = (*patterns)[j];
                    }
                    free(*patterns);
                    (*patterns) = newPatterns;
                    (*patternsCap) = (*patternsCap) * 2;
                }
                (*patterns)[*numPatterns].count = 0;
                (*patterns)[*numPatterns].changes = 0;
                (*patterns)[*numPatterns].pat = patternString;
                (*patterns)[*numPatterns].count += 1;
                (*patterns)[*numPatterns].changes = numChanges;
                (*numPatterns)+=1;
            }
        }
    }
}

void freePatterns(Pattern** patterns, int* numPatterns, int* patternsCap){
    for (int i = 0; i < (*numPatterns); i++){
        free(((*patterns)[i].pat));
    }

    free(*patterns);
    (*patterns) = NULL;
    (*numPatterns) = 0;
    (*patternsCap) = 4;
}

Pattern* pickPattern(Pattern** patterns, int numPatterns, char guess, int wordSize){
    Pattern* chosenPattern = NULL;
    chosenPattern = &((*patterns)[0]);

    for (int i = 0; i < numPatterns; i++){
        if ( ((*patterns)[i].count) > ((*chosenPattern).count) ) { //chosenPattern will be the pattern with the higher count
            chosenPattern = &((*patterns)[i]);
        } else if ( ((*patterns)[i].count) == ((*chosenPattern).count) ){ 
            
            if ( ((*patterns)[i].changes) < ((*chosenPattern).changes) ){ //chosenPattern will be the pattern with the less changes
                chosenPattern = &((*patterns)[i]);
            } else if (((*patterns)[i].changes) == ((*chosenPattern).changes)){
                for (int j = 0; j < wordSize; j++){ //checking for which string has the earliest instance of the guess
                    if ( ((*chosenPattern).pat)[j] == guess){
                        break;
                    }
                    if ( ((*patterns)[i].pat)[j] == guess ){
                        chosenPattern = &((*patterns)[i]);
                        break;
                    }
                }
            }

        }
    }

    return chosenPattern;
}

void reduceWordList(char*** wordList, int* listSize, int* capacity, int wordSize, Pattern** chosenPattern, char guess, char* guesses){

    int newListSize = 0;
    int newListCap = 4;
    char** reducedWordList = (char**)malloc( newListCap * sizeof (char*));
    char** tempReducedWordList = NULL;

    for(int i = 0; i < (*listSize); i++){//This for loop iterates through each word in wordList

        char* patternString = (char*)malloc((wordSize + 1) * sizeof(char));

        for (int j = 0; j < wordSize; ++j){ //This for loop iterates through each character in a word
            if ((*wordList)[i][j] == guess){ //compares it to our current guess
                patternString[j] = guess;
            } else {
                patternString[j] = '-';
            }

            for (int k = 0; k < 26; k++){ //Loops through the characters previously guessed and compares it to the current character we're at as we iterate through the characters in the word of the for loop we're currently in
                if(guesses[k] == (*wordList)[i][j]){
                    patternString[j] = guesses[k];
                }
            }
        }

        patternString[wordSize] = '\0';//adding a null character to the end of pattern string

        if(strcmp(patternString, ((**chosenPattern).pat)) == 0){
            if( (newListSize + 1) > newListCap){ //the reduced word list needs to be bigger so the below increases it's size
                tempReducedWordList = (char**)malloc( ((newListCap) * 2) * sizeof(char*));

                for(int j = 0; j < newListSize; ++j){
                    tempReducedWordList[j] = reducedWordList[j];
                }

                free(reducedWordList);
                reducedWordList = tempReducedWordList;
                newListCap = newListCap * 2;
                tempReducedWordList = NULL;
            }
            reducedWordList[newListSize] = (*wordList)[i];
            newListSize++;

        } else { //Since we're not transfering this word to the reduced word list we need to free that word before we lose access to it
            free((*wordList)[i]);
        }

        free(patternString);
    }

    //All words that haven't been added to the reduced list have already been freed and all other needed words have been passed to the reduced word list. So we can now free the old word list and ressign it to the new one
    free(*wordList);
    (*wordList) = reducedWordList;
    //Also change the associated variable with wordList to the variable associated with the new reducedWordList
    (*capacity) = newListCap;
    (*listSize) = newListSize;
}

void game(char*** wordList, int* listSize, int* capacity, int* wordSize, int* numGuesses, bool* statsMode, bool* wordListMode, bool* letterListMode, bool* patternListMode){
    char guesses[] = "__________________________";
    char guess = ' ';

    int numPatterns = 0;
    int patternsCap = 4;
    Pattern* patterns = NULL;
    Pattern* chosenPattern = NULL;

    bool gameWon = false;
    bool previouslyGuessed = false;
    bool validGuess = false;
    bool start = true;

    while(guess != '#' && (*numGuesses) != 0 && gameWon == false){
        printf("\n");
        if(validGuess == true || start == true){
            printf("Number of guesses remaining: %d\n", (*numGuesses));
        }

        validGuess =false;

        if((*letterListMode) == true){
            printf("Previously guessed letters: ");
            for(int i = 0; i < 26; i++){
                if ((guesses[i]) != '_'){
                    printf("%c", guesses[i]);
                    printf(" ");
                } else{}
            }
            printf("\n");
        }

        printf("Guess a letter (# to end game): ");
        printf("\n");
        scanf(" %c", &guess);
        for(int i = 0; i < 26; i++){
            if (guess == guesses[i]){
                previouslyGuessed = true;
                break;
            }
        }

        if (previouslyGuessed == true){
            printf("Letter previously guessed...");
            previouslyGuessed = false;
        } else if ( (!islower(guess) || !isalpha(guess)) && guess != '#'){
            printf("Invalid letter...");
        } else if (guess != '#'){
            validGuess = true;
            start = false;
            createPatternArray(wordList, *listSize, (*wordSize), &patterns, &numPatterns, &patternsCap, guess, guesses);
            if ((*patternListMode) == true){
                printf("All patterns for letter %c: \n", guess);
                for(int i = 0; i < numPatterns; i++){
                    printf("  %s    count = %d  changes = %d\n", patterns[i].pat, patterns[i].count, patterns[i].changes);
                }
            }

            chosenPattern = pickPattern(&patterns, numPatterns, guess, *wordSize);
            reduceWordList(wordList, listSize, capacity, *wordSize, &chosenPattern, guess, guesses);

            if ((*chosenPattern).changes == 0){
                printf("Oops, there are no %c's. You used a guess.\n", guess);
                (*numGuesses)-= 1;
            } else {
                printf("Good guess! The word has at least one %c.\n", guess);
            }

            if(*statsMode == true){
                printf("Number of possible words remaining: %d\n", (*listSize));
            }

            for (int i = 0; i < (*wordSize); i++){
                if (isalpha(((*chosenPattern).pat)[i])){
                    gameWon = true;
                } else {
                    gameWon = false;
                    break;
                }
            }

            if((*wordListMode) == true){
                printf("Possible words are now:\n");
                for (int i = 0; i < (*listSize); ++i){
                    printf("  %s\n", (*wordList)[i]);
                }
            }
            printf("The word pattern is: %s\n", (*chosenPattern).pat);

            guesses[(guess - 'a')] = guess;
            freePatterns(&patterns, &numPatterns, &patternsCap);

        }
    }
    
    printf("\n");

    if (guess == '#'){
        printf("Terminating game...");
        return;
    }

    if ((*numGuesses) == 0 && gameWon == false){
        printf("You ran out of guesses and did not solve the word.\n");
        printf("The word is: %s", (*wordList)[0]);
    }

    if (gameWon == true){
        printf("You solved the word!\n");
        printf("The word is: %s\n", (*wordList)[0]);
    }

    printf("Game over.\n");
}


int main(int argc, char* argv[]) {

    printf("Welcome to the (Evil) Word Guessing Game!\n");
    printf("\n");
    
    bool solved = false;
    bool invalidCommand = false;
    bool statsMode = false;
    bool wordListMode = false;
    bool letterListMode = false;
    bool patternListMode = false;

    int wordSize = 5;
    int numGuesses = 26;

    //The following for loop hands commandline arguments by: 
    //first finding the -parameter at some index in argv, then index + 1 in argv contains the strings with the value for that parameter
    for (int i = 0; i < argc; ++i){
        if ( strcmp(argv[i], "-n") == 0 ){
            wordSize = atoi(argv[i + 1]);
            if (wordSize < 2 || wordSize > 29){
                printf("Invalid word size.\n");
                printf("Terminating program...\n");
                invalidCommand = true;
                break;
            }
        }
        if ( strcmp(argv[i], "-g") == 0 ) {
            numGuesses = atoi(argv[i + 1]);
            if (numGuesses < 0){
                printf("Invalid number of guesses.\n");
                printf("Terminating program...\n");
                invalidCommand = true;
                break;
            }
        }
        if ( strcmp(argv[i], "-s")  == 0 ) {
            statsMode = true;
        }
        if ( strcmp(argv[i], "-w")  == 0 ) {
            wordListMode = true;
        }
        if ( strcmp(argv[i], "-l")  == 0 ) {
            letterListMode = true;
        }
        if ( strcmp(argv[i], "-p")  == 0 ) {
            patternListMode = true;
        }
        if ( strcmp(argv[i], "-v")  == 0 ) {
            patternListMode = true;
            letterListMode = true;
            wordListMode = true;
            statsMode = true;
        }
        if ( argv[i][0] == '-'){
            if ( (argv[i][1] != 'n') && (argv[i][1] != 'g') && (argv[i][1] != 's') && (argv[i][1] != 'w') && (argv[i][1] != 'l') && (argv[i][1] != 'p') && (argv[i][1] != 'v') ){
                invalidCommand = true;
                printf("Invalid command-line argument.\n");
                printf("Terminating program...\n");
                break;
            }
        }
    }

    if (invalidCommand == false){
        printGameSettings(wordSize, numGuesses, statsMode, wordListMode, letterListMode, patternListMode);
    }
    
    
    int capacity = 4;
    int wordsRead = 0;
    int wordsAdded = 0;
    char longestWord[30] = "";
    char** wordList = (char**)malloc(capacity*sizeof(char*));
    
    if(invalidCommand == false){
        loadWordList(&wordList, "dictionary.txt", &capacity, &wordsAdded, &wordsRead, wordSize, longestWord);
    }

    if (statsMode == true && invalidCommand == false){
        printf("The dictionary contains %d words total.\n", wordsRead);
        int longestWordLength = strlen(longestWord);
        printf("The longest word %s has %d chars.\n", longestWord, longestWordLength);
        printf("The dictionary contains %d words of length %d.\n", wordsAdded, wordSize);
        printf("Max size of the dynamic words array is %d.\n", capacity);
    }
    if (wordListMode == true && invalidCommand == false){
        printf("Words of length %d:\n", wordSize);
        for (int i = 0; i < wordsAdded; ++i){
            printf("  %s\n", wordList[i]);
        }
        if (wordsAdded == 0){
            printf("Dictionary has no words of length %d.\n", wordSize);
            printf("Terminating program...\n");
            invalidCommand = true;
        }
    }

    if (invalidCommand == false){
        printf("The word pattern is: ");
        for (int i = 0; i < wordSize; i++){
            printf("-");
        }
        printf("\n");
    }

    int uniquePatternCapacity = 4;
    int uniquePatternElements = 0;
    Pattern* uniquePatterns = (Pattern*)malloc(uniquePatternCapacity * sizeof(Pattern));
    
    if(invalidCommand == false && wordsAdded != 0){
        game(&wordList, &wordsAdded, &capacity, &wordSize, &numGuesses, &statsMode, &wordListMode, &letterListMode, &patternListMode);
    }

    

    //Freeing memory
    for(int i = 0; i < wordsAdded; i++){
        free(wordList[i]);
    }

    free(wordList);
    free(uniquePatterns);
    
    return 0;
}