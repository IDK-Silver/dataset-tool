/*
 *  File: annotations.h
 *  Author: IDK, 唐翊靜
 *  Created on: 2024-03-05
 *  Description: Provide commonly used functionalities in processing dataset annotations.
 */

#include "annotations.h"

void utility::annotations::dark_net_offset(const std::string& in_file, int offset,const std::string& out_file) {

    // the stream of input file
    std::ifstream ifs;
    std::ofstream ofs;

    auto open_file_failed = [] (const std::string& file) {
        std::cerr << "can't open file " << absolute(std::filesystem::path(file)) << std::endl;
        exit(-1);
    };

    // try to open input file
    ifs.open(in_file);
    if (!ifs.is_open())
        open_file_failed(in_file);

    // try to open output file
    ofs.open(out_file, std::ofstream::trunc);
    if (!ofs.is_open())
        open_file_failed(out_file);


    for (std::string line; std::getline(ifs, line);)
    {
        std::istringstream iss(line);
        uint32_t cls = 0;

        try {
            // get object class
            iss >> cls;

            // add offset
            cls += offset;

            // write to output file
            ofs << cls << " " << iss.str().substr(iss.str().find(' ')) << '\n';
        }
        catch (const std::exception &e) {
            std::cerr << "process string error, " << e.what();
            exit(-1);
        }
    }

    // close stream
    ifs.close();
    ofs.close();
}