#include <iostream>
#include <gecko2.hpp>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// using csv_t = std::vector<std::string>;

struct node_t {
  std::string url; // "udp:///1.2.3.4:5000"
  size_t msg_size; // size(bob_t)
  std::string msg; // "bob_t"
};

class TxtFileReader {
  public:
  bool read_file(std::string filename) {
    ifstream fd;
    fd.open(filename);
    if (!fd.is_open()) {
      cout << "couldn't open file" << endl;
      return false;
    }

    while (fd.good()) {
      string line;
      std::getline(fd, line);
      lines.push_back(line);
    }

    return true;
  }

  ascii_t lines;
};

// class Csv: public Ascii, public TxtFileReader {
//   public:
//   Csv(): Ascii(',') {}
// };

int main() {
  // Csv csv;
  // // string entry = "udp://1.2.3.4:4500,bob,27,250";
  // // ascii_t vals = c.unpack(entry);

  // string filename{"nodes.csv"};

  // // TxtFileReader csv;
  // csv.read_file(filename);
  // ascii_t file = csv.lines;

  // for (const string& line: file) {
  //   ascii_t vals = csv.unpack(line);
  //   for (const string& s: vals) cout << s << endl;
  // }

  return 0;
}