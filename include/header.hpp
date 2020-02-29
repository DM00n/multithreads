// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <thread>
#include <picosha2.h>
#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <random>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions/keyword.hpp>

namespace logging = boost::log;
class MultiThread{
public:
    MultiThread();
    explicit MultiThread(int num);
    std::string my_gen();
    void hash();
    void engine();
    void logger();
    size_t _count_of_threads;
    const static std::string VALUE = "0000";
    const static unsigned LOG_SIZE = 10 * 1024 * 1024;
    const static std::string LOG_NAME_TRACE = "trace_%N.log";
    const static std::string LOG_LOG_TRACE = "log_%N.log";
};
#endif // INCLUDE_HEADER_HPP_
