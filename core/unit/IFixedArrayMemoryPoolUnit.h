#include <atomic>
#include <cstddef>
#include <new>

template <typename T, std::size_t Size>
class IFixedArrayMemoryPoolUnit {
private:
    struct Node {
        void* ptr;
        Node* next;
    };

public:
    IFixedArrayMemoryPoolUnit() = default;
    ~IFixedArrayMemoryPoolUnit();
    T* allocateArray();
    void deallocateArray(T* ptr);
    void releaseAll();
    void freeNode(Node* node);

private:
    std::atomic<Node*> head{nullptr};
};

template <typename T, std::size_t Size>
IFixedArrayMemoryPoolUnit<T, Size>::~IFixedArrayMemoryPoolUnit() {
    releaseAll();
}

template <typename T, std::size_t Size>
T* IFixedArrayMemoryPoolUnit<T, Size>::allocateArray() {
    Node* node = head.load(std::memory_order_acquire);

    while (node) {
        // 直接比较是否能使用此节点
        if (Size <= sizeof(T) * Size) {
            if (head.compare_exchange_weak(node, node->next, std::memory_order_acquire, std::memory_order_relaxed)) {
                T* ptr = static_cast<T*>(node->ptr);
                delete node;
                return ptr;
            }
        } else {
            node = node->next;
        }
    }

    // 如果栈中没有足够的内存，创建一个新的内存块
    return static_cast<T*>(::operator new(sizeof(T) * Size));
}

template <typename T, std::size_t Size>
void IFixedArrayMemoryPoolUnit<T, Size>::deallocateArray(T* ptr) {
    Node* newNode = new Node{ptr, nullptr};

    Node* oldHead = head.load(std::memory_order_acquire);
    do {
        newNode->next = oldHead;
    } while (!head.compare_exchange_weak(oldHead, newNode, std::memory_order_release, std::memory_order_relaxed));
}

template <typename T, std::size_t Size>
void IFixedArrayMemoryPoolUnit<T, Size>::releaseAll() {
    Node* node = head.exchange(nullptr, std::memory_order_acquire);
    freeNode(node);
}

template <typename T, std::size_t Size>
void IFixedArrayMemoryPoolUnit<T, Size>::freeNode(Node* node) {
    while (node) {
        ::operator delete(node->ptr);
        Node* temp = node;
        node = node->next;
        delete temp;
    }
}
