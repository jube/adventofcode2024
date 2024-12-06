#include <cassert>
#include <iostream>
#include <set>
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

  int count = 0;

  for (std::size_t blocki = 0; blocki < area.size(); ++blocki) {
    for (std::size_t blockj = 0; blockj < area[blocki].size(); ++blockj) {
      std::cout << blocki << ',' << blockj << '\n';

      if (int(blocki) == initi && int(blockj) == initj) {
        continue;
      }

      if (area[blocki][blockj] == '#') {
        continue;
      }

      area[blocki][blockj] = '#';

      int diri = -1;
      int dirj = 0;

      int posi = initi;
      int posj = initj;

      std::set<std::tuple<int, int, int, int>> seen;
      seen.emplace(posi, posj, diri, dirj);
      bool loop = false;

      for (;;) {
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

        if (seen.find({ posi, posj, diri, dirj }) != seen.end()) {
          loop = true;
          break;
        } else {
          seen.emplace(posi, posj, diri, dirj);
        }

      }

      if (loop) {
        ++count;
      }

      // undo
      area[blocki][blockj] = '.';
    }
  }

  std::cout << count << '\n';
}
