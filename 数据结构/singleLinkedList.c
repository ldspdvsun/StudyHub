#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int data;
} list;

list *create_list() {
    // 创建一个新的节点，由于使用typedef关键字，此处node *head与struct Node *head等价
    list *head = (list *)malloc(sizeof(list));
    if (head == NULL) {
        return NULL;
    }
    // 初始化节点
    head->data = 0; // 头节点数据域，我们用来表示链表长度
    head->next = NULL;
    return head;
}

list *list_insert_node(list *head, int data, int pos) {
    int i;
    list *curr = head;

    // 如果要插入的位置比链表长，则属于非法操作
    if (pos > curr->data) {
        return NULL;
    }

    // 创建一个节点，并初始化
    list *node = (list *)malloc(sizeof(list));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    // 遍历链表，找到要插入的位置
    for (i = 0; i < pos; i++) {
        curr = curr->next;
    }

    // 插入
    node->next = curr->next;
    curr->next = node;

    // 链表长度加1
    head->data++;

    return head;
}

// 打印链表数据，不包括头节点的数据
void print_list(list *head) {
    list *curr = head->next;
    while (curr) {
        printf("%d \t", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// 单链表的删除
list *list_delete_data(list *head, int pos) {
    list *curr = head;
    // 如果要删除的位置比链表长，则属于非法操作
    if (pos >= curr->data) {
        return NULL;
    }

    // 遍历链表，找到要删除节点的前一个指针
    for (int i = 0; i < pos; i++) {
        curr = curr->next;
    }

    // 临时记录将被删除的节点
    list *temp = curr->next;
    // 删除节点
    curr->next = curr->next->next;

    // 释放掉被删除节点后的内容
    free(temp);
    head->data--;
    return head;
}

int main() {
    list *l = create_list();
    for (int i = 0; i < 5; i++) {
        list_insert_node(l, i * 10 + i, 0);
        print_list(l);
    }

    list_delete_data(l, 4);
    printf("+++++++++++++++\n");
    print_list(l);
    
    list_delete_data(l, 0);
    printf("+++++++++++++++\n");
    print_list(l);

    // 释放链表
    while (l != NULL) {
        list *temp = l;
        l = l->next;
        free(temp);
    }
    return 0;
}
