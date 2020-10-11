#include <iostream>
#include <vector>

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

    bool search(int &value)
    {
        node *curr = root;

        while (curr != nullptr)
        {
            if (curr->value == value)
                return true;

            if (curr->value > value)
                curr = curr->left;
            else
                curr = curr->right;
        }

        return false;
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

    vector<bool> results;
    cin >> num;

    while (num != -1)
    {
        results.push_back(myTree->search(num));
        cin >> num;
    }

    for (bool val : results)

        if (val)
            cout << "true" << endl;
        else
            cout << "false" << endl;

    return 0;
}