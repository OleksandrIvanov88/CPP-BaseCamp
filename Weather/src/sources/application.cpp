// application.cpp
#include "application.hpp"

#include <fstream>
#include <iostream>

#include "client.hpp"
#include "weather_error.hpp"

namespace net = boost::asio;

Application::Application(int argc, char* argv[])
    : argc(argc), argv(argv), options("Options") {}

void Application::command_line_setup(void) {
  options.add_options()("help,h", "Show help")(
      "city,c", opt::value<std::string>(&this->city),
      "Enter city (If the city name is divided into "
      "several words - use _ instead of space)")(
      "token,t", opt::value<std::string>(&this->token), "Enter token")(
      "address,a", opt::value<std::string>(&this->address),
      "Enter host address")("port,p", opt::value<std::string>(&this->port),
                            "Enter port");
}

Application::STATUS_RETURN Application::comand_line_parse(void) {
  opt::variables_map vm;

  try {
    opt::store(opt::parse_command_line(this->argc, this->argv, options), vm);
    opt::notify(vm);

    // Help option
    if (vm.count("help") || 1 == this->argc) {
      std::cout << options << std::endl;
      return this->OPTS_HELP;
    }

    // If city was not specified
    if (!vm.count("city")) {
      std::cout << "City must be specified!" << std::endl;
      return this->OPTS_NOCITY;
    }

    if (!vm.count("token")) {
      std::ifstream token_file("token.txt");
      std::stringstream ss;

      if (token_file.is_open()) {
        ss << token_file.rdbuf();
        token_file.close();
      }

      if (!ss.str().empty()) {
        this->token = ss.str();
        return this->OPTS_SUCSESS;
      }
      
      std::cout << "No token found!" << std::endl;
      return this->OPTS_NOTOKEN;
    }
  } catch (const std::exception& e) {

    std::cout << e.what() << std::endl;  

    return this->OPTS_FAILURE;
  } catch (...) {
    Log_error err("command line parsing error: (unknown type)");
    err.print_error();
    return this->OPTS_FAILURE;
  }
  return this->OPTS_SUCSESS;
}

int Application::exec() {
  this->command_line_setup();
  if (this->OPTS_SUCSESS != this->comand_line_parse()) {
    return 0;
  }

  std::shared_ptr<net::io_context> io_ptr = std::make_shared<net::io_context>();
  ClientLayer::Client client(io_ptr, this->address, this->port);
  client.setCity(this->city);
  client.setToken(this->token);
  client.process();

  return 0;
}