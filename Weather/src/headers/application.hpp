#pragma once
#include <boost/program_options.hpp>
#include <memory>
#include <string>

namespace opt = boost::program_options;

class Application {
 public:
  /**
   * @brief Ctor
   * @param argc - amount of command line arguments
   * @param host - amount of command line arguments
   * */
  Application(int argc, char* argv[]);

  // If no arguments are written
  /**
  Options:
    -h [ --help ]         Show help
    -c [ --city ] arg     Enter city (If the city name is divided into several
                          words - use _ instead of space)
    -t [ --token ] arg    Enter token
    -a [ --address ] arg  Enter host address
    -p [ --port ] arg     Enter port
  */

  // A standart output looks like the example below
  /**
    $ ./WeatherApp --city=Kyiv
    City: Kyiv
    Temperature: 0°C
    Wind's speed: 2 meter/sec
    Wind's direction: 140°
   */

  /**
   * @brief Parse command-line arguments ( Need to use boost::program_options ).
   * Call Client
   * */
  int exec();

 private:

  enum STATUS_RETURN {
    OPTS_SUCSESS = -5,
    OPTS_HELP,
    OPTS_FAILURE,
    OPTS_NOCITY,
    OPTS_NOTOKEN
  };
  /**
   * @brief Setup command-line arguments.
   * */
  void command_line_setup();
  /**
   * @brief Parse command-line arguments.
   * @return One of the status of STATUS_RETURN
   * */

  STATUS_RETURN comand_line_parse();

  int argc{0};
  char** argv{nullptr};
  std::string city;
  std::string token;
  std::string address{"api.openweathermap.org"};
  std::string port{"80"};
  opt::options_description options;
};
