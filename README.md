# ctak

Run the tak and ctak functions using multiple C++ threads.

The ctak function tests how efficiently the unix unwinds the stack using C++ exception
handling when multiple threads are doing it in parallel.
On macOS the performance as you increase the number of threads is not bad.
On Linux (debian) - it's disasterous!
