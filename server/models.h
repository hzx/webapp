#ifndef WEBAPP_MODELS_H
#define WEBAPP_MODELS_H


#include <string>
#include <vector>
#include <memory>
#include "shot/Model.h"
#include "shot/http.h"
#include "shot/values.h"


using namespace bson;


char const DF = shot::DELIM_FIELD;
char const DR = shot::DELIM_ROW;
/* size_t const OID_SIZE = 24; */
/* int const ID = 1; */
/* char const S_ID[] = "_id"; */


std::string newId();


class UserModel: public shot::Model {
public:
  static int const LOGIN = 2;
  static int const PASSWORD = 3;

  static std::string const S_LOGIN;
  static std::string const S_PASSWORD;

  int fromDbFormat(bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bob& builder);
  void toCompactFormat(ostream& stream);

  shot::String id;
  shot::String login;
  shot::String password;
};
typedef std::unique_ptr<UserModel> UserPtr;



#endif /* end of include guard: WEBAPP_MODELS_H */
