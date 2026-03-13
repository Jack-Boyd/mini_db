#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "parser/parser.h"
#include "table.h"

struct Person
{
  std::string name;
  int age;
  std::string phone;
};

int main() 
{
  std::string query = "CREATE TABLE Persons ( PersonID int, LastName varchar(255), FirstName varchar(255), Address varchar(255), City varchar(255) )";
  boost::char_separator<char> sep(" ,");
  boost::tokenizer<boost::char_separator<char>> tokenizer(query, sep);
  std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());

  Parser parser(tokens);
  Statement statement = parser.parse();

  Table person_table(std::get<CreateNode>(statement));
  return 0;
}

// int main()
// {
//   const std::string quitWord = "quit";

//   while (true) {
//     std::cout << "Enter Query: ";

//     std::string query;
//     std::getline(std::cin, query);

//     if (!std::cin) {
//       break;
//     }

//     if (query == quitWord) {
//       std::cout << "Exiting...\n";
//       break;
//     }

//     boost::char_separator<char> sep(" ,");
//     boost::tokenizer<boost::char_separator<char>> tokenizer(query, sep);
//     std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());

//     Parser parser(tokens);
//     Statement statement = parser.parse();
//   }

//   return 0;
// }
  // Person me = {"Jack", 29, "+447853251965"};
  // std::ofstream outfile;
  // outfile.open("db.dat", std::ios::binary | std::ios::out);
  // outfile.write(reinterpret_cast<const char*>(&me), sizeof(me));
  // outfile.close();

  // Person p;
  // std::ifstream infile("db.dat", std::ios::binary | std::ios::in);
  // infile.read(reinterpret_cast<char *>(&p), sizeof(p));