#pragma once

#include "table.h"

class Database 
{
public:
  Database();
private:
  std::vector<Table> m_tables;
};