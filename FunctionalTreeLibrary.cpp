#include <iostream>
#include <string>
#include <functional>

using namespace std;

using tree_t=function<const void*(function<const void*(const void*,const void*,const void*)>)>;

template<typename T>
tree_t make_tree(const void* left, const T* val, const void* right) {
    return [=](function<const void*(const void*,const void*,const void*)> f) {
        return f(left, (const void*)val, right);
    };
}

template<typename T>
const tree_t* Tree(const void* left, const T* val, const void* right) {
    return new auto(make_tree(left, val, right));
}

template<typename T>
const tree_t* Leaf(const T* val) {
    return Tree(nullptr, val, nullptr);
}

template<typename T>
T TreeVal(const tree_t* tree) {
    return *(const T*)((*tree)([](const void* left, const void* val, const void* right) {
        return val;
    }));
}

template<typename T>
const T* TreeValPointer(const tree_t* tree) {
    return (const T*)((*tree)([](const void* left, const void* val, const void* right) {
        return val;
    }));
}

const tree_t* TreeLeft(const tree_t* tree) {
    return (const tree_t*)((*tree)([](const void* left, const void* val, const void* right) {
        return left;
    }));
}

const tree_t* TreeRight(const tree_t* tree) {
    return (const tree_t*)((*tree)([](const void* left, const void* val, const void* right) {
        return right;
    }));
}

template <typename T>
string traversal(const tree_t* tree) {
    if (TreeLeft(tree) == nullptr && TreeRight(tree) == nullptr) {
        return to_string(TreeVal<T>(tree));
    }
    if (TreeLeft(tree) == nullptr) {
        return to_string(TreeVal<T>(tree)) + string(" ") + traversal<T>(TreeRight(tree));
    }
    if (TreeRight(tree) == nullptr) {
        return traversal<T>(TreeLeft(tree)) + string(" ") + to_string(TreeVal<T>(tree));
    }
    return traversal<T>(TreeLeft(tree)) + string(" ") + to_string(TreeVal<T>(tree)) + string(" ") + traversal<T>(TreeRight(tree));
}

template<typename T>
void deallocate(const tree_t* tree) {
    if (nullptr == tree) return;
    deallocate<T>(TreeLeft(tree));
    deallocate<T>(TreeRight(tree));
    delete TreeValPointer<T>(tree);
    delete tree;
}

int main()
{
    const auto t = Tree<int>(Leaf<int>(new int(6)), new int(8), Tree<int>(Leaf<int>(new int(4)), new int(7), Leaf<int>(new int(5))));
    cout << traversal<int>(t) << endl; // prints 6 8 4 7 5!!!!!
    deallocate<int>(t);
    return 0;
}

