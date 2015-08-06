#include "admin_handlers.h"
#include "shot/http.h"
#include "shot/system_handlers.h"
#include "global.h"
#include "SyncHandler.h"


namespace admin {


shot::type_factories factories({
  {"", shot::factory<AppHandler>},
  {"init", shot::factory<InitHandler>},
  {"main", shot::factory<MainHandler>},
  {"sync", shot::factory<SyncHandler>}
});


Handler* factory(Request* request) {
  auto userId = request->getSecureCookie("user");
  auto user = world.users.get(userId);
  if (not user.get()) {
    return new shot::RedirectHandler("/login");
  }

  // take second slug
  string slug = request->slugs.size() < 2 ? "" : request->slugs[1];

  // find factory
  auto it = factories.find(slug);
  if (it == factories.end()) return nullptr;

  return it->second(request);
}


void AppHandler::get() {
  appGet("Админка", "/static/admin.loader.js");
}


void InitHandler::xget() {
  setXsrf();
  response.setStreamHeader();
  response.content << getXsrf() <<
    shot::DELIM_FIELD << app.adminUrl <<
    shot::DELIM_FIELD;// << data;
}


void MainHandler::get() {
  response.setHtmlHeader();
  response.content << "";
}

  
} /* namespace admin */
