// RegisteredType.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// A RegisteredType<BaseType> describes a type registered with a
// DynamicFactory<BaseType>.  A RegisteredType has these properties:
//
// * A name that uniquely identifies it and can be used to create
//   an object of that type without having access to the actual type
// * A type_info object that describes the C++ type
// * A creation function that is used to create objects of that type

#ifndef REGISTEREDTYPE_HPP
#define REGISTEREDTYPE_HPP

#include <cxxabi.h>
#include <functional>
#include <memory>
#include <string>
#include <typeinfo>



namespace ics46::factory
{
    template <typename BaseType>
    class RegisteredType 
    {
    public:
        RegisteredType(
            const std::string& name, const std::type_info& type,
            std::function<std::unique_ptr<BaseType>()> creationFunction);

        std::unique_ptr<BaseType> build() const;
        const std::type_info& type() const;
        const std::string& typeName() const;
        const std::string& name() const;

    private:
        std::string name_;
        const std::type_info& type_;
        std::string typeName_;
        std::function<std::unique_ptr<BaseType>()> creationFunction;
    };



    namespace impl_
    {
        inline std::string demangleTypeName(const std::type_info& type)
        {
            int status;

            char* typeNameBuffer = abi::__cxa_demangle(
                type.name(), nullptr, nullptr, &status);

            try
            {
                std::string demangledTypeName{typeNameBuffer};
                delete[] typeNameBuffer;
                return demangledTypeName;
            }
            catch (...)
            {
                delete[] typeNameBuffer;
                throw;
            }
        }
    }



    template <typename BaseType>
    RegisteredType<BaseType>::RegisteredType(
        const std::string& name, const std::type_info& type,
        std::function<std::unique_ptr<BaseType>()> creationFunction)
        : name_{name}, type_{type}, typeName_{impl_::demangleTypeName(type)},
          creationFunction{creationFunction}
    {
    }

    
    template <typename BaseType>
    std::unique_ptr<BaseType> RegisteredType<BaseType>::build() const
    {
        return creationFunction();
    }


    template <typename BaseType>
    const std::type_info& RegisteredType<BaseType>::type() const
    {
        return type_;
    }


    template <typename BaseType>
    const std::string& RegisteredType<BaseType>::typeName() const
    {
        return typeName_;
    }


    template <typename BaseType>
    const std::string& RegisteredType<BaseType>::name() const
    {
        return name_;
    }
}



#endif

