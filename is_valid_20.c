#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define MAX_LEN 10000
#define MIN_LEN 1
#define STACK_LEN MAX_LEN/2

char    g_stack[STACK_LEN+1];
int     g_len = 0;
int     g_top = -1;

bool is_match(char new_c, char in_c)
{
    if (new_c == '}' && in_c == '{' ||
        new_c == ')' && in_c == '(' ||
        new_c == ']' && in_c == '[') {
        return true;
    }
    return false;
}

char pop_stack()
{
    assert(g_len > 0);
    g_len--;
    return g_stack[g_top--];
}

void push_stack(char new_c)
{
    assert(g_len < STACK_LEN);
    g_len++;
    g_stack[++g_top] = new_c;
}
void clear_stack()
{
    g_len = 0;
    g_top = -1;
}

bool isValid(char * s)
{
    clear_stack();
    int len = strlen(s);
    if (len & 0x1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        char new_c = s[i];
        char top_c = g_top >= 0 ? g_stack[g_top]:'x';
        if (is_match(new_c, top_c)) {
            pop_stack();
        } else {
            push_stack(new_c);
        }
    }
    return g_len > 0 ? false : true;
}

char t01[] = "()";
char t02[] = "()[]{}";
char t03[] = "(]";
char t04[] = "{()}";

int main()
{
    assert(isValid(t01) == true);
    assert(isValid(t02) == true);
    assert(isValid(t03) == false);
    assert(isValid(t04) == true);
}