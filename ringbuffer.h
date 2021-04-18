#include "dbg.h"
#include <stdint.h>

typedef struct
{
  char *buffer;
  int length;
  int start;
  int end;
  uint8_t empty;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);

void RingBuffer_destroy(RingBuffer *buffer);

int RingBuffer_read(RingBuffer * buffer, char *targer, int amount);

int RingBuffer_write(RingBuffer * buffer, char *data, int length);

int RingBuffer_empty(RingBuffer * buffer);

int RingBuffer_full(RingBuffer * buffer);

int RingBuffer_available_data(RingBuffer * buffer);

int RingBuffer_available_space(RingBuffer * buffer);

/*#define RingBuffer_full(B) (RingBuffer_available_data((B))\
  - (B)->length == 0)

#define RingBuffer_empty(B) (\
	RingBuffer_available_data((B)) == 0)*/

