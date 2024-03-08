//
// Created by asuka on 08.03.2024.
//

#include "../../include/Net/NetUtils.h"
#include <curl/curl.h>
#include <iostream>

std::string NetUtils::download_page(std::string url,std::string useropt) {
    CURL* curl;
    CURLcode res;
    std::string output;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, useropt.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch URL: " << curl_easy_strerror(res) << std::endl;}
        curl_easy_cleanup(curl);}
    curl_global_cleanup();
    return output;}

size_t NetUtils::WriteCallback(char *contents, size_t size, size_t nmemb, std::string *output) {
    output->append(contents, size * nmemb);
    return size * nmemb;
}

std::string NetUtils::download_page(std::string url) {
    return download_page(url,"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");}
