// HashSet.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet() noexcept;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8, in which case
    // the new capacity should be determined by this formula:
    //
    //     capacity * 2 + 1
    //
    // In the case where the array is resized, this function runs in linear
    // time (with respect to the number of elements, assuming a good hash
    // function); otherwise, it runs in constant time (again, assuming a good
    // hash function).  The amortized running time is also constant.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    struct Node
    {
        ElementType element;
        Node* next;
    };

    int hashSize;
    int hashCapacity;
    Node** hashTable;
};


namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    hashSize = 0;
    hashCapacity = DEFAULT_CAPACITY;
    hashTable = new Node*[hashCapacity];

    for (int i = 0; i < hashCapacity; i++)
    {
        hashTable[i] = nullptr;
    }
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    for (int i = 0; i < hashCapacity; i++)
    {
        Node* curr = hashTable[i];

        while (curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    delete[] hashTable;
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    hashSize = s.hashSize;
    hashCapacity = s.hashCapacity;
    hashTable = new Node*[hashCapacity];

    for (int i = 0; i < hashCapacity; i++)
    {
        hashTable[i] = nullptr;
 
        Node* curr = s.hashTable[i];
        while (curr != nullptr)
        {
            hashTable[i] = new Node{curr->element, hashTable[i]};
            curr = curr->next;
        }
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    hashSize = 0;
    hashCapacity = DEFAULT_CAPACITY;
    hashTable = new Node*[hashCapacity];

    for (int i = 0; i < hashCapacity; i++)
    {
        hashTable[i] = nullptr;
    }

    std::swap(hashSize, s.hashSize);
    std::swap(hashCapacity, s.hashCapacity);
    std::swap(hashTable, s.hashTable);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    delete[] hashTable;

    hashSize = s.hashSize;
    hashCapacity = s.hashCapacity;
    hashTable = new Node*[hashCapacity];

    for (int i = 0; i < hashCapacity; i++)
    {
        hashTable[i] = nullptr;

        Node* curr = s.hashTable[i];
        while (curr != nullptr)
        {
            hashTable[i] = new Node{curr->element, hashTable[i]};
            curr = curr->next;
        }       
    }

    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    std::swap(hashSize, s.hashSize);
    std::swap(hashCapacity, s.hashCapacity);
    std::swap(hashTable, s.hashTable);
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    if (contains(element))
    {
        return;
    }

    unsigned int index = hashFunction(element) % hashCapacity;
    hashTable[index] = new Node{element, hashTable[index]};
    hashSize++;

    if (hashSize > hashCapacity * 0.8)
    {
        int newHashCapacity = hashCapacity * 2;
        Node** newHashTable = new Node*[newHashCapacity];
        unsigned int newIndex;

        for (int i = 0; i < newHashCapacity; i++)
        {
            newHashTable[i] = nullptr;
        }

        for (int j = 0; j < hashCapacity; j++)
        {
            Node* oldCurr = hashTable[j];
            while (oldCurr != nullptr)
            {
                newIndex = hashFunction(oldCurr->element) % newHashCapacity;
                newHashTable[newIndex] = new Node{oldCurr->element, newHashTable[newIndex]};
                oldCurr = oldCurr->next;
            }
        }

        hashTable = newHashTable;
        hashCapacity = newHashCapacity;
    }
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    unsigned int index = hashFunction(element) % hashCapacity;
    Node* curr = hashTable[index];
    while (curr != nullptr)
    {
        if (curr->element == element)
        {
            return true;
        }

        curr = curr->next;
    }

    return false;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return hashSize;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    int totalElements = 0;
    
    if (index >= hashCapacity)
    {
        return totalElements;
    }

    Node* curr = hashTable[index];
    while (curr != nullptr)
    {
        totalElements++;
        curr = curr->next;
    }

    return totalElements;
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if (index >= hashCapacity)
    {
        return 0;
    }

    Node* curr = hashTable[index];
    while (curr != nullptr)
    {
        if (curr->element == element)
        {
            return true;
        }

        curr = curr->next;
    }

    return false;
}



#endif 

