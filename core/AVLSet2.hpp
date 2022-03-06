  
// AVLSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"

/*=====AVLNODE FRIEND CLASS=====*/
template<typename T>
class AvlNode
    {
    T element;
    AvlNode *left;//POINTER TO LEFT NODE
    AvlNode *right;//POINTER TO RIGHT NODE
    int level;//LEVEL NODE IS ON
    int count;//AMOUNT OF TIMES NODE'S ELEMENT WAS GIVEN
    AvlNode(const T & theElement, AvlNode *lt, AvlNode *rt, int l = 0, int c = 0)//CONSTRUCTOR
        : element(theElement), left(lt), right(rt), level(l), count(c) {}
    //FRIEND CLASS
    template<typename ElementType>
    friend class AVLSet;
    };

template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet() noexcept;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    bool balance = true;//IF TREE SHOULD BE BALANCED
    int sizeOfTree;//AMOUNT OF ELEMENTS IN TREE
    AvlNode<ElementType> *root;//ROOT OF TREE

    void makeEmpty(AvlNode<ElementType> * & t) const;//MAKE TREE EMPTY
    AvlNode<ElementType> *clone(AvlNode<ElementType> *t) const;//CLONE GIVEN TREE
    void add(const ElementType& element, AvlNode<ElementType> * & root);//ADD NEW NODE
    void addCount(const ElementType& element);//ADD COUNT
    void addCount(ElementType element, AvlNode<ElementType> *& root);//ADD COUNT HELPER
    int max(int lhs, int rhs) const;//RETURNS MAX BETWEEN TWO NODES
    int level(AvlNode<ElementType> *root);//RETURNS LEVEL OF GIVEN NODE
    //ROTATIONS
    void rotateWithLeftChild(AvlNode<ElementType> * & k2);
    void rotateWithRightChild(AvlNode<ElementType> * & k1);
    void doubleWithLeftChild(AvlNode<ElementType> * & k3);
    void doubleWithRightChild(AvlNode<ElementType> * & k1);
    //ORDER HELPERS
    void preorderHelper(const AvlNode<ElementType> *& root, VisitFunction visit) const;
    void inorderHelper(const AvlNode<ElementType> *& root, VisitFunction visit) const;
    void postorderHelper(const AvlNode<ElementType> *&root, VisitFunction visit) const;
};

/*=====INITIALIZE EMPTY TREE=====*/
template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    this->root = NULL;
    sizeOfTree = 0;
    balance = shouldBalance;
}

/*=====DESTRUCTOR=====*/
template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    makeEmpty(this->root);
    sizeOfTree = 0;
}

/*=====COPY CONSTRUCTOR=====*/
template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    this->balance = s.balance;
    this->sizeOfTree = s.sizeOfTree;
    this->root = s.root;
}

/*=====EMPTY THE TREE=====*/
template <typename ElementType>
void AVLSet<ElementType>::makeEmpty(AvlNode<ElementType> * & t) const
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

/*=====MOVE CONSTRUCTOR=====*/
template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    this->balance = std::move(s.balance);
    this->sizeOfTree = std::move(s.sizeOfTree);
    this->root = std::move(s.root);
}

/*=====EQUALS OPERATOR=====*/
template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        makeEmpty(root);
        root = clone(s.root);
    }
    return *this;
}

/*=====EQUALS OPERATOR=====*/
template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    if (this != &s)
    {
        makeEmpty(root);
        root = clone(s.root);
    }
    return *this;
}

/*=====CLONE NODE=====*/
template <typename ElementType>
AvlNode<ElementType> *AVLSet<ElementType>::clone(AvlNode<ElementType> *t) const
{
    if (t == NULL)
        return NULL;
    else
        return new AvlNode(t->element, clone(t->left), clone(t->right), t->level, t->count);
}

//=====AVLTREE IS IMPLEMENTED======//
template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}

//=====ADD ELEMENT=====//
template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
    if(contains(element))
    {
        addCount(element);
    }
    else
    {
        add(element, this->root);
        sizeOfTree++;
    }
}

/*====Increase count of element=====*/
template<typename ElementType>
void AVLSet<ElementType>::addCount(const ElementType & element)
{
    addCount(element, this->root);
}

/*======Increase count of element helper=====*/
template<typename ElementType>
void AVLSet<ElementType>::addCount(ElementType element, AvlNode<ElementType> *&root)
{
    if(element < root->element)
        addCount(element, root->left);
    if(element > root->element)
        addCount(element, root->right);
    else
        root->count += 1;
}

//=====ADD ELEMENT HELPER=====//
template<typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element, AvlNode<ElementType> * & root)
{
    if(root == NULL)
    {
        root = new AvlNode<ElementType>(element, NULL, NULL, 0, 0);
        root->count = 1;
    }
    else if (element < root->element)
    {
        add(element, root->left);
        if(balance == true)
        {
            if((level(root->left) - level(root->right)) == 2)
            {
                if(element < root->left->element)
                    rotateWithLeftChild(root);
                else
                    doubleWithLeftChild(root);
            }
        }
    }
    else if(root->element < element)
    {
        add(element, root->right);
        if(balance == true)
        {
            if(level(root->right) - level(root->left) == 2)
            {
                if(root->right->element < element)
                    rotateWithRightChild(root);
                else
                doubleWithRightChild(root);
            }
        }
    }

    if(root != NULL)
        root->level = max(level(root->left), level(root->right)) + 1;
}

//=====FIND MAX OF TWO VALUES=====//
template<typename ElementType>
int AVLSet<ElementType>::max(int lhs, int rhs) const
{
    return lhs > rhs? lhs : rhs;
}

//=====FIND THE LEVEL THE NODE IS ON=====//
template<typename ElementType>
int AVLSet<ElementType>::level(AvlNode<ElementType> *root)
{
    return root == NULL ? : root->level;
}

//=====ROTATE BINARY TREE NODE WITH LEFT CHILD=====//
template<typename ElementType>
void AVLSet<ElementType>::rotateWithLeftChild(AvlNode<ElementType> * & k2)
{
    AvlNode<ElementType> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->level = max(level(k2->left), level(k2->right)) + 1;
    k1->level = max(level(k1->left), k2->level) + 1;
    k2 = k1;
}

//=====ROTATE BINARY TREE WITH RIGHT CHILD=====//
template<typename ElementType>
void AVLSet<ElementType>::rotateWithRightChild(AvlNode<ElementType> * & k1)
{
    AvlNode<ElementType> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->level = max(level(k1->left), level(k1->right)) + 1;
    k2->level = max(level(k2->right), k1->level) + 1;
    k1 = k2;
}

//=====DOUBLE ROTATE BINARY TREE NODE LEFT FIRST=====//
template<typename ElementType>
void AVLSet<ElementType>::doubleWithLeftChild(AvlNode<ElementType> * & k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

//=====DOUBLE ROTATE BINARY TREE NODE RIGHT FIRST=====//
template<typename ElementType>
void AVLSet<ElementType>::doubleWithRightChild(AvlNode<ElementType> * & k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

//=====DOES TREE CONTAIN ELEMENT=====//
template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    AvlNode<ElementType>* n = this->root;
    
    while(n != NULL)
    {
        if(element == n->element)
            return true;
        else if(element < n->element)
            n = n->left;
        else if(element > n->element)
            n = n->right;
    }

    return false;
}

//=====ELEMENTS IN THE TREE=====//
template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return this->sizeOfTree;
}

//=====GET HEIGHT OF TREE======//
template <typename ElementType>
int AVLSet<ElementType>::height() const
{
    return this->root == NULL ? -1 : this->root->level;
}

/*=====PREORDER=====*/
template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    const AvlNode<ElementType>* n = this->root;
    preorderHelper(n, visit);
}

/*=====PREORDER HELPER=====*/
template <typename ElementType>
void AVLSet<ElementType>::preorderHelper(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const AvlNode<ElementType>*& n = root;
    const AvlNode<ElementType>* l = root->left;
    const AvlNode<ElementType>* r = root->right;
    visit(n->element);
    preorderHelper(l, visit);
    preorderHelper(r, visit);
}

/*=====INORDER=====*/
template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    const AvlNode<ElementType>* n = this->root;
    inorderHelper(n, visit);
}

/*=====INORDER HELPER=====*/
template<typename ElementType>
void AVLSet<ElementType>::inorderHelper(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const AvlNode<ElementType>*& n = root;
    const AvlNode<ElementType>* l = root->left;
    const AvlNode<ElementType>* r = root->right;
    inorderHelper(l, visit);
    visit(n->element);
    inorderHelper(r, visit);
}

/*=====POST ORDER=====*/
template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    const AvlNode<ElementType>* n = this->root;
    postorderHelper(n,visit);
}

/*=====POST ORDER HELPER=====*/
template<typename ElementType>
void AVLSet<ElementType>::postorderHelper(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const AvlNode<ElementType>*& n = root;
    const AvlNode<ElementType>* l = root->left;
    const AvlNode<ElementType>* r = root->right;
    postorderHelper(l, visit);
    postorderHelper(r, visit);
    visit(n->element);
}

#endif // AVLSET_HPP

