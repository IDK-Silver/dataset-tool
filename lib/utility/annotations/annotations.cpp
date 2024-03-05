/*
 *  File: annotations.h
 *  Author: IDK, 唐翊靜
 *  Created on: 2024-03-05
 *  Description: Provide commonly used functionalities in processing dataset annotations.
 */

#include "annotations.h"

void utility::annotations::dark_net_offset(const std::string& input_path, int offset,const std::string& output_path) {

    // get the path of input, output
    const auto in_file = std::filesystem::path(input_path);
    const auto out_file = std::filesystem::path(output_path);

    // check the path of input, output
    if (not exists(in_file)) {
        std::cerr << "input file is not exists" << std::endl;
        std::cerr << "the input file path is " << absolute(in_file) << std::endl;
        exit(-1);
    }
    else if ( is_directory(in_file))
    {
        std::cerr << "input file is is directory" << std::endl;
        std::cerr << "the input file path is " << absolute(in_file) << std::endl;
        exit(-1);
    }

    if (not is_directory(out_file.parent_path()))
    {
        std::cerr << "output file upper directory "
        << out_file.parent_path().filename() << " is not exist" << std::endl;
        std::cerr << "the output file path is " << absolute(out_file) << std::endl;
        exit(-1);
    }
    else if (is_directory(out_file))
    {
        std::cerr << "output file is directory" << std::endl;
        std::cerr << "the output file path is " << absolute(out_file) << std::endl;
        exit(-1);
    }

    // the stream of input file
    std::fstream ifs;
    std::fstream ofs;

    // the lambda function to check if the file stream is opened successfully
    auto check_file_stream = [] (const std::fstream & stream, const std::filesystem::path file) {
        if (not stream.is_open())
        {
            std::cerr << "can't open file " << absolute(std::filesystem::path(file)) << std::endl;
            exit(-1);
        }
    };

    // try to open input file
    ifs.open(in_file, std::fstream::in);
    check_file_stream(ifs, in_file);

    // try to open output file
    ofs.open(out_file, std::fstream::out | std::ofstream::trunc);
    check_file_stream(ofs, out_file);


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