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
    void signal_handler_abrt ( int hanlde )
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

    BasicLinkedList<int>    IntegerList;
    BasicLinkedList<int>    CopyIntegerList;

    printf( "-----------------------------------\n" );
    printf( "Testing basic object copy:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        //IntegerListPtr->push( i );
        IntegerList.push(i);
    }

    CopyIntegerList = IntegerList;

    CopyIntegerList.add( 10 );

    printf( "Copied list: \n" );
    CopyIntegerList.print();

    printf( "Original list\n" );
    IntegerList.print();

    assert( CopyIntegerList[ CopyIntegerList.size()-1 ] == 10 );

    int size1 = CopyIntegerList.size();
    int size2 = IntegerList.size();
    assert( size1 != size2 );


    //Testing creating object on the heap and changing from pointer to object on heap
    //To normal object.
    BasicLinkedList<int> *LinkedListPtr = new BasicLinkedList<int>();
    BasicLinkedList<int>  LinkedList;

    printf( "\n-----------------------------------\n" );
    printf( "Testing pointer to object copy:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        LinkedListPtr->push( i );
    }

    LinkedList = *LinkedListPtr;

    LinkedList.print();

    delete LinkedListPtr;

    //Test using as a list
    BasicLinkedList<int> Test3LinkedListArr;

    printf( "\n-----------------------------------\n" );
    printf( "Testing treating linked list as list:\n" );

    for ( int i = 1; i <= 6; i++ )
    {
        Test3LinkedListArr.add( i );
    }

    Test3LinkedListArr.print();

    assert( Test3LinkedListArr.size() == 6 );
    assert( Test3LinkedListArr[0] == 1 );
    assert( Test3LinkedListArr[ Test3LinkedListArr.size()-1 ] == 6 );

    printf( "\n-----------------------------------\n" );
    printf( "Testing == operator between two different list objects\n" );

    BasicLinkedList<int> Test4LinkedList1;
    BasicLinkedList<int> Test4LinkedList2;

    for( int i = 1; i <= 10; i++ )
    {
        Test4LinkedList1.push( i );
        Test4LinkedList2.push( i );
    }

    printf( "Checking if both list are the same:\n" );
    bool compareTest1 = ( Test4LinkedList1 == Test4LinkedList2 ) ? true : false;
    printf( "%s\n", ( compareTest1 ) ? "PASS" : "FAILED" );
    assert( compareTest1 );

    return 0;
}
