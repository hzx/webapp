#ifndef WEBAPP_LOGIN_HANDLERS_H
#define WEBAPP_LOGIN_HANDLERS_H


#include "shot/AppHandler.h"


namespace login {


shot::Handler* factory(shot::Request* request);


class AppHandler: public shot::AppHandler {
public: 
  void get();
  void xpost();
};


class InitHandler: public shot::Handler {
public:
  void xget();
};


class LogoutHandler: public shot::Handler {
public:
  void xpost();
private:
  void logout();
};


class ForgotHandler: public shot::Handler {
public:
  void xpost();
};

  
} /* namespace login */


#endif /* end of include guard: WEBAPP_LOGIN_HANDLERS_H */
