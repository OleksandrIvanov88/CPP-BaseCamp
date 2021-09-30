// networklayer.cpp
#include <boost/array.hpp>
#include "network.hpp"
#include "weather_error.hpp"

NetworkLayer::Network::Network(const ContextPtr& context_ptr,
                               IPAddress connectionIP)
    : context_ptr(context_ptr),
      connectionIP(connectionIP),
      stream(*context_ptr) {}


bool NetworkLayer::Network::start() {
  try {
    tcp::resolver resolver(*this->context_ptr);
    auto const results =
        resolver.resolve(this->connectionIP.host, this->connectionIP.port);
    stream.connect(results);
  } catch (const std::exception& e) {

    Log_error err("server connection error: ", e.what());
    err.print_error();
    return NET_FAILURE;
  } catch (...) {
   
    Log_error err("server connection error: (unknown type)");
    err.print_error(); 
    return NET_FAILURE;
  }
  return NET_SUCCESS;
}

void NetworkLayer::Network::send(const std::string& city_name,
                                 const std::string& token) {
  try {
    int version = 10;  // version 1.0
    //std::string target = "/data/2.5/weather?q=" + city_name + "&appid=" + token + "&units=metric";
    std::string target = "/data/2.5/weather?q=" + city_name + "&appid=" + token;
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, this->connectionIP.host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    p_send(req);
  } catch (const std::exception& e) {
    Log_error err("send to server:", e.what());
    err.print_error(); 
  } catch (...) {
    Log_error err("send to server: (unknown type)");
    err.print_error();
  }
}

std::string NetworkLayer::Network::receive() {
  http::response<http::dynamic_body> res{};
  try {
    res = p_receive();
  } catch (const std::exception& e) {
    
    Log_error err("receive from server:", e.what());
    err.print_error();
  } catch (...) {
 
    Log_error err("receive from server: (unknown type)");
    err.print_error();
  }

  try {
    // Gracefully close the socket
    boost::system::error_code error;
    stream.socket().shutdown(tcp::socket::shutdown_both, error);
    if (error && error != beast::errc::not_connected) {
      throw beast::system_error{error};
    }
  } catch (const std::exception& e) {
    Log_error err("socket closing: ", e.what());
    err.print_error();
  } catch (...) {
    Log_error err("socket closing: (unknown type)");
    err.print_error();
  }

  return boost::beast::buffers_to_string(res.body().data());
}

void NetworkLayer::Network::p_send(
    const http::request<http::string_body>& request) {
  boost::system::error_code error;
  http::write(this->stream, request, error);
  if (error) {
    throw boost::system::system_error(error);
  }
}

NetworkLayer::http::response<NetworkLayer::http::dynamic_body>
NetworkLayer::Network::p_receive() {
  http::response<http::dynamic_body> res;
  boost::system::error_code error;
  beast::flat_buffer buffer;
  http::read(stream, buffer, res, error);
  if (error) {
    throw boost::system::system_error(error);
  }

  return res;
}
