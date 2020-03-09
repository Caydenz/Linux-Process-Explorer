#include "ProcessExplorer.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include "utils.h"


ProcessExplorer::ProcessExplorer()
= default;

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
    //std::regex re(R"(.*Name:\s*([^\n\r]*))");
    //std::smatch match;


    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
	    auto x = entry.path().filename().string();
        if (std::all_of(x.begin(), x.end(), ::isdigit))
        {
            std::unique_ptr<Process> proc = std::make_unique<Process>(x);

            //std::string statusFile = Utils::readFile("/proc/" + x + "/status");

            //std::cout << statusFile;
            /*std::ifstream file("/proc/" + x + "/status", std::ios::binary);
            std::streambuf* raw_buffer = file.rdbuf();

            char block[1000];
            raw_buffer->sgetn(block, 1000);

            std::string status = std::string(block);*/
            //if (std::regex_search(statusFile, match, re) && match.size() > 1) {
                //std::cout << x << " - "  <<  match.str(1) << "\n";
            //}


            //auto y = statusFile.find("State:");

            //constexpr int ignored = 0;

            //std::istringstream test(statusFile);

            //std::string process_name;

            //test.ignore(sizeof("Name:") - 1);

            //test >> process_name;
            //test.clear();
            //test.seekg(0);
            //test.ignore(y + sizeof("State:") - 1 - sizeof("Name:") + 1);
            //std::string state_short;
            //std::string state_long;
            //test >> state_short >> state_long;

           // std::cout << Utils::getProcValue("Name:", statusFile, test);
            std::cout << proc->name << "-" << proc->state_short << "-" << proc->state_long << "\n";
            //std::cout << Utils::getProcValue (std::string("Name:"), statusFile, test) << '\n';
            //std::cout << x <<  " - " << process_name << " - " << state_short << " - " << state_long << '\n';

            //return std::string(block);
            //std::cout << x <<  ' ' << block << '\n';
        }
    }
}
