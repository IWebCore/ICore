#include <atomic>
#include <cstddef>
#include <new>

template <typename T>
class IDynamicArrayMemoryPoolUnit {
private:
    struct Node {
        void* ptr;
        std::size_t size;
        Node* next;
    };

public:
    IDynamicArrayMemoryPoolUnit() = default;
    ~IDynamicArrayMemoryPoolUnit();
    T* allocateArray(std::size_t count);
    void deallocateArray(T* ptr, std::size_t count);
    void releaseAll();
    void freeNode(Node* node);

private:
    std::atomic<Node*> head{nullptr};
};

template <typename T>
IDynamicArrayMemoryPoolUnit<T>::~IDynamicArrayMemoryPoolUnit() {
    releaseAll();
}

template <typename T>
T* IDynamicArrayMemoryPoolUnit<T>::allocateArray(std::size_t count) {
    std::size_t size = sizeof(T) * count;
    Node* node = head.load(std::memory_order_acquire);

    while (node) {
        // 找到合适大小的块
        if (node->size >= size) {
            if (head.compare_exchange_weak(node, node->next, std::memory_order_acquire, std::memory_order_relaxed)) {
                // 成功分配
                T* ptr = static_cast<T*>(node->ptr);
                delete node;
                return ptr;
            }
        } else {
            node = node->next;  // 继续查找下一个节点
        }
    }

    // 如果栈中没有足够的内存，创建一个新的内存块
    return static_cast<T*>(::operator new(size));
}

template <typename T>
void IDynamicArrayMemoryPoolUnit<T>::deallocateArray(T* ptr, std::size_t count) {
    Node* newNode = new Node{ptr, sizeof(T) * count, nullptr};

    Node* oldHead = head.load(std::memory_order_acquire);
    do {
        newNode->next = oldHead;
    } while (!head.compare_exchange_weak(oldHead, newNode, std::memory_order_release, std::memory_order_relaxed));
}

template <typename T>
void IDynamicArrayMemoryPoolUnit<T>::releaseAll() {
    Node* node = head.exchange(nullptr, std::memory_order_acquire);
    freeNode(node);
}

template <typename T>
void IDynamicArrayMemoryPoolUnit<T>::freeNode(Node* node) {
    while (node) {
        ::operator delete(node->ptr);
        Node* temp = node;
        node = node->next;
        delete temp;
    }
}
