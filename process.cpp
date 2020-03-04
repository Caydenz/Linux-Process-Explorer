//
// Created by andrei on 2/20/20.
//

#include "process.h"

int Process::getPid() const {
    return pid;
}

void Process::setPid(const int pid) {
    this->pid = pid;
}

Process::Process(const int pid): pid(pid)
{
}

Process::Process(const int pid, const std::string& name, const std::string& cmdline)
{
    this->pid = pid;
    this->name = name;
    this->cmdline = cmdline;
}
Process::Process(const Process& proc)
{
    this->pid = proc.pid;
}

Process::Process(Process&& proc) noexcept
{
    this->pid = proc.pid;
}

Process::~Process() = default;
