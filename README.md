# ctak

Run the tak and ctak functions using multiple C++ threads.

The ctak function tests how efficiently the unix unwinds the stack using C++ exception
handling when multiple threads are doing it in parallel.
On macOS the performance as you increase the number of threads is not bad.
On Linux (debian) - it's disasterous!

The results look like this on Linux:

The first column is the number of threads and the second is the time in milliseconds.

1, 46, 1 # ctak(allocate/1) 2 iterations on 1 threads -> 46 milliseconds
2, 127, 1 # ctak(allocate/1) 2 iterations on 2 threads -> 127 milliseconds
3, 187, 1 # ctak(allocate/1) 2 iterations on 3 threads -> 187 milliseconds
4, 268, 1 # ctak(allocate/1) 2 iterations on 4 threads -> 268 milliseconds
5, 371, 1 # ctak(allocate/1) 2 iterations on 5 threads -> 371 milliseconds
6, 486, 1 # ctak(allocate/1) 2 iterations on 6 threads -> 486 milliseconds
7, 624, 1 # ctak(allocate/1) 2 iterations on 7 threads -> 624 milliseconds


Full output...

1, 48, 0 # tak(allocate/0) 1000 iterations on 1 threads -> 48 milliseconds
2, 48, 0 # tak(allocate/0) 1000 iterations on 2 threads -> 48 milliseconds
3, 52, 0 # tak(allocate/0) 1000 iterations on 3 threads -> 52 milliseconds
4, 71, 0 # tak(allocate/0) 1000 iterations on 4 threads -> 71 milliseconds
5, 84, 0 # tak(allocate/0) 1000 iterations on 5 threads -> 84 milliseconds
6, 96, 0 # tak(allocate/0) 1000 iterations on 6 threads -> 96 milliseconds
7, 96, 0 # tak(allocate/0) 1000 iterations on 7 threads -> 96 milliseconds
1, 669, 1 # tak(allocate/1) 1000 iterations on 1 threads -> 669 milliseconds
2, 752, 1 # tak(allocate/1) 1000 iterations on 2 threads -> 752 milliseconds
3, 3671, 1 # tak(allocate/1) 1000 iterations on 3 threads -> 3671 milliseconds
4, 2766, 1 # tak(allocate/1) 1000 iterations on 4 threads -> 2766 milliseconds
5, 5573, 1 # tak(allocate/1) 1000 iterations on 5 threads -> 5573 milliseconds
6, 4686, 1 # tak(allocate/1) 1000 iterations on 6 threads -> 4686 milliseconds
7, 5093, 1 # tak(allocate/1) 1000 iterations on 7 threads -> 5093 milliseconds
1, 44, 0 # ctak(allocate/0) 2 iterations on 1 threads -> 44 milliseconds
2, 125, 0 # ctak(allocate/0) 2 iterations on 2 threads -> 125 milliseconds
3, 183, 0 # ctak(allocate/0) 2 iterations on 3 threads -> 183 milliseconds
4, 269, 0 # ctak(allocate/0) 2 iterations on 4 threads -> 269 milliseconds
5, 368, 0 # ctak(allocate/0) 2 iterations on 5 threads -> 368 milliseconds
6, 500, 0 # ctak(allocate/0) 2 iterations on 6 threads -> 500 milliseconds
7, 621, 0 # ctak(allocate/0) 2 iterations on 7 threads -> 621 milliseconds
1, 46, 1 # ctak(allocate/1) 2 iterations on 1 threads -> 46 milliseconds
2, 127, 1 # ctak(allocate/1) 2 iterations on 2 threads -> 127 milliseconds
3, 187, 1 # ctak(allocate/1) 2 iterations on 3 threads -> 187 milliseconds
4, 268, 1 # ctak(allocate/1) 2 iterations on 4 threads -> 268 milliseconds
5, 371, 1 # ctak(allocate/1) 2 iterations on 5 threads -> 371 milliseconds
6, 486, 1 # ctak(allocate/1) 2 iterations on 6 threads -> 486 milliseconds
7, 624, 1 # ctak(allocate/1) 2 iterations on 7 threads -> 624 milliseconds

