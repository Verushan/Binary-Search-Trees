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

    int getMin(node *rootNode)
    {
        if (rootNode == nullptr)
            return 0;

        node *curr = rootNode;

        while (curr->left != nullptr)
            curr = curr->left;

        return curr->value;
    }

    node *search(node *rootNode, int &value)
    {
        node *curr = rootNode;

        while (curr != nullptr)
        {
            if (curr->value == value)
                return curr;

            if (curr->value > value)
                curr = curr->left;
            else
                curr = curr->right;
        }

        return curr;
    }

    void deleteVal(node *rootNode, int value)
    {
        node *curr = rootNode, *parent = curr;
        bool found = false;

        while (curr != nullptr) // Traversing to parent
        {
            if (curr->value == value)
            {
                found = true;
                break;
            }

            parent = curr;

            if (value < curr->value)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (!found)
            return;

        if (curr->left == nullptr && curr->right == nullptr) // No children
        {
            if (parent->right == curr)
                parent->right = nullptr;
            else
                parent->left = nullptr;

            delete curr;
            curr = nullptr;
            return;
        }

        if (curr->left == nullptr ^ curr->right == nullptr) // 1 child
        {
            if (curr->right == nullptr)
            {
                if (parent->right == curr)
                    parent->right = curr->left;
                else
                    parent->left = curr->left;
            }
            else
            {
                if (parent->right == curr)
                    parent->right = curr->right;
                else
                    parent->left = curr->right;
            }

            delete curr;
            curr = nullptr;
            return;
        }

        curr->value = getMin(curr->right); // 2 Children
        deleteVal(curr->right, curr->value);
    }

    void deleteAllBelow(node *rootNode)
    {
        if (rootNode == nullptr)
            return;

        if (rootNode->right == nullptr && rootNode->left == nullptr)
        {
            delete rootNode;
            return;
        }

        //Delete children first
        deleteAllBelow(rootNode->right);
        deleteAllBelow(rootNode->left);

        delete rootNode;
    }

    ~tree()
    {
        deleteAllBelow(root);
    }
};

void printTraversal(tree *myTree)
{
    modes curr = preOrder;
    myTree->Display(myTree->root, curr);
    cout << endl;

    curr = inOrder;
    myTree->Display(myTree->root, curr);
    cout << endl;

    curr = postOrder;
    myTree->Display(myTree->root, curr);
    cout << endl;
}

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

    cin >> num;

    while (num != -1)
    {
        myTree->deleteVal(myTree->root, num);
        printTraversal(myTree);
        cout << endl;
        cin >> num;
    }

    return 0;
}