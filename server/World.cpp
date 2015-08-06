#include "World.h"
#include "shot/Options.h"
#include "db_tables.h"


World::World()
  : users(TS_USER) {
}


int World::init() {
  shot::Options& options = shot::Options::instance();
  // init db client
  if (!db.init(options.dbhost, options.dbport,
      options.dbuser, options.dbpassword, options.dbname)) {
    return -1;
  }

  return 0; // ok
}


void World::update(int table, std::string& id, std::string& params, std::ostream& updates) {
}


void World::insert(int table, std::string& beforeId, std::string& obj, std::ostream& updates) {
}


void World::append(int table, std::string& obj, std::ostream& updates) {
}


void World::remove(int table, std::string& id) {
}


void World::move(int table) {
}


void World::storeInitColls(std::ostream& store) {
}
