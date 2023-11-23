#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isSubsequence(char* s, char* t) {
    int si = 0;
    int slen = strlen(s);

    int ti = 0;
    int tlen = strlen(t);

    if (slen > tlen) {
        return false;
    }

    while (ti < tlen && si < slen) {
        if(t[ti] == s[si]) {
            si++;
            ti++;
        } else {
            ti++;
        }
    }
    return si == slen ? true : false;
}

char *g_s = "axc";
char *g_t = "ahbgdc";

int main()
{
    printf("%d\n", isSubsequence(g_s, g_t));
}