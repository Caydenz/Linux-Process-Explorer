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
    [[nodiscard]] std::vector<Process>::const_iterator cbegin() const noexcept;
    [[nodiscard]] std::vector<Process>::const_iterator cend() const noexcept;


};
