#pragma once

#include <atomic>
#include <new>
#include <cstddef>
#include <type_traits>
#include <stdint.h>
#include <QtCore>

#ifndef __IObjectMemoryPoolUnit
#define __IObjectMemoryPoolUnit

template <typename T>
class IObjectMemoryPoolUnit {
private:
    // 确保 Node 结构的 data 部分满足 T 的对齐要求
    struct alignas(alignof(T)) Node {
        std::atomic<Node*> next;
        unsigned char data[sizeof(T)]; // T 的实际存储空间

        Node() : next(nullptr) {}
    };

    static_assert(alignof(Node) >= alignof(T), "Node alignment must >= T alignment");
    static_assert(sizeof(Node) >= sizeof(T), "Node size must >= T size");

    std::atomic<Node*> m_stack{nullptr};

    static Node* getNodeFromObject(T* obj) noexcept {
        constexpr size_t data_offset = offsetof(Node, data);
        return reinterpret_cast<Node*>(reinterpret_cast<char*>(obj) - data_offset);
    }

public:
    IObjectMemoryPoolUnit() = default;
    ~IObjectMemoryPoolUnit() { releaseAll(); }

    template <typename... Args>
    T* allocate(Args&&... args);

    void deallocate(T* ptr) noexcept;
    void releaseAll() noexcept;

    // 禁用拷贝和移动
    IObjectMemoryPoolUnit(const IObjectMemoryPoolUnit&) = delete;
    IObjectMemoryPoolUnit& operator=(const IObjectMemoryPoolUnit&) = delete;
};

template <typename T>
template <typename... Args>
T* IObjectMemoryPoolUnit<T>::allocate(Args&&... args) {

    return new T(std::forward<Args>(args)...);

//    Node* old_head = m_stack.load(std::memory_order_acquire);

//    // 尝试复用现有节点
//    while (old_head) {
//        Node* next_node = old_head->next.load(std::memory_order_relaxed);

//        // 使用 memory_order_acq_rel 确保操作的原子性和可见性
//        if (m_stack.compare_exchange_weak(old_head, next_node,
//                                         std::memory_order_acq_rel,
//                                         std::memory_order_acquire)) {
//            T* obj = reinterpret_cast<T*>(old_head->data);
//            try {
//                new (obj) T(std::forward<Args>(args)...);
//            } catch (...) {
//                // 构造失败时直接释放节点，避免回退到池中导致竞争
//                old_head->next.store(nullptr, std::memory_order_relaxed);
//                ::operator delete(old_head);
//                throw;
//            }
//            return obj;
//        }
//    }

    // 分配新节点
//    Node* new_node = static_cast<Node*>(::operator new(sizeof(Node)));
//    new_node->next.store(nullptr, std::memory_order_relaxed);

//    T* obj = reinterpret_cast<T*>(new_node->data);
//    try {
//        new (obj) T(std::forward<Args>(args)...);
//    } catch (...) {
//        ::operator delete(new_node);
//        throw;
//    }
//    return obj;
}

template <typename T>
void IObjectMemoryPoolUnit<T>::deallocate(T* ptr) noexcept {
    if (!ptr) return;

    delete ptr;

//    // 析构对象
//    ptr->~T();

//    Node* node = getNodeFromObject(ptr);
//    Node* old_head = m_stack.load(std::memory_order_acquire);

//    do {
//        node->next.store(old_head, std::memory_order_relaxed);
//    } while (!m_stack.compare_exchange_weak(old_head, node,
//                                          std::memory_order_release,
//                                          std::memory_order_acquire));
}

template <typename T>
void IObjectMemoryPoolUnit<T>::releaseAll() noexcept {
    Node* current = m_stack.exchange(nullptr, std::memory_order_acquire);
    while (current) {
        Node* next = current->next.load(std::memory_order_relaxed);
        T* obj = reinterpret_cast<T*>(current->data);
        obj->~T(); // 安全析构（即使 deallocate 未被调用）
        ::operator delete(current);
        current = next;
    }
}

#endif
