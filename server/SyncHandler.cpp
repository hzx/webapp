#include <cstdlib>
#include "global.h"
#include "SyncHandler.h"


SyncHandler::SyncHandler() {}


void SyncHandler::xpost() {
  int op;
  string s_op = request->getParam(S_SYNC_OP);
  string name = request->getParam(S_SYNC_NAME);

  if (s_op.empty() or name.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  try {
    op = std::atoi(s_op.data());
    table = atoi(name.data());
  } catch (...) {
    op = SYNC_OP_NONE;
  }

  if (op == SYNC_OP_NONE) {
    return;
  }

  response.setTextHeader();

  switch (op) {
    case SYNC_OP_UPDATE:
      opUpdate();
      break;
    case SYNC_OP_INSERT:
      opInsert();
      break;
    case SYNC_OP_APPEND:
      opAppend();
      break;
    case SYNC_OP_REMOVE:
      opRemove();
      break;
    case SYNC_OP_MOVE:
      opMove();
      break;
    default:
      response.status = shot::HTTP_400;
      break;
  }
}


void SyncHandler::opUpdate() {
  string id = request->getParam(S_SYNC_ID);
  string params = request->getParam(S_SYNC_PARAMS);

  if (id.empty() or params.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  ostringstream updates;
  world.update(table, id, params, updates);

  response.content << updates.str();
}


void SyncHandler::opInsert() {
  string beforeId = request->getParam(S_SYNC_BEFOREID);
  string obj = request->getParam(S_SYNC_OBJ);

  if (beforeId.empty() or obj.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  ostringstream updates;
  /* world.insert(table, beforeId, obj, updates); */

  response.content << updates.str();
}


void SyncHandler::opAppend() {
  string obj = request->getParam(S_SYNC_OBJ);

  if (obj.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  ostringstream updates;
  /* world.append(table, obj, updates); */

  response.content << updates.str();
}


void SyncHandler::opRemove() {
  string id = request->getParam(S_SYNC_ID);

  if (id.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  /* world.remove(table, id); */
}


void SyncHandler::opMove() {
  string beforeId = request->getParam(S_SYNC_BEFOREID);
  string id = request->getParam(S_SYNC_ID);
  
  // empty beforeId allowed, means move to the end
  if (id.empty()) {
    response.status = shot::HTTP_400;
    return;
  }
}
