#include <cassert>
#include <cstdint>
#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

int main() {

  std::vector<std::string> area;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    area.push_back(std::move(line));
  }

  int initi = -1;
  int initj = -1;

  for (std::size_t i = 0; i < area.size(); ++i) {
    for (std::size_t j = 0; j < area[i].size(); ++j) {
      if (area[i][j] == '^') {
        initi = i;
        initj = j;
        break;
      }
    }
  }

  int diri = -1;
  int dirj = 0;

  int posi = initi;
  int posj = initj;

  for (;;) {
    area[posi][posj] = 'X';

    int nexti = posi + diri;
    int nextj = posj + dirj;

    if (nexti < 0 || nextj < 0 || nexti >= int(area.size()) || nextj >= int(area.front().size())) {
      break;
    }

    if (area[nexti][nextj] == '#') {
      int nextdirj = -diri;
      int nextdiri = dirj;
      dirj = nextdirj;
      diri = nextdiri;
    } else {
      posi = nexti;
      posj = nextj;
    }
  }

  int count = 0;

  for (auto& line : area) {
    for (char c : line) {
      std::cout << c;

      if (c == 'X') {
        ++count;
      }
    }

    std::cout << '\n';
  }

  std::cout << count << '\n';
}
