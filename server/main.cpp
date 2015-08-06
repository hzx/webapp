#include <iostream>
#include "shot/Options.h"
#include "shot/Server.h"
#include "shot/system_handlers.h"
#include "global.h"
#include "login_handlers.h"
#include "pub_handlers.h"
#include "admin_handlers.h"
#include "SitemapHandler.h"


int main(int argc, const char *argv[]) {
  shot::Options& options = shot::Options::instance();
  int error = options.parseCmd(argc, argv);
  if (error != 0) {
    std::cout << "parse server.options cmd params error: " << error << '\n';
    return error;
  }

  options.cookieSecret = "";
  options.dbname = "test";

  shot::type_factories factories = {
    {"login", login::factory},

    {"d", shot::factory<pub::AppHandler>},
    {"init", shot::factory<pub::InitHandler>},
    {"", shot::factory<pub::MainHandler>},
    {"contact", shot::factory<pub::ContactHandler>},

    {"admin", admin::factory},

    {"noscript", shot::factory<shot::NoscriptHandler>},
    {"static", shot::factory<shot::StaticHandler>},
    {"favicon.ico", shot::factory<shot::FaviconHandler>},
    {"robots.txt", shot::factory<shot::RobotsHandler>},

    {"sitemap.xml", shot::factory<SitemapHandler>},
#ifdef DEBUG
    {"debug", shot::factory<shot::DebugHandler>},
#endif
  };

  error = app.init();
  if (error < 0) {
    std::cout << "app init error: " << error << '\n';
    return error;
  }
  
  server.setFactories(factories);
  server.run();

  return server.getErrorCode();
}
