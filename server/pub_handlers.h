#ifndef WEBAPP_PUB_HANDLERS_H
#define WEBAPP_PUB_HANDLERS_H


#include "shot/HtmlTemplate.h"
#include "shot/Handler.h"
#include "shot/AppHandler.h"


namespace pub {


shot::Handler* factory(shot::Request* request);
shot::Handler* syncFactory(shot::Request* request);


class AppHandler: public shot::AppHandler {
public:
  void get();
};


class InitHandler: public shot::Handler {
public:
  void xget();
  void ensureUser();
};


class BaseTemplate: public shot::HtmlTemplate {
public:
  BaseTemplate();
};


class MainTemplate: public BaseTemplate {
public:
  MainTemplate();
};


class MainHandler: public shot::Handler {
public:
  void get();
};


class ContactTemplate: public BaseTemplate {
public:
  ContactTemplate();
};


class ContactHandler: public shot::Handler {
public:
  void get();
};

  
} /* namespace pub */


#endif /* end of include guard: WEBAPP_PUB_HANDLERS_H */
