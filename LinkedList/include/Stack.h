//
// Created by desilvey on 11/23/2015.
//

#ifndef CLIBS_STACK_H
#define CLIBS_STACK_H

#include "BasicLinkedList.h"

template<class ClassType> class Stack : protected BasicLinkedList<ClassType> {
    private:
    public:
        typedef ClassType TypeName;
        Stack() : BasicLinkedList<TypeName>(){}

        Stack(const Stack<TypeName> &__other_object) : BasicLinkedList<TypeName>( __other_object ){}

        TypeName pop(){
            BasicLinkedList<TypeName>::pop();
        }

        bool push(TypeName data){
            BasicLinkedList<TypeName>::push(data);
        }

        void print() const{
            BasicLinkedList<TypeName>::print();
        }

    protected:
};

#endif //CLIBS_STACK_H
