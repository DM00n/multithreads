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
        if (last_4 == VALUE) {
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
    logging::add_common_attributes();
    logging::add_file_log(
            logging::keywords::file_name = LOG_NAME_TRACE,
            logging::keywords::rotation_size = LOG_SIZE,
            logging::keywords::time_based_rotation =
                    logging::sinks::file::rotation_at_time_point(0, 0, 0),
            logging::keywords::filter = logging::trivial::severity
                               >= logging::trivial::trace,
            logging::keywords::format =
                    "[%TimeStamp%]:  [%ThreadID%]   %Message%");

    logging::add_file_log(
            logging::keywords::file_name = LOG_INFO_TRACE,
            logging::keywords::rotation_size = LOG_SIZE,
            logging::keywords::time_based_rotation =
                    logging::sinks::file::rotation_at_time_point(0, 0, 0),
            logging::keywords::filter = logging::trivial::severity
                               >= logging::trivial::info,
            logging::keywords::format =
                    "[%TimeStamp%]:   [%ThreadID%]   %Message%");
    logging::add_console_log
            (
                    std::cout,
                    logging::keywords::format =
                            "[%TimeStamp%]: [%ThreadID%]  "
                            "[%Severity%]: %Message%");
}
