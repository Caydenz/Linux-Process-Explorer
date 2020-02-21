#include "ProcessExplorer.h"


ProcessExplorer::ProcessExplorer()
{

}

std::vector<Process>::iterator ProcessExplorer::begin() noexcept {
    return processList.begin();
}

std::vector<Process>::iterator ProcessExplorer::end() noexcept {
    return processList.end();
}

std::vector<Process>::const_iterator ProcessExplorer::cbegin() noexcept {
    return processList.cbegin();
}

std::vector<Process>::const_iterator ProcessExplorer::cend() noexcept {
    return processList.cend();
}

void ProcessExplorer::populate() {
    //parse procfs and populate processList
}
