#ifndef UTIL_H
#define UTIL_H

int redUP(float n) {
    if (n == int(n)) return int(n);
    else return int(n) + 1;
}

#endif // UTIL_H
