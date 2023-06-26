#include <stdio.h>
#include <string>


int main()
{
    std::string s = "Hello";
    s = s + " World" + "!\r\n";
    printf("%s\r\n", s.c_str());

    std::string t;
    t = "Hello " + s;
    printf("%s\r\n", t.c_str());
}