// VectorSet.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// An implementation of the Set<ElementType> class template, which uses
// a std::vector to store its keys.  The keys are not sorted in any
// particular order.

#ifndef VECTORSET_HPP
#define VECTORSET_HPP

#include <algorithm>
#include "Set.hpp"



template <typename ElementType>
class VectorSet : public Set<ElementType>
{
public:
    VectorSet() noexcept;
    ~VectorSet() noexcept override;
    VectorSet(const VectorSet& s);
    VectorSet(VectorSet&& s) noexcept;
    VectorSet& operator=(const VectorSet& s);
    VectorSet& operator=(VectorSet&& s) noexcept;

    bool isImplemented() const noexcept override;
    void add(const ElementType& element) override;
    bool contains(const ElementType& element) const override;
    unsigned int size() const noexcept override;

private:
    std::vector<ElementType> elements;
};



template <typename ElementType>
VectorSet<ElementType>::VectorSet() noexcept
{
}


template <typename ElementType>
VectorSet<ElementType>::~VectorSet() noexcept
{
}


template <typename ElementType>
VectorSet<ElementType>::VectorSet(const VectorSet& s)
    : elements{s.elements}
{
}


template <typename ElementType>
VectorSet<ElementType>::VectorSet(VectorSet&& s) noexcept
{
    std::swap(elements, s.elements);
}


template <typename ElementType>
VectorSet<ElementType>& VectorSet<ElementType>::operator=(const VectorSet& s)
{
    elements = s.elements;
    return *this;
}


template <typename ElementType>
VectorSet<ElementType>& VectorSet<ElementType>::operator=(VectorSet&& s) noexcept
{
    std::swap(elements, s.elements);
    return *this;
}


template <typename ElementType>
bool VectorSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void VectorSet<ElementType>::add(const ElementType& element)
{
    if (!contains(element))
    {
        elements.push_back(element);
    }
}


template <typename ElementType>
bool VectorSet<ElementType>::contains(const ElementType& element) const
{
    return std::any_of(
        elements.begin(), elements.end(),
        [&](ElementType e) { return e == element; });
}


template <typename ElementType>
unsigned int VectorSet<ElementType>::size() const noexcept
{
    return elements.size();
}



#endif

