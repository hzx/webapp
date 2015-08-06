#ifndef WEBAPP_APP_H
#define WEBAPP_APP_H


#include <string>


class App {
public:
  int init();
  std::string createImagePath(std::string& name, int width, int height);
  std::string newImageName(std::string& prefix, std::string& filename);

  std::string imagePath;

  std::string pubUrl;
  std::string loginUrl;
  std::string adminUrl;
};


#endif /* end of include guard: WEBAPP_APP_H */
