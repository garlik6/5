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

int StrToInt(char *s)
{
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 — отрицательное
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}

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
int delittest(node**root)
{
    int a [14] = {};
}
const char *msgs[] = {"0. Quit","1. Add","2. Find next","3. Delete ","4. Show", "5. Open file" , "6. Find" , "7. Time" , "8. Print tree"};

int insert(node **root, int key, char *info);

node** findTargetNode(node **root, int key, int *pInt);

void newNodeMem(node **pNode, char *info);

int leORri(node **pNode, int key, node *pNode1);

int find(node** pNode);

node* searchPar (node* ptr, int key);

node *min(node *pNode);

int show (node **root);

int erase(node **tr, int num, node* parent, node**root);

int delTree(node **pNode);

int Time();

int checkDel(node** root, long a[]);

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

int show (node **root)
{   node *ptr = min(*root);
    while (ptr != NULL)
    {
        printf("%d %s\n",ptr->key,ptr->info);
        ptr = ptr->Next;
    }
    return 1;
}

int add (node **root)
{   int key, rc;
    char *info;
    printf("Enter key-->");
    getIntSmall(&key,2);
    printf("Enter info-->");
    info = getstring();
    rc = insert(root, key, info);
    if(rc == 0)
        printf("duplicate key");
    return 1;
}

int insert(node ** root, int key, char *info) {
    int target;
    node *newNode = NULL, *ptr = NULL, *prev = NULL, *buf = NULL;
    newNode = (node *) malloc(sizeof(node));
    if ((*root) == NULL){
        newNode->key = key;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->info = info;
        newNode->Next = NULL;
        (*root) = newNode;
        return 1;
    } else{
        node **jog = findTargetNode(root, key, &target);
        if(jog == NULL)
            return 1;
        ptr = min(*root);
        if(leORri(jog, key, newNode) == 1)
            return 0;
        newNode->key = key;
        newNode->info = info;
        newNode->Right = NULL;
        newNode->Left = NULL;
        newNode->Next = NULL;

        prev = ptr;
        int flag = 0;
        while(ptr != NULL && ptr->key <= key){
            prev = ptr;
            ptr = ptr->Next;
            flag++;
        }
        if (flag == 0)
        {
            newNode->Next = ptr;
        } else {
   //         if (prev->Next != NULL)
   //            buf = prev->Next;
            prev->Next = newNode;
            newNode->Next = ptr;
 //           if (ptr!= NULL)
 //               ptr->Next = buf;
            return 1;
        }return 1;
    }
}

int chek(node** root)
{

}

int checkDel(node** root, long a[])
{
    return 1;
}
int insertt(node ** root, int key, char *info) {
    int target;
    node *newNode = NULL, *ptr = NULL, *prev = NULL, *buf = NULL;
    newNode = (node *) malloc(sizeof(node));
    if ((*root) == NULL){
        newNode->key = key;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->info = info;
        newNode->Next = NULL;
        (*root) = newNode;
        return 1;
    } else{
        node **jog = findTargetNode(root, key, &target);
        if(jog == NULL)
            return 1;
        ptr = min(*root);
        if(leORri(jog, key, newNode) == 1)
            return 0;
        newNode->key = key;
        newNode->info = info;
        newNode->Right = NULL;
        newNode->Left = NULL;
        newNode->Next = NULL;
        }return 1;
    }



node** findTargetNode( node **root, int key, int *pInt) {
    node *ptr = *root;
    node *par = NULL;
    while (ptr!=NULL){
        par = ptr;
        if (ptr->key == key)
            return NULL;
        if (key < ptr->key)
            ptr = ptr->Left;
        else
            ptr = ptr->Right;
    }
    node** pPar=&par;
    return pPar;
}


node* search (node* ptr, int key){
    if (ptr == NULL)
        return NULL;
    else
    {
        while (ptr->key != key)

            if (key > ptr->key) {
                ptr = ptr->Right;
                if (ptr == NULL) return ptr;
            }
            else {
                ptr = ptr->Left;
                if (ptr == NULL) return ptr;
            }
    }
 return ptr;
}

int searchKey(node *ptr, int key)
{
  node *Ptr;
    Ptr= search (ptr,key);
    if (Ptr != NULL)
        return 1;
    else
        return 0;
}

node* searchPar (node* ptr, int key){
    node *par = NULL;
    if (ptr == NULL)
        return NULL;
    else
    {
        while (ptr->key != key) {
            par = ptr;
            if (key < ptr->key)
                ptr = ptr->Right;
            else
                ptr = ptr->Left;
        }
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

node *max (node *pNode) {
    node *ptr = pNode;
    if (pNode == NULL)
        return NULL;
    else {
        while (ptr->Right!= NULL)
            ptr = ptr->Right;
        return ptr;
    }
}
int leORri(node **pNode, int key, node *newNode) {
    if ((*pNode)->key==key)
        return 1;
    if(key < (*pNode)->key)
        (*pNode)->Left = newNode;
    else
        (*pNode)->Right = newNode;
    return 0;
}

int find(node** pNode){

      int key;
      node *rc;
        char *info;
        printf("Enter key-->");
        getIntSmall(&key,2);
        rc = search(*pNode,key);
        if(rc == NULL) {
            printf("Not found");
        }else
        {
            printf("%d %s",rc->key,rc->info);
        }


        return 1;

}
int findNext(node** pNode)
{ int key;
    node *rc;
    char *info;
    printf("Enter key-->");
    getIntSmall(&key,2);
    rc = search(*pNode,key);

    if(rc==NULL || rc->Next == NULL) {
        printf("Not found");
    }else
    {
        printf("Next:-->%d %s",rc->Next->key,rc->Next->info);
    }

    return 1;
}

int delete (node** root){
    int key;
    node *rc;
    int flag;
    char *info;
    printf("Enter key-->");
    getIntSmall(&key,2);

    flag = erase(root, key, NULL,root);


    return 1;
}

//int erase(node* dI, node** root)
//{int flag;
//    node *parent = searchPar(*root, dI->key);
//    if (dI->Left && dI->Right) {
//        node *localMax = max(dI->Left);
//        dI->info = localMax->info;
//        erase(localMax, root);
//        return 0;
//    } else if (dI->Left) {
//        if (dI == parent->Left) {
//            parent->Left = dI->Left;
//        } else {
//            parent->Right = dI->Left;
//        }
//    } else if (dI->Right) {
//        if (dI == parent->Right) {
//            parent->Right = dI->Right;
//        } else {
//            parent->Left = dI->Right;
//        }
//    } else {
//        if (dI == parent->Left) {
//            parent->Left = NULL;
//        } else {
//           parent->Right = NULL;
//        }
//    }
//    free(dI);
//}

node * minimum(node *tr)
{
    if (!tr->Left->Left) return tr;
    return minimum(tr->Left);
}
int delTree(node **pNode) {

    return 1;
}
node * findPrev (node** root,node* tr)
{ node * cur = min(*root), *prev;
  //if (!(tr)->Left && !tr->Right)
    //  return NULL;
  if(tr->Next == cur)
      return 0;
    while (cur!=NULL)
    {
        prev = cur;
        cur = cur->Next;
        if (cur == tr)
            return prev;

    }
    return NULL;
}
int erase(node **tr, int num, node* parent, node ** root)
{   node * prev = NULL;
    if (!(*tr)) return 0;

    if (num < (*tr)->key)
        erase(&((*tr)->Left), num, *tr, root);

    else if (num > (*tr)->key)
        erase(&((*tr)->Right), num, *tr, root);
    else {

        if (!(*tr)->Left && !(*tr)->Right) {//Если детей у удаляемого узла нет, то перед нами самый простой случай - листовой узел.

            if (parent) {//Родителю данного узла надо сообщить о том, что потомка у него теперь нет

                if (parent->Left) {

                    if (parent->Left->key == (*tr)->key) { //Если удаляется левый потомок
                        prev = findPrev(root,*tr);
                        if(prev)
                            prev->Next = parent;
                        free((*tr)->info);
                        free(*tr);
                        if(parent)
                            parent->Left = NULL;
                    }
                }  if(parent->Right) {

                    if (*tr!=NULL && parent->Right->key == (*tr)->key) { //Если удаляется правый потомок

                        if(parent)
                            parent->Next = (*tr)->Next;
                        free((*tr)->info);
                        free(*tr);
                        parent->Right = NULL;
                    }
                }
            }

           // Теперь можно освободить память
            *tr = NULL;
        } else if (!(*tr)->Left || !(*tr)->Right) { // Если у удаляемой вершины есть  один потомок

            node* nodeToRemove = NULL;
            if ((*tr)->Left) { //Находим того самого единственного потомка удаляемой вершины

                nodeToRemove = (*tr)->Left;
                if((*tr) != min(*root)) {
                    if(nodeToRemove->Left) {
                        prev = max(nodeToRemove->Left);
                        if(prev)
                            prev->Next = *tr;
                        prev = max((*tr)->Left);
                        if(prev)
                            prev->Next = (*tr)->Next;
                        (*tr)->Next = nodeToRemove->Next;
//                        if (*tr == parent->Right)
//                            parent->Next = min((*tr)->Left);

                    }
                    else if(nodeToRemove->Right) {
                        prev = max(nodeToRemove->Right);
                        if(prev)
                            prev->Next = *tr;
                        prev = max((*tr)->Left);
                        if(prev)
                            prev->Next = (*tr)->Next;
                        (*tr)->Next = nodeToRemove->Next;
                        prev = findPrev(root, min(nodeToRemove));
                        if(prev)
                            prev->Next = *tr;
                    }
                    else if(!nodeToRemove->Right && !nodeToRemove->Left) {
                        prev = findPrev(root, nodeToRemove);
                        if(prev)
                            prev->Next = *tr;
                    }
                }
            } else {
                nodeToRemove = (*tr)->Right;
                if(parent && parent->Right == *tr)parent->Next = (*tr)->Next;
                if((*tr)!=min(*root))
                    prev = findPrev(root,nodeToRemove);
                if(prev)
                    prev->Next = (*tr);
                (*tr)->Next = nodeToRemove->Next;



            }
            //Скопировать все данные из единственного потомка удаляемой вершины
            (*tr)->Left = nodeToRemove->Left;
            (*tr)->Right = nodeToRemove->Right;
            (*tr)->key = nodeToRemove->key;
            free((*tr)->info);
            (*tr)->info = nodeToRemove->info;

           // (*tr)->Next = nodeToRemove->Next;
            //Освободить память, выделенную ранее для данного потомка
            free(nodeToRemove);
        } else { //Если у удаляемой вершины есть оба потомка, то согласно алгоритму необходимо найти наименьший элемент в правом поддереве удаляемого элемента

            if (!(*tr)->Right->Left) { //Если у правого поддерева нет левых потомков, то это означает, что у всех потомков значение ключа больше, а значит надо просто скопировать значения из правого потомка в удаляемый элемент

                (*tr)->key = (*tr)->Right->key;
                free((*tr)->info);
                (*tr)->info = (*tr)->Right->info;// Скопировать значение из правого потомка
                node* rightRIghtChild = (*tr)->Right->Right;
                (*tr)->Next = (*tr)->Right->Next;
                free((*tr)->Right); // Освбодить память, выделенную для правого потомка
                printf("deleted");
                (*tr)->Right = rightRIghtChild;
            } else {

                node* minNodeParent = minimum((*tr)->Right); //Поиск наименьшего элемента в правом поддереве (он обязательно найдётся, случай когда его нет был разобран выше)

                (*tr)->key = minNodeParent->Left->key;//Скопировать значение из наименьшего жлемента в правом поддереве в удаляемый элемент
                free((*tr)->info);
                (*tr)->info = minNodeParent->Left->info;
                (*tr)->Next = minNodeParent;
                free(minNodeParent->Left);
                printf("deleted");
                minNodeParent->Left = NULL;
            }
        }
    }
}

int openFile (node** root){
    FILE *fd;
    int key;
    char * flag = 1;
    fd = fopen("C:\\Users\\Grigory\\CLionProjects\\untitled18\\File","r");
    while (1){
            char *info = (char *) calloc(128,sizeof(char));
            flag = fgets(info,128,fd);
            if(!flag)
                break;
            key = StrToInt(info);
            fgets(info,127,fd);
            insert(root,key,info);

        }
    return 1;
}

int Time()
{
    node **root =(node **) calloc(1,sizeof(node*));
    int n =50, key[100000], k, cnt = 1000000, i, m;
    clock_t first, last;
    srand(time(NULL));
    while (n-- > 0){
        for (i=0; i < 100000; ++i)
            key[i] = rand()*rand();
        for (i = 0;i<cnt;){
            k = rand()*rand();
            if(insertt(root,k,""))
                i++;

        }
        m = 0;
        first = clock();
        for(i = 0; i < 100000; i++)
           if(searchKey(*root, key[i])!=0)
               ++m;
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %d\n", 50-n, (50 - n)*cnt, last - first);
    }
    delTree(*root);
    return 1;

}

void print_Tree(node * p,int level)
{
    if(p)
    {
        print_Tree(p->Right,level + 1);
        for(int i = 0;i< level;i++) printf("   ");
        if(p->Next)
            printf("%d(%d)\n",p->key,p->Next->key);
        else
            printf("%d)\n",p->key);
        print_Tree(p->Left,level + 1);
    }
}
int print(node** root)
{
    print_Tree(*root,0);
    return 1;
}


int main() {
    int (*fptr[])(node **) = {NULL, add, findNext, delete, show, openFile, find, Time, print};// delete openFile

    node **root = calloc(1,sizeof(node*));
    int rc;
    while(rc = dialog())
        if(!fptr[rc](root))
            break;
    //saveFile(&table);
    printf("Thanks");
    delTree(*root);
    return 0;
}
