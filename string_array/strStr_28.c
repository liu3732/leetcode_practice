#include <string.h>
#include <stdio.h>

int strStr(char* haystack, char* needle) {
    int nlen = strlen(needle);
    int hlen = strlen(haystack);

    int left = 0;
    while (1) {
        while (left < hlen && needle[0] != haystack[left]) {
            left++;
        }
        if (left == hlen) {
            return -1;
        }
        if(strncmp(&haystack[left], needle, nlen) == 0) {
            return left;
        }
        left++;
    }
    return -1;
}

int main()
{
    char *haystack = "leetcode";
    char *needle = "leeto";

    printf("%d\n", strStr(haystack, needle));
}