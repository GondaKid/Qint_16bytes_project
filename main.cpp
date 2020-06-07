#include <bitset>

#include "./Header/MainLoop.h"

int main(int argc, char *argv[]) {
    MainLoop M;
    if (argc < 2)
        return 0;
    M.MainProcess(argv[1], argv[2]);

    return 0;
}
