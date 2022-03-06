// DuplicateTypeRegistrationException.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// Exception that is thrown when attempting to register the same type with
// the same DynamicFactory twice.  Since registration is primarily done
// using a global macro call, this will predominantly be thrown at startup.

#ifndef DUPLICATETYPEREGISTRATIONEXCEPTION_HPP
#define DUPLICATETYPEREGISTRATIONEXCEPTION_HPP

#include <typeinfo>



namespace ics46::factory
{
    class DuplicateTypeRegistrationException
    {
    public:
        DuplicateTypeRegistrationException(const std::type_info& duplicateType);
        const std::type_info& duplicateType() const;

    private:
        const std::type_info& duplicateType_;
    };



    inline DuplicateTypeRegistrationException::DuplicateTypeRegistrationException(
        const std::type_info& duplicateType)
        : duplicateType_{duplicateType}
    {
    }


    inline const std::type_info& DuplicateTypeRegistrationException::duplicateType() const
    {
        return duplicateType_;
    }
}



#endif

