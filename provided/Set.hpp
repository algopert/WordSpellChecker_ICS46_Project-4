// Set.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// The Set<ElementType> class template is an abstract base class
// template for implementations of a "set" (i.e., a collection of
// unique elements that allows you to add, search, and determine
// a size).

#ifndef SET_HPP
#define SET_HPP



template <typename ElementType>
class Set
{
public:
    // The destructor is declared here mainly so we can assure that it will
    // be virtual.  This is important because we'll be deriving from this class
    // template.
    virtual ~Set() noexcept = default;


    // isImplemented() should be modified to return true in any of the set
    // implemenations that you choose to do, and left to return false in any
    // of the ones that you don't.
    virtual bool isImplemented() const noexcept = 0;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.
    virtual void add(const ElementType& element) = 0;


    // contains() returns true if the given element is already in the set,
    // false otherwise.
    virtual bool contains(const ElementType& element) const = 0;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept = 0;
};



#endif

