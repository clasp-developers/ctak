# ctak

Run the tak and ctak functions using multiple C++ threads.

The ctak function tests how efficiently the unix unwinds the stack using C++ exception
handling when multiple threads are doing it in parallel.
On macOS the performance as you increase the number of threads is not bad.
On Linux (debian) - it's terrible.

It doesn't help to use llvm libunwind.
Fundamentally it comes down to that on Linux it walks every dynamically loaded library and that requires a mutex and on macOS it's doing some kind of clever caching.

From mstorsjo on the llvm discord:

The difference in libunwind between macOS and linux is this: https://github.com/llvm/llvm-project/blob/master/libunwind/src/AddressSpace.hpp#L397-L408 vs https://github.com/llvm/llvm-project/blob/master/libunwind/src/AddressSpace.hpp#L485-L571


The results look like this on macOS:
```
meister@CST14042 ctak$ ./mac-ctak -s
1, 29, 0 # ctak(allocate/0) on 1 threads -> 29 milliseconds
2, 32, 0 # ctak(allocate/0) on 2 threads -> 32 milliseconds
3, 28, 0 # ctak(allocate/0) on 3 threads -> 28 milliseconds
4, 28, 0 # ctak(allocate/0) on 4 threads -> 28 milliseconds
5, 32, 0 # ctak(allocate/0) on 5 threads -> 32 milliseconds
6, 36, 0 # ctak(allocate/0) on 6 threads -> 36 milliseconds
7, 40, 0 # ctak(allocate/0) on 7 threads -> 40 milliseconds
Average slowdown as threads are added (closer to zero the better): 1.83333 milliseconds
```

The results look like this on Linux:

```
meister@hermes:~/Development/ctak$ ./linux-ctak -s
1, 35, 0 # ctak(allocate/0) on 1 threads -> 35 milliseconds
2, 59, 0 # ctak(allocate/0) on 2 threads -> 59 milliseconds
3, 102, 0 # ctak(allocate/0) on 3 threads -> 102 milliseconds
4, 159, 0 # ctak(allocate/0) on 4 threads -> 159 milliseconds
5, 225, 0 # ctak(allocate/0) on 5 threads -> 225 milliseconds
6, 291, 0 # ctak(allocate/0) on 6 threads -> 291 milliseconds
7, 359, 0 # ctak(allocate/0) on 7 threads -> 359 milliseconds
Average slowdown as threads are added (closer to zero the better): 54 milliseconds
```
