#include "shot/SitemapTemplate.h"
#include "SitemapHandler.h"


void SitemapHandler::get() {
  shot::SitemapIndexTemplate t;
  t.setPrefix("http://an.oldschooldev.com/");

  t.write("sitemap-info.xml");
  t.write("sitemap-board.xml");
  t.write("sitemap-blog.xml");

  response.setXmlHeader();
  response.content << t.toString();
}


void SitemapInfoHandler::get() {
  shot::SitemapUrlsetTemplate t;
  t.setPrefix("http://an.oldschooldev.com/");

  response.setXmlHeader();
  response.content << t.toString();
}


void SitemapBoardHandler::get() {
  shot::SitemapUrlsetTemplate t;
  t.setPrefix("http://an.oldschooldev.com/");

  response.setXmlHeader();
  response.content << t.toString();
}


void SitemapBlogHandler::get() {
  shot::SitemapUrlsetTemplate t;
  t.setPrefix("http://an.oldschooldev.com/");

  response.setXmlHeader();
  response.content << t.toString();
}
