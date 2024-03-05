//
// Created by idk on 2024/2/24.
//

#ifndef DATASET_TOOL_SPLIT_COMMAND_H
#define DATASET_TOOL_SPLIT_COMMAND_H

#include <string>
#include <filesystem>
#include <vector>
#include <random>
#include <argparse/argparse.hpp>
#include <subcommand/command_runner.h>

class SplitCommand : public CommandRunner {

public:
    SplitCommand();
    ~SplitCommand() = default;

    void run() override;

private:

};




#endif //DATASET_TOOL_SPLIT_COMMAND_H
