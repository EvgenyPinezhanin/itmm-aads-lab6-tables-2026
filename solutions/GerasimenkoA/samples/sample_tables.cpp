// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Пинежанин Е.С.
//
// Тестирование работы с таблицами
//
// Для обеспечения работоспособности примера нужно заменить названия классов и хедеров

#include <iostream>
#include <vector>

#include <itable.h>
#include <Disordered_Linear_Table.h>
#include <Random_Search_Tree.h>
#include <Division_ChainHash_Table.h>
#include <Linear_OpenHash_Table.h>

using namespace std;

int main()
{
  vector<ITable<int>*> tables(4);

  Disordered_Linear_Table<int> linear_table;
  Random_Search_Tree<int> search_tree;
  Division_ChainHash_Table<int> hash_chain;
  Linear_OpenHash_Table<int> hash_open;

  tables[0] = &linear_table;
  tables[1] = &search_tree;
  tables[2] = &hash_chain;
  tables[3] = &hash_open;

  for (auto table : tables)
  {
      table->insert("5", 5);
      cout << table->find("5") << "\n";
      table->remove("5");

      try {
          cout << table->find("5") << "\n";
      }
      catch (const out_of_range&) {
          cout << "not found\n";
      }
  }

  return 0;
}
