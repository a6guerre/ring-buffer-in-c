#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"

RingBuffer *RingBuffer_create(int length)
{
  RingBuffer *buffer = calloc(1, sizeof(RingBuffer *));
  buffer->length = length;
  buffer->start = 0;
  buffer->end = 0; 
  buffer->empty = 1;
  buffer->buffer = calloc(buffer->length, 1);

  return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
  free(buffer->buffer);
  free(buffer);
}

int RingBuffer_read(RingBuffer * buffer, char *target, int amount)
{
  amount = (amount >= RingBuffer_available_data(buffer)) ? RingBuffer_available_data(buffer) : amount;
  buffer->empty = (amount >= RingBuffer_available_data(buffer)) ? 1 : 0;
  int remaining = buffer->length - buffer->start;

  char *read_ptr = buffer->buffer + buffer->start;

  if(amount > remaining)
  {
    memcpy(target, read_ptr, remaining);
    read_ptr = buffer->buffer;
    memcpy(target + remaining, read_ptr, amount - remaining);
  }
  else
  {
    memcpy(target, read_ptr, amount);
  }

  buffer->start = (amount + buffer->start) % (buffer->length);

  return 0;
}

int RingBuffer_write(RingBuffer * buffer, char *data, int length)
{
  check(buffer->length >= length, "data exceeds length of buffer");
  char *write_ptr = buffer->buffer + buffer->end;
  int remaining = buffer->length - buffer->end; 

  if(length > remaining)
  {
    memcpy(write_ptr, data, remaining);
    write_ptr = buffer->buffer;
    //TODO: add asserts
    memcpy(write_ptr, data + remaining, length - remaining);
  }
  else
  {
    memcpy(write_ptr, data, length);
  }

  printf("avial_space: %d\n", RingBuffer_available_space(buffer));
 
  if(length > RingBuffer_available_space(buffer))
  {
    printf("we're here\n");
    buffer->end = (length + buffer->end) % (buffer->length);
    buffer->start = buffer->end;
  }
  else
  {
    buffer->end = (length + buffer->end) % (buffer->length);
  }

  buffer->empty = 0;
  return 0;
error:
  return -1;
}

int RingBuffer_empty(RingBuffer * buffer)
{
  return RingBuffer_available_data(buffer) ? 1:0;
}

int RingBuffer_full(RingBuffer * buffer)
{
  return (RingBuffer_available_space(buffer) == 0) ? 1:0;
}

int RingBuffer_available_data(RingBuffer * buffer)
{
  int data;
  
  if (buffer->start > buffer->end)
  {
    data = (buffer->length + 1 - buffer->start) + buffer->end - 1;
  }
  else
  {
    if(buffer->end == buffer->start)
    {
      if(!buffer->empty)
      {
        data = buffer->length; 
      }
      else
      {
        data = buffer->end - buffer->start;
      }
    }
    else
    {
      data = buffer->end - buffer->start;
    }
  }
  
  return data;
}

int RingBuffer_available_space(RingBuffer * buffer)
{
  return (buffer->length - RingBuffer_available_data(buffer));
}
