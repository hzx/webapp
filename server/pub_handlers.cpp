#include "shot/http.h"
#include "global.h"
#include "pub_handlers.h"


namespace pub {


void AppHandler::get() {
  appGet("webapp", "/static/pub.loader.js");
}


void InitHandler::xget() {
  setXsrf();
  response.setStreamHeader();

  response.content << getXsrf() <<
    shot::DELIM_FIELD << app.pubUrl <<
    shot::DELIM_FIELD;// << data;

  world.storeInitColls(response.content);
}


void InitHandler::ensureUser() {
}


BaseTemplate::BaseTemplate() {
  lang = "ru";
  title = "webapp base";

  // redirect to client app
  head << R"(
<script type="text/javascript">
window.location = "/d#" + window.location.pathname + window.location.search;
</script>)";
}


MainTemplate::MainTemplate() {
  head << "<title>" << title << "</title>";
  body << "<h1>" << title << "</h1>";
}


void MainHandler::get() {
  MainTemplate templ;
  templ.title = "main page - " + templ.title;

  response.setHtmlHeader();
  response.content << templ.toString();
}


ContactTemplate::ContactTemplate() {
  head << "<title>" << title << "</title>";
  body << "<h1>" << title << "</h1>";
}


void ContactHandler::get() {
  ContactTemplate templ;
  templ.title = "contact page" + templ.title;

  response.setHtmlHeader();
  response.content << templ.toString();
}


void GetItemsHandler::xget() {
  // TODO: take all from params
  /* std::string pageId = request->getParam(journal::Node::S_PAGE_ID.c_str()); */
  /* std::string s_table = request->getParam(); */

  if (request->slugs.size() != 3 or request->slugs[1].empty() or
      request->slugs[2].empty()) {
    response.status = shot::HTTP_400;
    return;
  }

  std::string pageId = request->slugs[1];
  std::string s_table = request->slugs[2];

  int table;

  try {
    table = std::stoi(s_table);
  } catch (...) {
    response.status = shot::HTTP_400;
    return;
  }

  response.setStreamHeader();
  world.getPageItems(pageId, table, response.content);
}

  
} /* namespace pub */
