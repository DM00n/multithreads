// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <thread>
#include "picosha2.h"
#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <random>
class MultiThread{
public:
    MultiThread(){_count_of_threads = std::thread::hardware_concurrency();}
    explicit MultiThread(int num){_count_of_threads = num;}
    std::string my_gen(){
        std::random_device rd;
        std::mt19937 mersenne(rd());
        std::string str;
        for (unsigned i = 0; i < 5; ++i) {
            unsigned a = mersenne()%75+48;
            str+=(char)a;
        }
        return str;
    }
    void hash(){
        while(true) {
            std::string str = my_gen();
            const std::string hash = picosha2::hash256_hex_string(str);
            std::string last_4(hash, 60, 4);
            if (last_4 == "0000") {
                BOOST_LOG_TRIVIAL(info) << hash << " " << str << std::endl;
                //std::cout << hash << " " << str << std::endl<< "I AM HERE"<<std::endl;
                break;
            } else {
                BOOST_LOG_TRIVIAL(trace) << hash << " " << str << std::endl;
                //std::cout << hash << " " << str << std::endl;
            }
        }
    }
    void engine(){
        std::vector<std::thread> threads;
        for (unsigned i = 0; i < _count_of_threads; ++i) {
            std::thread thr(&MultiThread::hash, this);
            threads.emplace_back(std::move(thr));
        }
        for(auto& thr : threads) {
            thr.join();
        }
    }
    size_t _count_of_threads;
};
#endif // INCLUDE_HEADER_HPP_
