#include <boost/format.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <proc/readproc.h>
using namespace std;
using boost::format;


unsigned long query_memory_usage() {
    static struct proc_t usage;

    look_up_our_self(&usage);
    return usage.vsize;
}


void mem_usage_test() {
    vector<int> v;

    for(int i = 1; i < 7; i++) {
        cout << format("usage: %ld (%d bytes)") % query_memory_usage() % (v.size() * sizeof(int)) << endl;
        v.resize(i << 20);
    }

    for(int i = 6; i >= 0; i--) {
        cout << format("usage: %ld (%d bytes)") % query_memory_usage() % (v.size() * sizeof(int)) << endl;
        v.resize(i << 20);
    }

    v.clear();
    cout << format("usage: %ld (%d bytes)") % query_memory_usage() % (v.size() * sizeof(int)) << endl;
}


int main() {
    mem_usage_test();
    cout << format("usage: %ld") % query_memory_usage() << endl;
    return 0;
}
