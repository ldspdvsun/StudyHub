import random

class ArrayOperations:

    def __init__(self, arrs:list[int]):
        '''初始化数组'''
        self.arrs = arrs

    def random_access(self)->int:
        '''随机访问数组中的元素'''
        random_index = random.randint(0,len(self.arrs)-1)
        return self.arrs[random_index]
    
    def insert(self,index:int,value:int)->None:
        '''在数组的索引index处插入元素value'''
        for i in range(len(self.arrs)-1,index,-1):
            self.arrs[i]=self.arrs[i-1]
        self.arrs[index]=value
    
    def delete(self,index:int)->None:
        '''删除数组指定索引的元素'''
        # 此方法会导致原数组的末尾元素索引依然存在，遍历后会输出原有数组的最后一位元素
        # for i in range(index,len(self.arrs)-1):
        #     self.arrs[i]=self.arrs[i+1]
        for arr in self.arrs:
            if arr == self.arrs[index]:
                del self.arrs[index]

    def traverse(self):
        '''遍历数组'''
        for i ,arr in enumerate(self.arrs):
            print(f'index={i}, value = {arr}')

    def find(self,value:int)->int:
        '''查找数组中指定元素的索引'''
        for i,arr in enumerate(self.arrs):
            if arr == value:
                return i
            
    def extend(self,enlarge:int)->list[int]:
        '''扩展数组的大小'''
        # 初始化扩展后的数组
        res = [0]*(len(self.arrs)+enlarge)
        print(f'Extent array len {len(res)}')
        # 将原数组赋值到扩展后的数组
        for i in range(len(self.arrs)):
            res[i]=self.arrs[i]
        self.arrs = res


print('========== 1. 遍历数组 ==========')
arrs = ArrayOperations([1,2,3,4,5])
arrs.traverse()

print('========== 2. 随机访问数组 ==========')
print(arrs.random_access())

print('========== 3. 在数组的索引index处插入元素value ==========')  
arrs.insert(2,6)
arrs.traverse()

print('========== 4. 删除数组指定索引的元素 ==========')  
arrs.delete(2)
arrs.traverse()

print('========== 5. 查找数组中指定元素的索引 ==========')  
print(arrs.find(3))


print('========== 6. 扩展数组的大小 ==========')  
arrs.extend(3)  
arrs.traverse()
arrs.insert(4,14)
arrs.insert(5,15)
arrs.insert(6,16)
print('====================')
arrs.traverse()