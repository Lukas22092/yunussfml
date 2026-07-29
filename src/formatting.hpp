#pragma once
#include "networking.hpp"
#include "logging.hpp"
#include <format>
#include <string_view>



class Formatter
{   template<typename ToFormat, typename Func>
    constexpr static auto format(ToFormat to_format, Func&& function);

};
template <>
struct std::formatter<Error> : std::formatter<std::string_view> {
     constexpr static auto format(Error error, std::format_context& ctx) {
        std::string_view formatted = "Unknown";
        switch (error) {
            case Error::ParseError:   formatted = "ParseError"; break;
            case Error::NetworkError: formatted = "NetworkError"; break;
        }
        
       return std::ranges::copy(formatted, ctx.out()).out;
    }
};

template<>
struct std::formatter<ConnectionConfig> : std::formatter<std::string_view> {
    template <typename FormatContext>
    auto format(const ConnectionConfig& config, FormatContext& ctx) const {
        std::string formatted = std::format(
            "ConnectionConfig{{ip: {}, name: {}, use_udp: {}}}",
            config.ip_, config.name_, config.use_udp ? "true" : "false"
        );
        return std::formatter<std::string_view>::format(formatted, ctx);
    }
};

template<>
struct std::formatter<ConnectionObject> : std::formatter<std::string_view> {
    template <typename FormatContext>
    auto format(const ConnectionObject& obj, FormatContext& ctx) const {
        std::string formatted = std::format("ConnectionObject{{config: {}}}", obj.config());
        return std::formatter<std::string_view>::format(formatted, ctx);
    }
};
