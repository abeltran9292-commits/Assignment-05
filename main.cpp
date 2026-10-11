#include <iostream>
#include <stdexcept>
#include <string>

// All six structures store integers and are implemented without STL ADTs.

class ArrayStack {
private:
    int* data_;
    std::size_t capacity_;
    std::size_t size_;

    void grow() {
        const std::size_t newCapacity = capacity_ * 2;
        int* replacement = new int[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) replacement[i] = data_[i];
        delete[] data_;
        data_ = replacement;
        capacity_ = newCapacity;
    }

public:
    explicit ArrayStack(std::size_t capacity = 4)
        : data_(new int[capacity ? capacity : 1]),
          capacity_(capacity ? capacity : 1), size_(0) {}

    ~ArrayStack() { delete[] data_; }
    ArrayStack(const ArrayStack&) = delete;
    ArrayStack& operator=(const ArrayStack&) = delete;

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void push(int value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }

    int pop() {
        if (empty()) throw std::underflow_error("pop from empty ArrayStack");
        return data_[--size_];
    }

    int top() const {
        if (empty()) throw std::underflow_error("top of empty ArrayStack");
        return data_[size_ - 1];
    }
};

class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v, Node* n) : value(v), next(n) {}
    };

    Node* top_ = nullptr;
    std::size_t size_ = 0;

public:
    ~LinkedStack() {
        while (top_) {
            Node* old = top_;
            top_ = top_->next;
            delete old;
        }
    }

    LinkedStack() = default;
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    bool empty() const { return top_ == nullptr; }
    std::size_t size() const { return size_; }

    void push(int value) {
        top_ = new Node(value, top_);
        ++size_;
    }

    int pop() {
        if (empty()) throw std::underflow_error("pop from empty LinkedStack");
        Node* old = top_;
        int value = old->value;
        top_ = old->next;
        delete old;
        --size_;
        return value;
    }

    int top() const {
        if (empty()) throw std::underflow_error("top of empty LinkedStack");
        return top_->value;
    }
};

class ArrayQueue {
private:
    int* data_;
    std::size_t capacity_, size_, front_;

    void grow() {
        const std::size_t newCapacity = capacity_ * 2;
        int* replacement = new int[newCapacity];

        for (std::size_t i = 0; i < size_; ++i) {
            replacement[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = replacement;
        capacity_ = newCapacity;
        front_ = 0;
    }

public:
    explicit ArrayQueue(std::size_t capacity = 4)
        : data_(new int[capacity ? capacity : 1]),
          capacity_(capacity ? capacity : 1), size_(0), front_(0) {}

    ~ArrayQueue() { delete[] data_; }
    ArrayQueue(const ArrayQueue&) = delete;
    ArrayQueue& operator=(const ArrayQueue&) = delete;

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void enqueue(int value) {
        if (size_ == capacity_) grow();
        data_[(front_ + size_) % capacity_] = value;
        ++size_;
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("dequeue from empty ArrayQueue");
        int value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return value;
    }

    int front() const {
        if (empty()) throw std::underflow_error("front of empty ArrayQueue");
        return data_[front_];
    }
};

class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;
        explicit Node(int v) : value(v), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    ~LinkedQueue() {
        while (head_) {
            Node* old = head_;
            head_ = head_->next;
            delete old;
        }
    }

    LinkedQueue() = default;
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    void enqueue(int value) {
        Node* node = new Node(value);
        if (tail_) tail_->next = node;
        else head_ = node;
        tail_ = node;
        ++size_;
    }

    int dequeue() {
        if (empty()) throw std::underflow_error("dequeue from empty LinkedQueue");
        Node* old = head_;
        int value = old->value;
        head_ = old->next;
        if (!head_) tail_ = nullptr;
        delete old;
        --size_;
        return value;
    }

    int front() const {
        if (empty()) throw std::underflow_error("front of empty LinkedQueue");
        return head_->value;
    }
};

class ArrayDeque {
private:
    int* data_;
    std::size_t capacity_, size_, front_;

    void grow() {
        const std::size_t newCapacity = capacity_ * 2;
        int* replacement = new int[newCapacity];

        for (std::size_t i = 0; i < size_; ++i) {
            replacement[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = replacement;
        capacity_ = newCapacity;
        front_ = 0;
    }

public:
    explicit ArrayDeque(std::size_t capacity = 4)
        : data_(new int[capacity ? capacity : 1]),
          capacity_(capacity ? capacity : 1), size_(0), front_(0) {}

    ~ArrayDeque() { delete[] data_; }
    ArrayDeque(const ArrayDeque&) = delete;
    ArrayDeque& operator=(const ArrayDeque&) = delete;

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void pushBack(int value) {
        if (size_ == capacity_) grow();
        data_[(front_ + size_) % capacity_] = value;
        ++size_;
    }

    void pushFront(int value) {
        if (size_ == capacity_) grow();
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = value;
        ++size_;
    }

    int popFront() {
        if (empty()) throw std::underflow_error("popFront from empty ArrayDeque");
        int value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return value;
    }

    int popBack() {
        if (empty()) throw std::underflow_error("popBack from empty ArrayDeque");
        const std::size_t index = (front_ + size_ - 1) % capacity_;
        int value = data_[index];
        --size_;
        return value;
    }

    int front() const {
        if (empty()) throw std::underflow_error("front of empty ArrayDeque");
        return data_[front_];
    }

    int back() const {
        if (empty()) throw std::underflow_error("back of empty ArrayDeque");
        return data_[(front_ + size_ - 1) % capacity_];
    }
};

class LinkedDeque {
private:
    struct Node {
        int value;
        Node* prev;
        Node* next;

        explicit Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    ~LinkedDeque() {
        while (head_) {
            Node* old = head_;
            head_ = head_->next;
            delete old;
        }
    }

    LinkedDeque() = default;
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = head_;

        if (head_) head_->prev = node;
        else tail_ = node;

        head_ = node;
        ++size_;
    }

    void pushBack(int value) {
        Node* node = new Node(value);
        node->prev = tail_;

        if (tail_) tail_->next = node;
        else head_ = node;

        tail_ = node;
        ++size_;
    }

    int popFront() {
        if (empty()) throw std::underflow_error("popFront from empty LinkedDeque");
        Node* old = head_;
        int value = old->value;
        head_ = old->next;

        if (head_) head_->prev = nullptr;
        else tail_ = nullptr;

        delete old;
        --size_;
        return value;
    }

    int popBack() {
        if (empty()) throw std::underflow_error("popBack from empty LinkedDeque");
        Node* old = tail_;
        int value = old->value;
        tail_ = old->prev;

        if (tail_) tail_->next = nullptr;
        else head_ = nullptr;

        delete old;
        --size_;
        return value;
    }

    int front() const {
        if (empty()) throw std::underflow_error("front of empty LinkedDeque");
        return head_->value;
    }

    int back() const {
        if (empty()) throw std::underflow_error("back of empty LinkedDeque");
        return tail_->value;
    }
};

template <typename Function>
void verifyEmptyThrows(const std::string& label, Function operation) {
    try {
        operation();
        std::cout << label << ": ERROR (no exception)\n";
    } catch (const std::underflow_error&) {
        std::cout << label << ": caught underflow_error\n";
    }
}

int main() {
    std::cout << "Empty-case checks\n";

    ArrayStack as;
    verifyEmptyThrows("ArrayStack.pop", [&] { as.pop(); });

    LinkedStack ls;
    verifyEmptyThrows("LinkedStack.pop", [&] { ls.pop(); });

    ArrayQueue aq;
    verifyEmptyThrows("ArrayQueue.dequeue", [&] { aq.dequeue(); });

    LinkedQueue lq;
    verifyEmptyThrows("LinkedQueue.dequeue", [&] { lq.dequeue(); });

    ArrayDeque ad;
    verifyEmptyThrows("ArrayDeque.popFront", [&] { ad.popFront(); });

    LinkedDeque ld;
    verifyEmptyThrows("LinkedDeque.popBack", [&] { ld.popBack(); });

    std::cout << "\nOperation sequences (each line has at least 10 operations)\n";

    as.push(1);
    as.push(2);
    as.push(3);
    as.push(4);
    as.push(5); // forces growth

    std::cout << "ArrayStack pops: "
              << as.pop() << ' ' << as.pop() << ' '
              << as.pop() << ' ' << as.pop() << ' ' << as.pop() << "\n";

    ls.push(10);
    ls.push(20);
    ls.push(30);
    ls.push(40);
    ls.push(50);

    std::cout << "LinkedStack pops: "
              << ls.pop() << ' ' << ls.pop() << ' '
              << ls.pop() << ' ' << ls.pop() << ' ' << ls.pop() << "\n";

    aq.enqueue(1);
    aq.enqueue(2);
    aq.enqueue(3);
    aq.enqueue(4);
    aq.dequeue();
    aq.dequeue();
    aq.enqueue(5);
    aq.enqueue(6);
    aq.enqueue(7);
    aq.enqueue(8); // wraparound then growth

    std::cout << "ArrayQueue dequeues: "
              << aq.dequeue() << ' ' << aq.dequeue() << ' '
              << aq.dequeue() << ' ' << aq.dequeue() << ' '
              << aq.dequeue() << ' ' << aq.dequeue() << "\n";

    lq.enqueue(11);
    lq.enqueue(22);
    lq.enqueue(33);
    lq.enqueue(44);
    lq.enqueue(55);

    std::cout << "LinkedQueue dequeues: "
              << lq.dequeue() << ' ' << lq.dequeue() << ' '
              << lq.dequeue() << ' ' << lq.dequeue() << ' '
              << lq.dequeue() << "\n";

    ad.pushBack(1);
    ad.pushBack(2);
    ad.pushFront(0);
    ad.pushBack(3);
    ad.pushFront(-1);

    std::cout << "ArrayDeque removals: "
              << ad.popFront() << ' ' << ad.popBack() << ' '
              << ad.popFront() << ' ' << ad.popBack() << ' '
              << ad.popFront() << "\n";

    ld.pushBack(7);
    ld.pushFront(6);
    ld.pushBack(8);
    ld.pushFront(5);
    ld.pushBack(9);

    std::cout << "LinkedDeque removals: "
              << ld.popFront() << ' ' << ld.popBack() << ' '
              << ld.popFront() << ' ' << ld.popBack() << ' '
              << ld.popFront() << "\n";

    return 0;
}