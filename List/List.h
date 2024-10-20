#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>
#include <initializer_list>
#include <iostream>

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data;     // 存放数据
        Node *prev;     // 指向前一个节点
        Node *next;     // 指向后一个节点

        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator
    {
    public:
        const_iterator() : current{nullptr} {}

        const Object &operator*() const
        {
            return retrieve();
        }

        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator &operator--()
        {
            current = current->prev; 
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator old = *this; 
            --(*this);  
            return old; 
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        Node *current;  // 当前节点

        Object &retrieve() const
        {
            return current->data;  // 返回当前节点数据
        }

        const_iterator(Node *p) : current{p} {}

        friend class List<Object>;  // 允许 List 访问
    };

    class iterator : public const_iterator
    {
    public:
        iterator() {}

        Object &operator*()
        {
            return const_iterator::retrieve();  // 返回可修改数据
        }

        const Object &operator*() const
        {
            return const_iterator::operator*();  // 返回只读数据
        }

        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--()
        {
            this->current = this->current->prev;  // 将当前节点指向前一个节点
            return *this;
        }

        iterator operator--(int)
        {
            iterator old = *this;
            --(*this);  // 调用前缀递减运算符
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator{p} {}

        friend class List<Object>;  // 允许 List 访问
    };

public:
    List() { init(); }  // 默认构造函数

    List(std::initializer_list<Object> il) : List()
    {
        for (const auto &x : il)
            push_back(x);  // 初始化列表构造
    }

    List(const List &rhs)
    {
        init();  // 拷贝构造函数
        for (auto &x : rhs)
            push_back(x);
    }

    ~List()
    {
        clear();  // 析构函数，释放内存
        delete head;
        delete tail;
    }

    List &operator=(List copy)
    {
        std::swap(theSize, copy.theSize);
        std::swap(head, copy.head);
        std::swap(tail, copy.tail);
        return *this;  // 赋值运算符
    }

    List(List &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;  // 移动构造函数
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    iterator begin()
    {
        return {head->next};  // 返回第一个元素的迭代器
    }

    const_iterator begin() const
    {
        return {head->next};  // 返回第一个元素的只读迭代器
    }

    iterator end()
    {
        return {tail};  // 返回尾部（哨兵节点）的迭代器
    }

    const_iterator end() const
    {
        return {tail};  // 返回尾部的只读迭代器
    }

    int size() const
    {
        return theSize;  // 返回节点总数
    }

    bool empty() const
    {
        return size() == 0;  // 判断是否为空
    }

    void clear()
    {
        while (!empty())
            pop_front();  // 清空列表
    }

    Object &front()
    {
        return *begin();  // 返回第一个节点的数据
    }

    const Object &front() const
    {
        return *begin();  // 返回第一个节点的只读数据
    }

    Object &back()
    {
        return *--end();  // 返回最后一个节点的数据
    }

    const Object &back() const
    {
        return *--end();  // 返回最后一个节点的只读数据
    }

    void push_front(const Object &x)
    {
        insert(begin(), x);  // 在头部插入元素
    }

    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));  // 在头部插入右值元素
    }

    void push_back(const Object &x)
    {
        insert(end(), x);  // 在尾部插入元素
    }

    void push_back(Object &&x)
    {
        insert(end(), std::move(x));  // 在尾部插入右值元素
    }

    void pop_front()
    {
        erase(begin());  // 删除头部元素
    }

    void pop_back()
    {
        erase(--end());  // 删除尾部元素
    }

    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{x, p->prev, p}};  // 插入左值元素
    }

    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};  // 插入右值元素
    }

    iterator erase(iterator itr)
    {
        Node *p = itr.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;  // 删除指定节点
        theSize--;
        return retVal;  // 返回下一个节点的迭代器
    }

    iterator erase(iterator from, iterator to)
    {
        for (iterator itr = from; itr != to;)
            itr = erase(itr);  // 删除指定范围的节点
        return to;
    }

    void print() const
    {
        for (const_iterator itr = begin(); itr != end(); ++itr)
        {
            std::cout << *itr << " ";  // 打印每个节点的数据
        }
        std::cout << std::endl;  // 换行
    }

private:
    int theSize;     // 数据节点总数
    Node *head;      // 头指针
    Node *tail;      // 尾指针

    void init()
    {
        theSize = 0;  // 初始化列表
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#else
#endif
