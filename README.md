# C++17 Uniform Resource Identifier Implementation

The class represents Represents a Uniform Resource Identifier (URI) as defined by FC 3986, RFC 3987 and RFC 2732, including scoped IDs.

The implementation is largely based on the Java URI class implementation. The important difference is that this implementation is mutable. It allows to build URI on the fly:

```cpp
    URI uri{"http://www.example.com/path"};
    uri.set_path("/some/new/path");
    uri.set_port(8080);
    uri.add_to_query("name", "value");
    uri.set_fragment("useful fragment");
    uri.set_scheme("https");
    // now URI is "https://www.example.com:8080/some/new/path?name=value#useful%20fragment"
    std::cout << uri.to_ASCII_string() << std::endl;
```

It also supports:

- Normalizing
- Resolving
- Relativizing
- Comparing
- Encoding/decoding

Please refer to [API documentation](https://novalexei.github.io/nURI/doc/html/index.html)
