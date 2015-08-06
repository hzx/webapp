#include <sstream>
#include "shot/http.h"
#include "shot/Server.h"
#include "shot/utils.h"
#include "global.h"
#include "db_tables.h"
#include "login_handlers.h"


using std::ostringstream;


namespace login {


shot::type_factories factories({
  {"", shot::factory<AppHandler>},
  {"init", shot::factory<InitHandler>},
  {"logout", shot::factory<LogoutHandler>},
  {"forgot", shot::factory<ForgotHandler>},
});


shot::Handler* factory(shot::Request* request) {
  // take second slug
  string slug = request->slugs.size() < 2 ? "" : request->slugs[1];

  // find factory
  auto it = factories.find(slug);
  if (it == factories.end()) return nullptr;

  return it->second(request);
}
  

void AppHandler::get() {
  // if user logined redirect
  string userId = request->getSecureCookie("user");
  auto user = world.users.get(userId);

  if (user.get()) {
    redirectTemporarily("/admin");
    return;
  } else { // remove user cookie if not userId.empty() - if have user cookie
  }

  appGet("Логин", "/static/login.loader.js");
}


void AppHandler::xpost() {
  // get params
  auto login = request->getParam("login");
  auto password = request->getParam("password");

  // need for create new user
  /* ostringstream buf; */
  /* UserModel nuser; */
  /* nuser.login.set("admin"); */
  /* nuser.password.set("pass"); */
  /* world.users.append(nuser, buf); */
  /* return; */

  if (login.empty() or password.empty()) {
    setError(shot::HTTP_400, "Требуется логин и пароль");
    return;
  }

  auto user = world.users.getByLogin(login);

  if (!user.get() or !shot::checkPassword(password, user->password.value)) {
    setError(shot::HTTP_403, "Логин или пароль неверный");
    return;
  }

  response.setTextHeader();
  response.setSecureCookie("user", user->id.value.c_str());
  response.content << "/admin";
}


void InitHandler::xget() {
  setXsrf();
  response.setStreamHeader();
  response.content << getXsrf() <<
    shot::DELIM_FIELD << app.loginUrl <<
    shot::DELIM_FIELD;// << "";
}


void LogoutHandler::xpost() {
  logout();
}


void LogoutHandler::logout() {
  response.clearCookie("user");
  response.setTextHeader();
  /* response.content << ""; */
  /* redirectTemporarily("/login"); */
}


void ForgotHandler::xpost() {
  // send to user by login email
}


} /* namespace login */
