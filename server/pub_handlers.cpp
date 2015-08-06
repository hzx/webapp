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

  
} /* namespace pub */
