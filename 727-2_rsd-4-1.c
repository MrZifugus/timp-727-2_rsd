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

void printlist(struct list* l) //ok
{
  if (isEmpty(l)==1)
  {
    struct nodelist* tmp;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        if (tmp->adress == NULL) printf("_ ");
        else printf("%d ", tmp->adress->value);
        tmp = tmp->next;
    }
    if (tmp->adress == NULL) printf("_\n");
    else
    printf("%d\n", l->tail->adress->value);
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

int removeNode(struct tree* t, int val)
{
    struct node* tmp;
    if (find(t, val, &tmp)==1) return 1;
    if ((tmp->left==NULL)&&(tmp->right==NULL))
    {
        if (tmp->parent==NULL)
        {
            clear(t);
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=NULL;
        else tmp->parent->right=NULL;
        free(tmp);
        t->number--;
        return 0;
    }
if ((tmp->left==NULL) && (tmp->right!=NULL))
    {
        if (tmp->parent==NULL)
        {
            t->root=tmp->right;
            t->root->parent=NULL;
            free(tmp);
            t->number--;
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=tmp->right;
        else tmp->parent->right=tmp->right;
        t->number--;
        free(tmp);
        return 0;
    }
    if ((tmp->right==NULL) && (tmp->left!=NULL))
    {
        if (tmp->parent==NULL)
        {
            t->root=tmp->left;
            t->root->parent=NULL;
            t->number--;
            free(tmp);
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=tmp->left;
        else tmp->parent->right=tmp->left;
        t->number--;
        free(tmp);
        return 0;
    }
    if ((tmp->left!=NULL) && (tmp->right!=NULL))
    {
   struct node* min;
        min=tmp->right;
        while(min->left!=NULL)
            min=min->left;
        tmp->value=min->value;

        if (min->right!=NULL)
        {
            if (min->parent->left==min) min->parent->left=min->right;
            else min->parent->right=min->right;
            min->right->parent=min->parent;
        }
        else
        {
            if (min->parent->left==min) min->parent->left=NULL;
            else min->parent->right=NULL;
        }
        t->number--;
        free(min);
        return 0;
    }
}

int removeMin(struct node* n, struct tree* t)
{
    int MinV;
    while (n->left!=NULL)
        n=n->left;
    MinV=n->value;
    n->parent->left=NULL;
    if (n->right!=NULL)
        {
            n->parent->left=n->right;
            n->right->parent=n->parent;
        }
    t->number--;
    free(n);
    return MinV;
}
int rotateRight(struct node *n, struct tree *t)
{
    struct node *tmp;
    if (n->left==NULL) return 1;
    if (n->parent==NULL)
    {
        t->root=n->left;
        n->left->parent=NULL;
    }
    else
    {
        if (n->parent->left==n) n->parent->left=n->left;
        else n->parent->right=n->left;
        n->left->parent=n->parent;
    }
    n->parent=n->left;
    tmp=n->parent->right;
    n->parent->right=n;
    n->left=tmp;
    return 0;
}
int rotateLeft(struct node *n, struct tree *t)
{
    struct node *tmp;
    if (n->right==NULL) return 1;
    if (n->parent==NULL)
    {
        t->root=n->right;
        n->right->parent=NULL;
    }
    else
    {
        if (n->parent->left==n) n->parent->left=n->right;
        else n->parent->right=n->right;
        n->right->parent=n->parent;
    }
    n->parent=n->right;
    tmp=n->parent->left;
    n->parent->left=n;
    n->right=tmp;
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

void printTree(struct tree *t)
 {
     print(t->root);
 }

 int main()
{
    struct tree ApplesTree;
    struct node* b;
    int a1, a2, a3, a4;
    init(&ApplesTree);
    scanf("%d %d %d %d", &a1, &a2, &a3, &a4);
    insert(&ApplesTree, a1);
    insert(&ApplesTree, a2);
    insert(&ApplesTree, a3);
    insert(&ApplesTree, a4);
    printTree(&ApplesTree);
    scanf("%d %d %d", &a1, &a2, &a3);
    insert(&ApplesTree, a1);
    insert(&ApplesTree, a2);
    insert(&ApplesTree, a3);
    printTree(&ApplesTree);
    scanf("%d", &a1);
    a2=find(&ApplesTree, a1, &b);
    if (a2==1) printf("_\n");
    else
    {
        if (b->parent!=NULL) printf("%d ", b->parent->value);
        else printf("_ ");
        if (b->left!=NULL) printf("%d ", b->left->value);
        else printf("_ ");
        if (b->right!=NULL) printf("%d\n", b->right->value);
        else printf("_\n");
    }
    scanf("%d", &a1);
    a2=find(&ApplesTree, a1, &b);
    if (a2==1) printf("-\n");
    else
    {
        if (b->parent!=NULL) printf("%d ", b->parent->value);
        else printf("_ ");
        if (b->left!=NULL) printf("%d ", b->left->value);
        else printf("_ ");
        if (b->right!=NULL) printf("%d\n", b->right->value);
        else printf("_\n");
    }
    scanf("%d", &a1);
    removeNode(&ApplesTree, a1);
    printTree(&ApplesTree);
    while (rotateLeft(ApplesTree.root, &ApplesTree)==0)
        a2=0;
    printTree(&ApplesTree);
    while (rotateRight(ApplesTree.root, &ApplesTree)==0)
        a2=0;
    printTree(&ApplesTree);
    printf("%d\n", ApplesTree.number);
    clear(&ApplesTree);
    printTree(&ApplesTree);
    return 0;
}
