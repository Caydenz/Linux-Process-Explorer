#pragma once

#include <string>

class Process {
private:
    int pid;
    std::string name;
    std::string cmdline;
public:
    explicit Process(int pid);
    Process(int pid,const std::string & name,const std::string & cmdline);
    Process(const Process& proc);
    Process(Process&& proc) noexcept;

    virtual ~Process();

    int getPid() const;

    void setPid(int pid);


};