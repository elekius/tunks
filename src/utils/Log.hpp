#ifndef TUNKS_LOG_HPP
#define TUNKS_LOG_HPP

#include <easylogging++.h>

#define TK_INIT_LOG \
    el::Configurations conf; \
    conf.setToDefault(); \
    el::Loggers::reconfigureLogger("default", conf); \
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

#define TK_LOG LOG(INFO)
#define TK_LOG_D LOG(DEBUG)
#define TK_LOG_W LOG(WARNING)
#define TK_LOG_E LOG(ERROR)
#define TK_LOG_F LOG(FATAL)


#endif
