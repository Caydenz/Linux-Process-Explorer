#pragma once

#include <vector>
#include "process.h"

class ProcessExplorer {

private:
    std::vector<Process> processList;

public:
    ProcessExplorer();
    void populate();
    std::vector<Process>::iterator begin() noexcept;
    std::vector<Process>::iterator end() noexcept;
    std::vector<Process>::const_iterator cbegin() noexcept;
    std::vector<Process>::const_iterator cend() noexcept;


};
