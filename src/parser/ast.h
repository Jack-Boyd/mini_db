#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <optional>
#include <ostream>

struct SelectNode;
struct InsertNode;
struct CreateNode;

struct Column
{
  std::string name;
};

struct Table
{
  std::string name;
};

struct Condition
{
  std::string column;
  std::string op;
  std::string value;
};

struct ColumnDef
{
  std::string name;
  std::string type;
};

struct SelectNode
{
  std::vector<Column> columns;
  Table table;
  std::optional<Condition> where;
};

struct InsertNode
{
  Table table;
  std::vector<std::string> columns;
  std::vector<std::string> values;
};

struct CreateNode
{
  Table table;
  std::vector<ColumnDef> columnDefs;
};

using Statement = std::variant<SelectNode, InsertNode, CreateNode>;

std::ostream &operator<<(std::ostream &outs, const Column &col)
{
  return outs << col.name;
}

std::ostream &operator<<(std::ostream &outs, const Table &table)
{
  return outs << table.name;
}

std::ostream &operator<<(std::ostream &outs, const Condition &cond)
{
  return outs << cond.column << " " << cond.op << " " << cond.value;
}

std::ostream &operator<<(std::ostream &outs, const ColumnDef &def)
{
  return outs << def.name << " " << def.type;
}

std::ostream &operator<<(std::ostream &outs, const SelectNode &node)
{
  outs << "SELECT ";

  for (size_t i = 0; i < node.columns.size(); ++i) {
    if (i > 0) {
      outs << ", ";
    }
    outs << node.columns[i];
  }

  outs << " FROM " << node.table;

  if (node.where.has_value()) {
    outs << " WHERE " << *node.where;
  }

  return outs;
}

std::ostream &operator<<(std::ostream &outs, const InsertNode &node)
{
  outs << "INSERT INTO " << node.table;

  if (!node.columns.empty()) {
    outs << " (";
    for (size_t i = 0; i < node.columns.size(); ++i) {
      if (i > 0) {
        outs << ", ";
      }
      outs << node.columns[i];
    }
    outs << ")";
  }

  outs << " VALUES (";
  for (size_t i = 0; i < node.values.size(); ++i) {
    if (i > 0) {
      outs << ", ";
    }
    outs << node.values[i];
  }
  outs << ")";

  return outs;
}

std::ostream &operator<<(std::ostream &outs, const CreateNode &node)
{
  outs << "CREATE TABLE " << node.table << " (";

  for (size_t i = 0; i < node.columnDefs.size(); ++i) {
    if (i > 0) {
      outs << ", ";
    }
    outs << node.columnDefs[i];
  }

  outs << ")";
  return outs;
}

std::ostream &operator<<(std::ostream &outs, const Statement &stmt)
{
  std::visit(
      [&outs](const auto &node) {
        outs << node;
      },
      stmt);
  return outs;
}