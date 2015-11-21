#include <stdio.h>
#include <stdlib.h>

#include "../include/BasicLinkedList.h"

#ifdef NO_BUILD

struct node *list;
struct node *head;
struct node *tail;

/*template<typename TypeName> BasicLinkedList<TypeName>::BasicLinkedList()
{
    //ctor
    list = NULL;
}*/

/*BasicLinkedList::BasicLinkedList( int **values )
{
    list = NULL;

    for( int i = 0; i < 5; i++ )
    {
        cout << *values << endl;
        cout << **values << endl;
        int tmp = **values;
        push( &list, tmp );
        *values++;
    }
}*/

template<typename TypeName>
BasicLinkedList<TypeName>::~BasicLinkedList(){
    //dtor
    while( list->next != NULL )
    {
        free( list );
        list = list->next;
    }
}

/*BasicLinkedList& BasicLinkedList::operator++ ()
{
    if ( list->next != NULL )
        list = list->next;
    return *this;
}*/

template<typename TypeName>
BasicLinkedList<TypeName>& BasicLinkedList<TypeName>::operator= ( const BasicLinkedList<TypeName> &__other_object__ )
{
    struct node *previous_node = NULL;
    while( __other_object__.list->next != NULL )
    {
        struct node *new_copy_node = ( struct node* ) malloc ( sizeof ( struct node ) );

        if ( previous_node == NULL )
            head = previous_node;

        new_copy_node->data = __other_object__.list->data;
        new_copy_node->next = NULL;
        previous_node->next = new_copy_node;
        previous_node = new_copy_node;

        //Goto next item in the list
        __other_object__ = __other_object__.list->next;
    }
    tail = previous_node;
    list = head;
    return *this;
}

template<typename TypeName>
void BasicLinkedList<TypeName>::add( TypeName new_data )
{
    add( &list, new_data );
}

template<typename TypeName>
void BasicLinkedList<TypeName>::add( struct node **head_ref, TypeName new_data )
{
    struct node *new_node = ( struct node* ) malloc( sizeof( struct node ) );
    new_node->data = new_data;
    new_node->next = tail->next;
    tail->next = new_node;
    tail = new_node;

    //Make sure the that two addresses are equal
    assert( new_node == tail );

}

template<typename TypeName>
void BasicLinkedList<TypeName>::push( TypeName new_data )
{
    push( &list, new_data );
}

/**
* push a new node to the list
*/
template<typename TypeName>
void BasicLinkedList<TypeName>::push( struct node **head_ref, TypeName new_data )
{
    struct node* new_node = ( struct node* ) malloc( sizeof( struct node ) );
    new_node->data = new_data;
    new_node->next = ( *head_ref );
    ( *head_ref ) = new_node;
    head = new_node;

    if ( head->next == NULL ) // Base case for setting the tail pointer
        tail = head;

    assert( new_node == head );
}

/**
* Takes off the first element of the list
*/
template<typename TypeName>
TypeName BasicLinkedList<TypeName>::pop()
{
    TypeName first_element_data;

    if ( list != head )
        list = head;

    if( list != NULL )
    {
        first_element_data = list->data;
    }

    //Move head and list pointers to the next element
    struct node *tmp = list;

    free ( list );
    list = tmp->next;
    head = list;

    return first_element_data;
}

template<typename TypeName>
size_t BasicLinkedList<TypeName>::size( )
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

template<typename TypeName>
void BasicLinkedList<TypeName>::print()
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

#endif




