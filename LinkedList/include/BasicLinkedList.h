#ifndef BASICLINKEDLIST_H
#define BASICLINKEDLIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//template <class Type> extern BasicLinkedList<Type>;
//template <class Type> extern void add ( Type new_data );

template <class Type> class BasicLinkedList
{
    public:
        typedef   Type       Type_name;

        struct node {
            Type_name data; //data
            struct node *next;
        };

        typedef struct node* iterator;
        typedef struct node* node_ptr;
        typedef unsigned int usingn_int;

        ////////////////////////////////
        //Constructors
        //
        BasicLinkedList()
        {
            list = NULL;
            head = NULL;
            tail = NULL;
        }

        //Copy c'ctor
        BasicLinkedList ( const BasicLinkedList<Type_name> &__other_object__ )
        {
            list = NULL;
            head = NULL;
            tail = NULL;
            copy_list_internal( __other_object__ );
        }

        //Made virtual for possible child classes using this class
        virtual ~BasicLinkedList()
        {
            node_ptr del_node = list;
            while( list != NULL )
            {
                del_node = list;
                list = list->next;
                free( del_node );
            }
        }
        //
        //////////////////////////////////

        //Modifiers of the linked list
        void      add        ( Type_name new_data );
        void      add        ( struct node **head_ref, Type_name new_data );
        bool      push       ( Type_name new_data );
        bool      push       ( struct node **new_node, Type_name new_data );

        Type_name  pop        ();
        Type_name  getValue   ( const usingn_int __index__ );

        size_t    size() const;
        void      print() const;

        //Need to add the following for operator overloading
        //=, ==, []
        BasicLinkedList<Type_name>& operator=( const BasicLinkedList<Type_name> &__other_object__ )
        {
            if( this == &__other_object__ )
                return *this;

            list = NULL;
            head = NULL;
            tail = NULL;

            copy_list_internal( __other_object__ );
            return *this;
        }

        /*
        Type_name& operator[]( const usingn_int __index__ )
        {
            assert( ( __index__ >= 0 ) && ( __index__ <= size()-1 ) );

            if ( list != head )
                list = head;

            iterator _pl = begin() + __index__;

            return _pl->data;

            unsigned int index = 0;
            Type_name ret = -1;

            while ( list != NULL )
            {
                if ( index == __index__ )
                {
                    ret = list->data;
                    break;
                }
                index++;
                list = list->next;
            }

            list = head;
            return ret;
            */
        }

        /*TODO: Finish implementing*/
        bool operator==( const BasicLinkedList<Type_name> &__other_object )
        {
            bool isEquals = false;



            return isEquals;
        }

    protected:
        iterator begin() { return head; }
        iterator end() { return tail; }

    private:

        /**
        * Is type mutable so that the copy will iterate
        */
        mutable node_ptr list;
        node_ptr head;
        node_ptr tail;

        void copy_list_internal( const BasicLinkedList<Type_name> &__other_object_to_copy_from__ );
}; // END OF BASICLINKEDLIST CLASS HEADER DEF

template<typename Type_name>
void BasicLinkedList<Type_name>::copy_list_internal( const BasicLinkedList<Type_name> &__other_object_to_copy_from__ )
{
    while( __other_object_to_copy_from__.list != NULL )
    {
        add( __other_object_to_copy_from__.list->data );

        __other_object_to_copy_from__.list = __other_object_to_copy_from__.list->next;
    }

    __other_object_to_copy_from__.list = __other_object_to_copy_from__.head;

    assert( list != NULL );
    assert( tail != NULL );
    assert( head == list );
}

template<typename Type_name>
void BasicLinkedList<Type_name>::add( Type_name new_data )
{
    add( &list, new_data );
}

template<typename Type_name>
void BasicLinkedList<Type_name>::add( struct node **head_ref, Type_name new_data )
{
    struct node *new_node = ( struct node* ) malloc( sizeof( struct node ) );

    if ( head == NULL && list == NULL )
    {
        //First item in the list
        new_node->data = new_data;
        new_node->next = NULL;
        tail = new_node;

        list = tail;
        head = list;
    } else {
        new_node->data = new_data;
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
    }

    //At this point even with starting point
    //we need to check that everything is pointing correctly
    assert( new_node == tail );
    assert( head != NULL );
    assert( list != NULL );
    assert( head == list );
}

template<typename Type_name>
bool BasicLinkedList<Type_name>::push( Type_name new_data )
{
    return push( &list, new_data );
}

/**
* push a new node to the list
*/
template<typename Type_name>
bool BasicLinkedList<Type_name>::push( struct node **head_ref, Type_name new_data )
{
    struct node* new_node = ( struct node* ) malloc( sizeof( struct node ) );

    if( !new_node )
        return false;

    new_node->data = new_data;
    new_node->next = ( *head_ref );
    ( *head_ref ) = new_node;
    head = new_node;

    if ( head->next == NULL ) // Base case for setting the tail pointer
        tail = head;

    assert( new_node == head );
    return true;
}

/**
* Takes off the first element of the list
*/
template<typename Type_name>
Type_name BasicLinkedList<Type_name>::pop()
{
    Type_name popped_item = NULL;

    if ( list != head )
        list = head;

    if ( list != NULL )
        popped_item = list->data;

    //Move head and list pointers to the next element
    struct node *tmp = list;

    free ( list );
    list = tmp->next;
    head = list;

    return popped_item;
}

template<typename Type_name>
Type_name BasicLinkedList<Type_name>::getValue( const usingn_int __index__ )
{
    Type_name ret_data = NULL;

    if( list != head )
        list = head;

    if( list == NULL )
        return ret_data;

    usingn_int temp_index = 0;
    while( list != NULL )
    {
        if( temp_index == __index__ )
        {
            ret_data = list->data;
            break;
        }
        list = list->next;
        temp_index++;
    }

    list = head;

    return ret_data;
}

template<typename Type_name>
size_t BasicLinkedList<Type_name>::size( ) const
{
    if ( list != head ) //Make sure that the pointer for list is at the beginning
        list = head;

    size_t sz = 0;
    while( list != NULL )
    {
        sz++;
        list = list->next;
    }

    list = head;

    return sz;
}

template<typename Type_name>
void BasicLinkedList<Type_name>::print() const
{
    if ( list != head ) //Make sure that the pointer for list is at the beginning
        list = head;

    while( list != NULL )
    {
        printf( "%d ", list->data );
        list = list->next;
    }

    printf( "\n" );
    list = head;
}

#endif // BASICLINKEDLIST_H
