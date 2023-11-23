#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    ENGLISH = 0,
    NUM,
    INVALID
} type_t;

bool getType(char c, int *offset, type_t *type)
{
    bool ret = false;
    if (c >= 'a' && c <= 'z') {
        ret = true;
        *offset = c - 'a';
        *type = ENGLISH;
    } else if (c >= 'A' && c <= 'Z')
    {
        ret = true;
        *offset = c - 'A';
        *type = ENGLISH;
    } else if (c >= '0' && c <= '9')
    {
        ret = true;
        *offset = c - '0';
        *type = NUM;
    }
    return ret;
}

bool isPalindrome(char* s) {
    int l = 0;
    int cl = 0;
    type_t tl = INVALID;

    int r = strlen(s) - 1;
    int cr = 0;
    type_t tr = INVALID;

    while (1) {
        while(l < strlen(s) && !getType(s[l], &cl, &tl)) {
            l++;
        }
        if (l == strlen(s)) {
            return true;
        }

        while((r >= 0) && !getType(s[r], &cr, &tr)) {
            r--;
        }
        if (r == 0) {
            return true;
        }

        if (l >= r) {
            return true;
        }
        if (tl != tr || cl != cr) {
            return false;
        }

        l++;
        r--;
    }

    return true; // impossible here.
}

char *g_s = " ";
int main()
{
    printf("result: %d\n", isPalindrome(g_s));
}