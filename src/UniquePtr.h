#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <utility>
#include <cassert>

//sources 
// https://www.geeksforgeeks.org/cpp/templates-cpp/  :  Creating class template
// https://stackoverflow.com/questions/3106110/what-is-move-semantics : information and code examples about move semantics
// https://en.cppreference.com/cpp/utility/forward : for information about perfect forwarding

// Your implementation here
template <typename T> 
class UniquePtr {
private:
    T* ptr;
    template <typename U> //
    friend class UniquePtr; //
public:
    UniquePtr(): ptr(nullptr) {}
    UniquePtr(T* val): ptr(val) {}

    //copy constructor
    UniquePtr(const UniquePtr& ptr) = delete;

    //move constructor
    UniquePtr(UniquePtr&& temp) {
        ptr = temp.ptr;
        temp.ptr = nullptr;
    }

    //converting constructor
    template <typename U> //
    UniquePtr(UniquePtr<U>&& temp){
        ptr = temp.ptr;
        temp.ptr = nullptr;
    }

    //copy assignment 
    UniquePtr& operator=(const UniquePtr& newPtr) = delete;

    //move assignment
    UniquePtr& operator=(UniquePtr&& tempPtr){
        if (this != &tempPtr){
            delete ptr;
            ptr = tempPtr.ptr;
            tempPtr.ptr = nullptr;
            return *this; //
        }
        return *this;
    }

    //destructor
    ~UniquePtr() {
        delete ptr;
    }

    T& operator*()const{
        assert(ptr != nullptr);
        return *ptr;
    }

    T* operator->() const{
        assert(ptr != nullptr);
        return ptr;
    }

    T* get() const{
        return ptr;
    }

    bool operator==(const UniquePtr& secondPtr) const {
        return ptr == secondPtr.ptr;
    }

    T* release(){
        T* tempPtr = ptr;
        ptr = nullptr;
        return tempPtr;
    }

    void reset(T* newPtr = nullptr){
        assert(newPtr != ptr || newPtr == nullptr); //
        delete ptr;
        ptr = newPtr;
    }
    
    void swap(UniquePtr<T>& other){
        T* temp = other.ptr;
        other.ptr = ptr;
        ptr = temp;
    }

    explicit operator bool() const{
        return ptr!=nullptr;
    }
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...)); //
}

#endif
