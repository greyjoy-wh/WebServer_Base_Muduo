//HttpResponse.h

#pragma once
#include "copyable.h"
//#include "Types.h"

#include <map>


//响应报文保存在该类中

class Buffer;
class HttpResponse : public copyable
{
 public:
  enum HttpStatusCode
  {
    kUnknown,
    k200Ok = 200, //报文收到正确处理
    k301MovedPermanently = 301,//重定向
    k400BadRequest = 400,//请求报文有误
    k404NotFound = 404,//没有找到资源
  };

  explicit HttpResponse(bool close)
    : statusCode_(kUnknown),
      closeConnection_(close)
  {
  }

  void setStatusCode(HttpStatusCode code)
  { statusCode_ = code; }

  void setStatusMessage(const std::string& message)
  { statusMessage_ = message; }

  void setCloseConnection(bool on)
  { closeConnection_ = on; }

  bool closeConnection() const
  { return closeConnection_; }

  void setContentType(const std::string& contentType)
  { addHeader("Content-Type", contentType); }

  // void setContentLength(int length)
  // {
  //     addHeader("Content-Length", std::to_string(length));
  // }

  // FIXME: replace string with StringPiece
  void addHeader(const std::string& key, const std::string& value)
  { headers_[key] = value; }

  void setBody(const std::string& body)
  { body_ = body; }
  void setFile(std::string file)
  {
      g_file = file;
  }
  std::string g_file;
  void appendToBuffer(Buffer* output) const;

 private:
  std::map<std::string, std::string> headers_;
  HttpStatusCode statusCode_;//状态码
  // FIXME: add http version
  std::string statusMessage_;
  bool closeConnection_;//是否关闭连接
public:
  std::string body_;//正文
};



