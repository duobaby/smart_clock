#include <stdint.h>
#include "page_public.h"

#define MAX_SIZE 6


template <class T>
class PageStack_t {
private:
    T pages[MAX_SIZE];  // 存储栈元素的数组
    uint8_t top;            // 栈顶指针
public:
    // 构造函数，初始化栈
    PageStack_t() {
        top = 0;  // 初始化栈顶指针为-1，表示栈为空
    }

    // 判断栈是否为空
    bool isEmpty() {
        return (top == 0);  // 栈顶指针为-1则为空
    }

    // 判断栈是否已满
    bool isFull() {
        return (top >= MAX_SIZE);  // 栈顶指针等于MAX_SIZE-1则为满
    }

    // 入栈操作
    uint8_t push(T page) {
        if (isFull()) 
            return -1;
        pages[++top] = page;  // 栈顶指针先加1，然后将元素压入栈顶
        return 0;
    }

    // 出栈操作
    uint8_t pop() {
        if (isEmpty()) 
            return -1;  // 或者返回合适的值表示失败
        pages[top--].deinit();
        return 0;
    }

    // 查看栈顶元素
    T peek() {
        if (isEmpty()) {
            return nullptr;  // 或者返回合适的值表示失败
        }
        return pages[top - 1];  // 返回栈顶元素，但不将其弹出
    }
};

PageStack_t<Page_t *> PageStack;

extern PageStack_t<Page_t *> PageStack;