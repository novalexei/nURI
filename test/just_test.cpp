#include <iostream>
#include <nova/uri.h>

using namespace nova;

int main()
{
    URI uri{"http://www.example.com/path"};
    uri.set_path("/some/new/path");
    uri.set_port(8080);
    uri.add_to_query("name", "value");
    uri.set_fragment("useful fragment");
    uri.set_scheme("https");
    std::cout << uri.to_ASCII_string() << std::endl;
}
