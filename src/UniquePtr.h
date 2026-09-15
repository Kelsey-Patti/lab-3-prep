#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <utility>
#include <cassert>

//sources 
// https://www.geeksforgeeks.org/cpp/templates-cpp/  :  Creating class template and helped with constructor classes 
// https://stackoverflow.com/questions/3106110/what-is-move-semantics : information and code examples about move semantics
// https://en.cppreference.com/cpp/utility/forward : for information about perfect forwarding
// https://www.geeksforgeeks.org/cpp/const-member-functions-c/ : information about when to make a function const
// https://en.cppreference.com/cpp/language/friend?utm_source=chatgpt.com : for information about using template <typename U> friend class UniquePtr; in private
// https://www.geeksforgeeks.org/cpp/use-of-explicit-keyword-in-cpp/?utm_source=chatgpt.com : information about when to use explicit 

// Your implementation here
template <typename T>  
class UniquePtr {
private:
    T* ptr;
    template <typename U> 
    friend class UniquePtr; 
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
    template <typename U> 
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

    //dereference operator
    T& operator*()const{
        assert(ptr != nullptr);
        return *ptr;
    }

    //arrow operator
    T* operator->() const{
        assert(ptr != nullptr);
        return ptr;
    }

    // get the raw pointer
    T* get() const{
        return ptr;
    }

    // check if two UniquePtr have the same raw pointer
    bool operator==(const UniquePtr& secondPtr) const {
        return ptr == secondPtr.ptr;
    }

    //releases ownership of raw pointer
    T* release(){
        T* tempPtr = ptr;
        ptr = nullptr;
        return tempPtr;
    }

    //reset the raw pointer to a new value
    void reset(T* newPtr = nullptr){
        assert(newPtr != ptr || newPtr == nullptr); 
        delete ptr;
        ptr = newPtr;
    }
    
    //swaps the raw pointers of two UniquePtrs
    void swap(UniquePtr<T>& other){
        T* temp = other.ptr;
        other.ptr = ptr;
        ptr = temp;
    }

    // checks if the raw pointer is non-empty
    explicit operator bool() const{ //used chatGPT to find the keyword explicit then used https://www.geeksforgeeks.org/cpp/use-of-explicit-keyword-in-cpp/?utm_source=chatgpt.com to find how and why to use it
        return ptr!=nullptr;
    }
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...)); // used ChatGPT to find syntax for forwarding a variable number of arguments
}

#endif
