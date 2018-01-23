/*
 * This class is a c++ handler for the google maps api
 */

/* 
 * File:   GM_Handler.cpp
 * Author: forest schwartz
 * 
 * Created on January 7, 2018, 10:38 PM
 */

#include "GM_Handler.h"

//Global Varibales     
string data; //will hold the url's contents
// function prototypes
void get_json(string,string);
void get_json_distance_ll(vector<vector<double>>, string);
void get_json_distance_id(string,string,string);
size_t writeCallback(char*, size_t, size_t, void*);
int to_int(string);
vector<string> sub_vector(vector<string>&);
int index_of_largest_element(double*, int);


GM_Handler::GM_Handler() {
}

GM_Handler::GM_Handler(const GM_Handler& orig) {
}

GM_Handler::~GM_Handler() {
}

vector<vector<double>> GM_Handler::get_coordinates(vector<string> address_list){
    string address;
    vector<double> coord;
    vector<vector<double>> coord_list;
    for(int i=0;i<address_list.size();i++){
        address = address_list.at(i);
        coord = get_lat_lng(address);
        coord_list.push_back(coord);
    }
    
    
    return coord_list;

}


// Returns the google map place id for a given address
string GM_Handler::get_place_id(string address_){
    data.erase(data.begin(),data.end());
    get_json(address_ ,api_key);
    istringstream iss(data);
    string line;
    int count(0);
    int count2(0);
    string lat;
    string lng;
    int check(0);
    int check2(0);
    vector<double> coord;
    double lat_d;
    double lng_d;
    vector<string> lister;
    string place_id;

    while (std::getline(iss, line)) {
        string word;
        istringstream is(line);
            
        while(is >> word) {
            if(!word.compare("\"location\"")){
                check = 1;
            }
            if(check){
                count++;
                if(count==6){
                    lat = word;
                }else if(count==9){
                    lng=word;
                }
            }
            if(!word.compare("\"place_id\"")){
                check2=1;
            }
            if(check2){
                count2++;
                if(count2==3){
                    place_id = word;
                }
            }
        }

    }    

    
   
    if(place_id.empty()){
        cout << "Google maps cannot find address:  "+ address_ << endl;
        cout << "Please correct this address in your csv file and verify that google maps can find it." << endl;
        exit(EXIT_FAILURE);
    }


    return place_id;

}

// generic get lat_lng from string address
vector<double> GM_Handler::get_lat_lng(string address_){
    data.erase(data.begin(),data.end());
    get_json(address_ ,api_key);
    istringstream iss(data);
    string line;
    int count(0);
    int count2(0);
    string lat;
    string lng;
    int check(0);
    int check2(0);
    vector<double> coord;
    double lat_d;
    double lng_d;
    vector<string> lister;
    
    while (std::getline(iss, line)) {
        string word;
        istringstream is(line);
            
        while(is >> word) {
            if(!word.compare("\"location\"")){
                check = 1;
            }
            if(check){
                count++;
                if(count==6){
                    lat = word;
                }else if(count==9){
                    lng=word;
                    break;
                }
            }           
        }
    }    

    
    try{

        lat_d = stod(lat);
        lng_d = stod(lng);
    }catch(std::exception e){
        cout << "Google maps cannot find address:  "+ address_ << endl;
        cout << "Please correct this address in your csv file and verify that google maps can find it." << endl;
        exit(EXIT_FAILURE);
    }
    coord.push_back(lat_d);
    coord.push_back(lng_d);

    return coord;
}

// I will finish this one later
void GM_Handler::get_distance_ll(vector<vector<double>> coordinates){
    data.erase(data.begin(),data.end());
    get_json_distance_ll(coordinates,api_key); 
}

// input the place id of the origin and destination and it will spit out the distance and time it takes to travel from the origin to the destination
vector<double> GM_Handler::get_distance_and_time(string origin, string destination){
    data.erase(data.begin(),data.end());
    get_json_distance_id(origin,destination,api_key); 
    istringstream iss(data);
    string line;
    int count(0);
    int count1(0);
    int check1(0);
    int check2(0);
    int check3(0);
    int check4(0);
    string distance;
    string duration;
    while (std::getline(iss, line)) {
        string word;
        istringstream is(line);
            
        while(is >> word) {
            if(!word.compare("\"distance\"")){
                check1 = 1;
            }
            if(check1){
                if(!word.compare("\"value\"")){
                    check2=1;
                }
                if(check2){
                    ++count;
                }
                if(count==3){
                    distance = word;
                    check1=0;
                }
            }
            
            if(!word.compare("\"duration\"")){
                check3 = 1;
            }
             if(check3){
                if(!word.compare("\"value\"")){
                    check4=1;
                }
                if(check4){
                    ++count1;
                }
                if(count1==3){
                    duration = word;
                    check3=0;
                }
             }
        }
    }
   
    double distance_d = stod(distance);
    double duration_d = stod(duration);
    vector<double> return_data;
    return_data.push_back(distance_d);
    return_data.push_back(duration_d);
    return return_data;
}


void GM_Handler::set_api_key(string api_key_){
    api_key=api_key_;
}


size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}


void get_json(string input_address, string api_key){
    

string address;
string segment = "/json?address=";
address = "https://maps.googleapis.com/maps/api/";
address.append("geocode");
address.append(segment);
    istringstream iss(input_address); 
    string word;
    while(iss >> word) {
        address.append(word+"+");
    }
    address.append("&key=");
    address.append(api_key);
    
CURL* curl; //our curl object
curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
curl = curl_easy_init();

curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress


curl_easy_perform(curl);

curl_easy_cleanup(curl);
curl_global_cleanup();
}

void get_json_distance_ll(vector<vector<double>> coordinates,string api_key){
    
    vector<double> origin = coordinates.at(0);
    vector<double> destination = coordinates.at(1);
    string origin_lat = to_string(origin.at(0)); string origin_lng = to_string(origin.at(1));
    string destination_lat = to_string(destination.at(0)); string destination_lng = to_string(destination.at(1));


   string address = "https://maps.googleapis.com/maps/api/distancematrix/json?origins=";
   address.append(origin_lat+",");
   address.append(origin_lng+"&destinations=");
   address.append(destination_lat+",");
   address.append(destination_lng+"&mode=driving"+"&key="+api_key);

   

    CURL* curl; //our curl object
    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    
}

void get_json_distance_id(string origin,string destination,string api_key){
    
   string address = "https://maps.googleapis.com/maps/api/distancematrix/json?origins=place_id:";
   address.append(origin);
   address.append("&destinations=place_id:");
   address.append(destination+""+"&key="+api_key);

    CURL* curl; //our curl object
    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    
}
