#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    ofstream out;
    out.open("out.txt", ios::out);
    if(!out)
        srd::cerr << "failed to open the file" << std::endl;
    else {
        int x = 15;
        out << x << "abc" << endl;
        out.close();
    }
    return 0;
}
