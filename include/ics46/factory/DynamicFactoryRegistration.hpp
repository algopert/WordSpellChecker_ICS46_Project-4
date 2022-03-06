// DynamicFactoryRegistration.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// Implements a single registration entry for a DynamicFactory, along
// with the ICS46_DYNAMIC_FACTORY_REGISTER macro used to register a
// single class into a DynamicFactory.

#ifndef DYNAMICFACTORYREGISTRATION_HPP
#define DYNAMICFACTORYREGISTRATION_HPP



namespace ics46::factory
{
    template <typename BaseType, typename ObjectType, typename... ConstructorArgs>
    class DynamicFactoryRegistration
    {
    public:
        DynamicFactoryRegistration(
            const std::string& name, ConstructorArgs... constructorArgs);
    };



    template <typename BaseType, typename ObjectType, typename... ConstructorArgs>
    DynamicFactoryRegistration<BaseType, ObjectType, ConstructorArgs...>
        ::DynamicFactoryRegistration(
            const std::string& name, ConstructorArgs... constructorArgs)
    {
        DynamicFactory<BaseType>::instance().template registerType<ObjectType>(
            name, std::forward(constructorArgs)...);
    }
}



#define ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_NAME2_(BaseName, UniquePart) BaseName##UniquePart



#define ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_NAME_(BaseName, UniquePart) \
    ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_NAME2_(BaseName, UniquePart)



#define ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_UNIQUE_NAME_(BaseName) \
    ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_NAME_(BaseName, __COUNTER__)



#define ICS46_DYNAMIC_FACTORY_REGISTER(BaseType, ObjectType, ...) \
    namespace { \
        ics46::factory::DynamicFactoryRegistration<BaseType, ObjectType> \
            ICS46_DYNAMIC_FACTORY_REGISTER_MAKE_UNIQUE_NAME_(reg) {__VA_ARGS__}; \
    }



#endif

