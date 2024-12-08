#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

int main() {
  std::vector<std::string> map;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    map.push_back(std::move(line));
  }

  const int isize = int(map.size());
  const int jsize = int(map.front().size());

  auto is_in_bounds = [isize,jsize](int i, int j) {
    return 0 <= i && i < isize && 0 <= j && j < jsize;
  };

  std::map<char, std::vector<std::tuple<int, int>>> input;

  for (int i = 0; i < int(map.size()); ++i) {
    for (int j = 0; j < int(map[i].size()); ++j) {
      if (map[i][j] == '.' || map[i][j] == '\n') {
        continue;
      }

      std::cout << map[i][j] << '|' << i << ',' << j << '\n';

      input[map[i][j]].emplace_back(i, j);
    }
  }

  std::set<std::tuple<int, int>> antinodes;

  for (const auto& [ antenna, nodes ] : input) {
    std::cout << "Antennas: " << antenna << '\n';

    for (int a = 0; a < int(nodes.size()); ++a) {
      for (int b = a + 1; b < int(nodes.size()); ++b) {
        auto [ ai, aj ] = nodes[a];
        auto [ bi, bj ] = nodes[b];

        antinodes.insert({ ai, aj });
        antinodes.insert({ bi, bj });

        std::cout << '\t' << ai << ',' << aj << ' ' << bi << ',' << bj << '\n';

        // (c + b) / 2 = a => c = 2 * a - b = a + (a - b)
        int ci = 2 * ai - bi;
        int cj = 2 * aj - bj;

        while (is_in_bounds(ci, cj)) {
          antinodes.insert({ ci, cj });
          ci += (ai - bi);
          cj += (aj - bj);
        }

        // (d + a) / 2 = b => d = 2 * b - a = b + (b - a)
        int di = 2 * bi - ai;
        int dj = 2 * bj - aj;

        while (is_in_bounds(di, dj)) {
          antinodes.insert({ di, dj });
          di += (bi - ai);
          dj += (bj - aj);
        }
      }
    }
  }

  std::cout << antinodes.size() << '\n';
}
