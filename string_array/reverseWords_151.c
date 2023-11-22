#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char tmp[10000];

char* reverseWords(char* s) {
    int s_total = strlen(s);
    int i = 0;
    tmp[i] = '\0';

    int r = s_total - 1;
    while (1) {
        while(r >= 0 && s[r] == ' ') {
            r--;
        }
        if (r < 0) {
            return tmp;
        }

        int l = r-1;
        while(l >= 0 && s[l] != ' ') {
            l--;
        }
        
        int wlen = r-l;
        if (i > 0) {
            tmp[i++] = ' ';
        }
        strncpy(&tmp[i], &s[l+1], wlen);
        i += wlen;
        tmp[i] = '\0';
        r = l;
    }
}

char *s = "ae";

int main()
{
    char *p = reverseWords(s);
    printf("%s.\n", p);
}