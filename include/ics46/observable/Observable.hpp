// Observable.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// The template class Observable<ObserverType> serves as a base class
// that provides the ability for an object to have a list of "observer"
// objects associated with it, which can be "notified" when an interesting
// event occurs.

#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>



namespace ics46::observable
{
    template <typename ObserverType>
    class Observable
    {
    public:
        using NotifyFunction = std::function<void(std::shared_ptr<ObserverType>)>;

    public:
        void addObserver(std::weak_ptr<ObserverType> observerToAdd);
        void removeObserver(std::weak_ptr<ObserverType> observerToRemove);
        void notifyObservers(NotifyFunction notifyFunction);

    private:
        std::vector<std::weak_ptr<ObserverType>> observers;
    };



    template <typename ObserverType>
    void Observable<ObserverType>::addObserver(std::weak_ptr<ObserverType> observerToAdd)
    {
        if (observerToAdd.expired())
        {
            return;
        }

        if (!std::any_of(
                observers.begin(), observers.end(),
                [=](std::weak_ptr<ObserverType> observer)
                {
                    return observer.lock() == observerToAdd.lock();
                }))
        {
            observers.push_back(observerToAdd);
        }
    }


    template <typename ObserverType>
    void Observable<ObserverType>::removeObserver(std::weak_ptr<ObserverType> observerToRemove)
    {
        if (observerToRemove.expired())
        {
            return;
        }

        observers.erase(
            std::remove_if(
                observers.begin(), observers.end(),
                [=](std::weak_ptr<ObserverType> observer)
                {
                    return observer.lock() == observerToRemove.lock();
                }),
            observers.end());
    }


    template <typename ObserverType>
    void Observable<ObserverType>::notifyObservers(NotifyFunction notifyFunction)
    {
        observers.erase(
            std::remove_if(
                observers.begin(), observers.end(),
                [=](std::weak_ptr<ObserverType> observer)
                {
                    return observer.expired();
                }),
            observers.end());

        std::for_each(
            observers.begin(), observers.end(),
            [=](std::weak_ptr<ObserverType> observer)
            {
                if (!observer.expired())
                {
                    notifyFunction(observer.lock());
                }
            });
    }
}



#endif

