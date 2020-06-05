#include "./Header/MainLoop.h"

// int main() {
//     QInt a("1898003864", 10);
//     cout << (a.rol()).getDec();

//     return 0;
// }

int main(int argc, char *argv[]) {
    MainLoop M;
    if (argc < 2)
        return 0;
    M.MainProcess(argv[1], argv[2]);

    return 0;
}
