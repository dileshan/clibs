

#include "binary_tree.h"


// Linked list for Binary tree
// 2i+1 for left node
// 2i+2 for right node
// (i-1)/2 to get to the parent node
// 1 2 3 4 5 6 7
//       1
//     /   \
//    2     3
//   / \   / \
//  4   5 6   7

void BinaryTree::add( IntegerList list )
{
    int cur_index = 0;
    int listSize = list.size();

    for ( IntegerList::iterator it = list.begin(); it != list.end(); it++ )
    {
        int data = *it;
        //Before this we need to check for parenting.
        //if this node already has a parent node then
        //we can skip it.
        int parent_index = ( cur_index - 1 ) / 2;
        TreeNode* nodeAlreadyExists = findNode( data );
        if( nodeAlreadyExists != NULL )
        {
            cur_index++;
            continue;
        }

        TreeNode* new_node = add( data );
        int left_child_index = ( 2 * cur_index ) + 1;
        int right_child_index = ( 2 * cur_index ) + 2;

        if ( left_child_index < listSize )
        {
            TreeNode* left_node = add( list[left_child_index] );
            new_node->left = left_node;
        }

        if ( right_child_index < listSize )
        {
            TreeNode* right_node = add( list[right_child_index] );
            new_node->right = right_node;
        }

        cur_index++;
    }
}

BinaryTree::TreeNode* BinaryTree::add( int data )
{
    struct node* new_node = ( struct node* ) malloc( sizeof( struct node ) );

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    if ( root == NULL && listIterator == NULL )
    {
        root = new_node;
        listIterator = root;
    }

    return new_node;
}

/**
* Traverse the tree to find the maximum height of the tree
*/

int BinaryTree::height ( )
{
    return height( root );
}

int BinaryTree::height ( TreeNode* node )
{
    if( node == NULL ){
        return 0;
    }
    else {

        int lheight = height( node->left );
        int rheight = height( node->right );

        if( lheight > rheight )
            return ( lheight+1 );
        else
            return ( rheight+1 );
    }
}

TreeNode* BinaryTree::findNode( int data )
{
    return traverseTree( root, data );
}

TreeNode* BinaryTree::traverseTree( TreeNode* node, int data )
{
    static bool found = false;

    if ( node == NULL )
        return NULL;

    if( found )
    {
        return node;
    }

    if ( node->data == data )
    {
        found = true;
        return node;
    } else {
        found = false;
    }

    traverseTree( node->left, data );
    traverseTree( node->right, data );
}

void BinaryTree::preOrderTraversal( )
{
    preOrderTraversal( root );
}

void BinaryTree::preOrderTraversal( struct node* node )
{
    if( node == NULL )
        return;

    visit ( node );
    preOrderTraversal ( node->left );
    preOrderTraversal ( node->right );
}

void BinaryTree::visit( struct node* node ) const
{
    if ( node == NULL )
        return;

    //Class uses integers for node data.
    printf( "%d, ", node->data );
    printf( "\tleft-> %d", ( node->left != NULL ) ? node->left->data : -1 );
    printf( "\tright-> %d", ( node->right != NULL ) ? node->right->data : -1 ) ;
    printf( "\n" );
}

void BinaryTree::removeAllTreeNodes( TreeNode* node )
{
    if( node == NULL )
        return;

    removeAllTreeNodes( node->left );
    removeAllTreeNodes( node->right );
    removeNode( node );
}

void BinaryTree::removeNode( TreeNode* node )
{
    printf ( "Trying to free node: %d\n", node->data );
    if( node->left == NULL && node->right == NULL )
        free( node );
    else
        printf( "Unable to free node, had one or two child nodes attached.\n" );
}

