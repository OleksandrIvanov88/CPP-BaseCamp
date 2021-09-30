// client.cpp
#include "client.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

#include "weather_error.hpp"

template <typename T>
static std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

ClientLayer::Client::Client(const NetworkLayer::ContextPtr& context_ptr,
                            std::string host, std::string port)
    : m_connection(std::make_shared<NetworkLayer::Network>(
          NetworkLayer::Network(context_ptr, {host, port}))) {}

void ClientLayer::Client::process() {
  if (this->m_connection->start()) {
    std::cout << "Can't reach server" << std::endl;
    exit(0);
  }
  this->m_connection->send(this->city_name, this->token);
  std::stringstream ss(this->m_connection->receive());
  if (this->parce_json(ss)) {
    exit(0);
  }
  this->print_weather_data();
}

void ClientLayer::Client::setCity(const std::string& city_name) {
  this->city_name = city_name;
  if (this->city_name.find('_') != std::string::npos) {
    std::replace(this->city_name.begin(), this->city_name.end(), '_', ' ');
  }
}

void ClientLayer::Client::setToken(const std::string& token) {
  this->token = token;
}

bool ClientLayer::Client::parce_json(std::stringstream& ss) {
  boost::property_tree::ptree pt;

  try {
    boost::property_tree::read_json(ss, pt);
    if (pt.get_child("cod").get_value<int32_t>() == 401) {
      std::cout << pt.get_child("message").get_value<std::string>() << std::endl;
      return PARS_NOVALIDTOKEN;
    }
    if (pt.get_child("cod").get_value<int32_t>() == 404) {
      std::cout << "Can't get weather in " << this->city_name << std::endl;
      return PARS_NOVALIDCITY;
    }
    this->weather_data.city = pt.get_child("name").get_value<std::string>();
    this->weather_data.temp =
        pt.get_child("main").get_child("temp").get_value<double>();
    this->weather_data.wind_s =
        pt.get_child("wind").get_child("speed").get_value<double>();
    this->weather_data.wind_d =
        pt.get_child("wind").get_child("deg").get_value<double>();
  } catch (const std::exception& e) {
    Log_error err("json parsing error: ", e.what());
    err.print_error();
    return PARS_STDEX;
  } catch (...) {
    Log_error err("json parsing error: (unknown type)");
    err.print_error();
    return PARS_UNKNOWN;
  }
  return PARS_SUCCESS;
}

void ClientLayer::Client::print_weather_data() {
  std::cout << "City: " << this->weather_data.city << std::endl
            << "Temperature: " << to_string_with_precision(std::round(this->weather_data.temp - 273.5), 0) << "°C"
            << std::endl
            << "Wind's speed: " << to_string_with_precision(this->weather_data.wind_s, 2) << " meter/sec"
            << std::endl
            << "Wind's direction: " << to_string_with_precision(this->weather_data.wind_d,0) << "°"
            << std::endl;
}