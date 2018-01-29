///
/// \file    imchat.h
/// \brief   项目头文件，包含常用宏定义和函数
///
/// \author  shaonge@gmail.com
/// \date    10:35 PM 1/29/18
///

#ifndef IMCHAT_IMCHAT_H
#define IMCHAT_IMCHAT_H

#include <glog/logging.h>

#include <cassert>

static inline void loggerConfigure(const char *prog_name, const char *log_dir) {
    FLAGS_log_dir = log_dir;
    google::InitGoogleLogging(prog_name);
}

#define IMCHAT_ASSERT(expr) assert(expr)
#define IMCHAT_INFO(msg) LOG(INFO) << msg
#define IMCHAT_WARNING(msg) LOG(WARNING) << msg
#define IMCHAT_ERROR(msg) LOG(ERROR) << msg
#define IMCHAT_FATAL(msg) LOG(FATAL) << msg

#endif // IMCHAT_IMCHAT_H
