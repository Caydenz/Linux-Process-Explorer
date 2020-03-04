//
// Created by andrei on 2/26/20.
//

#include <fstream>
#include <iostream>
#include "utils.h"

std::string Utils::readFile(const std::string& path) {
    std::ifstream file(path);
    std::streambuf* raw_buffer = file.rdbuf();
    std::streamsize size = raw_buffer->pubseekoff(0,std::ifstream::end);

    raw_buffer->pubseekoff(0,std::ifstream::beg);

    if (size == 0)
    {
        char contents[2000];
        raw_buffer->sgetn(contents, 1000);

        file.close();
        return std::string(contents);
    } else {
        char contents[2000];
        raw_buffer->sgetn(contents, 1000);

        file.close();
        return std::string(contents);
    }
}
