#include "WCPICARUS/ExecMon.h"
#include <sstream>

using namespace WCPICARUS;

ExecMon::ExecMon(const std::string& msg, TimeKeeper::ptime starting_time)
    : tk(msg, starting_time)
    , mu(msg) { }
    
ExecMon::~ExecMon() { }

std::string ExecMon::operator()(std::string msg, TimeKeeper::ptime now, MemUsage::memusage mumu)
{
    std::stringstream ss;
    ss << "Time: " << tk(msg,now) << "\n"
       << "Memory: " << mu(msg,mumu);
    return ss.str();
}


std::string ExecMon::summary() const
{
    std::stringstream ss;
    ss << "Time summary:\n" << tk.summary() << "\nMemory usage:\n" << mu.summary();
    return ss.str();
}

