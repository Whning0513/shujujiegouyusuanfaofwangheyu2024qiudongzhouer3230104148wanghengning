# 第四次作业：链表
这次的作业就是上课做的那个双向链表。  
为了区分以及防止主测试程序崩溃，我另外建立了一个bug.cpp  
根据我一个一个看下来，没有函数被遗漏，测试程序直接或间接调用了所有函数  
根据学在浙大的通告，我猜测不希望我们对List.h删改过多，只需添加内容。所以我没有特别修改空指针等操作，也没有修改原有的内容，但是对于部分内容我在bug.cpp以及report的末尾提及了.我除了完成--，另外搞了一个print函数，用以输出链表。 但是这个print只能输出一个数据。   
如下     
void print() const  
    {  
        for (const_iterator itr = begin(); itr != end(); ++itr)  
        {  
            std::cout << *itr << " ";  // 打印每个节点的数据  
        }  
        std::cout << std::endl;  // 换行  
    }  

我在测试函数中反复使用了它。使用迭代器迭代。

根据课程作业要求，我的make没有在编译完成后删除中间产生的文件，但是能正常生成pdf。    
  
以下是valgrind的评价：  
给出了in use at exit: 0 bytes in 0 blocks       
total heap usage: 115 allocs, 115 frees       
All heap blocks were freed -- no leaks are possible      

## 一共有如下函数  

公有成员函数  
List(): 默认构造函数，初始化链表。  
List(std::initializer_list<Object> il): 使用初始化列表构造链表。  
List(const List &rhs): 拷贝构造函数，复制链表。  
~List(): 析构函数，释放链表内存。  
List &operator=(List copy): 赋值运算符，进行链表的赋值。  
List(List &&rhs): 移动构造函数，移动链表内容。    
iterator begin(): 返回指向链表第一个元素的迭代器。    
const_iterator begin() const: 返回指向链表第一个元素的只读迭代器。    
iterator end(): 返回指向链表尾部（哨兵节点）的迭代器。  
const_iterator end() const: 返回指向链表尾部的只读迭代器。  
int size() const: 返回链表中节点的数量。  
bool empty() const: 判断链表是否为空。  
void clear(): 清空链表中的所有元素。  
Object &front(): 返回链表第一个节点的数据。    
const Object &front() const: 返回链表第一个节点的只读数据。  
Object &back(): 返回链表最后一个节点的数据。  
const Object &back() const: 返回链表最后一个节点的只读数据。  
void push_front(const Object &x): 在链表头部插入元素。  
void push_front(Object &&x): 在链表头部插入右值元素。  
void push_back(const Object &x): 在链表尾部插入元素。  
void push_back(Object &&x): 在链表尾部插入右值元素。  
void pop_front(): 删除链表头部的元素。   
void pop_back(): 删除链表尾部的元素。  
iterator insert(iterator itr, const Object &x): 在指定位置插入元素。  
iterator insert(iterator itr, Object &&x): 在指定位置插入右值元素。     
iterator erase(iterator itr): 删除指定位置的节点。  
iterator erase(iterator from, iterator to): 删除指定范围内的节点。  

保护成员函数  
Object &retrieve() const: 返回当前节点的数据（仅在迭代器中使用）。    
const_iterator(Node *p): 迭代器构造函数。    
iterator(Node *p): 迭代器构造函数。    

私有成员函数  
void init(): 初始化链表的辅助函数。  

迭代器类   
const_iterator  
const_iterator(): 默认构造函数。  
const Object &operator() const*: 返回当前节点的只读数据。  
const_iterator &operator++(): 前缀递增运算符，移动到下一个节点。  
const_iterator operator++(int): 后缀递增运算符，返回旧的迭代器。  
const_iterator &operator--(): 前缀递减运算符，移动到前一个节点。  
const_iterator operator--(int): 后缀递减运算符，返回旧的迭代器。  
bool operator==(const const_iterator &rhs) const: 比较两个迭代器是否相等。  
bool operator!=(const const_iterator &rhs) const: 比较两个迭代器是否不相等。    

iterator相关  
iterator(): 默认构造函数。  
Object &operator()**: 返回当前节点的可修改数据。  
const Object &operator() const: 返回当前节点的只读数据。  
iterator &operator++(): 前缀递增运算符，移动到下一个节点。  
iterator operator++(int): 后缀递增运算符，返回旧的迭代器。  
iterator &operator--(): 前缀递减运算符，移动到前一个节点。  
iterator operator--(int): 后缀递减运算符，返回旧的迭代器。  
