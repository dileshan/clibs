#ifndef BINARY_TREE_H
#define BINARY_TREE_H


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

struct node;

class BinaryTree
{

    public:

        //typedef BasicLinkedList<int> _Base;
        typedef vector<int> IntegerList;

        struct node {
            int data;
            struct node* left;
            struct node* right;
        };

        typedef node TreeNode;

        BinaryTree( )
        {
            root = NULL;
            listIterator = NULL;
        }

        explicit BinaryTree( IntegerList input )
        {
            root = NULL;
            listIterator = NULL;
            add( input );
        }

        virtual ~BinaryTree( )
        {
            removeAllTreeNodes( root );
        }

        int height();

        void preOrderTraversal( void );
        void inOrderTraversal( void );
        void postOrderTraversal( void );

        TreeNode* traverseTree( TreeNode* node, int data );
        TreeNode* findNode( TreeNode* node );
        TreeNode* findNode( int data );

        // Adds based on balanced tree algorithm.
        void add( IntegerList list );

        void removeAllTreeNodes( TreeNode* node );
        void removeNode( TreeNode* node );

    protected:

        TreeNode* add( int data );

        void preOrderTraversal( TreeNode* node );
        void inOrderTraversal( TreeNode* node );
        void postOrderTraversal( TreeNode* node );

        //Prints out the current given node.
        void visit( TreeNode* node ) const;

        int height( TreeNode* node );

        //Structure for a binary tree.

    private:

    TreeNode* root;
    TreeNode* listIterator;
    size_t size;

};// END OF

#endif
