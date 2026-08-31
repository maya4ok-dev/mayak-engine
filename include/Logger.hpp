#pragma once

#include "mayak/logger/core/state.hpp"
#include <mayak/logger.hpp>

static inline mayak::logger::core::Level info("INFO", 50);
static inline mayak::logger::core::Level debug("DEBUG", 20);

inline mayak::logger::core::Logger mlogger;

inline void init_logger() {
    mlogger.setLevel(info);
    mlogger.addSink<mayak::logger::ConsoleSink>();
    mayak::logger::core::minLevelPriority(0);
}
