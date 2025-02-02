
#include <iostream>
#include <fstream>
#include <algorithm>

// using namespace std;
using std::endl;
using std::cout;

bool is_number(const std::string_view &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool is_double(const std::string_view &s) {
  if (!is_number(s)) return false;
  if (s.find(".") == std::string::npos) return false;
  return true;
}

bool is_matrix(const std::string_view &value) {
  if (value[0] == '[' && value[value.size()-1] == ']') return true;
  return false;
}

int main() {
  // std::ifstream is RAII, i.e. no need to call close
  std::ifstream cFile ("config.txt");
  if (cFile.is_open()) {
    std::string line;
    while(getline(cFile, line)){
      line.erase(
        std::remove_if(line.begin(), line.end(), ::isspace),
        line.end());
      if(line[0] == '#' || line.empty())
          continue;
      auto delimiterPos = line.find("=");
      std::string name = line.substr(0, delimiterPos);
      std::string value = line.substr(delimiterPos + 1);
      std::cout << name << ": " << value << endl;

      if (is_matrix(value)) cout << "value is matrix" << endl;
      else if (is_double(value)) cout << "value is double: " << std::stod(value) << endl;
    }
  }
  else {
    std::cerr << "Couldn't open config file for reading.\n";
  }
}