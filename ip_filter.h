#pragma once

#include <string>
#include <vector>
#include <utility>

using ip_type_s = std::vector<std::string>;
using ip_type = std::vector<uint8_t>;
using ip_pool_type = std::vector<ip_type>;

ip_type_s split(const std::string &str, char d);
bool is_valid_ip(const ip_type_s &ip);
std::pair<bool, ip_type> ip_str_to_uint8(const ip_type_s &ip);
void print_ip_pool(const ip_pool_type &ip_pool);
bool operator < (const ip_type &a, const ip_type &b);
ip_pool_type filter_ip_any(const ip_pool_type &ip_pool, uint8_t n);
ip_pool_type filter_ip(const ip_pool_type &ip_pool, uint8_t n1);
ip_pool_type filter_ip(const ip_pool_type &ip_pool, uint8_t n1, uint8_t n2);
