#pragma once
#include <string>
#include <expected>
#include "logging.hpp"
#include <format>

struct ConnectionConfig {
    std::string ip_{};
    std::string name_{};
    bool use_udp {false};
};

class ConnectionObject {
    ConnectionConfig config_;
public:
    explicit ConnectionObject(ConnectionConfig config = {}) : config_(std::move(config)) {}
    const ConnectionConfig& config() const { return config_; }
    friend std::string format_as(const ConnectionConfig& config) {
        return std::format(
            "ConnectionConfig{{ip: {}, name: {}, use_udp: {}}}",
            config.ip_, config.name_, config.use_udp ? "true" : "false"
        );
    }
};


class NetworkConnection {
public:
    [[nodiscard]] auto connect() -> std::expected<ConnectionObject, Error> {
        bool connection_failed = false; 
        
        if (connection_failed) {
            return std::unexpected(Error::NetworkError);
        }
        
        return ConnectionObject{};
    }
};