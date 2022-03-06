// UnregisteredNameException.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// An exception thrown by DynamicFactories when an attempt is made to create
// an object using an unregistered name.  For example, if the name "Student"
// hasn't previously been registered with DynamicFactory<Person>, this call
// would throw an UnregisteredNameException.
//
//     ics46::factory::DynamicFactory<Person>::instance().make("Student");

#ifndef UNREGISTEREDNAMEEXCEPTION_HPP
#define UNREGISTEREDNAMEEXCEPTION_HPP

#include <string>



namespace ics46::factory
{
    class UnregisteredNameException
    {
    public:
        UnregisteredNameException(const std::string& name);
        const std::string& name() const;

    private:
        std::string name_;
    };


    
    inline UnregisteredNameException::UnregisteredNameException(const std::string& name)
        : name_{name}
    {
    }


    inline const std::string& UnregisteredNameException::name() const
    {
        return name_;
    }
}



#endif

