#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CH_MAX_NUM 26
typedef struct {
    int cnt[CH_MAX_NUM];
} ch_map_t;

void init(ch_map_t *m)
{
    for (int i = 0; i < CH_MAX_NUM; i++) {
        m->cnt[i] = 0;
    }
}

bool isAnagram(char* s, char* t) {
    ch_map_t *smap = (ch_map_t *)malloc(sizeof(ch_map_t));
    ch_map_t *tmap = (ch_map_t *)malloc(sizeof(ch_map_t));
    init(smap);
    init(tmap);
    bool ret = true;

    int len;
    if ((len = strlen(s)) != strlen(t)) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        int ch_s = (int) (s[i] - 'a');
        int ch_t = (int) (t[i] - 'a');

        smap->cnt[ch_s]++;
        tmap->cnt[ch_t]++;
    }

    for (int i = 0; i < CH_MAX_NUM; i++) {
        if (smap->cnt[i] != tmap->cnt[i]) {
            ret = false;
        }
    }
    free(smap);
    free(tmap);
    return ret;
}

char *s = "rat";
char *t = "car";
int main()
{
    printf("%d.\n", isAnagram(s, t));
}