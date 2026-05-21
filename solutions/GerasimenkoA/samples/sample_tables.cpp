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
#include <tlineartable.h>
#include <tsearchtree.h>
#include <thashchain.h>
#include <thashopen.h>

using namespace std;

int main()
{
  vector<ITable<int>*> tables(4);

  TLinearTable<int> linear_table;
  TSearchTree<int> search_tree;
  THashChain<int> hash_chain;
  THashOpen<int> hash_open;

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
