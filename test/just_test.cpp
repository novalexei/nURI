#include <iostream>
#include <nova/uri.h>

using namespace nova;

int main()
{
    URI uri{"http://www.example.com/path"};
    uri.set_path("/some/new/path");
    uri.set_port(8080);
    uri.add_to_query("name", "の場合");
    uri.set_fragment("useful fragment");
    uri.set_scheme("https");
    // Result: "https://www.example.com:8080/some/new/path?name=%E3%81%AE%E5%A0%B4%E5%90%88#useful%20fragment"
    std::cout << uri.to_ASCII_string() << std::endl;
}
