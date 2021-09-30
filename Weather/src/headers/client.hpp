#pragma once
#include <memory>
#include <string>

#include "network.hpp"

namespace ClientLayer {
  using tcp = NetworkLayer::tcp;

  class Client {
  public:
  /**
   * @brief Ctor
   * @param context_ptr - smart pointer to io_context
   * @param host - server address
   * @param port - server port
   * */
  Client(const NetworkLayer::ContextPtr& context_ptr, std::string host,
          std::string port);

  /**
   * @brief Main function that connections to server, sends request and shows
   * result
   * */
  void process();

  void setCity(const std::string& city_name);
  void setToken(const std::string& token);

  private:
  std::shared_ptr<NetworkLayer::Network> m_connection{nullptr};
  std::string city_name{""};
  std::string token{""};
  struct {
    std::string city;
    double temp{0};
    double wind_s{0};
    double wind_d{0};
  } weather_data;

  enum STATUS_RETURN {
    PARS_NOVALIDTOKEN = 1,
    PARS_NOVALIDCITY = 1,
    PARS_STDEX = 1,
    PARS_UNKNOWN = 1,
    PARS_SUCCESS = 0
  };

  private:
  /**
   * @brief json parsing for city, temp, wind's speed and direction
   * @param ss - json stringstream
   * */
  bool parce_json(std::stringstream& ss);

  /**
   * @brief display weather info for the city
   * */
  void print_weather_data();
  };
}  // namespace ClientLayer