#include "src/HttpServer.h"
#include "src/HttpRequest.h"
#include "src/HttpResponse.h"
#include "src/EventLoop.h"
#include "log/log.h"

#include <iostream>
#include <map>


int main(int argc, char const *argv[])
{

  // 需要修改的数据库信息,登录名,密码,库名
  std::string user = "debian-sys-maint";
  std::string passwd = "PswKne1nJmoPbncQ";
  std::string databasename = "webserver";
  int sqlNum = 8;
  int numThreads = 3;
  Log::get_instance()->init("./ServerLog", 0, 2000, 800000, 800);
  EventLoop loop;
  HttpServer server(&loop, InetAddress(9005), "webserver", user, passwd, databasename, sqlNum);
  server.setThreadNum(numThreads);
  server.start();
  loop.loop();

  return 0;
}

