#include <meta>
#include <print>

enum class Color { Red, Green, Blue , Yellow};

struct Player {
    int age;
    std::string name{"Lukas"};
};

void print_container(Player& p) {
    template for (constexpr auto e :
                  define_static_array(std::meta::nonstatic_data_members_of(^^Player, std::meta::access_context::unprivileged()))) {
        std::println("  {} = {}", std::meta::identifier_of(e), p.[:e:]);
    }
}

int main() {
    Player playerrrrr{25};

    constexpr auto arr = define_static_array(
        std::meta::nonstatic_data_members_of(^^Player, std::meta::access_context::unprivileged()));

    template for (constexpr auto e : arr) {
        std::println("{} = {}", std::meta::identifier_of(e), playerrrrr.[:e:]);
    }
}



