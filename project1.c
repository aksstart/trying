#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 50

struct Stack
{
    int top;
    char Stack[MAX];
} left, right;

int leftisempty()
{

    if (left.top == -1)
        return 1;
    else
        return 0;
}
int rightisempty()
{

    if (right.top == -1)
        return 1;
    else
        return 0;
}

int leftisfull()
{

    if (left.top == MAX)
        return 1;
    else
        return 0;
}

int rightisfull()
{

    if (right.top == MAX)
        return 1;
    else
        return 0;
}

int rightpeek()
{
    return right.Stack[right.top];
}
int leftpeek()
{
    return left.Stack[left.top];
}

void leftpop()
{
    char data;

    if (!leftisempty())
    {
        data = left.Stack[left.top];
        left.top = left.top - 1;
    }
    else
    {
        printf("Could not retrieve data, Left Stack is empty.\n");
    }
}
void rightpop()
{
    char data;

    if (!rightisempty())
    {
        data = right.Stack[right.top];
        right.top = right.top - 1;
    }
    else
    {
        printf("Could not retrieve data, Right Stack is empty.\n");
    }
}

void leftpush(char data)
{

    if (!leftisfull())
    {
        left.top = left.top + 1;
        left.Stack[left.top] = data;
    }
    else
    {
        printf("Could not insert data, Left Stack is full.\n");
    }
}
void rightpush(char data)
{

    if (!rightisfull())
    {
        right.top = right.top + 1;
        right.Stack[right.top] = data;
    }
    else
    {
        printf("Could not insert data, Right Stack is full.\n");
    }
}

int rightsize()
{
    return right.top + 1;
}

int leftsize()
{
    return left.top + 1;
}

/**************STACK BASIC FUNCTIONS***************/

void ExamineTop()
{
    if (leftisempty() == 1)
        printf("Left Stack: empty.");
    else
        printf("Left Stack: %c , %d\t\t\t\t", leftpeek(), leftsize());

    if (rightisempty() == 1)
        printf("Right Stack: empty.");
    else
        printf("Right Stack: %c , %d", rightpeek(), rightsize());
}

void insertCharacter(char character)
{
    leftpush(character);
}

void insertWord(char word[])
{
    int i = 0;
    while (word[i] != '\0')
    {
        insertCharacter(word[i]);
        i++;
    }
}

void moveLeft(int position)
{
    int leftSize;
    leftSize = leftsize();
    while (position != leftSize)
    {
        rightpush(left.Stack[left.top]);
        leftpop();
        leftSize = leftsize();
    }
}

void moveRight(int count)
{
    int rightSize, i = 1;
    rightSize = rightsize();
    if (count > rightSize)
        printf(" Cannot move the cursor , right , to the specified position ");
    else
    {
        while (i <= count)
        {
            leftpush(right.Stack[right.top]);
            rightpop();
            i++;
        }
    }
}

void moveCursor(int position)
{
    int leftSize, rightSize, count;
    leftSize = leftsize();
    rightSize = rightsize();
    if (position < leftSize)
        moveLeft(position);
    else
    {
        count = position - leftSize;
        moveRight(count);
    }
}

int deleteCharacter()
{
    if (rightisempty() == 1)
        return 0;
    else
        rightpop();
    return 1;
}

int backSpaceCharacter()
{
    if (leftisempty() == 1)
        return 0;
    else
        leftpop();
    return 1;
}

void findAndReplaceChar(char findWhat, char replaceWith)
{
    int count = 1, originalCursorPoistion = leftsize();
    moveCursor(0); // Move characters from left stack to right stack
                   // Move characters from right stack to left stack and examine
    while (!rightisempty())
    {
        if (right.Stack[right.top] == findWhat)
        {
            deleteCharacter();
            insertCharacter(replaceWith);
        }
        else
            moveCursor(count);
        count++;
    } // End of while
    moveCursor(originalCursorPoistion);
}

/*************MAIN FUNCTIONS**************/

void main()
{
    int choice = 0;
    left.top = -1;
    right.top = -1;
    int i = 0;
    char word[20];
    int position;
    char character;
    while (1)
    { // printing choices for the user
        printf("\n\nEnter 1 to insert word. ");
        printf("\nEnter 2 to insert a character. ");
        printf("\nEnter 3 to move Cursor. ");
        printf("\nEnter 4 to backspace char. ");
        printf("\nEnter 5 to delete character. ");
        printf("\nEnter 6 to find and replace. ");
        printf("\nEnter 7 to exit: ");
        printf("\n \nEnter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            // Calling function to Add the records
            printf("Enter the word you want to insert: ");
            scanf("%s", &word);
            insertWord(word);

            ExamineTop();

            break;
        }
        case 2:
        {
            printf("Enter the character you want to insert: ");
            scanf("%c", &character);
            insertCharacter(character);

            ExamineTop();
            break;
        }
        case 3:
        {
            printf("Enter the position you want to move to: ");
            scanf("%d", &position);
            moveCursor(position);

            ExamineTop();
            break;
        }
        case 4:
        {
            // Calling function to Display the records
            backSpaceCharacter();

            ExamineTop();
            break;
        }
        case 5:
        {
            deleteCharacter();

            ExamineTop();
            break;
        }
        case 6:
        {
            char findWhat;
            char replaceWith;

            printf("Enter the character you want to replace : \n");
            findWhat = getch();
            printf("%c", findWhat);

            printf("\nEnter the character you want to replace with: ");

            scanf("%c", &replaceWith);
            replaceWith = getch();
            printf("%c\n", replaceWith);

            findAndReplaceChar(findWhat, replaceWith);

            ExamineTop();
            break;
        }
        case 7:
        {
            exit(0);
        }
        }
    } // end of while loop
} // end of main