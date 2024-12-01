#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {

  std::vector<int> left;
  std::vector<int> right;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    std::istringstream sstream(line);
    int l, r;
    sstream >> l >> r;
    left.push_back(l);
    right.push_back(r);
  }

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  const std::size_t sz = left.size();
  assert(sz == right.size());

  int total = 0;

  for (std::size_t i = 0; i < sz; ++i) {
    // assert(right[i] >= left[i]);
    total += std::abs(right[i] - left[i]);
  }

  std::cout << total << '\n';
}
