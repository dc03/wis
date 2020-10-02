/* See LICENSE at project root for license details */
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "Scanner/Scanner.hpp"
#include "Token.hpp"

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1], std::ios::in);
    std::string source{std::istreambuf_iterator<char>{file},
                       std::istreambuf_iterator<char>{}};
    Scanner scanner{source};
    const std::vector<Token> &tokens{scanner.scan()};
    std::cout << '\n';
    // for (const auto& token : tokens) {
    //     std::cout << (token.lexeme == "\n" ? "\\n" : token.lexeme) << "\t\t|\t" << token.line << '\n';
    // }
}