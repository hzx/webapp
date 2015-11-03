#ifndef WEBAPP_COLLECTIONS_H
#define WEBAPP_COLLECTIONS_H

#include <string>
#include <vector>
#include <ostream>
#include "models.h"


class UserCollection {
public:
  UserCollection(shot::DbClient* db, char const* table);
  void genId(UserModel& user, std::ostream& updates);
  UserPtr get(std::string& id);
  UserPtr getByLogin(std::string& login);
  void update(std::string& id, UserModel& user, std::ostream& updates);
  void append(UserModel& user, std::ostream& updates);
  void remove(std::string& id);

  shot::DbClient* db;
  char const* table;
};


#endif /* end of include guard: WEBAPP_COLLECTIONS_H */
