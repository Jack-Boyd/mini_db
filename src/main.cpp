#include <boost/tokenizer.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "parser/parser.h"

int main()
{
  const std::string quitWord = "quit";

  while (true) {
    std::cout << "Enter Query: ";

    std::string query;
    std::getline(std::cin, query);

    if (!std::cin) {
      break;
    }

    if (query == quitWord) {
      std::cout << "Exiting...\n";
      break;
    }

    boost::char_separator<char> sep(" ,");
    boost::tokenizer<boost::char_separator<char>> tokenizer(query, sep);
    std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());

    Parser parser(tokens);
    Statement statement = parser.parse();
  }

  return 0;
}