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
 */
template <class ClassType> class BasicLinkedList {
    public:
        typedef   ClassType       TypeName;

        template<class StructType> struct node {
            StructType data; //data
            struct node *next;
        };

        /*template<typename ObjectType> struct type_name_def {
            static const char* name() {
                static_assert(false, "You are missing a Declartion type!");
            }
        };*/

        typedef struct node<ClassType>* iterator;
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
        virtual void      add        ( TypeName new_data );
        virtual bool      push       ( TypeName new_data );

        virtual TypeName  pop        ();
        TypeName  getValue   (const usingn_int __index__ );

        size_t    size() const;
        virtual void      print() const;

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

        TypeName operator[]( const usingn_int __index__ ) {
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

        /**
        * Is type mutable so that the copy will iterate
        */
        typedef struct node<ClassType>* node_ptr;

        /*******************
        * The Head pointer should never be modified since it is the source of truth for the entire list.
        */
        node_ptr head;

        /*******************
        * The Tail pointer should only be modified when we add, since an add only modifies the end of the list.
        */
        node_ptr tail;
        mutable node_ptr list;

    private:
        bool      push       ( struct node<ClassType> **new_node, TypeName new_data );
        void      add        ( struct node<ClassType> **head_ref, TypeName new_data );

        size_t listSize = 0;

        void copy_list_internal( const BasicLinkedList<TypeName> &__other_object_to_copy_from__ );
}; // END OF BASICLINKEDLIST CLASS HEADER DEF

/*template<> struct type_name_def<int> { static const char* name(){return "int";}};
template<> struct type_name_def<string> { static const char* name(){return "string";}};
template<> struct type_name_def<float> { static const char* name(){return "float";}};
*/

template<class ClassType>
void BasicLinkedList<ClassType>::copy_list_internal( const BasicLinkedList<ClassType> &__other_object_to_copy_from__ ) {
    while( __other_object_to_copy_from__.list != NULL ) {
        add( __other_object_to_copy_from__.list->data );

        __other_object_to_copy_from__.list = __other_object_to_copy_from__.list->next;
    }

    __other_object_to_copy_from__.list = __other_object_to_copy_from__.head;

    assert( list != NULL );
    assert( tail != NULL );
    assert( head == list );
}

template<class ClassType>
void BasicLinkedList<ClassType>::add( ClassType new_data ) {
    add( &list, new_data );
}

template<typename ClassType>
void BasicLinkedList<ClassType>::add( struct node<ClassType> **head_ref, ClassType new_data ) {
    struct node<ClassType> *new_node = ( struct node<ClassType>* ) malloc( sizeof( struct node<ClassType> ) );

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

template<class ClassType>
bool BasicLinkedList<ClassType>::push( ClassType new_data ) {
    return push( &list, new_data );
}

/**
* push a new node to the list
*/
template<class ClassType>
bool BasicLinkedList<ClassType>::push( struct node<ClassType> **head_ref, ClassType new_data ) {
    node_ptr new_node = ( node_ptr ) malloc( sizeof( struct node<ClassType> ) );

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
template<class ClassType>
ClassType BasicLinkedList<ClassType>::pop() {
    ClassType popped_item = NULL;

    if ( list != head )
        list = head;

    if ( list != NULL )
        popped_item = list->data;

    //Move head and list pointers to the next element
    node_ptr tmp = list;

    free ( list );
    list = tmp->next;
    head = list;

    listSize--;
    return popped_item;
}

template<class ClassType>
ClassType BasicLinkedList<ClassType>::getValue( const usingn_int __index__ ) {
    ClassType ret_data = NULL;

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

template<class ClassType>
size_t BasicLinkedList<ClassType>::size( ) const {
    return listSize;
}

template<class ClassType>
void BasicLinkedList<ClassType>::print() const {
    if ( list != head ) //Make sure that the pointer for list is at the beginning
        list = head;

    while( list != NULL ) {
        cout<<list->data<<" ";
        list = list->next;
    }

    printf( "\n" );
    list = head;
}

#endif // BASICLINKEDLIST_H
