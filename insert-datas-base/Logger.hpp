#ifndef LOGGER_H_FILE
#define LOGGER_H_FILE

#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace ManageLog
{

       #define LOG_SILENT 0
       #define LOG_ERR 1
       #define LOG_ERROR 1
       #define LOG_WARN 2
       #define LOG_WARNING 2
       #define LOG_INFO 3
       #define LOG_TIME 4
       #define LOG_DEBUG 5
       #define LOG_DEFAULT 4

       #define LOG_INIT_COUT() Logger log(std::cout, __PRETTY_FUNCTION__)
       #define LOG_INIT_CERR() Logger log(std::cerr, __PRETTY_FUNCTION__)
       #define LOG_INIT_CLOG() Logger log(std::clog, __PRETTY_FUNCTION__)
       #define LOG_INIT_CUSTOM(X) Logger log((X), __PRETTY_FUNCTION__)

       #ifdef BSLOG_NO_COLORS

              #define BSLOG_TIME    "[ TIME    ]"
              #define BSLOG_DEBUG   "[ DEBUG   ]"
              #define BSLOG_ERROR   "[ ERROR   ]"
              #define BSLOG_WARNING "[ WARNING ]"
              #define BSLOG_INFO    "[ INFO    ]"
       #else
              #define BSLOG_TIME    "\033[0;35m[ TIME    ]\033[0;0m"
              #define BSLOG_DEBUG             "[ DEBUG   ]"
              #define BSLOG_ERROR   "\033[0;31m[ ERROR   ]\033[0;0m"
              #define BSLOG_WARNING "\033[0;33m[ WARNING ]\033[0;0m"
              #define BSLOG_INFO    "\033[0;34m[ INFO    ]\033[0;0m"
       #endif

       class Logger
       {
          private:
                time_t now;
                time_t start;
                std::vector<time_t> snaps;
                std::vector<std::string> snap_ns;
                unsigned message_level;
                std::ostream& fac;
                std::string name;

          public:
                inline Logger(std::ostream&, unsigned, std::string);
                inline Logger(std::ostream&, std::string n);
                template <typename T>
                friend Logger& operator<<(Logger& logger, const T& s);
                inline Logger& operator()(unsigned log_level);
                inline void add_snapshot(std::string n, bool quiet = true)
                {
                  time_t now;
                  time(&now);
                  snaps.push_back(now);
                  snap_ns.push_back(n);
                  if (get_log_level() >= LOG_TIME && !quiet)
                    fac << BSLOG_TIME << prepare_time(*this) << prepare_name(*this)
                         << ": Added snap '" << n << "'\n";
                }
                inline void flush() { fac.flush(); }

                friend std::string prepare_level(Logger& logger);
                friend std::string prepare_time(Logger& logger);
                friend std::string prepare_name(Logger& logger);

                static unsigned& get_log_level()
                {
                  static unsigned log_level_internal = LOG_DEFAULT;
                  return log_level_internal;
                };
                inline void set_log_level(unsigned log_level) { get_log_level() = log_level; }
       };

       inline std::string prepare_level(Logger& logger);
       inline std::string prepare_time(Logger& logger);
       inline std::string prepare_name(Logger& logger);

       // unsigned Logger::get_loglevel = LOG_DEFAULT;

       template <typename T>
       Logger& operator<<(Logger& logger, const T& s)
       {
         if (logger.message_level <= logger.get_log_level())
         {
           logger.fac << s;
           return logger;
         }
         else
         {
           return logger;
         }
       }

       Logger::Logger(std::ostream& f, std::string n)
           : message_level(LOG_SILENT), fac(f), name(n)
       {
         time(&now);
         time(&start);
       }

       Logger::Logger(std::ostream& f, unsigned log_level, std::string n)
           : message_level(LOG_SILENT), fac(f), name(n)
       {
         time(&now);
         time(&start);
         get_log_level() = log_level;
       }

       Logger& Logger::operator()(unsigned log_level)
       {
         message_level = log_level;
         if (message_level <= get_log_level())
         {
           fac << prepare_level(*this) << prepare_time(*this) << prepare_name(*this) << ": ";
         }
         return *this;
       }

       std::string prepare_level(Logger& logger)
       {
         switch (logger.message_level)
         {
           case LOG_ERR:
             return BSLOG_ERROR;
             break;
           case LOG_WARN:
             return BSLOG_WARNING;
             break;
           case LOG_INFO:
             return BSLOG_INFO;
             break;
           case LOG_DEBUG:
             return BSLOG_DEBUG;
             break;
           case LOG_TIME:
             return BSLOG_TIME;
             break;
           default:
             return "";
         }
         return "";
       }

       std::string prepare_time(Logger& logger)
       {
         time(&logger.now);
         struct tm* t;
         t = localtime(&logger.now);
         std::string s, m, h, D, M, Y;
         s = std::to_string(t->tm_sec);
         m = std::to_string(t->tm_min);
         h = std::to_string(t->tm_hour);
         D = std::to_string(t->tm_mday);
         M = std::to_string(t->tm_mon + 1);
         Y = std::to_string(t->tm_year + 1900);

         if (t->tm_sec < 10) s = "0" + s;
         if (t->tm_min < 10) m = "0" + m;
         if (t->tm_hour < 10) h = "0" + h;
         if (t->tm_mday < 10) D = "0" + D;
         if (t->tm_mon + 1 < 10) M = "0" + M;

         std::string ret =
             "[ " + Y + "/" + M + "/" + D + "  " + h + ":" + m + ":" + s + " ]";

         return ret;
       }

       std::string prepare_name(Logger& logger)
       {
              return "[ " + logger.name + " ]";
       }
}

#endif // LOGGER_H_FILE
