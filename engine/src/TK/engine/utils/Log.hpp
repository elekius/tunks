#ifndef TUNKS_LOG_HPP
#define TUNKS_LOG_HPP

#include "easylogging++.h"
#include <filesystem>

#define TK_INIT_LOG \
     std::string logDirectory = "log"; \
     if (!std::filesystem::exists(logDirectory)) std::filesystem::create_directory(logDirectory); \
     el::Configurations conf; \
     conf.setToDefault(); \
     conf.setGlobally(el::ConfigurationType::Filename, logDirectory + "/log.log"); \
     conf.setGlobally(el::ConfigurationType::ToFile, "true"); \
     conf.setGlobally(el::ConfigurationType::ToStandardOutput, "true"); \
     conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "2000000");  \
     conf.setGlobally(el::ConfigurationType::LogFlushThreshold, "0"); \
     el::Loggers::reconfigureLogger("default", conf); \
     el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput)

#define TK_LOG(group) LOG(INFO) << "[" << (group) << "] "
#define TK_LOG_W(group) LOG(WARNING) << "[" << (group) << "] "
#define TK_LOG_E(group) LOG(ERROR) << "[" << (group) << "] "
#define TK_LOG_F(group) LOG(FATAL) << "[" << (group) << "] "
#define TK_LOG_D(group) LOG(DEBUG) << "[" << (group) << "] "



#endif
