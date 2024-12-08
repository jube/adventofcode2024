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

        std::cout << '\t' << ai << ',' << aj << ' ' << bi << ',' << bj << '\n';

        // (c + b) / 2 = a => c = 2 * a - b
        int ci = 2 * ai - bi;
        int cj = 2 * aj - bj;

        if (0 <= ci && ci < isize && 0 <= cj && cj < jsize) {
          std::cout << '\t' << "# " << ci << ',' << cj << '\n';
          antinodes.insert({ ci, cj });
        }

        // (d + a) / 2 = b => d = 2 * b - a
        int di = 2 * bi - ai;
        int dj = 2 * bj - aj;

        if (0 <= di && di < isize && 0 <= dj && dj < jsize) {
          std::cout << '\t' << "# " << di << ',' << dj << '\n';
          antinodes.insert({ di, dj });
        }
      }
    }
  }

  std::cout << antinodes.size() << '\n';
}
