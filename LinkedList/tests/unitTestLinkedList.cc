//
//
// Basic unit testing framework for the linked list library.
// Uses Google test for backend testing of functions.
//

////////////////////////////////////////

#include "gtest/gtest.h"
#include "BasicLinkedList.h"
#include "binary_tree.h"

#include <string>

////////////////////////////////////////

// This test creates an object by value and inserts a couple
// of integers as types and tests the push function.

//Remove this define when you want tests
//that are being ignored to run.
#define TEST_IGNORE

TEST( BinaryTree, BasicSetup )
{
    vector<int> list;
    for( int i = 1; i <= 7; i++ )
        list.push_back( i );

    BinaryTree tree( list );
    tree.preOrderTraversal();
}

#ifndef TEST_IGNORE
TEST( BasicLinkedList, BasicStackWithIntegers )
{
    BasicLinkedList<int> list;

    for( int i = 6; i > 0; i-- )
    {
        list.push( i );
    }

    // This also tests the overloading operator[]
    // for this class.
    EXPECT_EQ( 1, list[0] );
    EXPECT_EQ( 2, list[1] );
    EXPECT_EQ( 3, list[2] );
    EXPECT_EQ( 4, list[3] );
    EXPECT_EQ( 5, list[4] );
    EXPECT_EQ( 6, list[5] );
}
#endif


// This tests the functionlity of the copy constructor
// type is double
TEST( BasicLinkedList, TestCopyConstructor )
{
    BasicLinkedList<double> list;
    list.add( 1 );
    list.add( 2 );
    BasicLinkedList<double> copy = list;
    copy.add( 3 );// Add to make sure that the lists in memory are different.

    EXPECT_EQ( 2, list.size() );
    EXPECT_EQ( 3, copy.size() );
}

//Test the overloading operator= for a proper copy
//Though using strings for a type will not work because
//Allocation is not set up for type classes.
/// @todo (mkd#1#): Needs to add a type allocator for class types.
#ifndef TEST_IGNORE
TEST( BasicLinkedList, TestCopyOperator )
{
    BasicLinkedList<string> list;
    list.add( "First" );
    BasicLinkedList<string> copy;

    EXPECT_EQ( 1, strcmp( copy.getValue( 0 ).c_str(), "First" ) );

    //Make sure the copy worked properly
    //meaning that they don't share the same pointers.
    copy = list;
    copy.add( "Second" );

    EXPECT_EQ( 1, list.size() );
    EXPECT_EQ( 2, copy.size() );
}
#endif

//Test the overloading operator= for a proper copy
TEST( BasicLinkedList, TestCopyOperatorInts )
{
    BasicLinkedList<int> list;
    list.push( 2 );
    list.push( 1 );
    BasicLinkedList<int> copy;
    copy = list;

    EXPECT_EQ( 2, copy.size() );

    copy.add( 3 );
    EXPECT_EQ( 3, copy.size() );
    EXPECT_EQ( 2, list.size() );
}

//Test pointer to class object and copy from that pointer to basic object
TEST( BasicLinkedList, TestCopyClassPointerToObject )
{
    BasicLinkedList<int> *list_ptr = new BasicLinkedList<int>();
    BasicLinkedList<int> copy;

    for( int i = 6; i > 0; i-- )
    {
        list_ptr->push( i );
    }

    copy = *list_ptr;

    EXPECT_EQ( 6, copy.size() );

    //Change one of the this so that we know that
    //the two objects are not pointing to the same
    //reference values.
    list_ptr->push( 34 );
    EXPECT_EQ( 7, list_ptr->size() );
    EXPECT_EQ( 6, copy.size() );
    delete( list_ptr );
}

TEST( BasicLinkedList, TestGetValue )
{
    BasicLinkedList<double> list;
    list.add( 7.3 );
    EXPECT_EQ( 7.3, list.getValue( 0 ) );
}

TEST( BasicLinkedList, TestPopBasic )
{
    BasicLinkedList<int> list;
    list.push( 2 );
    EXPECT_EQ( 1, list.size() );
    int val = list.pop();
    EXPECT_EQ( 0, list.size() );
    EXPECT_EQ( 2, val );
}

