#pragma once

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <string>
// #include "../Logger.h"
#include <mutex>
#include <condition_variable>

class ConnectionPool
    {
    public:
        MYSQL *getConnection();              // 获取数据库连接
        bool releaseConnection(MYSQL *conn); // 释放连接
        int getFreeConn();                   // 获取连接
        void destroyPool();                  // 销毁所有连接

        // 单例模式
        static ConnectionPool *getInstance();

        void init(std::string url, std::string User, std::string PassWord, std::string DataBaseName, int Port, int MaxConn);

    private:
        ConnectionPool();
        ~ConnectionPool();

        int maxConn_;          // 最大连接数
        int curConn_;          // 当前已使用的连接数
        int freeConn_;         // 当前空闲的连接数
        std::list<MYSQL *> connList; // 连接池
        std::mutex mutex_;
        std::condition_variable condition_;

    public:
        std::string url_;          // 主机地址
        std::string port_;         // 数据库端口号
        std::string user_;         // 登陆数据库用户名
        std::string passwd_;     // 登陆数据库密码
        std::string databaseName_; // 使用数据库名
    };

    class ConnectionRAII
    {

    public:
        ConnectionRAII(MYSQL **con, ConnectionPool *connPool);
        ~ConnectionRAII();

    private:
        MYSQL *conRAII_;
        ConnectionPool *poolRAII_;
    };
