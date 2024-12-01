#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {

  std::map<int, int> left;
  std::map<int, int> right;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    std::istringstream sstream(line);
    int l, r;
    sstream >> l >> r;
    ++left[l];
    ++right[r];
  }

  int similarity = 0;

  for (auto [ number, count ] : left) {
    if (auto iterator = right.find(number); iterator != right.end()) {
      similarity += count * iterator->first * iterator->second;
    }
  }

  std::cout << similarity << '\n';
}
