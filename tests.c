#include "minunit.h"
#include "ringbuffer.h"
#include <stdint.h>

RingBuffer *buffer;

char *test_create_buffer(void)
{
  buffer = RingBuffer_create(10);
  check(buffer != NULL, "Could not create ring buffer\n");
  check(buffer->buffer != NULL, "Could not allocate buffer memory\n");
  
  return NULL;
error:
  return "Error creating buffer\n"; 

}

char *test_add_data(void)
{
  uint8_t arr[] = {1,2,3,4,5,6,7,8,9,10};
  uint8_t arr2[] = {11,12,13,14,15};

  RingBuffer_write(buffer, (char *)&arr[0], 4);
  for (int i = 0; i < 4; ++i)
  {
    printf("%d\n", buffer->buffer[i]);
  }
  check((buffer->start == 0), "Start pointer incorrect\n");
  check((buffer->end == 4), "End pointer incorrect\n");
  check((RingBuffer_available_data(buffer) == 4), "Number of available data is incorrect\n");
  check((RingBuffer_available_space(buffer) == 6), "Number of available spaces is incorrect\n");

  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  RingBuffer_write(buffer, (char *)&arr[4], 6);
  for (int i = 0; i < 10; ++i)
  {
    printf("%d\n", buffer->buffer[i]);
  }
  check((buffer->start == 0), "Start pointer incorrect\n");
  check((buffer->end == 0), "End pointer incorrect\n");
  check((RingBuffer_available_data(buffer) == 10), "Number of available data is incorrect\n");
  check((RingBuffer_available_space(buffer) == 0), "Number of available spaces is incorrect\n");

  printf("start: %d end: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));
  
  RingBuffer_write(buffer, (char *)&arr2[0], 5);
  for (int i = 0; i < 10; ++i)
  {
    printf("%d\n", buffer->buffer[i]);
  }

  check((buffer->start == 5), "Start pointer incorrect\n");
  check((buffer->end == 5), "End pointer incorrect\n");
  check((RingBuffer_available_data(buffer) == 10), "Number of available data is incorrect\n");
  check((RingBuffer_available_space(buffer) == 0), "Number of available spaces is incorrect\n");

  printf("start: %d end: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  return NULL;
error:
  return "Error with writing to buffer\n";
}

char *test_read_data(void)
{
  char buf[6];

  RingBuffer_read(buffer, buf, 5);
  for (int i = 0; i < 5; ++i)
  {
    printf("%d\n", buf[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  RingBuffer_read(buffer, buf, 7);
  for (int i = 0; i < 5; ++i)
  {
    printf("%d\n", buf[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  return NULL;
}

char *test_add_read_data(void)
{
  uint8_t arr[] = {16,17,18,19,20,21,22,23,24,25};
  RingBuffer_write(buffer, &arr[0], 6);
  for (int i = 0; i < 10; ++i)
  {
    printf("%d\n", buffer->buffer[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));
  
  uint8_t buf[6];
  RingBuffer_read(buffer, buf, 2);
  
  for (int i = 0; i < 2; ++i)
  {
    printf("%d\n", buf[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));
  
  RingBuffer_read(buffer, buf, 4);

  for (int i = 0; i < 4; ++i)
  {
    printf("%d\n", buf[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  RingBuffer_write(buffer, &arr[6], 4);

  for (int i = 0; i < 10; ++i)
  {
    printf("%d\n", buffer->buffer[i]);
  }
  printf("Start: %d End: %d\n", buffer->start, buffer->end);
  printf("avaialble data: %d free space: %d\n", RingBuffer_available_data(buffer), RingBuffer_available_space(buffer));

  return NULL;
}


char *all_tests()
{
  char *msg;
  mu_suite_start();
  check((msg = test_create_buffer()) == NULL, "Test Create Buffer failed\n");
  check((msg = test_add_data()) == NULL, "Adding data failed\n");
  check((msg = test_read_data()) == NULL, "Read data failed\n");
  check((msg = test_add_read_data()) == NULL, "Adding and reading failed\n");

  return NULL;

error:
  return msg;
}

RUN_TESTS(all_tests);

