#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

#define MAP_LEN 1000
int g_cnt_map[MAP_LEN];

void init_map()
{
    for (int i = 0; i < MAP_LEN; i++) {
        g_cnt_map[i] = 0;
    }
}

void put_map(char a)
{
    int i = (int)a;
    g_cnt_map[i]++;
}

int cnt_in_map(char a)
{
    return g_cnt_map[(int) a];
}

void delete_map(char a)
{
    int i = (int)a;
    if(g_cnt_map[i] > 0) {
        g_cnt_map[i]--;
    } else {
        printf("error delete, char %c not in the map.\n", a);
    }
}

int lengthOfLongestSubstring(char* s) {

    int l = 0;
    int r = 1;
    int len = strlen(s);
    int ret = 1;
    
    if (len == 0) {
        return 0;
    }
    
    init_map();
    put_map(s[l]);
    
    // window [l, r)
    while(l < r) {
        // expand r to the longest
        while(r < len && cnt_in_map(s[r]) == 0) {
            put_map(s[r]);
            r++;
        }
        ret = max(ret, r-l);

        if (r == len) {
            break;
        }
        // shrink l
        while(l < r && s[l] != s[r]) {
            delete_map(s[l]);
            l++; 
        }

        // now s[l] == s[r], next l
        delete_map(s[l]);
        l++;
        if(l == r) {
            put_map(s[r]);
            r++;
        }
    }
    return ret;
}

char *s = "pwwkew";

int main()
{
    printf("%d.\n", lengthOfLongestSubstring(s));
}