// AVLSet.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain bBalance every time a
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
#include "AvlNode.hpp"

template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType &)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    ~AVLSet() noexcept override;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet &s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet &&s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet &operator=(const AVLSet &s);

    // Assigns an expiring AVLSet into another.
    AVLSet &operator=(AVLSet &&s) noexcept;

    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    bool isImplemented() const noexcept override;

    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType &element) override;

    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType &element) const override;

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
    bool bBalance = true;
    AvlNode<ElementType> *root;
    int levelAVL;

    void balanceRight(AvlNode<ElementType> *&_node1);
    void balanceLeft(AvlNode<ElementType> *&_node2);
    void doubleBalanceRight(AvlNode<ElementType> *&_node3);
    void doubleBalanceLeft(AvlNode<ElementType> *&_node4);
    void preOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const;
    void inOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const;
    void postOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const;
    void clearAVL(AvlNode<ElementType> *&t) const;
    AvlNode<ElementType> *cloneNode(AvlNode<ElementType> *t) const;
    void add(const ElementType &element, AvlNode<ElementType> *&root);
    void addCount(const ElementType &element);
    void addCount(ElementType element, AvlNode<ElementType> *&root);
    int max(int a1, int a2) const;
    int getLevel(AvlNode<ElementType> *root);
};

template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    this->root = NULL;
    bBalance = shouldBalance;
    levelAVL = 0;
}

template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    clearAVL(this->root);
    levelAVL = 0;
}

template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet &s)
{
    this->bBalance = s.bBalance;
    this->levelAVL = s.levelAVL;
    this->root = s.root;
}

template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet &&s) noexcept
{
    this->bBalance = std::move(s.bBalance);
    this->levelAVL = std::move(s.levelAVL);
    this->root = std::move(s.root);
}

template <typename ElementType>
AVLSet<ElementType> &AVLSet<ElementType>::operator=(const AVLSet &s)
{
    if (this != &s)
    {
        clearAVL(root);
        root = cloneNode(s.root);
    }
    return *this;
}

template <typename ElementType>
AVLSet<ElementType> &AVLSet<ElementType>::operator=(AVLSet &&s) noexcept
{
    if (this != &s)
    {
        clearAVL(root);
        root = cloneNode(s.root);
    }
    return *this;
}

template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}

template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType &element)
{
    if (contains(element))
    {
        addCount(element);
    }
    else
    {
        add(element, this->root);
        levelAVL++;
    }
}

template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType &element) const
{
    AvlNode<ElementType> *n = this->root;

    while (n != NULL)
    {
        if (element == n->element)
            return true;
        else if (element < n->element)
            n = n->pLeft;
        else if (element > n->element)
            n = n->pRight;
    }

    return false;
}

template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return this->levelAVL;
}

template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return this->root == NULL ? -1 : this->root->deep;
}

template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    const AvlNode<ElementType> *n = this->root;
    preOrderAssist(n, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    const AvlNode<ElementType> *n = this->root;
    inOrderAssist(n, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    const AvlNode<ElementType> *n = this->root;
    postOrderAssist(n, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::preOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if (root == NULL)
        return;
    const AvlNode<ElementType> *&n = root;
    const AvlNode<ElementType> *l = root->pLeft;
    const AvlNode<ElementType> *r = root->pRight;
    visit(n->element);
    preOrderAssist(l, visit);
    preOrderAssist(r, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::inOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if (root == NULL)
        return;
    const AvlNode<ElementType> *&n = root;
    const AvlNode<ElementType> *l = root->pLeft;
    const AvlNode<ElementType> *r = root->pRight;
    inOrderAssist(l, visit);
    visit(n->element);
    inOrderAssist(r, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postOrderAssist(const AvlNode<ElementType> *&root, VisitFunction visit) const
{
    if (root == NULL)
        return;
    const AvlNode<ElementType> *&n = root;
    const AvlNode<ElementType> *l = root->pLeft;
    const AvlNode<ElementType> *r = root->pRight;
    postOrderAssist(l, visit);
    postOrderAssist(r, visit);
    visit(n->element);
}

template <typename ElementType>
int AVLSet<ElementType>::max(int a1, int a2) const
{
    return a1 > a2 ? a1 : a2;
}

template <typename ElementType>
int AVLSet<ElementType>::getLevel(AvlNode<ElementType> *root)
{
    return root == NULL ? -1 : root->deep;
}

template <typename ElementType>
void AVLSet<ElementType>::balanceLeft(AvlNode<ElementType> *&_node2)
{
    AvlNode<ElementType> *_node1 = _node2->pLeft;
    _node2->pLeft = _node1->pRight;
    _node1->pRight = _node2;
    _node2->deep = max(getLevel(_node2->pLeft), getLevel(_node2->pRight)) + 1;
    _node1->deep = max(getLevel(_node1->pLeft), _node2->deep) + 1;
    _node2 = _node1;
}

template <typename ElementType>
void AVLSet<ElementType>::balanceRight(AvlNode<ElementType> *&_node1)
{
    AvlNode<ElementType> *_node2 = _node1->pRight;
    _node1->pRight = _node2->pLeft;
    _node2->pLeft = _node1;
    _node1->deep = max(getLevel(_node1->pLeft), getLevel(_node1->pRight)) + 1;
    _node2->deep = max(getLevel(_node2->pRight), _node1->deep) + 1;
    _node1 = _node2;
}

template <typename ElementType>
void AVLSet<ElementType>::doubleBalanceRight(AvlNode<ElementType> *&_node3)
{
    balanceRight(_node3->pLeft);
    balanceLeft(_node3);
}

template <typename ElementType>
void AVLSet<ElementType>::doubleBalanceLeft(AvlNode<ElementType> *&_node4)
{
    balanceLeft(_node4->pRight);
    balanceRight(_node4);
}

template <typename ElementType>
void AVLSet<ElementType>::addCount(const ElementType &element)
{
    addCount(element, this->root);
}

template <typename ElementType>
void AVLSet<ElementType>::addCount(ElementType element, AvlNode<ElementType> *&root)
{
    if (element < root->element)
        addCount(element, root->pLeft);
    if (element > root->element)
        addCount(element, root->pRight);
    else
        root->count += 1;
}

template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType &element, AvlNode<ElementType> *&root)
{
    if (root == NULL)
    {
        root = new AvlNode<ElementType>(element, NULL, NULL, 0, 0);
        root->count = 1;
    }
    else if (element < root->element)
    {
        add(element, root->pLeft);
        if (bBalance == true)
        {
            if ((getLevel(root->pLeft) - getLevel(root->pRight)) == 2)
            {
                if (element < root->pLeft->element)
                    balanceLeft(root);
                else
                    doubleBalanceRight(root);
            }
        }
    }
    else if (root->element < element)
    {
        add(element, root->pRight);
        if (bBalance == true)
        {
            if (getLevel(root->pRight) - getLevel(root->pLeft) == 2)
            {
                if (root->pRight->element < element)
                    balanceRight(root);
                else
                    doubleBalanceLeft(root);
            }
        }
    }

    if (root != NULL)
        root->deep = max(getLevel(root->pLeft), getLevel(root->pRight)) + 1;
}

template <typename ElementType>
void AVLSet<ElementType>::clearAVL(AvlNode<ElementType> *&t) const
{
    if (t != NULL)
    {
        clearAVL(t->pLeft);
        clearAVL(t->pRight);
        delete t;
    }
    t = NULL;
}

template <typename ElementType>
AvlNode<ElementType> *AVLSet<ElementType>::cloneNode(AvlNode<ElementType> *t) const
{
    if (t == NULL)
        return NULL;
    else
        return new AvlNode(t->element, cloneNode(t->pLeft), cloneNode(t->pRight), t->deep, t->count);
}

#endif
