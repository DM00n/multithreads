// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <thread>
#include <picosha2.h>
#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <random>
class MultiThread{
public:
    MultiThread();
    explicit MultiThread(int num);
    std::string my_gen();
    void hash();
    void engine();
    void logger();
    size_t _count_of_threads;
};
#endif // INCLUDE_HEADER_HPP_
