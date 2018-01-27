#ifndef IMCHAT_IMCHAT_H
#define IMCHAT_IMCHAT_H

#include <glog/logging.h>

#include <cassert>

static inline void loggerConfigure(const char *prog_name, const char *log_dir) {
    FLAGS_log_dir = log_dir;
    google::InitGoogleLogging(prog_name);
}

template <typename T> static inline void IMCHAT_ASSERT(T &&expr) {
    CHECK(expr);
    assert(expr);
}

static inline void IMCHAT_INFO(const char *msg) { LOG(INFO) << msg; }
static inline void IMCHAT_WARNING(const char *msg) { LOG(WARNING) << msg; }
static inline void IMCHAT_ERROR(const char *msg) { LOG(ERROR) << msg; }
static inline void IMCHAT_FATAL(const char *msg) { LOG(FATAL) << msg; }

#endif // IMCHAT_IMCHAT_H
