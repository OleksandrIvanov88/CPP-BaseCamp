# Weather monitoring application

Weather conditions monitoring using components from the Boost library.

The program is divided into 3 modules:
- `network` - is responsible for connecting to the external server, sending a request, and receiving a response.
- `client` - is responsible for passing data to `network`, processing results from it, and printing results on a screen.
- `application` - is responsible for processing command-line arguments and passing them to `client`.

The program is capable of:
- Showing help (as shown in `application.hpp`), if no arguments present or it was `-h` or `--help` argument;
- Reading city from the console;
- Reading token from console (If not present, checks the file `token.txt` in the same directory as executable). 
- Showing information about the weather in specified city. (as shown in `application.hpp`):
    - Name of the city
    - Temperature (degree Celsius)
    - Wind velocity (meters per second)
    - Wind direction (degrees)
- Connection to the server:
    - Reading host - `api.openweathermap.org` is set as default.
    - Reading port - `80` is set as default.


