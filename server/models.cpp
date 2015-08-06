#include "models.h"


std::string const UserModel::S_LOGIN = std::to_string(UserModel::LOGIN);
std::string const UserModel::S_PASSWORD = std::to_string(UserModel::PASSWORD);


std::string newId() {
  return mongo::OID::gen().toString();
}


int UserModel::fromDbFormat(bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(S_LOGIN)) login.set(obj.getField(S_LOGIN).String());
  if (obj.hasField(S_PASSWORD)) password.set(obj.getField(S_PASSWORD).String());
  return 0;
}


int UserModel::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case LOGIN:
      login.set(value);
      break;
    case PASSWORD:
      password.set(value);
      break;
  }
  return 0;
}


void UserModel::toDbFormat(bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (login.has) builder << S_LOGIN << login.value;
  if (password.has) builder << S_PASSWORD << password.value;
}


void UserModel::toCompactFormat(std::ostream& stream) {
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (login.has) stream << S_LOGIN << DF << login.value << DF;
  if (password.has) stream << S_PASSWORD << DF << password.value << DF;
}
