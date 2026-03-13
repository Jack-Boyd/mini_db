#pragma once

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "parser/ast.h"

class Parser
{
public:
  Parser(const std::vector<std::string> &tokens)
    : m_tokens(tokens), m_pos(0) {}
  Parser(std::vector<std::string> &&tokens)
    : m_tokens(std::move(tokens)), m_pos(0) {}

  Statement parse()
  {
    const std::string &keyword = peek();
    if (keyword == "SELECT") { return parseSelect(); }
    if (keyword == "INSERT") { return parseInsert(); }
    if (keyword == "CREATE") { return parseCreate(); }

    throw std::runtime_error("Unexpected token: " + peek());
  }

private:
  std::vector<std::string> m_tokens;
  size_t m_pos;

  const std::string &peek() const
  {
    if (m_pos >= m_tokens.size())
      throw std::runtime_error("Unexpected end of input");

    return m_tokens[m_pos];
  }
  
  std::string next() 
  {
    std::string word = peek();
    m_pos++;
    return word;
  }

  void expect(const std::string& expected) 
  {
    const std::string &word = toUpper(next());
    if (word != expected) {
      throw std::runtime_error("Expected '" + expected + "', got '" + word + "'");
    }
  }

  bool atEnd() const { return m_pos >= m_tokens.size(); }

  bool checkKeyword(const std::string& kw) const {
    return !atEnd() && toUpper(peek()) == kw;
  }

  static std::string toUpper(std::string word) 
  {
    std::transform(
      word.begin(), 
      word.end(), 
      word.begin(), 
      [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return word;
  }

  SelectNode parseSelect()
  {
    SelectNode node;
    expect("SELECT");

    do {
      node.columns.push_back({next()});
    } while (!checkKeyword("FROM") && !atEnd());

    expect("FROM");
    node.tableName = {next()};

    if (!atEnd() && checkKeyword("WHERE")) {
      next(); 
      Condition cond;
      cond.column = next();
      cond.op = next();
      cond.value = next();
      node.where = cond;
    }

    return node;
  }

  InsertNode parseInsert()
  {
    InsertNode node;
    expect("INSERT");
    expect("INTO");

    node.tableName = {next()};

    if (checkKeyword("(")) {
      next();
      while (!checkKeyword(")")) {
        node.columns.push_back(next());
      }
      expect(")");
    }

    expect("VALUES");

    expect("(");
    while (!checkKeyword(")")) {
      node.values.push_back(next());
    }
    expect(")");

    return node;
  }

  CreateNode parseCreate() {
    CreateNode node;
    expect("CREATE");
    expect("TABLE");

    node.tableName = {next()};

    expect("(");
    while (!checkKeyword(")")) {
      ColumnDef def;
      def.name = next();
      def.type = next();
      def.nullable = true;
      if (checkKeyword("NOT")) {
        next();
        if (checkKeyword("NULL")) {
          def.nullable = false;
          next();
        }
      }

      node.columnDefs.push_back(def);
    }
    expect(")");

    return node;
  }
};
