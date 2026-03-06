export module libyunpa:KeyBind;
export import :Events;

namespace libyunpa {
export class KeyBind {
public:
    [[nodiscard]]
    bool operator()(const Events::KeyEvent &) const;
    [[nodiscard]]
    bool test() const;
};
} // namespace libyunpa
