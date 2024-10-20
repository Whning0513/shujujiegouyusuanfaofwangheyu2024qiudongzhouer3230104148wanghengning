您好  

我们这个就是上课做的那个双向链表。  

我除了完成--，另外搞了一个print函数，用以输出链表。  
这个print只能输出一个数据，但是挺方便的    
void print() const  
    {  
        for (const_iterator itr = begin(); itr != end(); ++itr)  
        {  
            std::cout << *itr << " ";  // 打印每个节点的数据  
        }  
        std::cout << std::endl;  // 换行  
    }  

我在测试函数中反复使用了它。使用迭代器迭代。

我的make没有在编译完成后删除中间产生的文件，但是能正常生成pdf。  

  
#  一共有如下函数  
## 公有成员函数
1. **List()**: 默认构造函数，初始化链表。
2. **List(std::initializer_list<Object> il)**: 使用初始化列表构造链表。
3. **List(const List &rhs)**: 拷贝构造函数，复制链表。
4. **~List()**: 析构函数，释放链表内存。
5. **List &operator=(List copy)**: 赋值运算符，进行链表的赋值。
6. **List(List &&rhs)**: 移动构造函数，移动链表内容。
7. **iterator begin()**: 返回指向链表第一个元素的迭代器。
8. **const_iterator begin() const**: 返回指向链表第一个元素的只读迭代器。
9. **iterator end()**: 返回指向链表尾部（哨兵节点）的迭代器。
10. **const_iterator end() const**: 返回指向链表尾部的只读迭代器。
11. **int size() const**: 返回链表中节点的数量。
12. **bool empty() const**: 判断链表是否为空。
13. **void clear()**: 清空链表中的所有元素。
14. **Object &front()**: 返回链表第一个节点的数据。
15. **const Object &front() const**: 返回链表第一个节点的只读数据。
16. **Object &back()**: 返回链表最后一个节点的数据。
17. **const Object &back() const**: 返回链表最后一个节点的只读数据。
18. **void push_front(const Object &x)**: 在链表头部插入元素。
19. **void push_front(Object &&x)**: 在链表头部插入右值元素。
20. **void push_back(const Object &x)**: 在链表尾部插入元素。
21. **void push_back(Object &&x)**: 在链表尾部插入右值元素。
22. **void pop_front()**: 删除链表头部的元素。
23. **void pop_back()**: 删除链表尾部的元素。
24. **iterator insert(iterator itr, const Object &x)**: 在指定位置插入元素。
25. **iterator insert(iterator itr, Object &&x)**: 在指定位置插入右值元素。
26. **iterator erase(iterator itr)**: 删除指定位置的节点。
27. **iterator erase(iterator from, iterator to)**: 删除指定范围内的节点。

## 保护成员函数
- **Object &retrieve() const**: 返回当前节点的数据（仅在迭代器中使用）。
- **const_iterator(Node *p)**: 迭代器构造函数。
- **iterator(Node *p)**: 迭代器构造函数。

## 私有成员函数
- **void init()**: 初始化链表的辅助函数。

## 迭代器类
### const_iterator
1. **const_iterator()**: 默认构造函数。
2. **const Object &operator*() const**: 返回当前节点的只读数据。
3. **const_iterator &operator++()**: 前缀递增运算符，移动到下一个节点。
4. **const_iterator operator++(int)**: 后缀递增运算符，返回旧的迭代器。
5. **const_iterator &operator--()**: 前缀递减运算符，移动到前一个节点。
6. **const_iterator operator--(int)**: 后缀递减运算符，返回旧的迭代器。
7. **bool operator==(const const_iterator &rhs) const**: 比较两个迭代器是否相等。
8. **bool operator!=(const const_iterator &rhs) const**: 比较两个迭代器是否不相等。

### iterator
1. **iterator()**: 默认构造函数。
2. **Object &operator*()**: 返回当前节点的可修改数据。
3. **const Object &operator*() const**: 返回当前节点的只读数据。
4. **iterator &operator++()**: 前缀递增运算符，移动到下一个节点。
5. **iterator operator++(int)**: 后缀递增运算符，返回旧的迭代器。
6. **iterator &operator--()**: 前缀递减运算符，移动到前一个节点。
7. **iterator operator--(int)**: 后缀递减运算符，返回旧的迭代器。
