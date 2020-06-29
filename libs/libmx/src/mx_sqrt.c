#include "libmx.h"

// Returns square root of integer.
int mx_sqrt(int x) {
    if (x == 1 || x == 0)
        return x;
    else if (x < 0)
        return 0;
    int start = 1;
    int end = x / 2;
    int ans;

    // > max. int
    if (x / 2 > 46340)
        end = 46340;
        while (start <= end) {
            int middle = (start + end) / 2;
            if (middle * middle == x)
                return middle;
            if (middle * middle < x) {
                start = middle + 1;
                ans = 0;
            }
            else
                end = middle - 1;
        }
    return ans;
}
