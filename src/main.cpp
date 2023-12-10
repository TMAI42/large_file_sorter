

#include "helpers/helper_functions.hpp"

int main(int argc, char* argv[]) {

    // Simple command line interface
    if (argc == 3) {
        //sort(argv[1], argv[2]);
        return 0;
    } else if (argc == 2) {
        std::string arg = argv[1];
        if (arg.rfind("--generate=", 0) == 0) {
            std::string filename = arg.substr(11);
            helpers::generate_random_file_of_doubles(filename);
            return 0;
        } else if (arg.rfind("--iterate=", 0) == 0) {
            std::string filename = arg.substr(10);
            helpers::iterate_through_file(filename);
            return 0;
        }
    }

    // handle invalid input
    std::cerr << "Usage: <program> "
                 "\n\t--generate=filename  : Generate file of size 1GB with given name "
                 "\n\t--iterate=filename   : Iterate through file line by line"
                 "\n\tinputFile outputFile : Sort given inputFile into outputFile"
                 << std::endl;
    return 1;

}

