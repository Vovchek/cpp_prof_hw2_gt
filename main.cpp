#include <iostream>
#include <algorithm>
#include <cassert>

#include "ip_filter.h"

#define UNUSED(v) (void)(v)

using namespace std;

int main(int argc, char const *argv[])
{
UNUSED(argc);
UNUSED(argv);

    try
    {
        ip_pool_type ip_pool;

        for(string line; getline(cin, line);)
        {
            ip_type v = split(split(line, '\t').at(0), '.');
            if(is_valid_ip(v)) {
                ip_pool.push_back(v);
            } else {
                // throw ?
            }
        }

        // TODO reverse lexicographically sort
        sort(ip_pool.begin(), ip_pool.end(), [](const auto &a, const auto &b) {return b < a;} );
        print_ip_pool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        cout << '\n' << "filter(1)" << endl;
        print_ip_pool(filter_ip(ip_pool, 1));

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        cout << '\n' << "filter(46, 70)" << endl;
        print_ip_pool(filter_ip(ip_pool, 46, 70));

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        cout << '\n' << "filter_any(46)" << endl;
        print_ip_pool(filter_ip_any(ip_pool, 46));

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
