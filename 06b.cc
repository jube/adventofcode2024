#include <cassert>
#include <array>
#include <iostream>
#include <string>
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

      auto dir_index = [](int diri, int dirj) {
        if (diri == -1) { return 0; }
        if (diri == 1) { return 1; }
        if (dirj == -1) { return 2; }
        assert(dirj == 1);
        return 3;
      };

      int posi = initi;
      int posj = initj;

      assert(0 <= dir_index(diri, dirj) && dir_index(diri, dirj) < 4);

      std::vector<std::vector<std::array<bool, 4>>> seen(area.size(), std::vector<std::array<bool, 4>>(area.front().size(), { false, false, false, false }));
      seen[posi][posj][dir_index(diri, dirj)] = true;

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

        assert(0 <= dir_index(diri, dirj) && dir_index(diri, dirj) < 4);

        if (seen[posi][posj][dir_index(diri, dirj)]) {
          loop = true;
          break;
        } else {
          seen[posi][posj][dir_index(diri, dirj)] = true;
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
