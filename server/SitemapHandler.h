#ifndef KONFIRMAT_SITEMAPHANDLER_H
#define KONFIRMAT_SITEMAPHANDLER_H


#include "shot/Handler.h"


class SitemapHandler: public shot::Handler {
public:
  void get();
};


class SitemapInfoHandler: public shot::Handler {
public:
  void get();
};


class SitemapBoardHandler: public shot::Handler {
public:
  void get();
};


class SitemapBlogHandler: public shot::Handler {
public:
  void get();
};


#endif /* end of include guard: KONFIRMAT_SITEMAPHANDLER_H */
