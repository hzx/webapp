#include "World.h"
#include <sstream>
#include "shot/Options.h"
#include "shot/utils.h"
#include "db_tables.h"


World::World()
    : users(&db, TS_USER)
    , mainPage(&db, TS_MAIN_PAGE, T_MAIN_PAGE, TS_PAGE_ITEMS)
    , contactPage(&db, TS_CONTACT_PAGE, T_CONTACT_PAGE, TS_PAGE_ITEMS)
    , items(&db, TS_PAGE_ITEMS) {
}


bool World::init() {
  auto& options = shot::Options::instance();

  // init db client
  if (!db.init(options.dbhost, options.dbport,
      options.dbuser, options.dbpassword, options.dbname)) {
    return false;
  }

  // save all document pages if not present
  mainPage.init();
  contactPage.init();

  return true;
}

void World::update(int table, std::string& id, std::string& params,
    std::string parentId, int parentField, int polymorph,
    std::ostream& updates) {
  // debug
  std::cout << "World::update, table: " << table << ", id: " << id <<
    ", params: " << params <<
    ", parentId: " << parentId << ", parentField: " << parentField <<
    ", polymorph: " << polymorph <<
    std::endl;

  switch (table) {
    case T_MAIN_PAGE:
      if (parentField == 0) {
        mainPage.updateRaw(id, params, updates);
      } else {
        mainPage.updateField(id, params, parentField, polymorph, updates);
      }
      break;
    case T_CONTACT_PAGE:
      if (parentField == 0) {
        contactPage.updateRaw(id, params, updates);
      } else {
        contactPage.updateField(id, params, parentField, polymorph, updates);
      }
      break;
  }
}

void World::insert(int table, std::string& beforeId, std::string& obj,
    std::string parentId, int parentField, int polymorph,
    std::ostream& updates) {
  // debug
  std::cout << "World::insert, table: " << table << ", beforeId: " <<
    beforeId << ", obj: " << obj << 
    ", parentId: " << parentId << ", parentField: " << parentField <<
    ", polymorph: " << polymorph <<
    std::endl;

  switch (table) {
    case T_MAIN_PAGE:
      if (not parentId.empty()) {
        mainPage.insertField(obj, beforeId, parentId, parentField,
            polymorph, updates);
      }
      break;
    case T_CONTACT_PAGE:
      if (not parentId.empty()) {
        contactPage.insertField(obj, beforeId, parentId, parentField,
            polymorph, updates);
      }
      break;
  }
}

void World::remove(int table, std::string& id,
    std::string parentId, int parentField, int polymorph) {
  // debug
  std::cout << "World.remove, table: " << table << ", id: " << id <<
    ", parentId: " << parentId << ", parentField: " << parentField <<
    ", polymorph: " << polymorph <<
    std::endl;

  switch (table) {
    case T_MAIN_PAGE:
      mainPage.removeField(id, parentId, parentField, polymorph);
      break;
    case T_CONTACT_PAGE:
      contactPage.removeField(id, parentId, parentField, polymorph);
      break;
  }
}

void World::move(int table, std::string& id, std::string& beforeId,
    std::string parentId, int parentField) {
  // debug
  std::cout << "World.move, table: " << table << ", id: " << id <<
    ", beforeId: " << beforeId <<
    ", parentId: " << parentId << ", parentField: " << parentField <<
    std::endl;

  switch (table) {
    case T_MAIN_PAGE:
      mainPage.moveField(id, beforeId, parentId, parentField);
      break;
    case T_CONTACT_PAGE:
      contactPage.moveField(id, beforeId, parentId, parentField);
      break;
  }
}


void World::storeInitColls(std::ostream& store) {
  journal::Journal mainJournal;
  journal::Journal contactJournal;

  mainPage.getFirst(mainJournal);
  contactPage.getFirst(contactJournal);

  store << T_MAIN_PAGE << shot::DELIM_ROW;
  mainJournal.toCompactFormat(store);
  store << shot::DELIM_ROW;

  store << T_CONTACT_PAGE << shot::DELIM_ROW;
  contactJournal.toCompactFormat(store);
}


void World::getPageItems(std::string& pageId, int table, std::ostream& store) {
  if (pageId.length() < shot::OID_SIZE) return;

  std::string itemsIds;

  switch (table) {
    case T_MAIN_PAGE:
      {
        journal::Journal doc;
        mainPage.getFirst(doc);
        itemsIds = shot::join(doc.items, ',');
      }
      break;
    case T_CONTACT_PAGE:
      {
        journal::Journal doc;
        contactPage.getFirst(doc);
        itemsIds = shot::join(doc.items, ',');
      }
      break;
    /* case T_ARTICLES: */
    /*   { */
    /*     auto doc = articles.get(pageId); */
    /*     if (doc.get() != nullptr) { */
    /*       itemsIds = shot::join(doc->items, ','); */
    /*     } */
    /*   } */
    /*   break; */
  }

  if (not itemsIds.empty()) {
    store << itemsIds << DR;
  }

  items.queryPageItems(pageId, store);
}


bool World::uploadFile(journal::FileUpload& fu,
    std::vector<shot::File>& files, std::ostream& store) {
  // debug
  std::cout << "World.uploadFile:\n";

  switch (fu.collection.value) {
    case T_PAGE_ITEMS:
      std::cout << "items:\n";
      return items.uploadFiles(fu, files, store);
  }

  return false;
}
