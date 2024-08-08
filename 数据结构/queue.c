#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 队列节点
typedef struct queue_node
{
    /* 后继节点 */
    struct queue_node *next;
    /* 值 */
    void *data;
} queue_node;

// 队列本身
typedef struct queue
{
    // 队头
    struct queue_node *head;
    // 队尾
    struct queue_node *tail;
    // 队列长度
    int length;
} queue;

// 创建队列
queue *queue_create()
{
    // 创建一个队列
    queue *queue = (struct queue *)malloc(sizeof(struct queue));

    // 为了方便操作，队列默认创建一个队列节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (queue == NULL || node == NULL)
    {
        return NULL;
    }
    node->data = NULL;
    node->next = NULL;

    // 初始化队列
    queue->head = queue->tail = node;
    queue->length = 0;
    return queue;
}

// 入队
queue *queue_push(queue *queue, void *data)
{
    // 创建一个节点
    queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;

    // 在队尾插入元素
    queue->tail->next = node;
    queue->tail = queue->tail->next;

    queue->length++;
    return queue;
}

// 出队
void *queue_pull(queue *queue)
{
    queue_node *curr = queue->head->next;

    // 判断队列中是否有数据
    if (curr == NULL)
    {
        return NULL;
    }

    void *data = curr->data;

    queue->head->next = curr->next;

    // 判断队列中除头节点外，是否只有一个节点，避免尾指针丢失
    if (queue->tail == curr)
    {
        queue->tail = queue->head;
    }
    free(curr);
    queue->length--;
    return data;
}

// 清空队列
void queue_empty(queue *queue)
{
    int length = queue->length;
    queue_node *curr, *next;

    // 注意这里不释放节点
    curr = queue->head->next;
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }

    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}

// 释放队列，包括队列中节点
void queue_release(queue *queue)
{
    queue_empty(queue);
    // 注意头节点也要释放
    free(queue->head);
    free(queue);
}
int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';

    queue *queue = queue_create();
    printf("pull:%p\n", queue_pull(queue));

    printf("====================\n");

    queue_push(queue, &a);
    queue_push(queue, &b);
    queue_push(queue, &c);

    while (queue->length)
    {
        char *temp = (char *)queue_pull(queue);
        printf("queue_pull:%c %p\n", *temp, temp);
    }
    printf("====================\n");

    queue_push(queue, &c);
    queue_push(queue, &c);

    // 释放队列中节点
    queue_empty(queue);
    printf("pull:%p\n", queue_pull(queue));

    // 释放队列
    queue_release(queue);

    return 0;
}