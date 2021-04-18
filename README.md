# ring-buffer-in-c
Ring Buffer in C

git clone https://github.com/a6guerre/ring-buffer-in-c

cd ring-buffer-in-c

# Build
gcc ringbuffer.c tests.c -o tests

./tests

Windows:
TBD

Feel free to modify tests, or link this library to your code if you need a ring buffer data structure.

Currently, the data structure will handle overwriting. For example, if the user has written the entire ring, then the oldest element will be overwritting and reading
will resume from the oldest data present.
It is to the developer's discretion whether he/she will use the buffer being full when determining to overwritte old data in favor of new data.
