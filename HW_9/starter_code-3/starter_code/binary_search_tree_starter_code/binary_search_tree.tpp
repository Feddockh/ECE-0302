#include "binary_search_tree.h"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementation using a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    // TODO 
    if (isEmpty()) {
        root = new Node<KeyType, ItemType>; // Allocate space for the root node
        root->key = key;
        root->data = item;
        return true;
    }

    Node<KeyType, ItemType>* curr;          // Create a pointer to the current node
    Node<KeyType, ItemType>* curr_parent;   // Create a pointer to the parent of the current node
    search(key, curr, curr_parent);         // Use the search function to get to the insertion position

    if (curr->key == key) {                 // If the current node's key is equal to our key
        return false;                       // Return false because we cannot duplicate nodes

    } else {                                // The current node's key is not equal to our key
        Node<KeyType, ItemType>* newNode = new Node<KeyType, ItemType>;
        newNode->key = key;                 // Set the key of the new node
        newNode->data = item;               // Set the data of the new node

        if (key < curr->key) {              // If new node key < current node key
            curr->left = newNode;           // Insert new node at left subtree
        } else {                            // If new node key > current node key
            curr->right = newNode;          // Insert new node at right subtree
        }
    }

    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree


    // TODO
    Node<KeyType, ItemType>* curr;              // Create a pointer to the current node
    Node<KeyType, ItemType>* curr_parent;       // Create a pointer to the parent of the current node
    search(key, curr, curr_parent);             // Use the search function to get to the insertion position

    // case one thing in the tree
    if (root->left == 0 && root->right == 0) {
        delete root;
        root = 0;
        return true;
    }

    // case, found deleted item at leaf
    if (curr->left == 0 && curr->right == 0) {
        
        if (curr_parent->right == curr) {       // If the current node is to the right of the parent
            curr_parent->right = 0;             // Set the right parent pointer to 0
        } else {                                // If the current node is to the left of the parent
            curr_parent->left = 0;              // Set the left parent pointer to 0
        }
        delete curr;                            // Delete the current node
        return true;
    }

    // case, item to delete has only a right child
    if (curr->left == 0 && curr->right != 0) {
        
        if (curr_parent == 0) {                // If there is no parent, assign the right child directly to root
            root = curr->right;
            delete curr;
            return true;
        }
        
        if (curr_parent->left == curr) {       // If the current node is to the left of the parent node
            curr_parent->left = curr->right;   // Set the parent node left pointer to the right child
        } else {                               // If the current node is to the right of the parent node
            curr_parent->right = curr->right;  // Set the parent node right pointer to the right child
        }

        delete curr;                           // Delete the current node
        return true;
    }

    // case, item to delete has only a left child
    if (curr->left != 0 && curr->right == 0) {

        if (curr_parent == 0) {                // If there is no parent, assign the left child directly to root
            root = curr->left;
            delete curr;
            return true;
        }

        if (curr_parent->left == curr) {       // If the current node is to the left of the parent node
            curr_parent->left = curr->left;    // Set the parent node left pointer to the left child
        } else {                               // If the current node is to the right of the parent node
            curr_parent->right = curr->left;   // Set the parent node right pointer to the left child
        }

        delete curr;                           // Delete the current node
        return true;
    }

    // case, item to delete has two children
    // Remember that the left child is greater than the right child in BST
    // TODO: deal with child swapping to preserve order?
    if (curr->left != 0 && curr->right != 0) {

        if (curr_parent == 0) {                // If there is no parent, assign the left child directly to root
            root = curr->left;
            curr_parent = root;
        } else if (curr_parent->left == curr) {// If the current node is to the left of the parent node
            curr_parent->left = curr->left;    // Set the parent node left pointer to the left child
        } else {                               // If the current node is to the right of the parent node
            curr_parent->right = curr->left;   // Set the parent node right pointer to the left child
        }

        // Insert the right subtree into the left subtree
        Node<KeyType, ItemType>* leftSubtree = curr->left;        // Create a pointer to the left subtree
        Node<KeyType, ItemType>* rightSubtree = curr->right;      // Create a pointer to the right subtree
        Node<KeyType, ItemType>* leftSubtreeParent = curr_parent; // Create a pointer to the parent of the left subtree
        
        // Use the search function to get to the insertion position of the right child key within the left child subtree
        search(rightSubtree->key, leftSubtree, leftSubtreeParent); 

        if (rightSubtree->key < leftSubtree->key) {               // If new node key < current node key
            leftSubtree->left = rightSubtree;                     // Insert new node at left subtree
        } else {                                                  // If new node key > current node key
            leftSubtree->right = rightSubtree;                    // Insert new node at right subtree
        }

        delete curr;                           // Delete the current node
        return true;
    }

    return false;                              // default should never get here
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    ItemType *arr, int &i)
{
    // TODO
    // The TODO was incredibly unclear and the prototype also didn't make sense,
    // since it was a private function, I changed it so that I could use the function
    // as an in order traversal method that used recursion to return the nodes in order
    // and refill the array

    if (curr != 0) {
        inorder(curr->left, arr, i);
        arr[i++] = curr->data;
        inorder(curr->right, arr, i);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) {

    destroy(); // Get rid of any previous data in the tree

    for (int i=0;i<size;i++) {
        insert(arr[i], arr[i]); // Insert array items into a tree, duplicated items will be skipped by the function
    }

    // TODO: overwrite input array values with sorted values
    // Recursive inorder function traverses the binary tree in order
    int index = 0;
    inorder(root, arr, index);

}
