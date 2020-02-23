#include "ProcessExplorer.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


ProcessExplorer::ProcessExplorer()
{

}

std::vector<Process>::iterator ProcessExplorer::begin() noexcept {
    return processList.begin();
}

std::vector<Process>::iterator ProcessExplorer::end() noexcept {
    return processList.end();
}

std::vector<Process>::const_iterator ProcessExplorer::cbegin() const noexcept {
    return processList.cbegin();
}

std::vector<Process>::const_iterator ProcessExplorer::cend() const noexcept {
    return processList.cend();
}

void ProcessExplorer::populate() {
    //parse procfs and populate processList
    const std::string path = "/proc/";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
	    auto x = entry.path().filename().string();
        if (std::all_of(x.begin(), x.end(), ::isdigit))
        {
            std::unique_ptr<Process> proc = std::make_unique<Process>();
            std::ifstream file("/proc/" + x + "/cmdline", std::ios::binary);
            std::streambuf* raw_buffer = file.rdbuf();

            char block[255];
            raw_buffer->sgetn(block, 255);
            //return std::string(block);
            std::cout << x << '\n';
        }
    }
}
