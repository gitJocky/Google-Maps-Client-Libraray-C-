# Google-Maps-Client-Libraray-C-
C++ Library for working with google maps

This repository was made to simplify accessing the google maps api.
the main.cpp file shows examples of how to use the library.
After creating a GM_Handler and setting the api_key you can use any of the public functions to get the latitude and longitude of an adrress, the place_id of an address (if you have a premium api key), the distance and time between two points, etc...

# Setup
To build the repository simply open up your terminal in the main directory and run ./builder.sh

# Dependencies
curl
there is a libcurl.so in the external libraries that you can try to use by changing the cmake directory. If it does not work then you will need to build curl on your computer separately

