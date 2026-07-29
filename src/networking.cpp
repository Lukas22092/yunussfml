#include "networking.hpp"

TCP_Object::TCP_Object(net::io_context& ctx, std::shared_ptr<ConnectionRegistry> registry, std::string user_id)
    : ctx_{ctx}, tcp_resolver_{ctx}, socket_{ctx}, 
      connection_registry_{std::move(registry)}, user_id_{std::move(user_id)} {}

std::shared_ptr<TCP_Object> TCP_Object::create(net::io_context& ctx, 
                                          std::shared_ptr<ConnectionRegistry> registry, 
                                          std::string user_id)
{
    struct enable_maker : public TCP_Object {
        enable_maker(net::io_context& c, std::shared_ptr<ConnectionRegistry> r, std::string id)
            : TCP_Object(c, r, std::move(id)) {}
    };
    
    auto instance = std::make_shared<enable_maker>(ctx, registry, user_id);

    if (registry) {
        registry->add_connection(user_id, instance);
    }

    return instance;
}

TCP_Object::~TCP_Object() noexcept
{
    if (connection_registry_) {
        connection_registry_->remove_connection(user_id_);
    }
}

void ConnectionRegistry::add_connection(const std::string& user_id, std::shared_ptr<TCP_Object> tcp_obj)
{
    connected_users_[user_id] = ConnectionObject{std::move(tcp_obj)};
}

void ConnectionRegistry::remove_connection(const std::string& user_id)
{
    connected_users_.erase(user_id);
}