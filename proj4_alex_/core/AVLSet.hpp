// AVLSet.hpp
//
// ICS 46 Winter 2022
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


template<typename T>
class myNode
{
    T element;
    myNode *left;
    myNode *right;
    int level;
    int count;
    myNode(const T & theElement, myNode *_lt, myNode *_rt, int lvl = 0, int cnt = 0)
        : element(theElement), left(_lt), right(_rt), level(lvl), count(cnt) {}
    
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
    ~AVLSet() noexcept override;

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
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const noexcept;


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
    bool balance = true;
    int sizeOfTree;
    myNode<ElementType> *root;

    void makeEmpty(myNode<ElementType> * & t) const;
    myNode<ElementType> *clone(myNode<ElementType> *t) const;
    void add(const ElementType& element, myNode<ElementType> * & root);
    void addWord(const ElementType& element);
    void addWord(ElementType element, myNode<ElementType> *& root);
    int max(int lhs, int rhs) const;
    int level(myNode<ElementType> *root);
    void rotateWithLeftWord(myNode<ElementType> * & k2);
    void rotateWithRightWord(myNode<ElementType> * & k1);
    void twiceToRightWord(myNode<ElementType> * & k3);
    void twiceToLeftWord(myNode<ElementType> * & k1);
    void preorderHelper(const myNode<ElementType> *& root, VisitFunction visit) const;
    void inorderHelper(const myNode<ElementType> *& root, VisitFunction visit) const;
    void postorderHelper(const myNode<ElementType> *&root, VisitFunction visit) const;
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    this->root = NULL;
    sizeOfTree = 0;
    balance = shouldBalance;
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    makeEmpty(this->root);
    sizeOfTree = 0;
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    this->balance = s.balance;
    this->sizeOfTree = s.sizeOfTree;
    this->root = s.root;
}

template <typename ElementType>
void AVLSet<ElementType>::makeEmpty(myNode<ElementType> * & t) const
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    this->balance = std::move(s.balance);
    this->sizeOfTree = std::move(s.sizeOfTree);
    this->root = std::move(s.root);
}


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

template <typename ElementType>
myNode<ElementType> *AVLSet<ElementType>::clone(myNode<ElementType> *t) const
{
    if (t == NULL)
        return NULL;
    else
        return new myNode(t->element, clone(t->left), clone(t->right), t->level, t->count);
}




template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true; //-------------------------------------------------------
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
    if(contains(element))
    {
        addWord(element);
    }
    else
    {
        add(element, this->root);
        sizeOfTree++;
    }
}

template<typename ElementType>
void AVLSet<ElementType>::addWord(const ElementType & element)
{
    addWord(element, this->root);
}

template<typename ElementType>
void AVLSet<ElementType>::addWord(ElementType element, myNode<ElementType> *&root)
{
    if(element < root->element)
        addWord(element, root->left);
    if(element > root->element)
        addWord(element, root->right);
    else
        root->count += 1;
}

template<typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element, myNode<ElementType> * & root)
{
    if(root == NULL)
    {
        root = new myNode<ElementType>(element, NULL, NULL, 0, 0);
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
                    rotateWithLeftWord(root);
                else
                    twiceToRightWord(root);
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
                    rotateWithRightWord(root);
                else
                twiceToLeftWord(root);
            }
        }
    }

    if(root != NULL)
        root->level = max(level(root->left), level(root->right)) + 1;
}

template<typename ElementType>
int AVLSet<ElementType>::max(int lhs, int rhs) const
{
    return lhs > rhs? lhs : rhs;
}

template<typename ElementType>
int AVLSet<ElementType>::level(myNode<ElementType> *root)
{
    return root == NULL ? -1: root->level;
}

template<typename ElementType>
void AVLSet<ElementType>::rotateWithLeftWord(myNode<ElementType> * & k2)
{
    myNode<ElementType> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->level = max(level(k2->left), level(k2->right)) + 1;
    k1->level = max(level(k1->left), k2->level) + 1;
    k2 = k1;
}

template<typename ElementType>
void AVLSet<ElementType>::rotateWithRightWord(myNode<ElementType> * & k1)
{
    myNode<ElementType> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->level = max(level(k1->left), level(k1->right)) + 1;
    k2->level = max(level(k2->right), k1->level) + 1;
    k1 = k2;
}

template<typename ElementType>
void AVLSet<ElementType>::twiceToRightWord(myNode<ElementType> * & k3)
{
    rotateWithRightWord(k3->left);
    rotateWithLeftWord(k3);
}

template<typename ElementType>
void AVLSet<ElementType>::twiceToLeftWord(myNode<ElementType> * & k1)
{
    rotateWithLeftWord(k1->right);
    rotateWithRightWord(k1);
}


template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    myNode<ElementType>* n = this->root;
    
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


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return this->sizeOfTree;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return this->root == NULL ? -1 : this->root->level;
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    const myNode<ElementType>* n = this->root;
    preorderHelper(n, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::preorderHelper(const myNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const myNode<ElementType>*& n = root;
    const myNode<ElementType>* l = root->left;
    const myNode<ElementType>* r = root->right;
    visit(n->element);
    preorderHelper(l, visit);
    preorderHelper(r, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    const myNode<ElementType>* n = this->root;
    inorderHelper(n, visit);
}

template<typename ElementType>
void AVLSet<ElementType>::inorderHelper(const myNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const myNode<ElementType>*& n = root;
    const myNode<ElementType>* l = root->left;
    const myNode<ElementType>* r = root->right;
    inorderHelper(l, visit);
    visit(n->element);
    inorderHelper(r, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    const myNode<ElementType>* n = this->root;
    postorderHelper(n,visit);
}

template<typename ElementType>
void AVLSet<ElementType>::postorderHelper(const myNode<ElementType> *&root, VisitFunction visit) const
{
    if(root == NULL)
        return;
    const myNode<ElementType>*& n = root;
    const myNode<ElementType>* l = root->left;
    const myNode<ElementType>* r = root->right;
    postorderHelper(l, visit);
    postorderHelper(r, visit);
    visit(n->element);
}

#endif

