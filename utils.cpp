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

std::string Utils::getProcValue(std::string key, std::string file, std::istringstream &stream, int position) {

    std::string result;
    //reset stream
    stream.clear();
    stream.seekg(0);

    stream.ignore(file.find(key) + key.length());

    for(int i=0; i<position+1; i++)
    {
        stream >> result;
    }

    return result;
}
