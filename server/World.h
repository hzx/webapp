#ifndef WEBAPP_WORLD_H
#define WEBAPP_WORLD_H

#include <ostream>
#include <string>
#include "shot/DbClient.h"
#include "journal/models.h"
#include "journal/collections.h"
#include "collections.h"


class World {
public:
  World();
  bool init();

  void update(int table, std::string& id, std::string& params,
      std::string parentId, int parentField, int polymorph,
      std::ostream& updates);

  void insert(int table, std::string& beforeId, std::string& obj,
      std::string parentId, int parentField, int polymorph,
      std::ostream& updates);

  void remove(int table, std::string& id,
      std::string parentId, int parentField, int polymorph);

  void move(int table, std::string& id, std::string& beforeId,
      std::string parentId, int parentField);

  void storeInitColls(std::ostream& store);
  void getPageItems(std::string& pageId, int table, std::ostream& store);

  bool uploadFile(journal::FileUpload& fu,
      std::vector<shot::File>& files, std::ostream& store);

  shot::DbClient db;
  UserCollection users;
  journal::Collection mainPage;
  journal::Collection contactPage;
  journal::ItemsCollection items;
};


#endif /* end of include guard: WEBAPP_WORLD_HORLD_H */
