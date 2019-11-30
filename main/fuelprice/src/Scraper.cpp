#include <curl/curl.h>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/lexical_cast.hpp>

#include "proto/users.pb.h"
#include "Base64.h"

bool debug = false;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char *) ptr, size * nmemb);
    return size * nmemb;
}

std::string scraper(std::string userPath) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    users::UserManagement userManagement;
    std::fstream input(userPath, std::ios::in | std::ios::binary);
    userManagement.ParseFromIstream(&input);
    input.close();

    auto curl = curl_easy_init();
    for (int i = 0; i < userManagement.users_size(); i++) {
        users::User *user = userManagement.mutable_users(i);

        if (curl) {
            std::string lat = std::to_string(user->latitude());
            std::string fuel_url =
                    "https://www.clever-tanken.de/tankstelle_liste?lat=" + std::to_string(user->latitude()) + "&lon=" +
                    std::to_string(user->longitude()) + "&spritsorte=" + std::to_string(user->fuel_kind()) +
                    "&r=5.0&sort=km";

            curl_easy_setopt(curl, CURLOPT_URL, fuel_url.c_str());
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.108 Safari/537.36");
            curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
            curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

            std::string response_string;
            std::string header_string;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

            char *url;
            long response_code;
            double elapsed;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

            curl_easy_perform(curl);

            std::string token;
            std::istringstream tokenStream(response_string);

            std::regex begin("^[[:blank:]]*<a href=\"/tankstelle_details/[[:digit:]]*\".*$");
            std::regex name("^[[:blank:]]*<span class=\"fuel-station-location-name\">.*</span>[[:blank:]]*$");
            std::regex street("^[[:blank:]]*<div class=\"fuel-station-location-street\">.*</div>[[:blank:]]*$");
            std::regex city("^[[:blank:]]*<div class=\"fuel-station-location-city\">.*</div>[[:blank:]]*$");
            std::regex price("^[[:blank:]]*[[:digit:]].[[:digit:]][[:digit:]]<sup>[[:digit:]]</sup>[[:blank:]]*$");

            std::string tmp;
            int b;
            int e;
            user->mutable_fuel_prices()->DeleteSubrange(0, user->fuel_prices().size());
            users::FuelPrice *fp;
            while (std::getline(tokenStream, token, '\n')) {
                if (std::regex_match(token, begin)) {
                    fp = user->add_fuel_prices();
                    fp->set_price(-1.0);
                } else if (std::regex_match(token, price)) {
                    tmp = token;
                    boost::replace_all(tmp, " ", "");
                    boost::replace_all(tmp, "<sup>", "");
                    boost::replace_all(tmp, "</sup>", "");
                    if(debug) std::cout << "Price: " << boost::lexical_cast<double>(tmp) << std::endl;
                    fp->set_price(boost::lexical_cast<double>(tmp));
                } else if (std::regex_match(token, street)) {
                    b = token.find("<div class=\"fuel-station-location-street\">") + 42;
                    e = token.find("</div>");
                    tmp = token.substr(b, e - b);
                    if(debug) std::cout << "Street: " << tmp << std::endl;
                    fp->set_street(tmp);
                } else if (std::regex_match(token, city)) {
                    b = token.find("<div class=\"fuel-station-location-city\">") + 40;
                    e = token.find("</div>");
                    tmp = token.substr(b, e - b);
                    if(debug) std::cout << "City: " << tmp << std::endl;
                    fp->set_city(tmp);
                } else if (std::regex_match(token, name)) {
                    b = token.find("<span class=\"fuel-station-location-name\">") + 41;
                    e = token.find("</span>");
                    tmp = token.substr(b, e - b);
                    if(debug) std::cout << "Name: " << tmp << std::endl;
                    fp->set_name(tmp);
                }
            }

            user->CheckInitialized();

        }
    }

    // clean up the curl object
    curl_easy_cleanup(curl);
    curl = NULL;

    std::string result = userManagement.SerializeAsString();

    google::protobuf::ShutdownProtobufLibrary();

    macaron::Base64 base64;

    if(debug) std::cout << base64.Encode(result) << std::endl;

    return base64.Encode(result);
}