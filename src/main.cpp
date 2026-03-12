#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

int main() {
  std::string query = "SELECT name,age FROM users";

  boost::char_separator<char> sep(" ,");
  boost::tokenizer<boost::char_separator<char>> tok(query, sep);

  for (const auto& token : tok) {
    std::cout << token << std::endl;
  }
}