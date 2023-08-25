#pragma once

#include <memory>
#include <functional>

class Buffer;
class TcpConnection;
class Timestamp;


template <typename T>
inline T *get_pointer(const std::shared_ptr<T> &ptr)
{
    return ptr.get();
}

template <typename T>
inline T *get_pointer(const std::unique_ptr<T> &ptr)
{
    return ptr.get();
}

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void (const TcpConnectionPtr&)>;
using CloseCallback = std::function<void (const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void (const TcpConnectionPtr&)>;
using MessageCallback = std::function<void (const TcpConnectionPtr&,
                                        Buffer*,
                                        Timestamp)>;
using HighWaterMarkCallback = std::function<void (const TcpConnectionPtr&, size_t)>;