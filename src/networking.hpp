#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <variant>

namespace net = boost::asio;
using tcp = net::ip::tcp;
using UdpEndpoint = net::ip::udp::endpoint;

class ConnectionRegistry;
class TCP_Object;

using ConnectionType = std::variant<UdpEndpoint, std::shared_ptr<TCP_Object>>;

class TCP_Object : public std::enable_shared_from_this<TCP_Object>
{
private:
    net::io_context& ctx_;
    tcp::resolver tcp_resolver_;
    tcp::socket socket_;
    std::shared_ptr<ConnectionRegistry> connection_registry_;
    std::string user_id_;

    TCP_Object(net::io_context& ctx, std::shared_ptr<ConnectionRegistry> registry, std::string user_id);

public:
    TCP_Object(const TCP_Object&) = delete;
    TCP_Object& operator=(const TCP_Object&) = delete;
    TCP_Object(TCP_Object&&) = delete;
    TCP_Object& operator=(TCP_Object&&) = delete;

    static std::shared_ptr<TCP_Object> create(net::io_context& ctx, 
                                              std::shared_ptr<ConnectionRegistry> registry, 
                                              std::string user_id);

    ~TCP_Object() noexcept;

    tcp::socket& get_socket() { return socket_; }
};

struct ConnectionObject
{
    ConnectionType connection_type_;
};

class ConnectionRegistry 
{
private:
    std::unordered_map<std::string, ConnectionObject> connected_users_; 

public:
    void add_connection(const std::string& user_id, std::shared_ptr<TCP_Object> tcp_obj);
    void remove_connection(const std::string& user_id);
};