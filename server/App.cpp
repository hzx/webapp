#include <iostream>
#include <sstream>
#include "shot/utils.h"
#include "shot/url.h"
#include "imgutil/imgutil.h"
#include "global.h"


using std::ostringstream;
using std::cout;
using std::endl;


int App::init() {
  initLib();

  pubUrl = shot::staticUrl("/static/pub.js");
  loginUrl = shot::staticUrl("/static/login.js");
  adminUrl = shot::staticUrl("/static/admin.js");

  if (pubUrl.empty()) { cout << "pubUrl empty\n";  return false; }
  if (loginUrl.empty()) { cout << "loginUrl empty\n";  return false; }
  if (adminUrl.empty()) { cout << "adminUrl empty\n";  return false; }

  int error = world.init();
  if (error < 0) {
    std::cout << "world init fail: "  << error << '\n';
    return error;
  }

  return 0;
}


string App::createImagePath(string& name, int width, int height) {
  ostringstream buf;
  buf << imagePath << width << 'x' << height << '_' << name;
  return buf.str();
}


string App::newImageName(string& filename, string& prefix) {
  ostringstream buf;
  buf << imagePath << prefix << shot::randomFilename(filename);
  return buf.str();
}
