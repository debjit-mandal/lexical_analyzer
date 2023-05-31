#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // Include the <stdlib.h> header for malloc and free functions

// Token types
typedef enum {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PUNCTUATION,
    KEYWORD
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
} Token;

// Function to check if a character is a valid operator
bool isOperator(char c) {
    char operators[] = "+-*/=";
    for (int i = 0; i < strlen(operators); i++) {
        if (c == operators[i])
            return true;
    }
    return false;
}

// Function to check if a character is a valid punctuation
bool isPunctuation(char c) {
    char punctuations[] = ".,;(){}[]";
    for (int i = 0; i < strlen(punctuations); i++) {
        if (c == punctuations[i])
            return true;
    }
    return false;
}

// Function to check if a string is a keyword
bool isKeyword(char *str) {
    char *keywords[] = {"if", "else", "while", "for", "int", "float", "void", "return"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

// Function to tokenize the input string
Token* tokenize(char *input) {
    Token *tokens = malloc(strlen(input) * sizeof(Token));
    int tokenCount = 0;
    int i = 0;

    while (input[i] != '\0') {
        // Skip whitespaces
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Identify identifiers or keywords
        if (isalpha(input[i])) {
            int j = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                tokens[tokenCount].value[j++] = input[i++];
            }
            tokens[tokenCount].value[j] = '\0';

            if (isKeyword(tokens[tokenCount].value)) {
                tokens[tokenCount].type = KEYWORD;
            } else {
                tokens[tokenCount].type = IDENTIFIER;
            }

            tokenCount++;
            continue;
        }

        // Identify numbers
        if (isdigit(input[i])) {
            int j = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                tokens[tokenCount].value[j++] = input[i++];
            }
            tokens[tokenCount].value[j] = '\0';
            tokens[tokenCount].type = NUMBER;
            tokenCount++;
            continue;
        }

        // Identify operators
        if (isOperator(input[i])) {
            tokens[tokenCount].value[0] = input[i++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = OPERATOR;
            tokenCount++;
            continue;
        }

        // Identify punctuation
        if (isPunctuation(input[i])) {
            tokens[tokenCount].value[0] = input[i++];
            tokens[tokenCount].value[1] = '\0';
            tokens[tokenCount].type = PUNCTUATION;
            tokenCount++;
            continue;
        }

        // Ignore unrecognized characters
        i++;
    }

    tokens[tokenCount].type = -1;  // Mark end of tokens
    return tokens;
}

// Function to print the tokens
void printTokens(Token *tokens) {
    int i = 0;
    while (tokens[i].type != -1) {
        printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        i++;
    }
}

int main() {
    char input[100];
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove the trailing newline character from fgets
    if (input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';

    Token *tokens = tokenize(input);
    printTokens(tokens);

    free(tokens);
    return 0;
}
