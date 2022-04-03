#include <iostream>
using std::cout;
using std::endl;

#include "BinaryTree.h"

typedef std::string ItemType;
typedef void (*FunctionType)(ItemType& anItem);

void PrintNode(ItemType& i) { cout << i << " "; };

int main(int argc, char** argv)
{
    //Structure trees
    BinaryTree<ItemType, FunctionType> T1("A");
    BinaryTree<ItemType, FunctionType> T2("B");
    BinaryTree<ItemType, FunctionType> T3("C");
    BinaryTree<ItemType, FunctionType> T4("D");
    BinaryTree<ItemType, FunctionType> T5("E");
    BinaryTree<ItemType, FunctionType> T6("F");
    BinaryTree<ItemType, FunctionType> T7("G");

    // Assemble left subtree
    T2.attachLeftSubtree(T4);
    T2.attachRightSubtree(T5);

    // Assemble right subtree
    T3.attachLeftSubtree(T6);
    T3.attachRightSubtree(T7);

    // Assemble main tree with left and right subtrees
    T1.attachLeftSubtree(T2);
    T1.attachRightSubtree(T3);


    // Use print function to print out tree traversals
    cout << "Postorder Traversal should be: D E B F G C A" << endl;
    T1.postorderTraverse(&PrintNode);
    cout << endl;
    cout << "Preorder Traversal should be: A B D E C F G" << endl;
    T1.preorderTraverse(&PrintNode);
    cout << endl;
    cout << "Inorder Traversal should be: D B E A F C G" << endl;
    T1.inorderTraverse(&PrintNode);
    cout << endl;

    // now T1 and T2 are no longer trees, but empty objects

    return 0;
};
