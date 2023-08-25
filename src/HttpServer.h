//HttpServer.h
#pragma once

#include "TcpServer.h"
#include "noncopyable.h"
#include "EventLoop.h"
#include <string>
#include "../SqlConnection/SqlConnectionPool.h"
#include <sys/stat.h>

class HttpRequest;
class HttpResponse;


class HttpServer : noncopyable
{
  public:
    typedef std::function<void (const HttpRequest&,
                                HttpResponse*)> HttpCallback;

    HttpServer(EventLoop* loop,
              const InetAddress& listenAddr,
              const std::string& name,
              const std::string& user,
              const std::string& password,
              const std::string& databaseName,
              int sqlNum,
              TcpServer::Option option = TcpServer::kNoReusePort);

    EventLoop* getLoop() const { return server_.getLoop(); }

  
    void setHttpCallback(const HttpCallback& cb)
    {
      httpCallback_ = cb;
    }

    void setThreadNum(int numThreads)
    {
      server_.setThreadNum(numThreads);
    }

    void start();

  private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn,
                  Buffer* buf,
                  Timestamp receiveTime);
    void onRequest(const TcpConnectionPtr&, const HttpRequest&);
    void onWriteComplete(const TcpConnectionPtr &conn);
    void initmysql(ConnectionPool *connPool);
    void onHttpProcess(const HttpRequest &req, HttpResponse *resp);

    
    TcpServer server_;
    HttpCallback httpCallback_;
    ConnectionPool *connPool_;      // 数据库相关
    std::string user_;              // 登陆数据库用户名
    std::string passwd_;            // 登陆数据库密码
    std::string databaseName_;      // 使用数据库名
    int sqlNum_;
    std::map<std::string, std::string> users;
    char* mmap_file;
    struct stat fileStat;
};



