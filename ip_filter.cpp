#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "ip_filter.h"

using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

ip_type_s split(const string &str, char d)
{
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

pair<bool, ip_type> ip_str_to_uint8(const ip_type_s &ip)
{
    ip_type ip_t;
    if(ip.size() != 4) {
        return {false, ip_t};
    }
    for(auto &s : ip) {
        int n;
        if( !all_of(s.begin(), s.end(), ::isdigit) ||
            (n = static_cast<unsigned>(stoi(s))) > 255) {
            return {false, ip_t};
        }
        ip_t.push_back(static_cast<uint8_t>(n));
    }
    return {true, ip_t};
}

bool is_valid_ip(const ip_type_s &ip)
{
  if(ip.size() != 4) {
        return false;
    }
    for(auto &s : ip) {
        if(!all_of(s.begin(), s.end(), ::isdigit) ||
        static_cast<unsigned>(stoi(s)) > 255) {
            return false;
        }
    }
    return true;
}

// print IPs
void print_ip_pool(const ip_pool_type &ip_pool)
{
    for(const auto &ip : ip_pool) {
        cout << static_cast<unsigned>(ip[0]) << '.' 
            << static_cast<unsigned>(ip[1]) << '.' 
            << static_cast<unsigned>(ip[2]) << '.' 
            << static_cast<unsigned>(ip[3]) << '\n';
    }
}

bool operator < (const ip_type &a, const ip_type &b)
{
    auto it_b {b.begin()};
    for(auto n_a : a) {
        if(n_a < *it_b) {
            return true;
        } else if(n_a > *it_b) {
            return false;
        }
        ++it_b;
    }
    return false; // a == b
}

static bool ip_contains(const ip_type &ip, uint8_t n)
{
    for(auto ax : ip) {
        if(ax == n) {
            return true;
        }
    }
    return false;
}

ip_pool_type filter_ip_any(const ip_pool_type &ip_pool, uint8_t n)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(ip_contains(ip, n)) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

ip_pool_type filter_ip(const ip_pool_type &ip_pool, uint8_t n1)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(ip[0] == n1) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

ip_pool_type filter_ip(const ip_pool_type &ip_pool, uint8_t n1, uint8_t n2)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(ip[0] == n1 && ip[1] == n2) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

