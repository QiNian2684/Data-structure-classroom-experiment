#include <iostream>

// ����ջ�ڵ�ṹ��
template<typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode(T data) : data(data), next(nullptr) {}
};

// ������ջ�ṹ��
template<typename T>
struct LinkedStack {
    StackNode<T>* top;
    LinkedStack() : top(nullptr) {}

    // �ж�ջ�Ƿ�Ϊ��
    bool isEmpty() const {
        return top == nullptr;
    }

    // ��ջ����
    void push(T data) {
        StackNode<T>* node = new StackNode<T>(data);
        node->next = top;
        top = node;
        std::cout << "Element " << data << " pushed onto the stack." << std::endl;
    }

    // ��ջ����
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty. Cannot pop.");
        }
        StackNode<T>* node = top;
        T data = node->data;
        top = top->next;
        delete node;
        std::cout << "Element " << data << " popped from the stack." << std::endl;
        return data;
    }

    // ��ȡջ��Ԫ��
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty. Cannot peek.");
        }
        std::cout << "The top element is: " << top->data << std::endl;
        return top->data;
    }

    // ����������������нڵ�
    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// ������
int main() {
    LinkedStack<int> stack;

    // ��ʾ��ջ����
    std::cout << "=== Pushing elements onto the stack ===" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        stack.push(i);
    }

    // ��ʾ��ȡջ��Ԫ��
    std::cout << "\n=== Peeking the top element ===" << std::endl;
    stack.peek();

    // ��ʾ��ջ����
    std::cout << "\n=== Popping elements from the stack ===" << std::endl;
    while (!stack.isEmpty()) {
        stack.pop();
    }

    // ��ʾջ�ռ��
    std::cout << "\n=== Checking if the stack is empty ===" << std::endl;
    std::cout << "Is the stack empty? " << (stack.isEmpty() ? "Yes" : "No") << std::endl;

    // �ٴ���ʾ��ջ����
    std::cout << "\n=== Pushing more elements onto the stack ===" << std::endl;
    stack.push(10);
    stack.push(20);

    // �ٴ���ʾ��ȡջ��Ԫ��
    std::cout << "\n=== Peeking the top element again ===" << std::endl;
    stack.peek();

    // ��ʾ����ջ
    std::cout << "\n=== Destroying the stack ===" << std::endl;
    // ���������ᱻ�Զ����ã�������нڵ�

    return 0;
}
