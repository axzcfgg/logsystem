#ifndef LOGHPP
#define LOGHPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace core {
	class log {

	 	time_t current;
		tm *local;
		std::ofstream ofs;
		bool marked_time;

		// constructor
		// save file with named current time 
		log() :
		local(nullptr) ,
		marked_time(false)
		{
			time(&current);
 			local = localtime(&current);
			std::stringstream fname;
			fname << local->tm_year + 1900 << "." <<
				std::setw(2) << std::setfill('0') << 
				local->tm_mon + 1 << "." << 
				std::setw(2) << std::setfill('0') << 
				local->tm_mday << "__" << 
				std::setw(2) << std::setfill('0') << 
				local->tm_hour << "." << 
				std::setw(2) << std::setfill('0') << 
				local->tm_min << "." << 
				std::setw(2) << std::setfill('0') << 
				local->tm_sec << ".log";
			ofs.open(fname.str().c_str());
		}

		// mark current time
		void mark() {
			time(&current);
 			local = localtime(&current);
			ofs << local->tm_year + 1900 << "/" << 
				std::setw(2) << std::setfill('0') << 
				local->tm_mon + 1 << "/" << 
				std::setw(2) << std::setfill('0') << 
				local->tm_mday << " " << 
				std::setw(2) << std::setfill('0') << 
				local->tm_hour << ":" << 
				std::setw(2) << std::setfill('0') << 
				local->tm_min << ":" << 
				std::setw(2) << std::setfill('0') << 
				local->tm_sec << "]";
		}

		// dump variables
		template <class T> void dump(const T &arg) { ofs << arg; }

	public:

		// retrieve instance
		static log &get() {
			static log l;
			return l;
		}

		// dump line and col
		// do not call this func immediately
		template <int LINE> void lcdump (
			const char *fname ,
			const char *func
		)
		{
			ofs << "[" << fname << ", " << func << ":" <<
				LINE << " | ";
		}

		// dump variables
		template <class FIRST, class ...ARG> 
		void dump(const FIRST &first, const ARG&... arg) {
			if( ! marked_time) {
				mark();
				ofs << " ";
				marked_time = true;
			}
			dump(first);
			dump(arg...);
			if(marked_time) {
				ofs << std::endl;
				marked_time = false;
			}
		}
	};
}

#define VAR_DUMP(ARG) \
	core::log::get().lcdump<__LINE__>(__FILE__, __func__);\
	core::log::get().dump(#ARG + std::string(" <- "), ARG)


#endif
