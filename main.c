#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

typedef struct node {  // двоичное дерево поиска с прошивкой левый элемент всегда меньше родителя а правый элемент всегда больше родителя
     int key;
     struct node* Left ;
     struct node* Right ;
     struct node* Next ; // казательна следующий элемент в прямом порядке обхода
     char* info ;
}node;


typedef struct tree {
    node *root;
} tree;

char *getstring() {
    char *ptr = (char *) malloc(1);
    char buf[81];
    unsigned int n, len = 0;
    *ptr = '\0';
    fflush(stdin);
    do {
        n = scanf("%5[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0) scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *) realloc(ptr, len + 1);
            strncat(ptr, buf, len);
        }
    } while (n > 0);
    return ptr;
}

int getIntSmall(int *a,int e) {
    int n;

    if (e == 1) {
        srand(rand()*time(0));
        printf("%s\n", "random");
        *a = rand() % 10000 + 1;
        return 1;
    }

    if (e == 2)
    { do {
            fflush(stdin);
            n = scanf("%i", a);
            printf("%s\n", "manual");
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "Error! Repeat input");
                scanf("%*[^\n]", 0);
            }
        } while (n == 0);
        scanf("%*c");
        return 1;
    }
}

const char *msgs[] = {"0. Quit","1. Add","2. Find next","3. Delete ","4. Show", "5. Open file" , "6. Find"};

int insert(tree *pTree, int key, char *info);

node* findTargetNode(tree *pTree, int key, int *pInt);

void newNodeMem(node **pNode, char *info);

int leORri(node *pNode, int key, node *pNode1);

node* searchPar (node* ptr, int key);

int leORri(node *pNode, int key, node *newNode);

void newNodeMem(node **pNode,char *info);

node *min(node *pNode);

int show (tree * pTree);

const int  N = sizeof(msgs) / sizeof(msgs[0]);

int dialog()
{
    char *errmsg = "";
    int rc;
    int i,n;

    do{
        puts(errmsg);
        errmsg = "You are wrong, repeat please";
        fflush(stdin);
        for(i = 0;i < N;++i)
            puts(msgs[i]);
        puts("Make your choice: -->");

        n = getIntSmall(&rc,2);
        if(n == 0)
            rc = 0;
    }while(rc < 0 || rc >= N);
    return rc;
}

int show (tree *pTree)
{   node *ptr = min(pTree->root);
    while (ptr != 0)
    {
        printf("%d %s\n",ptr->key,ptr->info);
    }
    return 1;
}

int add (tree * pTree)
{   int key;
    char *info;
    printf("Enter key-->");
    getIntSmall(&key,2);
    printf("Enter info-->");
    info = getstring();
    if(insert(pTree, key, info) == 1)
        printf("duplicate key");


    return 1;
}

int insert(tree *pTree, int key, char *info) {
    int target;
    node *newNode = NULL, *ptr, *prev, *buf;
    newNode = (node *) calloc(1,sizeof(node*));
    if (pTree->root == NULL){
        pTree->root = newNode;
        pTree->root->key = key;
        pTree->root->Left = NULL;
        pTree->root->Right = NULL;
        pTree->root->info = info;
        pTree->root->Next = NULL;
        return 0;
    } else{
        if(leORri(findTargetNode(pTree, key, &target), key, newNode) == 1)
            return 1;
        newNode->key = key;
        newNode->info = info;
        newNode->Right = NULL;
        newNode->Left = NULL;
        ptr = min(pTree->root);
        if (key < ptr->key)
            newNode->Next = ptr;
        prev = pTree->root;
        while(ptr->key > key){
            prev = ptr;
            ptr = ptr->Next;
        }
        if(prev->Next != NULL)
            buf = prev->Next;
        prev->Next = ptr;
        if(prev->Next != NULL)
            ptr->Next = buf;
        return 0;
    }
}



node* findTargetNode(tree *pTree, int key, int *pInt) {
    node *ptr = pTree->root;
    node *par = NULL;
    while (ptr!=NULL){
        par = ptr;
        if (key < ptr->key)
            ptr = ptr->Left;
        else
            ptr = ptr->Right;
    }
    return par;
}

int leORri(node *pNode, int key, node *newNode) {
    if (pNode->key==key)
        return 1;
    if(key < pNode->key)
        pNode->Left = newNode;
    else
        pNode->Right = newNode;
}


node *searchNext(node* x, node *par, node* root){
    node * left, *right, *ptr;
    ptr = x;
    if (ptr->Right != NULL) {
        ptr = min(ptr);
        return ptr;
    } else
        ptr = par;
    while (ptr != NULL && ptr->Right == x)
    {
        x = ptr;
        ptr = searchPar(root, x->key);
    }
    return ptr;
}

node* search (node* ptr, int key){
    if (ptr == NULL)
        return NULL;
    else
    {
        while (ptr->key != key)

            if (key< ptr->key)
                ptr = ptr->Right;
            else
                ptr = ptr->Left;
        return ptr;
    }

}

node* searchPar (node* ptr, int key){
    node *par = NULL;
    if (ptr == NULL)
        return NULL;
    else
    {
        while (ptr->key != key)
            par = ptr;
            if (key< ptr->key)
                ptr = ptr->Right;
            else
                ptr = ptr->Left;
        return par;
    }

}
node *min(node *pNode) {
    node *ptr = pNode;
    if (pNode == NULL)
        return NULL;
    else {
        while (ptr->Left != NULL)
            ptr = ptr->Left;
        return ptr;
    }
}

int main() {
    int (*fptr[])(tree *) = {NULL, add, show};//, //findNext, delete ,show, openFile, find}; //,find,delete,show
    tree *pTree = (tree *)calloc(1,sizeof(tree*));
    //pTree->root = (node *)calloc(1,sizeof(node*));
    int rc;
    while(rc = dialog())
        if(!fptr[rc](pTree))
            break;
    //saveFile(&table);
    printf("Thanks");
//    delTable(&table);
    return 0;
}
