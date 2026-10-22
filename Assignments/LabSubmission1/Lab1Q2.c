#include <stdio.h>

void display_key(int stack[], int top, int key)
{
    int i;

    for (i = top; i >= 0; i--)
    {
        if (stack[i] == key)
        {
            printf("Key found: %d\n", stack[i]);
            return;
        }
    }

    printf("Key not found\n");
}

int main(void)
{
    int stack[] = {20, 45, 65, 75, 33, 50};
    int top = 5;

    display_key(stack, top, 65);

    return 0;
}