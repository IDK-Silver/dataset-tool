#include <iostream>
#include <array>
#include <argparse/argparse.hpp>
#include <subcommand/split_command.h>
#include <subcommand/command_runner.h>
#include <subcommand/offset_command.h>

int main(int argc, char *argv[])
{
    // create program argument parser
    argparse::ArgumentParser program("dataset_split");

    // create subcommand
    std::array<argparse::ArgumentParser*, 2> sub_commands {
        new SplitCommand(),
        new OffsetCommand()
    };

    // add subcommand into program
    for (auto command : sub_commands) {
        program.add_subparser(*command);
    }

    // decode the c style argument
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        exit(1);
    }

    // run with command that used
    for (auto command : sub_commands)
    {
        if (program.is_subcommand_used(*command))
        {
            auto runner = (CommandRunner* ) command;
            runner->run();
        }
    }

    // do not attempt to delete (free) the subcommand.

    return 0;
}