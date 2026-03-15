#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "parser/parser.h"
#include "table.h"

Statement generateStatement(const std::string &query) 
{
  boost::char_separator<char> sep(" ,");
  boost::tokenizer<boost::char_separator<char>> tokenizer(query, sep);
  std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());

  Parser parser(tokens);
  return parser.parse();
}

int main() 
{
  std::string create = "CREATE TABLE Persons ( PersonID int, LastName varchar(255), FirstName varchar(255), Address varchar(255), City varchar(255) )";
  std::string insert = "INSERT INTO Persons VALUES ( 0, Boyd, Jack, 20 Narra Ave, Auckland )";
  Statement statementCreate = generateStatement(create);
  Statement statementInsert = generateStatement(insert);

  Table person_table(std::get<CreateNode>(statementCreate));
  person_table.insert(std::get<InsertNode>(statementInsert));

  std::cout << person_table << std::endl;

  return 0;
}

// struct Person
// {
//   std::string name;
//   int age;
//   std::string phone;
// };
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