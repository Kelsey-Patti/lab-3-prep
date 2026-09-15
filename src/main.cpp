#include "UniquePtr.h"
#include <iostream>
#include <cassert>
#include <utility>

int main() {
    
    UniquePtr<int> ptr;
    assert(!ptr);
    assert(ptr.get() == nullptr);

    UniquePtr<int> ptr2(new int(7));
    assert(ptr2.get() != nullptr);
    assert(*ptr2 ==7);

    *ptr2 = 10;
    assert(*ptr2.get() == 10);

    UniquePtr<int> ptr3(new int(10));
    UniquePtr<int> ptr4(new int(20));

    ptr3.swap(ptr4);

    assert(*ptr3 == 20);
    assert(*ptr4 == 10);


    return 0;
}
