
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>


struct Foo {
    size_t thing;
};

int tak_aux(int x, int y, int z, bool allocate)
{
    if (y < x) {
        return tak_aux(tak_aux(x-1,y,z,allocate),tak_aux(y-1,z,x,allocate),tak_aux(z-1,x,y,allocate),allocate);
    } else {
        if (allocate) new Foo();
        return z;
    }
}

int tak(int x, int y, int z, bool allocate, int times) {
    int ret;
    for ( int ii=0; ii<times; ++ii ) {
        ret = tak_aux(x,y,z,allocate);
    }
    return ret;
}

struct Ctak {
    int val;
    Ctak(int v) : val(v) {};
};

int ctak_aux(int x, int y, int z, bool allocate)
{
    if (!(y < x)) {
        Ctak ret(z);
        if (allocate) new Foo();
        throw ret;
    } else {
        int rx;
        try {
            ctak_aux(x-1,y,z,allocate);
        } catch (Ctak& val) {
            rx = val.val;
        }
        int ry;
        try {
            ctak_aux(y-1,z,x,allocate);
        } catch (Ctak& val) {
            ry = val.val;
        }
        int rz;
        try {
            ctak_aux(z-1,x,y,allocate);
        } catch (Ctak& val) {
            rz = val.val;
        }
        return ctak_aux(rx,ry,rz,allocate);
    }
}

int ctak(int x, int y, int z, bool allocate,int times) {
    int ret;
    for (int ii=0; ii<times; ++ii) {
        try {
            ctak_aux(x,y,z,allocate);
        } catch (Ctak& val) {
            ret = val.val;
        }
    }
    return ret;
}



int main(int argc, char* argv[]) {

    size_t total_threads = 8;
    size_t tak_iters = 1000;
    for (int allocate=0; allocate<2; ++allocate) {
        for (size_t num_threads=1; num_threads<total_threads; num_threads++) {
            std::vector<std::thread> vecOfThreads;
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t ti=0; ti<num_threads; ti++ ) {
                std::thread thr(tak,22,12,8,allocate,tak_iters);
                vecOfThreads.push_back(std::move(thr));
            }
            for (size_t ti=0; ti<num_threads; ti++ ) {
                vecOfThreads[ti].join();
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
            std::cout << num_threads << ", " << duration.count() << ", " << allocate << " # tak(allocate/" << allocate<< ") " << tak_iters << " iterations on " << (num_threads) << " threads -> " << duration.count() << " milliseconds\n";
        }
    }
    size_t ctak_iters = 2;
    for (int allocate=0; allocate<2; ++allocate) {
        for (size_t num_threads=1; num_threads<total_threads; num_threads++) {
            std::vector<std::thread> vecOfThreads;
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t ti=0; ti<num_threads; ti++ ) {
                std::thread thr(ctak,22,12,8,allocate,2);
                vecOfThreads.push_back(std::move(thr));
            }
            for (size_t ti=0; ti<num_threads; ti++ ) {
                vecOfThreads[ti].join();
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
            std::cout << num_threads << ", " << duration.count() << ", " << allocate << " # ctak(allocate/" << allocate<< ") " << ctak_iters << " iterations on " << (num_threads) << " threads -> " << duration.count() << " milliseconds\n";
        }
    }
}

