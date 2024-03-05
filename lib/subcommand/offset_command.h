//
// Created by idk on 2024/3/4.
//

#ifndef DATASET_SPLIT_OFFSET_H
#define DATASET_SPLIT_OFFSET_H

#include <utility/annotations/annotations.h>
#include <argparse/argparse.hpp>
#include <subcommand/command_runner.h>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

class OffsetCommand : public CommandRunner {
public:
    OffsetCommand();
    ~OffsetCommand() = default;

    void run() override;

};


#endif //DATASET_SPLIT_OFFSET_H
