//
// Created by idk on 2024/3/4.
//

#include "offset_command.h"

OffsetCommand::OffsetCommand() : CommandRunner("offset") {
    this->add_description("Split the dataset into several subsets.");
    this->add_argument("annotations")
            .help("Annotations (Label) 資聊夾路徑");

    this->add_argument("offset")
            .help("Class 要偏移的數值")
            .scan<'i', int>();

    this->add_argument("--out")
            .help("存放輸出檔案的資聊夾位置")
            .default_value("offset_result");
}

void OffsetCommand::run() {
    auto dataset = std::filesystem::directory_entry(this->get<std::string>("annotations"));

    if (!dataset.is_directory())
    {
        std::cerr << "can't find directory of dataset  in " << dataset << std::endl;
        exit(-1);
    }

    std::vector<std::string> files;

    for (const auto & file :std::filesystem::directory_iterator(dataset)) {
        files.push_back(file.path());
    }

    const auto result = std::filesystem::path(this->get<std::string>("out"));
    const auto offset = this->get<int>("offset");

    for (const auto& file_name : files)
    {
        auto file = std::filesystem::path(file_name);
        auto target = result / file.filename();
        utility::annotations::dark_net_offset(absolute(file), offset, absolute(target));
        std::cout  << "change "<< absolute(file) << " to " << absolute(target) << "by offset " << offset << '\n';
    }

}



