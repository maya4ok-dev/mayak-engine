#pragma once

#include <mayak/logger.hpp>

static inline mayak::logger::core::Level error("error", 100);
static inline mayak::logger::core::Level info("info", 50);
static inline mayak::logger::core::Level debug("debug", 20);

inline mayak::logger::core::Logger mlogger;

inline void init_logger() {
    mlogger.setLevel(info);
    mlogger.addSink<mayak::logger::ConsoleSink>();
    mayak::logger::core::minLevelPriority(0);
}
