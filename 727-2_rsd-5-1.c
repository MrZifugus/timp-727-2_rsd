#include <stdio.h>
#include <stdlib.h>

struct node //ok
{
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct nodelist //ok
{
    struct node* adress;
    struct nodelist *next;
};

struct list //ok
{
    struct nodelist *head;
    struct nodelist *tail;
};

void initlist(struct list* l) //ok
{
    l->head=NULL;
    l->tail=NULL;
}

void clearlist(struct list* l) //ok
{
    struct nodelist* tmp_1;
    struct nodelist* tmp_2;
    tmp_1=l->head;
    while (tmp_1->next!=NULL)
    {
        tmp_2=tmp_1;
        tmp_1=tmp_1->next;
        free(tmp_2);
    }
    free(tmp_1);
    initlist(l);
}
int isEmpty(struct list* l) //ok
{
    if (l->head==NULL) return 0;
    else return 1;
}

int push_back(struct list* l, struct node* val) //ok
{
    struct nodelist* new_node;
    new_node=(struct nodelist*)malloc(sizeof(struct nodelist));
    new_node->adress = val;
    new_node->next = NULL;
    if (l->head==NULL) l->head=new_node;
    else if (l->head->next==NULL) l->head->next = new_node;
    else l->tail->next = new_node;
    l->tail=new_node;
    return 0;
}
int Spase=0;
void printlist(struct list* l) //ok
{

  if (isEmpty(l)==1)
  {
    struct nodelist* tmp;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        printf(" %d", tmp->adress->value);
        tmp = tmp->next;

    }
    if (Spase==1) printf(" ");
    printf("%d", l->tail->adress->value);
    Spase=1;
  }
}

int noempty(struct list* l) //?ok
{
    int tmp=0;
    if (isEmpty(l)==0) return 0;
    struct nodelist* n;
    n=l->head;
    while (n!=NULL)
    {
        if (n->adress!=NULL) tmp=1;
        n=n->next;
    }
    return tmp;
}
//start treeeeeeeeee

struct tree
{
    struct node *root;
    int number;
};

void init(struct tree* t)
{
    t->number=0;
    t->root=NULL;
}
void clear(struct tree *t) //ok?or?not
{
    struct list tmp1, tmp2;
    struct nodelist *node_tmp;
    initlist(&tmp1);
    initlist(&tmp2);
    push_back(&tmp1, t->root);
    while(noempty(&tmp1)|| noempty(&tmp2))
    {
        if (isEmpty(&tmp2)==0)
        {
            node_tmp=tmp1.head;
            while(node_tmp!=NULL)
            {
                if (node_tmp->adress==NULL)
                {
                    push_back(&tmp2, NULL);
                    push_back(&tmp2, NULL);
                }
                else
                {
                    push_back(&tmp2, node_tmp->adress->left);
                    push_back(&tmp2, node_tmp->adress->right);
                }
                free(node_tmp->adress);
                node_tmp=node_tmp->next;
            }
            clearlist(&tmp1);
        }
        else
        {
            node_tmp=tmp2.head;
            while(node_tmp!=NULL)
            {
                if (node_tmp->adress==NULL)
                {
                    push_back(&tmp1, NULL);
                    push_back(&tmp1, NULL);
                }
                else
                {
                push_back(&tmp1, node_tmp->adress->left);
                push_back(&tmp1, node_tmp->adress->right);
                }
                free(node_tmp->adress);
                node_tmp=node_tmp->next;
            }
            clearlist(&tmp2);
        }
    }
    init(t);
}

int find(struct tree* t, int val, struct node** n) //ok
{
    struct node* node_tmp;
    node_tmp=t->root;
    if (node_tmp==NULL) return 1;
    while((node_tmp!=NULL))
    {
        if (node_tmp->value==val)
        {
            (*n)=node_tmp;
            return 0;
        }
        if (node_tmp->value>val)
        {
            if (node_tmp->left==NULL) return 1;
            else node_tmp=node_tmp->left;
        }
        else
        {
            if (node_tmp->right==NULL) return 1;
            else node_tmp=node_tmp->right;
        }
    }
    return 1;
}

int insert(struct tree* t, int val) //ooooook
{
    struct node* new_node;
    if (find(t, val, &new_node)==0) return 1;
    new_node=(struct node*)malloc(sizeof(struct node));
    if (new_node==NULL) return 2;
    t->number++;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->value=val;
    if (NULL==t->root)
    {
        new_node->parent=NULL;
        t->root=new_node;
    }
    else
    {
        struct node* tmp;
        int InsertOK=0;
        tmp=t->root;
        while (0==InsertOK)
        {
            if (val<tmp->value)
            {
                if (tmp->left!=NULL) tmp=tmp->left;
                else
                {
                    new_node->parent=tmp;
                    tmp->left=new_node;
                    InsertOK=1;
                }
            }
            else
            {
                if (tmp->right!=NULL) tmp=tmp->right;
                else
                {
                    new_node->parent=tmp;
                    tmp->right=new_node;
                    InsertOK=1;
                }
            }
        }
    }
    return 0;
}

void print(struct node* n)
{
    if (n==NULL)
    {
        printf("-\n");
        return;
    }
    struct list tmp1, tmp2;
    struct nodelist *node_tmp;
    initlist(&tmp1);
    initlist(&tmp2);
    push_back(&tmp1, n);
    while(noempty(&tmp1)|| noempty(&tmp2))
    {
        if (isEmpty(&tmp2)==0)
        {
            printlist(&tmp1);
            node_tmp=tmp1.head;
            while(node_tmp!=NULL)
            {
            if (node_tmp->adress==NULL)
                {
                    push_back(&tmp2, NULL);
                    push_back(&tmp2, NULL);
                }
                else
                {
                    push_back(&tmp2, node_tmp->adress->left);
                    push_back(&tmp2, node_tmp->adress->right);
                }
                node_tmp=node_tmp->next;
            }
            clearlist(&tmp1);
        }
        else
        {
            printlist(&tmp2);
            node_tmp=tmp2.head;
            while(node_tmp!=NULL)
            {
                if (node_tmp->adress==NULL)
                {
                    push_back(&tmp1, NULL);
                    push_back(&tmp1, NULL);
                }
                else
                {
                push_back(&tmp1, node_tmp->adress->left);
                push_back(&tmp1, node_tmp->adress->right);
                }
                node_tmp=node_tmp->next;
            }
            clearlist(&tmp2);
        }
    }
}

void printTreeS(struct tree *t)
 {
     print(t->root);
 }

 int main()
{
    struct tree ApplesTree;
    struct node* b;
    int a1, a2, a3, a4, a5, a6, a7;
    init(&ApplesTree);
    scanf("%d %d %d %d %d %d %d", &a1, &a2, &a3, &a4, &a5, &a6, &a7);
    insert(&ApplesTree, a1);
    insert(&ApplesTree, a2);
    insert(&ApplesTree, a3);
    insert(&ApplesTree, a4);
    insert(&ApplesTree, a5);
    insert(&ApplesTree, a6);
    insert(&ApplesTree, a7);
    printTreeS(&ApplesTree);
    printf("\n");
    return 0;
}
