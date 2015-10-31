#include <cstdlib>
#include <cstdio>

#include <EtudesHost.hpp>

int main(){
    etudes::EtudesHost host;

    host.initialise();
    while(host.loopIteration()) {}

    return 0;
}
