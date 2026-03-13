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
  std::vector<Value> values;
};

class Table 
{
public:
  Table(const CreateNode &create) : m_name(create.tableName), m_noCols(create.columnDefs.size()){
    m_schema.reserve(m_noCols);
    for (const auto &col : create.columnDefs) {
      m_schema.push_back({col.name, col.type, col.nullable});
    }
  };

  void insert(const InsertNode &insert) {
    Row row;
    row.values.reserve(m_noCols);
    for (const auto &col : insert.values) {
      row.values.push_back(col);
    }
    m_rows.push_back(row);
  };
  
  const std::string &name() const { return m_name; }
  const std::vector<Column> &schema() const { return m_schema; }
  const std::vector<Row> &rows() const { return m_rows; }

private:
  std::string m_name;
  std::vector<Column> m_schema;
  std::vector<Row> m_rows;
  size_t m_noCols;
};
