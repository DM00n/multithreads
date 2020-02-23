// Copyright 2018 Your Name <your_email>

#include "header.hpp"
MultiThread::MultiThread(){_count_of_threads =
                                   std::thread::hardware_concurrency();}

MultiThread::MultiThread(int num){_count_of_threads = num;}

std::string MultiThread::my_gen(){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::string str;
    for (unsigned i = 0; i < 5; ++i) {
        unsigned a = mersenne()%75+48;
        str+=(char)a;
    }
    return str;
}

void MultiThread::hash() {
    while(true) {
        std::string str = my_gen();
        const std::string hash = picosha2::hash256_hex_string(str);
        std::string last_4(hash, 60, 4);
        if (last_4 == "0000") {
            BOOST_LOG_TRIVIAL(info) << hash << " " << str << std::endl;
            break;
        } else {
            BOOST_LOG_TRIVIAL(trace) << hash << " " << str << std::endl;
        }
    }
}

void MultiThread::engine(){
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < _count_of_threads; ++i) {
        std::thread thr(&MultiThread::hash, this);
        threads.emplace_back(std::move(thr));
    }
    for(auto& thr : threads) {
        thr.join();
    }
}