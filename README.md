# WebServer_Base_Muduo
基于(重写)muduo库的webserver，结合了My_webserver[](https://github.com/greyjoy-wh/My_website)的 **日志**、**连接池**，**传递文件**的思路，但是主要的建立连接以及读写方式是基于muduo。
主要特点如下：
1. 原来的webserver是epoll + 线程池的方案（单reactor+多线程），主线程负责新链接的建立以及接收读写事件并且写入消息队列中。线程池中线程循环从消息队列中取出事件并且执行。改进后主线程(main-reactor)只负责建立连接，将新链接的fd发送给子线程(subreactor),由子线程来管理这些已经建立连接的读写事件
2. 利用了eventfd唤醒的方式来给子线程添加执行函数（例如添加fd），优化了多线程从消息队列中读取数据存在的并发问题
3. 采用大量的回调函数，实现业务与读写的完全解耦，只需要新建立一个SERVER类，写相应的读写事件，然后注册进TCPServer就好。
4. 使用 mmap + writev的方式实现零拷贝（虽然不是真正的零拷贝，但是比read + write 好太多了）。
5. 单例模式 + 阻塞队列实现日志系统，实现异步写入
6. 连接池优化了反复创建连接与销户的缺点 (后面三个特性跟原来的webserver类似)


## 测试
改成简单的返回hello页面后，webbench 下 1w个连接 5s QPS = 2.7w左右，原来的设计QPS在1.7w左右 （感觉没想象的提升的多）。

