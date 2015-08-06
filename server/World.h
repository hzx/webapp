#ifndef WEBAPP_WORLD_H
#define WEBAPP_WORLD_H


#include <ostream>
#include <string>
#include "shot/DbClient.h"
#include "collections.h"


class World {
public:
  World();
  int init();

  void update(int table, std::string& id, std::string& params, std::ostream& updates);
  void insert(int table, std::string& beforeId, std::string& obj, std::ostream& updates);
  void append(int table, std::string& obj, std::ostream& updates);
  void remove(int table, std::string& id);
  void move(int table);

  void storeInitColls(std::ostream& store);

  shot::DbClient db;
  UserCollection users;
};


#endif /* end of include guard: WEBAPP_WORLD_HORLD_H */
