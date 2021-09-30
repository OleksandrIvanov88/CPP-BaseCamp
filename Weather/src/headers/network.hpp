#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace NetworkLayer {
namespace beast = boost::beast;
namespace http = beast::http;
namespace ip = boost::asio::ip;
using tcp = ip::tcp;
using ContextPtr = std::shared_ptr<boost::asio::io_context>;

typedef struct IPAddress {
  std::string host;
  std::string port;
} IPAddress;

class Network {
 public:
  /**
   * @brief Ctor
   * @param context_ptr - smart pointer to io_context
   * @param connectionIP - structure that contains host and port for connection
   * */

  explicit Network(const ContextPtr& context_ptr, IPAddress connectionIP);
  /**
   * @brief Connection to server
   * @returns successful connection
   * */
  bool start();

  /**
   * @brief Prepare request and call p_send
   * */
  void send(const std::string& city_name, const std::string& token);

  /**
   * @brief Convert response to string
   * @returns Server response
   * */
  std::string receive();

 private:
  /**
   * @brief Send request to connectionIP
   * @param request - ready for send request
   * */
  void p_send(const http::request<http::string_body>& request);

  /**
   * @brief Receive server response
   * @returns server response
   * */
  http::response<http::dynamic_body> p_receive();

 private:
  NetworkLayer::ContextPtr context_ptr{nullptr};
  NetworkLayer::IPAddress connectionIP;
  beast::tcp_stream stream;

  enum STATUS_RETURN {
    NET_SUCCESS = 0,
    NET_FAILURE
  };
};
}  // namespace NetworkLayer