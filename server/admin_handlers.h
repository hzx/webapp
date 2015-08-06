#ifndef WEBAPP_ADMIN_HANDLERS_H
#define WEBAPP_ADMIN_HANDLERS_H


#include "shot/HtmlTemplate.h"
#include "shot/Handler.h"
#include "shot/AppHandler.h"


using shot::Handler;
using shot::Request;


namespace admin {
  

Handler* factory(Request* request);


class AppHandler: public shot::AppHandler {
public:
  void get();
};


class InitHandler: public shot::Handler {
public:
  void xget();
};


class MainHandler: public shot::Handler {
public:
  void get();
};


} /* namespace admin */



#endif /* end of include guard: WEBAPP_ADMIN_HANDLERS_H */
