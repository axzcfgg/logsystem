#ifndef LOGHPP
#define LOGHPP

#include "impl/log.hpp"

#define VAR_DUMP(ARG) \
	core::log::get().lcdump<__LINE__>(__FILE__, __func__);\
	core::log::get().dump(#ARG + std::string(" <- "), ARG)
	
#define LOG(any) \
	core::log::get().lcdump<__LINE__>(__FILE__, __func__);\
	core::log::get().dump_single((any))

#define LOGS(...) \
	core::log::get().lcdump<__LINE__>(__FILE__, __func__);\
	core::log::get().dump(__VA_ARGS__)

#endif
