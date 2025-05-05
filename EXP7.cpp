#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char production[MAX][20];
char leading[MAX][10], trailing[MAX][10];
int n;

// Check if a symbol is a non-terminal
int isNonTerminal(char c) {
    return isupper(c);
}

// Add a symbol to a set if not already present
void addToSet(char set[], char symbol) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == symbol)
            return;
    }
    int len = strlen(set);
    set[len] = symbol;
    set[len + 1] = '\0';
}

// Compute LEADING of a non-terminal
void computeLeading() {
    for (int i = 0; i < n; i++) {
        char nt = production[i][0];
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == '|') continue;
            if (!isNonTerminal(production[i][j])) {
                addToSet(leading[nt - 'A'], production[i][j]);
                break;
            } else {
                // Look for LEADING of that non-terminal
                int found = 0;
                for (int k = 0; k < n; k++) {
                    if (production[k][0] == production[i][j]) {
                        for (int l = 2; production[k][l] != '\0'; l++) {
                            if (!isNonTerminal(production[k][l])) {
                                addToSet(leading[nt - 'A'], production[k][l]);
                                found = 1;
                                break;
                            }
                        }
                    }
                    if (found) break;
                }
                break;
            }
        }
    }
}

// Compute TRAILING of a non-terminal
void computeTrailing() {
    for (int i = 0; i < n; i++) {
        char nt = production[i][0];
        int len = strlen(production[i]);
        for (int j = len - 1; j >= 2; j--) {
            if (production[i][j] == '|') continue;
            if (!isNonTerminal(production[i][j])) {
                addToSet(trailing[nt - 'A'], production[i][j]);
                break;
            } else {
                // Look for TRAILING of that non-terminal
                int found = 0;
                for (int k = 0; k < n; k++) {
                    if (production[k][0] == production[i][j]) {
                        int plen = strlen(production[k]);
                        for (int l = plen - 1; l >= 2; l--) {
                            if (!isNonTerminal(production[k][l])) {
                                addToSet(trailing[nt - 'A'], production[k][l]);
                                found = 1;
                                break;
                            }
                        }
                    }
                    if (found) break;
                }
                break;
            }
        }
    }
}

// Display the sets
void displaySets() {
    printf("\nLEADING sets:\n");
    for (int i = 0; i < n; i++) {
        char nt = production[i][0];
        printf("LEADING(%c) = { ", nt);
        for (int j = 0; leading[nt - 'A'][j] != '\0'; j++) {
            printf("%c ", leading[nt - 'A'][j]);
        }
        printf("}\n");
    }

    printf("\nTRAILING sets:\n");
    for (int i = 0; i < n; i++) {
        char nt = production[i][0];
        printf("TRAILING(%c) = { ", nt);
        for (int j = 0; trailing[nt - 'A'][j] != '\0'; j++) {
            printf("%c ", trailing[nt - 'A'][j]);
        }
        printf("}\n");
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., E=E+T):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    computeLeading();
    computeTrailing();
    displaySets();

    return 0;
}