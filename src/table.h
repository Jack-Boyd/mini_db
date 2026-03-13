#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "parser/parser.h"

using Value = std::variant<std::monostate, int64_t, double, std::string>;

struct Column
{
  std::string name;
  Value type;
  bool nullable;
};

struct Row
{
  std::vector<Value> m_values;
};

class Table 
{
public:
  Table(const CreateNode &create) : m_name(create.tableName) {
    m_schema.reserve(create.columnDefs.size());
    for (const auto &col : create.columnDefs) {
      m_schema.push_back({col.name, col.type, col.nullable});
    }
  };
private:
  std::string m_name;
  std::vector<Column> m_schema;
  std::vector<Row> m_rows;
};
