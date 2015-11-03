#include "UploadFileHandler.h"
#include <sstream>
#include <vector>
#include <string>
#include "shot/utils.h"
#include "journal/models.h"
#include "db_tables.h"
/* #include "session/models.h" */
#include "global.h"


void UploadFileHandler::xpost() {
  std::string obj = request->getHeader(shot::KL_HASH);
  std::ostringstream buf;

  // debug
  std::cout << "UploadFileHandler:\nobj: " << obj << "\n";

  if (obj.empty()) {
    response.status = 400;
    return;
  }

  std::cout << "after check obj empty\n";

  journal::FileUpload fu;
  fu.fromCustomCompactFormat(obj, ':');

  std::cout << "after fromCustomCompactFormat\n";

  if (!fu.collection.has or fu.collection.value == 0 or
      !fu.field.has or fu.field.value == 0 or
      !fu.objId.has or fu.objId.value.empty()) {
    response.status = 400;
    return;
  }

  std::cout << "after fu check\n";

  // keep files in tmp directory
  request->keepFiles = world.uploadFile(fu, request->files, response.content);

  std::cout << "after world.uploadFile\n";

  response.setStreamHeader();

  // save files to session
  /* for (auto& file: request->files) { */
  /*   session::FileModel f; */

  /*   f.name.set(file.name); */
  /*   f.filename.set(shot::getFilename(file.path)); */
  /*   if (not hash.empty()) f.bunchId.set(hash); */

  /*   world.sessionFiles.append(f); */ 

  /*   f.toCompactFormat(response.content); */
  /*   response.content << shot::DELIM_ROW; */
  /* } */
}
