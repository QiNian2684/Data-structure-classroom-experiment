#include <iostream>

// 定义栈节点结构体
template<typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode(T data) : data(data), next(nullptr) {}
};

// 定义链栈结构体
template<typename T>
struct LinkedStack {
    StackNode<T>* top;
    LinkedStack() : top(nullptr) {}

    // 判断栈是否为空
    bool isEmpty() const {
        return top == nullptr;
    }

    // 入栈操作
    void push(T data) {
        StackNode<T>* node = new StackNode<T>(data);
        node->next = top;
        top = node;
        std::cout << "Element " << data << " pushed onto the stack." << std::endl;
    }

    // 出栈操作
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

    // 获取栈顶元素
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty. Cannot peek.");
        }
        std::cout << "The top element is: " << top->data << std::endl;
        return top->data;
    }

    // 析构函数，清除所有节点
    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// 主函数
int main() {
    LinkedStack<int> stack;

    // 演示入栈操作
    std::cout << "=== Pushing elements onto the stack ===" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        stack.push(i);
    }

    // 演示读取栈顶元素
    std::cout << "\n=== Peeking the top element ===" << std::endl;
    stack.peek();

    // 演示出栈操作
    std::cout << "\n=== Popping elements from the stack ===" << std::endl;
    while (!stack.isEmpty()) {
        stack.pop();
    }

    // 演示栈空检测
    std::cout << "\n=== Checking if the stack is empty ===" << std::endl;
    std::cout << "Is the stack empty? " << (stack.isEmpty() ? "Yes" : "No") << std::endl;

    // 再次演示入栈操作
    std::cout << "\n=== Pushing more elements onto the stack ===" << std::endl;
    stack.push(10);
    stack.push(20);

    // 再次演示读取栈顶元素
    std::cout << "\n=== Peeking the top element again ===" << std::endl;
    stack.peek();

    // 演示销毁栈
    std::cout << "\n=== Destroying the stack ===" << std::endl;
    // 析构函数会被自动调用，清除所有节点

    return 0;
}
