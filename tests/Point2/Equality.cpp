import libyunpa;

auto Point2_Equality(int /*argc*/, char* /*argv*/[]) -> int {
  using namespace libyunpa;
  auto lhs = Point2{.x = 4, .y = 3};
  return lhs == lhs ? 0 : 1;
}
