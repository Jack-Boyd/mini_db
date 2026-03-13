#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
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
  std::string create = "CREATE TABLE Persons ( PersonID int, LastName varchar(255), FirstName varchar(255), Address varchar(255), City varchar(255) )";
  std::string insert = "INSERT INTO Persons VALUES ( 0, Boyd, Jack, 20 Narra Ave, Auckland )";
  boost::char_separator<char> sep(" ,");
  boost::tokenizer<boost::char_separator<char>> tokenizerCreate(create, sep);
  boost::tokenizer<boost::char_separator<char>> tokenizerInsert(insert, sep);
  std::vector<std::string> tokensCreate(tokenizerCreate.begin(), tokenizerCreate.end());
  std::vector<std::string> tokensInsert(tokenizerInsert.begin(), tokenizerInsert.end());

  Parser parserCreate(tokensCreate);
  Parser parserInsert(tokensInsert);
  Statement statementCreate = parserCreate.parse();
  Statement statementInsert = parserInsert.parse();

  Table person_table(std::get<CreateNode>(statementCreate));
  person_table.insert(std::get<InsertNode>(statementInsert));

  std::cout << person_table.name() << std::endl;
  for (const auto &col : person_table.schema()) {
    std::cout << col.name << " ";
  }
    std::cout << std::endl;
  for (const auto &row : person_table.rows()) {
    for (const auto &value : row.values) {
      std::visit([](const auto &v) {
        using T = std::decay_t<decltype(v)>;

        if constexpr (std::is_same_v<T, std::monostate>)
          std::cout << "NULL ";
        else
          std::cout << v << " ";
      }, value);
    }
    std::cout << std::endl;
  }
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