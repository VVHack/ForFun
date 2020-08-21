#include <iostream>
#include <string>
#include <functional>

using namespace std;

using tree_t=function<const void*(function<const void*(const void*,long,const void*)>)>;

tree_t Tree(const void* left, long val, const void* right) {
    return [=](function<const void*(const void*,int,const void*)> f) {
        return f(left, val, right);
    };
}

tree_t Leaf(long val) {
    return Tree(nullptr, val, nullptr);
}

long TreeVal(const tree_t* tree) {
    return (long)((*tree)([](const void* left, long val, const void* right) {
        return (const void*)val;
    }));
}

const tree_t* TreeLeft(const tree_t* tree) {
    return (const tree_t*)((*tree)([](const void* left, long val, const void* right) {
        return left;
    }));
}

const tree_t* TreeRight(const tree_t* tree) {
    return (const tree_t*)((*tree)([](const void* left, long val, const void* right) {
        return right;
    }));
}

string traversal(const tree_t* tree) {
    if (TreeLeft(tree) == nullptr && TreeRight(tree) == nullptr) {
        return to_string(TreeVal(tree));
    }
    if (TreeLeft(tree) == nullptr) {
        return to_string(TreeVal(tree)) + string(" ") + traversal(TreeRight(tree));
    }
    if (TreeRight(tree) == nullptr) {
        return traversal(TreeLeft(tree)) + string(" ") + to_string(TreeVal(tree));
    }
    return traversal(TreeLeft(tree)) + string(" ") + to_string(TreeVal(tree)) + string(" ") + traversal(TreeRight(tree));
}

int main()
{
    const auto l1 = Leaf(5);
    const auto l2 = Leaf(6);
    const auto t1 = Tree(&l1, 3, &l2);
    const auto l3 = Leaf(7);
    const auto l4 = Leaf(9);
    const auto t2 = Tree(&l3, 4, &l4);
    const auto t3 = Tree(&t1, 8, &t2);
    cout << traversal(&t3) << endl; // prints 5 3 6 8 7 4 9 !!!
    return 0;
}
