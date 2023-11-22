#include <string.h>
#include <stdio.h>

int lengthOfLastWord(char* s) {
    int len = strlen(s);

    // start from end. get s(l:r]    
    int r = len-1;
    while (r >= 0 && s[r] == ' ') {
        r--;
    }
    if (r < 0) {
        return 0;
    }

    int l = r - 1;
    while (l >= 0 && s[l] != ' ') {
        l--;
    }
    if (l < 0) {
        return r+1;
    } else {
        return r-l;
    }
}

int main()
{
    char *s = "";

    printf("%d\n", lengthOfLastWord(s));
}