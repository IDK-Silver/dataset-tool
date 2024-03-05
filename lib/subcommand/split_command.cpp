//
// Created by idk on 2024/2/24.
//

#include "split_command.h"


SplitCommand::SplitCommand() : CommandRunner("split")
{
    this->add_description("Split the dataset into several subsets.");
    this->add_argument("dataset")
            .help( "Dataset 路徑");

    this->add_argument("--train")
            .default_value("train");

    this->add_argument("--val")
            .default_value("val");

    this->add_argument("--test")
            .default_value("test");

    this->add_argument("--annotations", "--label")
            .default_value("");

    this->add_argument("--annotations_extension", "--label_ext")
            .default_value("xml");

    this->add_argument("--proportion", "--p")
            .help("The proportions of sub dataset (train, val, test)")
            .nargs(3)
            .default_value(std::vector<double>{ 0.7, 0.2, 0.1 })
            .scan<'g', double>();
}

void SplitCommand::run()
{
    // load the dataset
    auto dataset = std::filesystem::directory_entry(this->get<std::string>("dataset"));

    // check dataset's path is directory
    if (!dataset.is_directory())
    {
        std::cerr << "can't find dataset directory in " << dataset << std::endl;
        exit(-1);
    }

    // the files that are under dataset
    std::vector<std::string> files;

    // add each file to files
    for (const auto & file :std::filesystem::directory_iterator(dataset)) {
        files.push_back(file.path());
    }

    // get the subset names
    auto subset_names = std::vector<std::string> {
            this->get<std::string>("train"),
            this->get<std::string>("val"),
            this->get<std::string>("test")
    };

    // confirm whether to split annotation files.
    std::unique_ptr<std::filesystem::path> annotations = nullptr;
    if (!this->get<std::string>("annotations").empty())
    {
        annotations = std::make_unique<std::filesystem::path>(this->get<std::string>("annotations"));
    }

    // create subset directory
    for (const auto& name : subset_names) {

        std::filesystem::create_directory(
                std::filesystem::path(name)
        );


        // create directory of annotation
        if (annotations != nullptr) {
            std::filesystem::create_directory(
                    std::filesystem::path(name+ "_annotations" )
            );
        }

    }

    // get the proportions of subsets
    auto subset_proportions = this->get<std::vector<double>>("proportion");

    // check the proportion
    if (std::reduce(subset_proportions.begin(), subset_proportions.end()) > 1.0)
    {
        std::cerr << "sum of proportion must be 1";
        exit(-1);
    }

    // shuffle the file path
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(files), std::end(files), rng);


    const auto total_file_size = files.size();

    // split_command dataset to subset
    for (auto index = 0; index < subset_names.size(); index++)
    {
        auto subset = std::filesystem::path(subset_names.at(index));

        // cal the number of splits
        auto split_num = (uint32_t) ((uint32_t) total_file_size * subset_proportions.at(index));

        // if out range than set value to the dataset reminds
        if (split_num > (uint32_t) files.size())
            split_num = (uint32_t) files.size();

        // split files
        for (auto batch_remind = split_num; batch_remind > 0; batch_remind--)
        {
            auto file = std::filesystem::path(files.back());
            files.pop_back();

            std::filesystem::copy (
                    file, subset / file.filename()
            );


            // split annotation files
            if (annotations != nullptr)
            {
                auto annotation_file = file.stem().string() + "."+ this->get<std::string>("annotations_extension");

                std::filesystem::copy(
                    *annotations / annotation_file,
                    std::filesystem::path(subset.string()+ "_annotations" ) / annotation_file
                );
            }

        }

    }

}

