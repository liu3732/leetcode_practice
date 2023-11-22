#include <string.h>
#include <assert.h>
#include <stdio.h>

/*
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/


typedef struct {
    char *roman;
    int  v;
} romanType;

const romanType romanMap[] = {
    {
        .roman = "MMM",
        .v = 3000
    },
    {
        .roman = "MM",
        .v = 2000
    },
    {
        .roman = "M",
        .v = 1000
    },
    {
        .roman = "CM",
        .v = 900
    },
    {
        .roman = "DCCC",
        .v = 800
    },
    {
        .roman = "DCC",
        .v = 700
    },
    {
        .roman = "DC",
        .v = 600
    },
    {
        .roman = "D",
        .v = 500
    },
    {
        .roman = "CD",
        .v = 400
    },
    {
        .roman = "CCC",
        .v = 300
    },
    {
        .roman = "CC",
        .v = 200
    },
    {
        .roman = "C",
        .v = 100
    },
    {
        .roman = "XC",
        .v = 90
    },
    {
        .roman = "LXXX",
        .v = 80
    },
    {
        .roman = "LXX",
        .v = 70
    },
    {
        .roman = "LX",
        .v = 60
    },
    {
        .roman = "L",
        .v = 50
    },
    {
        .roman = "XL",
        .v = 40
    },
    {
        .roman = "XXX",
        .v = 30
    },
    {
        .roman = "XX",
        .v = 20
    },
    {
        .roman = "X",
        .v = 10
    },
    {
        .roman = "IX",
        .v = 9
    },
    {
        .roman = "VIII",
        .v = 8
    },
    {
        .roman = "VII",
        .v = 7
    },
    {
        .roman = "VI",
        .v = 6
    },
    {
        .roman = "V",
        .v = 5
    },
    {
        .roman = "IV",
        .v = 4
    },
    {
        .roman = "III",
        .v = 3
    },
    {
        .roman = "II",
        .v = 2
    },
    {
        .roman = "I",
        .v = 1
    }
};


int romanToInt(char* s) {
    int s_total_len = strlen(s); 
    int si = 0;

    int mi = 0;
    int m_total_len = sizeof(romanMap)/sizeof(romanType);
    
    int ret = 0;
    while (si < s_total_len) {
        int slen = s_total_len-si;
        while(1) {
            if(mi >= m_total_len) {
                printf("impossible here.\n");
                return -1;
            }
            int rlen = strlen(romanMap[mi].roman);
            if(rlen > slen) {
                mi++;
                continue;
            }
            int cmp = strncmp(&s[si], romanMap[mi].roman, rlen);
            if(!cmp) {
                ret += romanMap[mi].v;
                mi++;
                si += rlen;
                break;
            } else {
                mi++;
            }
        }
    }
    return ret;
}

char *s = "LVIII";
int main()
{
    printf("hello: %d.\n", romanToInt(s));
}