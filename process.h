#pragma once

#include <string>

class Process {
private:
    int pid;

    std::string cmdline;
public:
    std::string state_short;
    std::string state_long;
    std::string name;
    explicit Process(int pid);
    explicit Process(std::string pid);
    Process(int pid,const std::string & name,const std::string & cmdline);
    Process(const Process& proc);
    Process(Process&& proc) noexcept;

    virtual ~Process();

    int getPid() const;

    void setPid(int pid);

};