/*
 *  File: annotations.h
 *  Author: IDK, 唐翊靜
 *  Created on: 2024-03-05
 *  Description: Provide commonly used functionalities in processing dataset annotations.
 */


#ifndef DATASET_TOOL_ANNOTATIONS_H
#define DATASET_TOOL_ANNOTATIONS_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace utility {
    namespace annotations {
        /**
         *  To offset the class in Darknet-format annotation files.
         * @param in_file source path
         * @param offset class offset
         * @param out_file output file path
         */
        void dark_net_offset(const std::string &in_file, int offset, const std::string &out_file);
    };
}





#endif //DATASET_TOOL_ANNOTATIONS_H
