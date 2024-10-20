/* xinji2301 whn 3230104148 10.12 */
#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node//只有单链表class能调用这个子class
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) { data = _val; }

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;


    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    T getCurrentVal() const; // 返回当前位置的值
    void setCurrentVal(const T &_val); // 设置当前位置的值
    bool isEmpty() const; // 判断链表是否为空

    int getSize() const; //获取链表大小
    void emptyList();  //清空内存
    SingleLinkedList() {}; // 默认构造函数
    ~SingleLinkedList(); // 析构函数
    SingleLinkedList(std::initializer_list<T> _l); // 初始化列表
    void printList() const; // 输出列表
    SingleLinkedList(const SingleLinkedList<T> &_l); // 拷贝构造函数
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l); // =重载
    bool find(const T &_val); // 查找元素
    void insert(T _val); // 在当前位置后插入一个元素
    void remove(); // 删除当前位置后面的元素
};


// 1. T getCurrentVal() const 实现
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos == nullptr)
    {
        // 你说的若当前位置为空，则报错"Empty current position! Can't get value!"并停止退出；
        std::cerr << "Empty current position! Can't get value!" << std::endl;
        exit(EXIT_FAILURE); // 真的退了
    }
    return currentPos->data; // 返回当前位置的值
}

// 2. void setCurrentVal(const T &_val) 实现
template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos == nullptr)
    {
        // 若当前位置为空，则报错"Empty current position! Can't setvalue!"并停止退出；
        std::cerr << "Empty current position! Can't set value!" << std::endl;
        exit(EXIT_FAILURE);
    }
    currentPos->data = _val; // set当前的值
}

// 3. bool isEmpty() const 实现 注意这里名称的改动，课上代码多了个l?
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return true ? head == nullptr : false ;
}

// 4. void insert(T _val) 实现
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node* newNode = new Node(_val);

    if (isEmpty()) // 空链表的情况,若为空链表则插入一个元素
    {
        head = newNode;
        currentPos = head;
    }
    else if (currentPos != nullptr) // 非空链表，插入到 currentPos 后面
    {
        newNode->next = currentPos->next;
        currentPos->next = newNode;
        //insert函数没有及时更新currentpos为指向新插入元素；
        //insert函数没有及时更新currentpos为指向新插入元素；
        //insert函数没有及时更新currentpos为指向新插入元素；
        currentPos = newNode;
    }
    else
    {
        std::cerr << "shituzaikongptrcharu" << std::endl;
        delete newNode; // 防止内存泄漏
        exit(EXIT_FAILURE); // 前面的报错都退出了，所以我猜这个要退出
    }

    ++size;
}

// 5. void remove() 实现
template <typename T>
void SingleLinkedList<T>::remove()
{
    if (isEmpty()) // 如果链表为空，直接返回
    {
        std::cerr << "konglianbiao" << std::endl;
        return;
    }

    if (currentPos == nullptr) // 如果当前位置为空，不进行操作
    {
        std::cerr << "kongzhizhen" << std::endl;
        return;
    }

    if (size == 1) // 如果链表只有一个元素
    {
        // 删除唯一的元素
        delete head;
        head = nullptr;
        currentPos = nullptr;
        size = 0;
        return;
    }

    if (currentPos->next == nullptr) // 如果当前位置是最后一个节点，无法删除其后节点
    {
        std::cerr << "zhegejiedianshizuihouyigejiedian" << std::endl;
        return;
    }

    // 删除 currentPos 后面的节点
    Node* nodeToDelete = currentPos->next;
    currentPos->next = nodeToDelete->next; // 让 currentPos 指向 nodeToDelete 之后的节点
    delete nodeToDelete;
    --size;
}

//原有的查找，返回true修改currentPos指向找到的节点，否则返回false
template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node* p = head;  // 从头开始遍历链表
    while (p != nullptr)
    {
        if (p->data == _val)  // 如果找到目标值
        {
            currentPos = p;  // 将 currentPos 移动到找到的节点
            return true;  // 返回 true
        }
        p = p->next;
    }
    return false;  // 没找到目标值，返回 false
}

//getsize
template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

//最重要的构造函数实现
template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

//也很重要的清空列表，保证没有剩内存
template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

//输出列表，tab分隔
template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

//析构函数
template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}