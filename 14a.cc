#include <cassert>
#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace {

  std::vector<std::string_view> split_string(std::string_view string, char delimiter)
  {
    const std::size_t size = string.size();
    std::size_t i = 0;
    std::vector<std::string_view> result;

    while (i < size) {
      while (i < size && string[i] == delimiter) {
        ++i;
      }

      if (i == size) {
        break;
      }

      const char* start = string.data() + i;
      size_t length = 0;

      while (i < size && string[i] != delimiter) {
        ++i;
        ++length;
      }

      result.emplace_back(start, length);
    }

    return result;
  }

  struct Input {
    int px, py;
    int vx, vy;
  };

  constexpr int Width = 101; // 11; // 101
  constexpr int Height = 103; // 7; // 103

  constexpr int HaflWidth = (Width - 1) / 2;
  constexpr int HaflHeight = (Height - 1) / 2;

}

int main() {

  std::vector<Input> inputs;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    Input input = {};

    auto parts = split_string(line, ' ');
    assert(parts.size() == 2);

    parts[0].remove_prefix(2);
    auto position = split_string(parts[0], ',');
    assert(position.size() == 2);

    std::from_chars(position[0].begin(), position[0].end(), input.px);
    std::from_chars(position[1].begin(), position[1].end(), input.py);

    parts[1].remove_prefix(2);
    auto velocity = split_string(parts[1], ',');
    assert(velocity.size() == 2);

    std::from_chars(velocity[0].begin(), velocity[0].end(), input.vx);
    std::from_chars(velocity[1].begin(), velocity[1].end(), input.vy);

    // std::cout << input.px << ',' << input.py << ' ' << input.vx << ',' << input.vy << '\n';

    inputs.push_back(input);
  }

  for (auto& input : inputs) {
    for (int i = 0; i < 100; ++i) {
      input.px += input.vx;
      input.py += input.vy;

      if (input.px < 0) {
        input.px += Width;
      }

      if (input.px >= Width) {
        input.px -= Width;
      }

      if (input.py < 0) {
        input.py += Height;
      }

      if (input.py >= Height) {
        input.py -= Height;
      }
    }

    // std::cout << input.px << ',' << input.py << '\n';
  }



  int upper_left = 0;
  int upper_right = 0;
  int lower_left = 0;
  int lower_right = 0;

  for (const auto& input : inputs) {
    // std::cout << input.px << ',' << input.py << '\n';

    if (input.px < HaflWidth) {
      if (input.py < HaflHeight) {
        ++upper_left;
      } else if (input.py > HaflHeight) {
        ++lower_left;
      }
    } else if (input.px > HaflWidth) {
      if (input.py < HaflHeight) {
        ++upper_right;
      } else if (input.py > HaflHeight) {
        ++lower_right;
      }
    }
  }

  std::cout << upper_left << ' ' << upper_right << ' ' << lower_left << ' ' << lower_right << '\n';

  int factor = upper_left * upper_right * lower_left * lower_right;

  std::cout << factor << '\n';
}
