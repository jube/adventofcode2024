#include <cassert>
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
  constexpr int Max = 10000000; // SHAME! SHAME! SHAME!

  for (std::size_t blocki = 0; blocki < area.size(); ++blocki) {
    for (std::size_t blockj = 0; blockj < area[blocki].size(); ++blockj) {
      std::cout << blocki << ',' << blockj << '\n';

      if (int(blocki) == initi && int(blockj) == initj) {
        continue;
      }

      if (area[blocki][blockj] == '#') {
        continue;
      }

      auto copy = area;
      copy[blocki][blockj] = '#';

      int diri = -1;
      int dirj = 0;

      int posi = initi;
      int posj = initj;

      bool loop = false;
      int step = 0;

      for (;;) {
        ++step;

        if (step > Max) {
          loop = true;
          break;
        }

        int nexti = posi + diri;
        int nextj = posj + dirj;

        if (nexti < 0 || nextj < 0 || nexti >= int(copy.size()) || nextj >= int(copy.front().size())) {
          break;
        }

        if (copy[nexti][nextj] == '#') {
          int nextdirj = -diri;
          int nextdiri = dirj;
          dirj = nextdirj;
          diri = nextdiri;
        } else {
          posi = nexti;
          posj = nextj;
        }
      }

      if (loop) {
        ++count;
      }
    }
  }

  // for (auto& line : area) {
  //   for (char c : line) {
  //     std::cout << c;
  //
  //     if (c == 'X') {
  //       ++count;
  //     }
  //   }
  //
  //   std::cout << '\n';
  // }

  std::cout << count << '\n';
}
