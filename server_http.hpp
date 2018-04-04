#ifndef SERVER_HTTP_HPP
#define SERVER_HTTP_HPP
#include "ServerBase.hpp"

namespace server{

typedef boost::asio::ip::tcp::socket HTTP;
template<>
class Server<HTTP> : public ServerBase<HTTP>
{
public:
  //通过端口、线程数来构造web服务器，http服务器比较简单，不需要做相关配置文件的初始化
  Server(unsigned short port, size_t num_threads = 1) : ServerBase<HTTP>::ServerBase(port, num_threads){};

private:
  void accept()
  {
    auto socket = std::make_shared<HTTP>(m_io_service);
    acceptor.async_accept(*socket,[this, socket](const boost::system::error_code& ec){
      accept();
      if(! ec)
      {
        process_request_and_respond(socket);
      }
    });
  }
};
}

#endif
