#include <iostream>

using namespace std;

enum modes
{
    preOrder,
    inOrder,
    postOrder
};

struct node
{
public:
    node *left, *right;
    int value;

    node(int value, node *left = nullptr, node *right = nullptr)
    {
        this->left = left;
        this->right = right;
        this->value = value;
    }
};

class tree
{
public:
    node *root;

    void insert(int value)
    {
        if (root == nullptr)
        {
            root = new node(value);
            return;
        }

        node *curr = root, *temp;

        while (curr != nullptr)
        {
            temp = curr;

            if (value < curr->value)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (value < temp->value)
            temp->left = new node(value);
        else
            temp->right = new node(value);
    }

    void Display(node *curr, modes &mode)
    {
        if (curr == nullptr)
            return;

        if (mode == preOrder)
        {
            cout << curr->value << " ";
            Display(curr->left, mode);
            Display(curr->right, mode);
            return;
        }

        if (mode == inOrder)
        {
            Display(curr->left, mode);
            cout << curr->value << " ";
            Display(curr->right, mode);
            return;
        }

        if (mode == postOrder)
        {
            Display(curr->left, mode);
            Display(curr->right, mode);
            cout << curr->value << " ";
        }
    }

    void deleteNode(node *rootNode)
    {
        if (rootNode == nullptr)
            return;

        if (rootNode->right == nullptr && rootNode->left == nullptr)
        {
            delete rootNode;
            return;
        }

        //Delete children first
        deleteNode(rootNode->right);
        deleteNode(rootNode->left);

        delete rootNode;
    }

    ~tree()
    {
        deleteNode(root);
    }
};

int main()
{
    tree *myTree = new tree;

    int num;
    cin >> num;

    while (num != -1)
    {
        myTree->insert(num);
        cin >> num;
    }

    modes curr = preOrder;
    myTree->Display(myTree->root, curr);
    cout << endl;

    curr = inOrder;
    myTree->Display(myTree->root, curr);
    cout << endl;

    curr = postOrder;
    myTree->Display(myTree->root, curr);

    cout << endl;
    return 0;
}