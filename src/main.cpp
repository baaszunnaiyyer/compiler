#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <optional>
#include <vector>
#include "./generation.hpp"
#include "./parser.hpp"
#include "./tokenization.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Incorrect Usage" << std::endl;
        std::cerr << "Example: hydro ../test.hy" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream content_stream;
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();
        contents = content_stream.str();
    }

    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = parser.parse_program();

    if (!prog.has_value()) {
        std::cerr << "invalid Program " << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(prog.value());

    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }

    system("nasm -felf64 out.asm");
    //system("ld -o out out.o");

    return EXIT_SUCCESS;
}
