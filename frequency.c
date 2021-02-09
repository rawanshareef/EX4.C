#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#define NUM_LETTERS ((int)26)

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;

typedef struct node
{
    char letter;                        //the charthat appears on the node that enters it
    long unsigned int count;            //count the num of word in the node
    struct node *children[NUM_LETTERS]; //array in size 26 pointers
    boolean endWord;
} node;

//creat the head
node *myNode()
{
    node *p = NULL;
    p = (node *)malloc(sizeof(node));
    p->letter = '\0';
    p->endWord = FALSE;
    p->count = 0;

    for (int i = 0; i < NUM_LETTERS; i++)
    {
        p->children[i] = NULL;
    }
    return p;
}
//insert word and add to tree
void insert(node *root, char *data)
{
    node *head = root; //the head of trie
    int lenword = strlen(data);
    int location = 0;
    for (int i = 0; i < lenword; i++)
    {
        location = (int)data[i] - (int)'a';
        if (!(head->children[location]))
        { //if the node(char) not exist in array children->bulid node
            head->children[location] = myNode();
            head->children[location]->letter = data[i];
        }
        head = head->children[location];
    }
    head->count++;
    head->endWord = TRUE;
}

void printTree(node *root, char *str, int location)
{
    if (root == NULL)
    {
        return;
    }
    if (root->endWord)
    {
        str[location] = 0;
        if (str[0] != '\0')
            printf("%s %ld\n", str, root->count);
    }
    int i = 0;
    while (i < NUM_LETTERS)
    {
        if (root->children[i])
        {
            str[location] = root->children[i]->letter;
            printTree(root->children[i], str, location + 1);
        }
        i++;
    }
}

void printRevers(node *root, char *str, int location)
{
    int i = NUM_LETTERS - 1;
    while (i >= 0)
    {
        if (root->children[i])
        {
            str[location] = root->children[i]->letter;
            printRevers(root->children[i], str, location + 1);
        }
        i--;
    }

    if (root->endWord)
    {
        str[location] = 0;
        if (str[0] != '\0')
            printf("%s %ld\n", str, root->count);
    }
}

void freet(node *root)
{
    if (!root)
        return;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (root->children[i] != NULL)
        {
            freet(root->children[i]);
        }
    }

    free(root); //in the end we will realeas the root
}

int main(int argc, const char *argv[])
{
    char *str = (char *)calloc(26, sizeof(char));
    int counter = 0;
    char c = getchar();
    node *root = myNode();
    while (1)
    {
        if (isalpha(c))
        {
            c = tolower(c);
        }

        if ((c == '\n' || c == ' ' || c == '\0' || c == '\t'))
        {

            str[counter] = '\0';
            if (counter > 0)
            {
                insert(root, str);
            }
            counter = 0;
        }

        if (c != '\n' && c != ' ' && c != '\0' && c != EOF && c >= 'a' && c <= 'z')
        {
            str[counter] = c;
            counter = counter + 1;
        }

        c = getchar();
        if (c == EOF)
        {
            break;
        }
    }

    if (argc == 2 && (*argv[1] == 'r'))
    {
        printRevers(root, str, 0);
    }
    else
    {
        printTree(root, str, 0);
    }
    free(str);
    freet(root);
    return 0;
}
