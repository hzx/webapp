#ifndef KONFIRMAT_SYNCHANDLER_H
#define KONFIRMAT_SYNCHANDLER_H

#include <unordered_map>
#include "shot/Handler.h"
#include "shot/http.h"


int const SYNC_OP = 1;
char const S_SYNC_OP[] = "1";
int const SYNC_NAME = 2;
char const S_SYNC_NAME[] = "2";
int const SYNC_PARAMS = 3;
char const S_SYNC_PARAMS[] = "3";
int const SYNC_BEFOREID = 4;
char const S_SYNC_BEFOREID[] = "4";
int const SYNC_OBJ = 5;
char const S_SYNC_OBJ[] = "5";
int const SYNC_ID = 6;
char const S_SYNC_ID[] = "6";
int const SYNC_PARENT_ID = 7;
char const S_SYNC_PARENT_ID[] = "7";
int const SYNC_PARENT_FIELD = 8;
char const S_SYNC_PARENT_FIELD[] = "8";
int const SYNC_POLYMORPH = 9;
char const S_SYNC_POLYMORPH[] = "9";

int const SYNC_OP_NONE = 0;
int const SYNC_OP_UPDATE = 1;
int const SYNC_OP_INSERT = 2;
int const SYNC_OP_APPEND = 3;
int const SYNC_OP_REMOVE = 4;
int const SYNC_OP_MOVE = 5;


bool opUserAllowed(int const table, int const op);
bool opManagerAllowed(int const table, int const op);
bool opAdminAllowed(int const table, int const op);


class SyncHandler: public shot::Handler {
public:
  SyncHandler();
  void xpost();
  void opUpdate();
  void opInsert();
  void opAppend();
  void opRemove();
  void opMove();

  int table;
  std::string parentId;
  int parentField = 0;
  int polymorph = 0;
};


#endif /* end of include guard: KONFIRMAT_SYNCHANDLER_H */
