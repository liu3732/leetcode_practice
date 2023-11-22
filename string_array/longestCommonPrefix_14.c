#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    int minC = strlen(strs[0]);
    for(int r = 1; r < strsSize; r++) {
        int col = strlen(strs[r]);
        if (col < minC) {
            minC = col;
        }
    }
    char *ret = (char *)malloc(minC+1);
    int i = 0;
    ret[i] = '\0';

    int c;
    for(c = 0; c < minC ; c++) {
        int r = 0;
        char common = strs[0][c];
        for (int r = 1; r < strsSize; r++) {
            if (common != strs[r][c]) {
                return ret;
            }
        }
        ret[i++] = common;
        ret[i] = '\0';
    }
    return ret;
}


const char *s[] = {
"dog"
};

char **copyStrs() {
    char **ptr = (char **)malloc(sizeof(s));
    for (int r = 0; r < sizeof(s)/sizeof(char *); r++) {
        int len = strlen(s[r]) + 1;
        ptr[r] = (char *)malloc(len);
        strncpy(ptr[r], s[r], len);
    }
    return ptr;
}

int main()
{
    int len = sizeof(s)/sizeof(char *);
    char **ptr = copyStrs();

    char *ret = longestCommonPrefix(ptr, len);
    printf("%s\n", ret);

    free(ret);
    for (int r = 0; r < len; r++) {
        free(ptr[r]);
    }
    free(ptr);
}