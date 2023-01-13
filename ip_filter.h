#pragma once

#include <string>
#include <vector>

using ip_type = std::vector<std::string>;
using ip_pool_type = std::vector<ip_type>;

ip_type split(const std::string &str, char d);
bool is_valid_ip(const ip_type &ip);
void print_ip_pool(const ip_pool_type &ip_pool);
bool operator < (const ip_type &a, const ip_type &b);
ip_pool_type filter_ip_any(const ip_pool_type &ip_pool, unsigned char n);
ip_pool_type filter_ip(const ip_pool_type &ip_pool, unsigned char n1);
ip_pool_type filter_ip(const ip_pool_type &ip_pool, unsigned char n1, unsigned char n2);
