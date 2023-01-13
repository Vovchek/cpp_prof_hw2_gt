#include <iostream>
#include <cstdlib>

#include "ip_filter.h"

using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

ip_type split(const string &str, char d)
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

bool is_valid_ip(const ip_type &ip)
{
    if(ip.size() != 4) {
        return false;
    }
    for(auto &s : ip) {
        if(static_cast<unsigned>(stoi(s)) > 255) {
            return false;
        }
    }
    return true;
}

// print IPs
void print_ip_pool(const ip_pool_type &ip_pool)
{
    for(const auto &ip : ip_pool) {
        for(const auto &ip_part : ip) {
            if(&ip_part != &ip[0]) { // is it evil to play with pointers... just to avoid multiplying entities?
                cout << ".";
            }
            cout << ip_part;
        }
        cout << endl;
    }
}

// compare IPs
bool operator < (const ip_type &a, const ip_type &b)
{
    auto it_b = b.begin();
    for(const auto &s_a : a) {
        if(it_b == b.end()) { // i really feel uncomfortable without this rudundant check
            return false; // common parts of a == b
        }
        auto n_a = stoi(s_a);
        auto n_b = stoi(*it_b);
        if(n_a < n_b) {
            return true; // a < b
        } else if(n_a > n_b) {
            return false; // a > b
        }
        ++it_b;
    }
    return false; // common parts of a == b
}

static bool ip_contains(const ip_type &ip, unsigned char n)
{
    for(auto &s : ip) {
        if(static_cast<unsigned char>(stoi(s)) == n) {
            return true;
        }
    }
    return false;
}

ip_pool_type filter_ip_any(const ip_pool_type &ip_pool, unsigned char n)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(ip_contains(ip, n)) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

ip_pool_type filter_ip(const ip_pool_type &ip_pool, unsigned char n1)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(static_cast<unsigned char>(stoi(ip[0])) == n1) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

ip_pool_type filter_ip(const ip_pool_type &ip_pool, unsigned char n1, unsigned char n2)
{
    ip_pool_type filtered;

    for(const auto &ip : ip_pool) {
        if(static_cast<unsigned char>(stoi(ip[0])) == n1 &&
            static_cast<unsigned char>(stoi(ip[1])) == n2) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

