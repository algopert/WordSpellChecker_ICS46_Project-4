// DynamicFactory.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// A DynamicFactory<BaseType> is an object that is capable of creating objects
// whose types inherit from BaseType, returning BaseType pointers to them.
// The goal is to allow it to be possible to do two things that C++ otherwise
// makes difficult:
//
// (1) Find out a list of what types are available that inherit from BaseType.
// (2) Create objects of types that inherit from BaseType without necessarily
//     knowing the names of those types or having access to their source code
//     (e.g., types compiled into libraries without declarations provided in
//     header files.
//
// For ICS 46, this will be useful for allowing students to supply their own
// types to existing programs without requiring me to provide all of the
// source code; it will also be useful for allowing students to create objects
// of classes I provide in libraries without providing their source code.
//
// Making a type available to a DynamicFactory is done by using the macro
// ICS46_DYNAMIC_FACTORY_REGISTER.  It's important to understand that this
// must be done in a source file and that it can only be done once for a
// given type.  For example, if you wanted to register your own type
// MyCoolMazeGenerator with the DynamicFactory<MazeGenerator>, you would
// include this line -- outside of any function -- in MyCoolMazeGenerator.cpp:
//
//     ICS46_DYNAMIC_FACTORY_REGISTER(
//         MazeGenerator, MyCoolMazeGenerator,
//         "My Cool Maze Generator");
//
// where the third argument is a display name for your type.
//
// Subsequently, my code could do something like this to create an object
// of your type:
//
//     std::unique_ptr<MazeGenerator> generator =
//         ics46::factory::DynamicFactory<MazeGenerator>
//         ::instance().make("My Cool Maze Generator");
//
// Or get a collection of all available types like this:
//
//     ics46::factory::DynamicFactory<MazeGenerator>
//         ::instance().allRegisteredTypes()
//
// then iterate through them, etc.

#ifndef DYNAMICFACTORY_HPP
#define DYNAMICFACTORY_HPP

#include <algorithm>
#include <map>
#include <memory>
#include <typeindex>
#include <vector>
#include "RegisteredType.hpp"
#include "UnregisteredNameException.hpp"
#include "UnregisteredTypeException.hpp"
#include "DuplicateTypeRegistrationException.hpp"



namespace ics46::factory
{
    template <typename BaseType>
    class DynamicFactory
    {
    public:
        static DynamicFactory<BaseType>& instance();

    public:
        const std::vector<std::shared_ptr<RegisteredType<BaseType>>>& allRegisteredTypes() const;

        template <typename ObjectType, typename... ConstructorArgs>
        void registerType(const std::string& name, ConstructorArgs... constructorArgs);

        template <typename ObjectType>
        std::unique_ptr<BaseType> make() const;

        std::unique_ptr<BaseType> make(const std::string& name) const;

    private:
        DynamicFactory();

    private:
        std::vector<std::shared_ptr<RegisteredType<BaseType>>> registeredTypes;
        std::map<std::type_index, std::shared_ptr<RegisteredType<BaseType>>> registeredTypesByType;
        std::map<std::string, std::shared_ptr<RegisteredType<BaseType>>> registeredTypesByName;
    };



    template <typename BaseType>
    DynamicFactory<BaseType>::DynamicFactory()
    {
    }


    template <typename BaseType>
    DynamicFactory<BaseType>& DynamicFactory<BaseType>::instance()
    {
        static DynamicFactory<BaseType> factoryInstance;
        return factoryInstance;
    }


    template <typename BaseType>
    const std::vector<std::shared_ptr<RegisteredType<BaseType>>>& DynamicFactory<BaseType>
        ::allRegisteredTypes() const
    {
        return registeredTypes;
    }


    template <typename BaseType>
    template <typename ObjectType, typename... ConstructorArgs>
    void DynamicFactory<BaseType>::registerType(
        const std::string& name, ConstructorArgs... constructorArgs)
    {
        static_assert(
            std::is_base_of<BaseType, ObjectType>::value,
            "DynamicFactory registration requires that the object type is derived from the factory's base type");

        auto it = registeredTypesByType.find(std::type_index(typeid(ObjectType)));

        if (it == registeredTypesByType.end())
        {
            std::shared_ptr<RegisteredType<BaseType>> registeredType =
                std::make_shared<RegisteredType<BaseType>>(
                    name, typeid(ObjectType),
                    [=]()
                    {
                        return std::unique_ptr<ObjectType>{
                            new ObjectType{std::forward<ConstructorArgs>(constructorArgs)...}};
                    });

            registeredTypes.push_back(registeredType);
            registeredTypesByType[std::type_index(typeid(ObjectType))] = registeredType;
            registeredTypesByName[name] = registeredType;
        }
        else
        {
            throw DuplicateTypeRegistrationException{typeid(ObjectType)};
        }
    }


    template <typename BaseType>
    template <typename ObjectType>
    std::unique_ptr<BaseType> DynamicFactory<BaseType>::make() const
    {
        auto it = registeredTypesByType.find(std::type_index(typeid(ObjectType)));

        if (it != registeredTypesByType.end())
        {
            return it->second->build();
        }
        else
        {
            throw UnregisteredTypeException{typeid(ObjectType)};
        }
    }


    template <typename BaseType>
    std::unique_ptr<BaseType> DynamicFactory<BaseType>::make(const std::string& name) const
    {
        auto it = registeredTypesByName.find(name);

        if (it != registeredTypesByName.end())
        {
            return it->second->build();
        }
        else
        {
            throw UnregisteredNameException(name);
        }
    }
}



#include "DynamicFactoryRegistration.hpp"



#endif

