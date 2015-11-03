#include <cstdlib>
#include "global.h"
#include "SyncHandler.h"


SyncHandler::SyncHandler() {}


void SyncHandler::xpost() {
  int op;
  string s_op = request->getParam(S_SYNC_OP);
  string s_table = request->getParam(S_SYNC_NAME);

  // debug
  std::cout << "op: " << s_op << ", table: " << s_table << std::endl;

  parentId = request->getParam(S_SYNC_PARENT_ID);
  std::string s_polymorph = request->getParam(S_SYNC_POLYMORPH);

  std::string s_parentField = request->getParam(S_SYNC_PARENT_FIELD);
  if (!s_parentField.empty()) {
    try {
      parentField = std::stoi(s_parentField);
    } catch (...) {
    }
  }

  if (s_op.empty() or s_table.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  try {
    op = std::stoi(s_op);
    table = std::stoi(s_table);
  } catch (...) {
    op = SYNC_OP_NONE;
  }

  if (op == SYNC_OP_NONE) {
    response.status = shot::HTTP_400;
    return;
  }

  if (not s_polymorph.empty()) {
    try {
      polymorph = std::stoi(s_polymorph);
    } catch (...) {
    }
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

  world.update(table, id, params, parentId, parentField, polymorph,
      response.content);
}


void SyncHandler::opInsert() {
  string beforeId = request->getParam(S_SYNC_BEFOREID);
  string obj = request->getParam(S_SYNC_OBJ);

  if (obj.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  world.insert(table, beforeId, obj, parentId, parentField, polymorph,
      response.content);
}


void SyncHandler::opAppend() {
  string obj = request->getParam(S_SYNC_OBJ);

  if (obj.empty()) {
    // debug
    std::cout << "SyncHandler.opAppend\n";

    response.status = shot::HTTP_400;
    return;
  }

  std::string beforeId;
  world.insert(table, beforeId, obj, parentId, parentField, polymorph,
      response.content);
}


void SyncHandler::opRemove() {
  string id = request->getParam(S_SYNC_ID);

  if (id.empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  world.remove(table, id, parentId, parentField, polymorph);
}


void SyncHandler::opMove() {
  string beforeId = request->getParam(S_SYNC_BEFOREID);
  string id = request->getParam(S_SYNC_ID);
  
  // empty beforeId allowed, means move to the end
  /* if (id.empty()) { */
  /*   response.status = shot::HTTP_400; */
  /*   return; */
  /* } */

  world.move(table, id, beforeId, parentId, parentField);
}
