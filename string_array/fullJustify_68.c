#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    char **ret = NULL;
    *returnSize = 0;

    int left = 0;
    int right = 1;
    int accumulate_words_num = 0;
    while(left < wordsSize) {
        // caculate words_num
        int words_num = 1;
        int words_width = strlen(words[left]);
        int space_nums;

        while (right < wordsSize && 
                words_width + strlen(words[right]) < maxWidth) {
            words_width += strlen(words[right]);
            right++;
            words_num++;
        }
    recallate:
        if (words_num == 1) {
            // can be any space_nums.
            ret = (char **) realloc(ret, (*returnSize + 1)* sizeof(char *));
            ret[*returnSize] = (char *) malloc(maxWidth + 1);
            strncpy(ret[*returnSize], words[left], words_width);
            for (int i = words_width; i < maxWidth; i++) {
                ret[*returnSize][i] = ' ';
            }
            ret[*returnSize][maxWidth] = '\0';
            (*returnSize)++;
        } else {
            space_nums = maxWidth - words_width;
            int base_spaces = space_nums/(words_num-1);
            int extra_spaces = space_nums%(words_num-1);
            if (base_spaces == 0) {
                words_width -= strlen(words[--right]);
                words_num--;
                goto recallate;
            }

            ret = (char **) realloc(ret, (*returnSize + 1)* sizeof(char *));
            ret[*returnSize] = (char *) malloc(maxWidth + 1);
            int shift = 0;
            if(accumulate_words_num + words_num == wordsSize) {
                // left aligned
                for (int i = left; i < left + words_num; i++) {
                    strncpy(&ret[*returnSize][shift], words[i], strlen(words[i]));
                    shift += strlen(words[i]);
                    if(shift >= maxWidth) {
                        break;
                    } else {
                        ret[*returnSize][shift++] = ' ';
                        space_nums--;
                    }   
                }
                while (space_nums > 0) {
                    ret[*returnSize][shift++] = ' ';
                    space_nums--;
                }
            } else {
                for (int i = left; i < left + words_num; i++) {
                    strncpy(&ret[*returnSize][shift], words[i], strlen(words[i]));
                    shift += strlen(words[i]);
                    int spaces = base_spaces + (extra_spaces > 0 ? 1: 0);
                    if(shift + spaces-1 >= maxWidth) {
                        spaces = maxWidth - shift;
                    }
                    for (int j = 0; j < spaces; j++) {
                        ret[*returnSize][shift++] = ' ';
                    }
                    extra_spaces--;
                }
            }
            ret[*returnSize][shift] = '\0';
            (*returnSize)++;
        }

        accumulate_words_num += words_num;
        left = right;
        right = left+1;
    }
    return ret;
}

char *g_words[] = {"Science"};

int main()
{
    char **words = (char **)malloc(sizeof(g_words));
    int wordSize = sizeof(g_words)/sizeof(char *);
    for (int r = 0; r < wordSize; r++) {
        words[r] = (char *)malloc(strlen(g_words[r] + 1));
        strncpy(words[r], g_words[r], strlen(g_words[r]) + 1);
    }

    int maxWidth = 20;
    int rowSize = 0;
    char **ret = fullJustify(words, wordSize, maxWidth, &rowSize);

    for (int r = 0; r < wordSize; r++) {
        free(words[r]);
    }
    free(words);

    for (int r = 0; r < rowSize; r++) {
        free(ret[r]);
    }
    free(ret);
}