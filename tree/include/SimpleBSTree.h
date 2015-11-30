#ifndef TREE_H
#define TREE_H

class SimpleBSTree {
    public:

        struct node {
            int nodeId;
            void * data;
            struct node *left;
            struct node *right;
        };

        //Default constructor
        SimpleBSTree();

        //Copy constructor
        SimpleBSTree(const SimpleBSTree &otherObject);
        virtual ~SimpleBSTree();
        SimpleBSTree(const SimpleBSTree& other);
    protected:
    private:
};

#endif // TREE_H
