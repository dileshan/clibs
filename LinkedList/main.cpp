#include <vector>
#include <string>

#include "BasicLinkedList.h"
#include "signal_handler.h"
#include "node.h"

//extern template class BasicLinkedList<int>;
//template <class Type> extern BasicLinkedList<Type>;

extern bool sigint_was_hit;
extern bool sigabrt_was_hit;

extern "C"
{
    void signal_handler ( int handle )
    {
        sigint_was_hit = true;
        cout << "Ctrl-C was hit" << endl;
    }
}

extern "C"
{
    void signal_handler_abrt ( int handle )
    {
        sigabrt_was_hit = true;
        cout << "Abort signal was hit" << endl;
    }
}

/**
* Basic Testing framework for all functions
* that are used in the LinkedList container.
*/

int main()
{
    //Set up signals
    Signal_init sh_int( SIGINT, signal_handler );
    Signal_init sh_abrt( SIGABRT, signal_handler_abrt );

    BasicLinkedList<int>    integerList;
    BasicLinkedList<int>    copyIntegerList;

    printf( "-----------------------------------\n" );
    printf( "Testing basic object copy:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        //IntegerListPtr->push( i );
        integerList.push(i);
    }

    copyIntegerList = integerList;

    copyIntegerList.add( 10 );

    printf( "Copied list: \n" );
    copyIntegerList.print();

    printf( "Original list\n" );
    integerList.print();

    assert( copyIntegerList[ copyIntegerList.size()-1 ] == 10 );

    int size1 = copyIntegerList.size();
    int size2 = integerList.size();
    assert( size1 != size2 );


    //Testing creating object on the heap and changing from pointer to object on heap
    //To normal object.
    BasicLinkedList<int> *linkedListPtr = new BasicLinkedList<int>();
    BasicLinkedList<int>  linkedList;

    printf( "\n-----------------------------------\n" );
    printf( "Testing pointer to object copy:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        linkedListPtr->push( i );
    }

    linkedList = *linkedListPtr;

    linkedList.print();

    delete linkedListPtr;

    //Test using as a list
    BasicLinkedList<int> test3LinkedListArr;

    printf( "\n-----------------------------------\n" );
    printf( "Testing treating linked list as list:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        test3LinkedListArr.add( i );
    }

    test3LinkedListArr.print();

    assert( test3LinkedListArr.size() == 6 );
    assert( test3LinkedListArr[0] == 1 );
    assert( test3LinkedListArr[ test3LinkedListArr.size()-1 ] == 6 );

    printf( "\n-----------------------------------\n" );
    printf( "Testing == operator between two different list objects\n" );

    BasicLinkedList<int> test4LinkedList1;
    BasicLinkedList<int> test4LinkedList2;

    for( int i = 1; i <= 10; i++ )
    {
        test4LinkedList1.push( i );
        test4LinkedList2.push( i );
    }

    printf( "Checking if both list are the same:\n" );
    bool compareTest1 = ( test4LinkedList1 == test4LinkedList2 );
    printf( "%s\n", ( compareTest1 ) ? "PASS" : "FAILED" );
    assert( compareTest1 );

    return 0;
}
