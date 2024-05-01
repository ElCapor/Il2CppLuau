#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton {
public:
    static T* get() {
        static T instance; // This will be created only once
        return &instance;
    }

    // Delete copy constructor and assignment operator to prevent duplication
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};

#endif