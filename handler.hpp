#ifndef _HANDLER_HPP
#define _HANDLER_HPP
#include "ServerBase.hpp"
#include <fstream>

using namespace std;
using namespace server;

template<typename SERVER_TYPE>
void start_server(SERVER_TYPE &server)
{
  server.resource["^/string/?$"]["POST"] = [](ostream& response, Request& request){
    stringstream ss;
    *request.content>>ss.rdbuf();  // 读取请求内容到stringstream中
    string content = ss.str();
    response<< "HTTP/1.1 200 OK\r\nContent-Length: "<<content.length()<<"\r\n\r\n"<<content;
  };

  server.resource["^/info/?$"]["GET"]=[](ostream& response, Request& request){
    stringstream content_stream;
    content_stream<<"<h1>Request:</h1>";
    content_stream<<request.method<<"  "<<request.path<<"HTTP/"<<request.http_version<<"<br>";
    for(auto& header:request.header)
    {
      content_stream<<header.first<<": "<<header.second<<"<br>";
    }

    //获得content_stream的长度 使用content.telp()
    content_stream.seekp(0, ios::end);
    response <<"HTTP/1.1 200 OK\r\nContent-Length: "<<content_stream.tellp()<<"\r\n\r\n"<<content_stream.rdbuf();
  };

  server.resource["^match/([0-9a-zA-Z]+)/?$"]["GET"]=[](ostream& response, Request& request){
    string number = request.path_match[1];
    response<<"HTTP/1.1 200 OK\r\nContent-Length"<<number.length()<<"\r\n\r\n"<<number;  
  };

  //处理默认GET请求，如果没有其他匹配成功，则该匿名函数会被调用
  //将
  server.default_resource["^/?(.*)$"]["GET"]=[](ostream& response, Request& request){
    string filename = "www/";
    string path = request.path_match[1];

    //防止使用../ 访问web目录外的内容
    size_t last_pos = path.rfind(".");
    size_t current_pos = 0;
    size_t pos;
    while((pos = path.find(".", current_pos) != string::npos && pos != last_pos))
    {
      current_pos = pos;
      path.erase(pos, 1);
      last_pos--;
    }

    filename += path;

    ifstream ifs;
    if(filename.find(".") == string::npos)
    {
      if(filename[filename.length() - 1] != '/')
        filename += '/';
      filename += "index.html";
    }

    ifs.open(filename, ifstream::in);

    if(ifs)
    {
      ifs.seekg(0, ios::end);
      size_t length = ifs.tellg();
      ifs.seekg(0, ios::beg);

      //文件内容拷贝到 response-stream中，不应该用于大型文件
      response<<"HTTP/1.1 200 OK\r\nContent-Length: "<<length<<"\r\n\r\n"<<ifs.rdbuf();

      ifs.close();
    }
    else
    {
      string content = "Could not open file " + filename;
      response<<"HTTP/1.1 400 Bad Request\r\nContent-Length: "<<content.length()<<"\r\n\r\n" <<content;
    }
  };

  //运行 HTTP服务器
  server.start();
}

#endif
