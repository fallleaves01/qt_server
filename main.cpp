#include <cstdio>
#include "scanner.hpp"
#include "worklog.hpp"

int main() {
    const int PORT = 8180;

    SocketScanner scanner(PORT);
    try {
        scanner.connect();
        scanner.work();
    } catch (Worklog e) {
        e.post();
        if (e.has_error()) {
            e.exit();
        }
        return e.geteid();
    }
    return 0;
}