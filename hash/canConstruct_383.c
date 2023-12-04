#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define CHAR_NUMS 26
int g_src_map[CHAR_NUMS];
int g_tgt_map[CHAR_NUMS];

void clear_map(int *map)
{
    for (int i = 0; i < CHAR_NUMS; i++) {
        map[i] = 0;
    }
}

int get_ch_idx(char c)
{
    if (c >= 'a' && c <= 'z') {
        return (int)(c - 'a');
    }
    return -1;
}

bool set_map(int *map, char *string)
{
    char *ch = string;
    while (*ch != '\0') {
        int ch_idx = get_ch_idx(*ch);
        if (ch_idx < 0) {
            printf("only permit 'a' - 'z' but %c is input", *ch);
            return false;
        }
        map[ch_idx]++;
        ch++;
    }
    return true;
}

bool canConstruct(char * ransomNote, char * magazine){
    clear_map(g_src_map);
    clear_map(g_tgt_map);

    if (set_map(g_src_map, ransomNote) == false) {
        return false;
    }

    if (set_map(g_tgt_map, magazine) == false) {
        return false;
    }
    
    for (int i = 0; i < CHAR_NUMS; i++) {
        if (g_tgt_map[i] < g_src_map[i]) {
            return false;
        }
    }
    return true;
}

char *test_case[2] = {
    "a",
    "b"
};

char *test_case01[2] = {
    "aa",
    "ab"
};

char *test_case02[2] = {
    "aa",
    "aab"
};

int main()
{
    assert(canConstruct(test_case[0], test_case[1]) == false);
    assert(canConstruct(test_case01[0], test_case01[1]) == false);
    assert(canConstruct(test_case02[0], test_case02[1]) == true);
    printf("the test has been passed.\n");        
}