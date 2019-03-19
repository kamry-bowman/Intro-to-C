#include <stdio.h>
#include <stdlib.h>

void mem_copy(void *dest, const void *src, int n)
{
  char *char_dest = (char *)dest;
  char *char_src = (char *)src;
  for (int i = 0; i < n; i++)
  {
    char_dest[i] = char_src[i];
  }
}

void *resize_memory(void *ptr, int old_size, int new_size)
{
  char *char_ptr = (char *)ptr;
  if (old_size != new_size)
  {
    char *new_ptr = malloc(new_size);
    for (int i = 0; i < old_size; i++)
    {
      new_ptr[i] = char_ptr[i];
    }
    free(ptr);
    return (void *)new_ptr;
  }
  return ptr;
}

typedef struct Queue
{
  unsigned int length;
  unsigned int capacity;
  int *storage;
} Queue;

/*
    Creates a queue by allocating the appropriate amount of memory for an
    instance of the Queue struct, and initializes all of the fields of the
    struct. Also allocates memory for the queue's storage structure. 
*/
Queue *createQueue(unsigned capacity)
{
  Queue *new_queue = malloc(sizeof(Queue));
  new_queue->length = 0;
  new_queue->capacity = capacity;

  int *storage = malloc(sizeof(int) * capacity);
  new_queue->storage = storage;

  return new_queue;
}

/*
    Adds the given item to the end of the queue. If the queue does
    not have room, expand the queue's available storage so that it 
    does have room for the additional item.
*/
void enqueue(Queue *q, int item)
{
  unsigned int old_length = q->length;
  unsigned int new_length = old_length + 1;

  // create buffer for new length
  int buffer[new_length];

  // add new item to beginning of buffer
  buffer[0] = item;

  // copy current storage into buffer after first item
  mem_copy((buffer + 1), q->storage, sizeof(int) * old_length);

  // double q->storage memory if exhausted
  if (sizeof(item) * new_length > q->capacity)
  {
    unsigned int new_capacity = q->capacity * 2;
    int *new_memory = resize_memory(q->storage, q->capacity, new_capacity);
    q->storage = new_memory;
    q->capacity = new_capacity;
  }
  // copy buffer into storage
  mem_copy(q->storage, buffer, sizeof(int) * new_length);
  q->length = new_length;
}

/*
    Removes the item at the front of the queue and returns it. 
    If the queue is empty, this function should return -1.
*/
int dequeue(Queue *q)
{
  if (q->length == 0)
  {
    return -1;
  }
  q->length--;
  return q->storage[q->length];
}

/*
    Frees the memory used to hold the queue instance and its
    associated storage. 
*/
void destroyQueue(Queue *q)
{
  free(q->storage);
  free(q);
}

#ifndef TESTING
int main(void)
{
  Queue *q = createQueue(4);

  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  enqueue(q, 5);
  enqueue(q, 6);

  printf("length: %d\n", q->length);
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("length: %d\n", q->length);

  destroyQueue(q);

  return 0;
}
#endif