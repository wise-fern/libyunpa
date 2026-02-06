module;

export module libyunpa.Mapping;
export import libyunpa.System;
export import ftxui;
export import std;

namespace libyunpa {
export struct Tile {
  char sym;
  bool passesLight;
  bool walkable;
  int  movementCost;
};

export constexpr auto Wall = Tile{.sym = '#',
  .passesLight                         = false,
  .walkable                            = false,
  .movementCost                        = std::numeric_limits<int>::max()};

export constexpr auto Floor
  = Tile{.sym = ' ', .passesLight = true, .walkable = true, .movementCost = 1};

export template <typename RNG, unsigned int width, unsigned int height>
  requires std::uniform_random_bit_generator<RNG>
class Map {
private:
  std::array<Tile, static_cast<std::size_t>(width) * height> _tiles{};
  Point2i                                                    _center{};

protected:
  auto& operator[](unsigned int xCoord, unsigned int yCoord) {
    return _tiles[xCoord + (width * yCoord)];
  }

  auto swap(std::array<Tile, static_cast<std::size_t>(width) * height> newMap) {
    _tiles.swap(newMap);
  }

public:
  const auto& operator[](Point2i coordinate) const {
    return (*this)[coordinate.x, coordinate.y];
  }

  auto setWalkable(Point2i coordinate, bool walkable) {
    (*this)[coordinate.x, coordinate.y].walkable = walkable;
  }

  auto setPassesLight(Point2i coordinate, bool passesLight) {
    (*this)[coordinate.x, coordinate.y].passesLight = passesLight;
  }

  [[nodiscard]]
  auto render() const {
    return ftxui::vbox();
  }

  auto setCenter(Point2i center) {
    _center = center;
  }

  virtual void generate() = 0;
  virtual ~Map()          = default;
};

constexpr auto DEFAULT_SEED_CHANCE = 0.45F;
constexpr auto DEFAULT_BIRTH_LIMIT = 5;
constexpr auto DEFAULT_DEATH_LIMIT = 3;
constexpr auto DEFAULT_ITERATIONS  = 4;

constexpr auto NEIGHBORS = std::to_array<Point2i>({{.x = -1, .y = -1},
  {.x = 0, .y = -1},
  {.x = 1, .y = -1},
  {.x = -1, .y = 0},
  {.x = 1, .y = 0},
  {.x = -1, .y = 1},
  {.x = 0, .y = 1},
  {.x = 1, .y = 1}});

export struct CellularOptions {
  float seedChance = DEFAULT_SEED_CHANCE;
  int   birthLimit = DEFAULT_BIRTH_LIMIT;
  int   deathLimit = DEFAULT_DEATH_LIMIT;
};

export template <typename RNG, unsigned int width, unsigned int height>
  requires std::uniform_random_bit_generator<RNG>
class CellularMap : public Map<RNG, width, height> {
private:
  CellularOptions _options{};

  auto getNeighbors(Point2i tile) {
    auto neighbors = 0;
    for (const auto& neighbor : NEIGHBORS) {
      auto target = tile + neighbor;
      if (target.x < 0
          or target.x >= width
          or target.y < 0
          or target.y > height) {
        ++neighbors;
        continue;
      }
      if (not this[target].walkable) {
        ++neighbors;
        continue;
      }
    }
    (void)tile;
    return neighbors;
  }

public:
  CellularMap(CellularOptions options) : _options(options) {
    generate();
  }

  void generate() override {
    auto map = std::array<Tile, static_cast<std::size_t>(width) * height>{};
    // Make a new map to work on
    map.fill(Wall);
    for (auto& tile : map) {
      tile = Map<RNG, width, height>::getRandom() >= _options.seedChance ? Floor
                                                                         : Wall;
    }
  }
};

} // namespace libyunpa
