
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
      int rx = 0;
        try {
            ctak_aux(x-1,y,z,allocate);
        } catch (Ctak& val) {
            rx = val.val;
        }
        int ry=0;
        try {
            ctak_aux(y-1,z,x,allocate);
        } catch (Ctak& val) {
            ry = val.val;
        }
        int rz=0;
        try {
            ctak_aux(z-1,x,y,allocate);
        } catch (Ctak& val) {
            rz = val.val;
        }
        return ctak_aux(rx,ry,rz,allocate);
    }
}

int ctak(int x, int y, int z, bool allocate,int times) {
    int ret=0;
    for (int ii=0; ii<times; ++ii) {
        try {
            ctak_aux(x,y,z,allocate);
        } catch (Ctak& val) {
            ret = val.val;
        }
    }
    return ret;
}


void all_tests() {
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


size_t many_ctak(size_t num_threads) {
    std::vector<std::thread> vecOfThreads;
    bool allocate = false;
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
    std::cout << num_threads << ", " << duration.count() << ", " << allocate << " # ctak(allocate/" << allocate<< ") on " << (num_threads) << " threads -> " << duration.count() << " milliseconds\n";
    return duration.count();
}


void help() {
    printf("ctak tests\n");
    printf("-h     This message.\n");
    printf("-a     Run all tests.\n");
    printf("-m     Run many ctak in a number of threads\n");
    printf("-s     Calculate per-thread slowdown\n");
    printf("-t <n> Use <n> threads.\n");
    printf("-l <n> Number of loops to run.\n");
};

int main(int argc, char* argv[]) {
    if (argc==1) {
        help();
    } else {
        int iarg=1;
        bool run_all_tests = false;
        size_t num_threads = 8;
        size_t num_loops = 1;
        bool run_many_ctak = false;
        bool run_calculate_slowdown = false;
        while (iarg<argc) {
            std::string arg = argv[iarg];
            if (arg=="-h") {
                help();
                exit(0);
            } else if (arg == "-a") {
                run_all_tests = true;
            } else if (arg == "-m") {
                run_many_ctak = true;
            } else if (arg == "-s") {
                run_calculate_slowdown = true;
            } else if (arg == "-t") {
                num_threads = atoi(argv[iarg+1]);
                iarg++;
            } else if (arg == "-l") {
                num_loops = atoi(argv[iarg+1]);
                iarg++;
            }
            iarg++;
        }
        if (run_all_tests) {
            all_tests();
        }
        if (run_many_ctak) {
            printf("Running %lu loops\n", num_loops);
            for (size_t il=0; il<num_loops; il++) {
                many_ctak(num_threads);
            }
        }
        if (run_calculate_slowdown) {
            std::vector<size_t> mss;
            double total_per_thread_performance = 0.0;
            for (size_t nt=1;nt<num_threads;nt++) {
                size_t ms = many_ctak(nt);
                mss.push_back(ms);
            }
            int total = 0;
            int count = 0;
            for (size_t nt=1; nt<num_threads-1; nt++ ) {
                size_t msm1=mss[nt-1];
                size_t ms = mss[nt];
                int delta = ms-msm1;
                total += delta;
                count++;
            }
            std::cout << "Average millisecond slowdown as threads are added (closer to zero the better): " << (total/(double)count) << "\n";
        }
    }
}
