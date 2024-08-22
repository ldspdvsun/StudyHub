class ListNode:
    '''链表节点类'''
    def __init__(self, val: int):
        self.val = val  # 节点值    
        self.next: ListNode | None = None  # 指向下一个节点的指针

    def insert(self, P: 'ListNode'):
        '''在当前节点self后插入新节点P'''
        P.next = self.next  # 让P的next指向当前节点self的下一个节点
        self.next = P  # 让当前节点self的next指向P

    def delete(self, P: 'ListNode'):
        '''删除节点P'''
        if self.next == P:  # 如果P是当前节点的下一个节点
            self.next = P.next  # 让当前节点的next指向P的下一个节点
        else:
            current = self  # 从当前节点开始遍历
            while current.next and current.next != P:  # 遍历链表，找到P的前一个节点
                current = current.next
            # 如果找到P的前一个节点，删除P
            if current.next == P:
                current.next = P.next  # 让P的前一个节点的next指向P的下一个节点

    def __iter__(self):
        '''定义链表的迭代器'''
        current = self  # 从当前节点开始
        while current:  # 当current不为None时
            yield current  # 返回当前节点
            current = current.next  # 移动到下一个节点

    def traverse(self):
        '''遍历链表'''
        current = self
        for i,current in enumerate(self):
            print(f'i = {i}, val = {current.val}')

    def access(self,index:int)->'ListNode':
        '''访问链表的第 index 个节点'''
        current = self
        for i in range(index):
            current = current.next
        return current
    
    def find(self,value:int)->int:
        '''查找链表中值为value的节点的索引'''
        current = self
        for i,current in enumerate (self):
            if current.val == value:
                return i
        return -1

# 示例使用
if __name__ == "__main__":
    print('========== 1. 初始化链表 0 -> 1 -> 2 -> 3 -> 4 ==========')
    # 初始化各个节点
    n0 = ListNode(0)
    n1 = ListNode(1)
    n2 = ListNode(2)
    n3 = ListNode(3)
    n4 = ListNode(4)
    

    # 构建节点之间的引用
    n0.next = n1
    n1.next = n2
    n2.next = n3
    n3.next = n4

    # 遍历链表并打印节点值
    n0.traverse()

    print('========== 2. 插入节点 ==========')
    # 在n1后插入n5
    n5 = ListNode('aa')
    n4.insert(n5)
    n0.traverse()
    print('========== 3. 删除节点 ==========')
    # 删除n2
    n0.delete(n2)
    n0.delete(n1)
    n0.traverse()
    print('========== 4. 访问节点 ==========')
    # 访问第3个节点
    print(n1.access(2).val)
    print('========== 5. 查找节点 ==========')
    # 查找值为3的节点的索引
    print(n0.find(3))    # 输出 1
