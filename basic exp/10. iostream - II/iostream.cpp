#include <fstream>
#include <iostream>
#include <string>

void copy_file(std::string s) {
    char data[100];
    std::ifstream in;
    std::ofstream out;
    in.open("s");
    out.open("out.txt");
    std::cout << "-----copy-----" << std::endl;
    while(!in.eof()) {
        in >> data;
        std::cout << data;
        out << data;
    }
}

int main(int argc, char *argv[]) {
    std::string s;
    std::cin >> s;
    copy_file(s);
    return 0;
}
