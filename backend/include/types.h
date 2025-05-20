#pragma once

typedef enum{
    Consecutive,
    Separate
} LSBType;

typedef enum{
    DES,
    AES,
    GOST_28147_89,
    RSA
} CipherType;