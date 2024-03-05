//
// Created by idk on 2024/2/24.
//

#ifndef DATASET_SPLIT_COMMAND_RUNNER_H
#define DATASET_SPLIT_COMMAND_RUNNER_H
#include <argparse/argparse.hpp>
#include <string>
#include <utility>

class CommandRunner : public argparse::ArgumentParser {
public:
    explicit CommandRunner(std::string name) : argparse::ArgumentParser(std::move(name)) {

    };
    ~CommandRunner() = default;

    virtual void run() = 0;

private:
};


#endif //DATASET_SPLIT_COMMAND_RUNNER_H
