#include <iostream>
#include <string>

int main() {
    std::string s = "<!DOCTYPE html>";
    s += "<htmllang=\"en\">";
    s += "<head>";
    s += "<metacharset=\"UTF-8\">";
    s += "<metaname=\"viewport\"content=\"width=device-width,initial-scale=1.0\">";
    s += "<title>Document</title>";
    s += "</head>";
    s += "<body>";
    s += "</body>";
    s += "</html>";
    std::cout << s;
    return 0;
}