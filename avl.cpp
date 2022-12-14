#include <iostream>
using namespace std;

class Tree
{
    public:
        int data;
        Tree *left;
        Tree *right;
        int height;
        Tree(int key)
        {
            data = key;
            left = NULL;
            right = NULL;
            height = 1;
        }
};

void ptr()
{
    for(int i =0; i<25; i++)
    {
        cout << "-";
    }
    cout << endl;
}

Tree *node(int data)
{
    Tree *tem = new Tree(data);
    return tem;
}

int height(Tree *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    return tree->height;
}

int BF(Tree *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    return (height(tree->left) - height(tree->right));
}

int max(int a, int b)
{
    if(a >= b)
    {
        return a;
    }
    return b;
}

Tree *RotateLeft(Tree *tree)
{
    Tree *t = tree->right->left;
    tree->right->left = tree;
    tree = tree->right;
    tree->left->right = t;

    tree->left->height = 1 + max(height(tree->left->left),  height(tree->left->right));
    tree->right->height = 1 + max(height(tree->right->left), height(tree->right->right));
    tree->height = 1 + max(height(tree->left), height(tree->right));

    return tree;
}

Tree *RotateRight(Tree *tree)
{
    Tree *t = tree->left->right;
    tree->left->right = tree;
    tree = tree->left;
    tree->right->left = t;

    tree->left->height = 1 + max(height(tree->left->left),  height(tree->left->right));
    tree->right->height = 1 + max(height(tree->right->left), height(tree->right->right));
    tree->height = 1 + max(height(tree->left), height(tree->right));

    return tree;
}

Tree *insert(Tree *tree, int data)
{
    if(tree == NULL)
    {
        return node(data);
    }
    else if(data < tree->data)
    {
        tree->left = insert(tree->left, data);
    }
    else if (data > tree->data)
    {
        tree->right  = insert(tree->right, data);
    }
    else
    {
        return tree;
    }

    tree->height = 1 + max(height(tree->left), height(tree->right));

    int b = BF(tree);

    if(b < -1 && BF(tree->right) <= 0)
    {
        tree = RotateLeft(tree);
    }
    else if(b > 1 && BF(tree->left) >= 0)
    {
        tree = RotateRight(tree);
    }
    else if(b > 1 && BF(tree->left) < 0)
    {
        tree->left = RotateLeft(tree->left);
        tree = RotateRight(tree);
    }
    else if(b < -1 && BF(tree->right) > 0)
    {
        tree->right = RotateRight(tree->right);
        tree = RotateLeft(tree);
    }

    return tree;
}

Tree *LeastValue(Tree *tree)
{
    Tree *tem = tree;
    while(tem->left != NULL)
    {
        tem = tem->left;
    }
    return tem;
}

Tree *pop(Tree *tree, int key)
{
    if(tree == NULL)
    {
        return tree;
    }
    else if(key < tree->data)
    {
        tree->left = pop(tree->left, key);
        tree->height = 1 + max(height(tree->left), height(tree->right));
    }
    else if(key > tree->data)
    {
        tree->right = pop(tree->right, key);
        tree->height = 1 + max(height(tree->left), height(tree->right));
    }
    else
    {
        if(tree->left == NULL || tree->right == NULL)
        {
            Tree *tem = (tree->left == NULL) ? tree->right : tree->left;
            if(tem == NULL)
            {
                tree = NULL;
            }
            else
            {
                tree = tem;
                tree->height = 1 + max(height(tree->left), height(tree->right));
            }
        }
        else
        {
            Tree *tem = LeastValue(tree->right);
            tree->data = tem->data;
            tree->right = pop(tree->right, tem->data);

            tree->height = 1 + max(height(tree->left), height(tree->right));
        }
    }

    int b = BF(tree);

    if(b < -1 && BF(tree->right) <= 0)
    {
        tree = RotateLeft(tree);
    }
    else if(b > 1 && BF(tree->left) >= 0)
    {
        tree = RotateRight(tree);
    }
    else if(b > 1 && BF(tree->left) < 0)
    {
        tree->left = RotateLeft(tree->left);
        tree = RotateRight(tree);
    }
    else if(b < -1 && BF(tree->right) > 0)
    {
        tree->right = RotateRight(tree->right);
        tree = RotateLeft(tree);
    }

    return tree;
}

void InTraversal(Tree *t)
{
    if(t != NULL)
    {
        InTraversal(t->left);
        cout << t->data << " ";
        InTraversal(t->right);
    }
}

void PreTraversal(Tree *t)
{
    if(t != NULL)
    {
        cout << t->data << " ";
        PreTraversal(t->left);
        PreTraversal(t->right);
    }
}

void PostTraversal(Tree *t)
{
    if(t != NULL)
    {
        PostTraversal(t->left);
        PostTraversal(t->right);
        cout << t->data << " ";
    }
}

void Converse_PreTraversal(Tree *tree)
{
    if(tree != NULL)
    {
        cout << tree->data << " ";
        Converse_PreTraversal(tree->right);
        Converse_PreTraversal(tree->left);
    }
}

void Converse_InTraversal(Tree *tree)
{
    if(tree != NULL)
    {
        Converse_InTraversal(tree->right);
        cout << tree->data << " ";
        Converse_InTraversal(tree->left);
    }
}

void Converse_PostTraversal(Tree *tree)
{
    if(tree != NULL)
    {
        Converse_PostTraversal(tree->right);
        Converse_PostTraversal(tree->left);
        cout << tree->data << " ";
    }
}

Tree *search(Tree *tree, int data)
{
    if(tree != NULL)
    {
        if(tree->data > data)
        {
            return search(tree->left, data);
        }
        else if(tree->data < data)
        {
            return search(tree->right, data);
        }
        else
        {
            return tree;
        }
    }
    cout << "The data '" << data << "' is not present in the tree" << endl;
    return NULL;
}

int main()
{
    Tree *tree = NULL; int i=-1;
    tree = insert(tree, 1);
    tree = insert(tree, 2);
    tree = insert(tree, 3);
    tree = insert(tree, 4);
    tree = insert(tree, 5);
    tree = insert(tree, 6);
    tree = insert(tree, 7);
    tree = insert(tree, 8);
    tree = insert(tree, 9);
    tree = insert(tree, 10);

    ptr();
    cout << "          MENU\n";
    ptr();
    cout << "    1 --> insert\n    2 --> delete\n    3 --> search\n    4 --> InTraversal\n    5 --> PreTraversal\n    6 --> PostTraversal\n    7 --> Converse InTraversal\n    8 --> Converse PreTraversal\n    9 --> Converse PostTraversal\n    10 --> BF of node\n    0 --> exit\n";
    ptr();

    while(i != 0)
    {
        int a; Tree *tem = NULL;
        cout << endl << "choose option from menu : ";
        cin >> i;
        switch(i)
        {
            case 1:
                cout << "Enter data to be inserted : ";
                cin >> a;
                tree = insert(tree, a);
                cout << "Successfully inserted " << a << endl;
                break;
            case 2:
                cout << "Enter data to be deleted : ";
                cin >> a;
                tem = pop(tree, a);
                cout << "Successfully deleted " << a << endl;
                break;
            case 3:
                cout << "Enter key to be searched : ";
                cin >> a;
                tem = search(tree, a);
                if(tem != NULL)
                {
                    cout << "The data '" << tem->data << "' is present in the tree" << endl;
                }
                break;
            case 4:
                cout << "The InTraversal is :" << endl;
                InTraversal(tree);
                cout << endl;
                break;
            case 5:
                cout << "The PreTraversal is :" << endl;
                PreTraversal(tree);
                cout << endl;
                break;
            case 6:
                cout << "The PostTraversal is :" << endl;
                PostTraversal(tree);
                cout << endl;
                break;
            case 7:
                cout << "The Converse InTraversal is :" << endl;
                Converse_InTraversal(tree);
                cout << endl;
                break;
            case 8:
                cout << "The Converse PreTraversal is :" << endl;
                Converse_PreTraversal(tree);
                cout << endl;
                break;
            case 9:
                cout << "The Converse PostTraversal is :" << endl;
                Converse_PostTraversal(tree);
                cout << endl;
                break;
            case 10:
                cout << "Enter data of node whose BF is required : ";
                cin >> a;
                tem = search(tree, a);
                a = BF(tem);
                cout << "The Balance factor is : " << a << endl;
                break;
            case 0:
                cout << "Successfully exited" << endl;
                break;
        }
    }
    return 0;
}