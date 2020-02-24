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
        str+=static_cast<char>(a);
    }
    return str;
}

void MultiThread::hash() {
    while (true) {
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
    logger();
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < _count_of_threads; ++i) {
        std::thread thr(&MultiThread::hash, this);
        threads.emplace_back(std::move(thr));
    }
    for (auto& thr : threads) {
        thr.join();
    }
}

void MultiThread::logger() {
    boost::log::logging::add_common_attributes();
    boost::log::logging::add_file_log(
            boost::log::keywords::file_name = "/log/trace_%N.log",
            boost::log::keywords::rotation_size = 10 * 1024 * 1024,
            boost::log::keywords::time_based_rotation =
                    boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
            boost::log::keywords::filter = boost::log::
                    logging::trivial::severity
                               >= boost::log::logging::trivial::trace,
            boost::log::keywords::format =
                    "[%TimeStamp%]:  [%ThreadID%]   %Message%")

    boost::log::logging::add_file_log(
            boost::log::keywords::file_name = "/log/info_%N.log",
            boost::log::keywords::rotation_size = 1024 * 1024,
            boost::log::keywords::time_based_rotation =
                    boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
            boost::log::keywords::filter = boost::log::
                    logging::trivial::severity
                               >= boost::log::logging::trivial::info,
            boost::log::keywords::format =
                    "[%TimeStamp%]:   [%ThreadID%]   %Message%")
    boost::log::logging::add_console_log
            (
                    std::cout,
                    boost::log::logging::keywords::format =
                            "[%TimeStamp%]: [%ThreadID%]  "
                            "[%Severity%]: %Message%");
}
