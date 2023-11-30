#include <stdio.h>
#include "cs50.h"

int main(void) 
{
    string first = get_string("What's your first name? ");
    string last = get_string("What's your last name? ");
    printf("hello, %s %s! You got 100%% refund\n", first, last);
}