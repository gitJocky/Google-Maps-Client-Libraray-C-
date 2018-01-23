/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GM_Handler.h
 * Author: forest
 *
 * Created on January 7, 2018, 10:38 PM
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <curl/curl.h> 
#include "Helper_Functions.h"

//namespace declarations
using std::string; using std::istringstream; using std::cout; using std::endl; 
using std::vector; using std::cin; using std::pair; using std::to_string;

#ifndef GM_HANDLER_H
#define GM_HANDLER_H

class GM_Handler {
public:
    GM_Handler();
    GM_Handler(const GM_Handler& orig);
    virtual ~GM_Handler();
    
    vector<vector<double>> get_coordinates(vector<string>);
    string get_place_id(string);
    vector<double> get_lat_lng(string);
    void get_distance_and_time_ll(vector<vector<double>>);
    vector<double> get_distance_and_time(string,string);
    void set_api_key(string);
private:
    string api_key;
};

#endif /* GM_HANDLER_H */

