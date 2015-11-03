#include "shot/utils.h"
#include "global.h"
#include "collections.h"


UserCollection::UserCollection(shot::DbClient* db, char const* table) {
  this->db = db;
  this->table = table;
}


void UserCollection::genId(UserModel& user, std::ostream& updates) {
  std::string id = shot::newId();
  user.id.set(id);
  updates << shot::ID << DF << user.id.value << DF;
}


UserPtr UserCollection::get(std::string& id) {
  if (id.length() < shot::OID_SIZE) return nullptr;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return nullptr;

  UserPtr user(new UserModel());
  user->fromDbFormat(obj);

  return user;
}


UserPtr UserCollection::getByLogin(std::string& login) {
  bson::bo obj = db->conn.findOne(table, BSON(UserModel::S_LOGIN << login));
  if (obj.isEmpty()) return nullptr;

  UserPtr user(new UserModel());
  user->fromDbFormat(obj);

  return user;
}


void UserCollection::update(std::string& id, UserModel& user, std::ostream& updates) {
  bson::bob builder;

  user.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void UserCollection::append(UserModel& user, std::ostream& updates) {
  if (user.id.value.length() < shot::OID_SIZE) genId(user, updates);
  if (user.password.value.length() > 0)
    user.password.set(shot::encodePassword(user.password.value));

  bson::bob builder;

  user.toDbFormat(builder);
  db->conn.insert(table, builder.obj());
}


void UserCollection::remove(std::string& id) {
  if (id.length() < shot::OID_SIZE) return;

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}
