//
// Created by andrei on 2/20/20.
//

#include "process.h"

int Process::getPid() const {
    return pid;
}

void Process::setPid(int pid) {
    this->pid = pid;
}

Process::Process(int pid) : pid(pid) {

}

Process::~Process() = default;
