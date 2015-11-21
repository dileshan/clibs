#ifndef BASICLINKEDLIST_H
#define BASICLINKEDLIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

/***
 * Class BasicLinkedList uses simple templating (only of primitive data types)
 * In future implementations will use Allocator to keep any object in memory or maintaining a void pointer.
 *
 * This BasicLinkedList is modified to behave like a list, the subscript modifier is overloaded to "pretend" that
 * it has random access, but really does a linear search on the list with O(n) running time.
 *
 *
 */
template <class Type> class BasicLinkedList {
    public:
        typedef   Type       TypeName;

        struct node {
            TypeName data; //data
            struct node *next;
        };

        typedef struct node* iterator;
        typedef unsigned int usingn_int;

        ////////////////////////////////
        //Constructors
        //
        BasicLinkedList() {
            list = NULL;
            head = NULL;
            tail = NULL;
        }

        //Copy c'ctor
        BasicLinkedList ( const BasicLinkedList<TypeName> &__other_object__ ) {
            list = NULL;
            head = NULL;
            tail = NULL;
            copy_list_internal( __other_object__ );
        }

        //Made virtual for possible child classes using this class
        virtual ~BasicLinkedList() {
            node_ptr del_node = list;
            while( list != NULL ) {
                del_node = list;
                list = list->next;
                free( del_node );
            }
        }
        //
        //////////////////////////////////

        //Modifiers of the linked list
        void      add        ( TypeName new_data );
        void      add        ( struct node **head_ref, TypeName new_data );
        bool      push       ( TypeName new_data );
        bool      push       ( struct node **new_node, TypeName new_data );

        TypeName pop        ();
        TypeName getValue   (const usingn_int __index__ );

        size_t    size() const;
        void      print() const;

        //Need to add the following for operator overloading
        //=, ==, []
        BasicLinkedList<TypeName>& operator=(const BasicLinkedList<TypeName> &__other_object__ ) {
            if( this == &__other_object__ )
                return *this;

            list = NULL;
            head = NULL;
            tail = NULL;

            copy_list_internal( __other_object__ );
            return *this;
        }

        TypeName operator[]( const usingn_int __index__ )
        {
            assert( ( __index__ >= 0 ) && ( __index__ <= size()-1 ) );

            if ( list != head )
                list = head;

            if ( __index__ == 0 ) {
                return head->data;
            }

            if ( __index__ == size()-1) {
                return tail->data;
            }

            unsigned int index = 0;
            TypeName ret = -1;

            while ( list != NULL ) {
                if ( index == __index__ ) {
                    ret = list->data;
                    break;
                }
                index++;
                list = list->next;
            }

            list = head;
            return ret;
        }

        bool operator==( const BasicLinkedList<TypeName> &__other_object ) {
            bool equals = true;

            if( __other_object.list == NULL ) {
                return false;
            }

            if( listSize != __other_object.size() ){
                return false;
            }

            if ( list != head )
                list = head;

            while( list != NULL ) {
                if( list->data != __other_object.list->data){
                    equals = false;
                    break;
                }
                list = list->next;
                __other_object.list = __other_object.list->next;
            }

            //reset lists
            list = head;
            __other_object.list = __other_object.head;

            return equals;
        }

    protected:
        iterator begin() { return head; }
        iterator end() { return tail; }

    private:
        /**
        * Is type mutable so that the copy will iterate
        */
        typedef struct node* node_ptr;
        mutable node_ptr list;
        node_ptr head;
        node_ptr tail;

        size_t listSize = 0;

        void copy_list_internal( const BasicLinkedList<TypeName> &__other_object_to_copy_from__ );
}; // END OF BASICLINKEDLIST CLASS HEADER DEF

template<typename TypeName>
void BasicLinkedList<TypeName>::copy_list_internal( const BasicLinkedList<TypeName> &__other_object_to_copy_from__ ) {
    while( __other_object_to_copy_from__.list != NULL ) {
        add( __other_object_to_copy_from__.list->data );

        __other_object_to_copy_from__.list = __other_object_to_copy_from__.list->next;
    }

    __other_object_to_copy_from__.list = __other_object_to_copy_from__.head;

    assert( list != NULL );
    assert( tail != NULL );
    assert( head == list );
}

template<typename TypeName>
void BasicLinkedList<TypeName>::add( TypeName new_data ) {
    add( &list, new_data );
}

template<typename TypeName>
void BasicLinkedList<TypeName>::add( struct node **head_ref, TypeName new_data ) {
    struct node *new_node = ( struct node* ) malloc( sizeof( struct node ) );

    if ( head == NULL && list == NULL ) {
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
    listSize++;
}

template<typename TypeName>
bool BasicLinkedList<TypeName>::push( TypeName new_data ) {
    return push( &list, new_data );
}

/**
* push a new node to the list
*/
template<typename TypeName>
bool BasicLinkedList<TypeName>::push( struct node **head_ref, TypeName new_data ) {
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
    listSize++;
    return true;
}

/**
* Takes off the first element of the list
*/
template<typename TypeName>
TypeName BasicLinkedList<TypeName>::pop() {
    TypeName popped_item = NULL;

    if ( list != head )
        list = head;

    if ( list != NULL )
        popped_item = list->data;

    //Move head and list pointers to the next element
    struct node *tmp = list;

    free ( list );
    list = tmp->next;
    head = list;

    listSize--;
    return popped_item;
}

template<typename TypeName>
TypeName BasicLinkedList<TypeName>::getValue( const usingn_int __index__ ) {
    TypeName ret_data = NULL;

    if( list != head )
        list = head;

    if( list == NULL )
        return ret_data;

    usingn_int temp_index = 0;
    while( list != NULL ) {
        if( temp_index == __index__ ) {
            ret_data = list->data;
            break;
        }
        list = list->next;
        temp_index++;
    }

    list = head;
    return ret_data;
}

template<typename TypeName>
size_t BasicLinkedList<TypeName>::size( ) const {
    return listSize;
}

template<typename TypeName>
void BasicLinkedList<TypeName>::print() const {
    if ( list != head ) //Make sure that the pointer for list is at the beginning
        list = head;

    while( list != NULL ) {
        printf( "%d ", list->data );
        list = list->next;
    }

    printf( "\n" );
    list = head;
}

#endif // BASICLINKEDLIST_H
