#include "ppmc.h"

int main(int argc, char const *argv[])
{
    PPMC ppm(atoi(argv[1]), argv[2], "Outputs/output.txt");

    ppm.Compress();

    return 0;
}
