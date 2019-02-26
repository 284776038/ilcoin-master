// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Ilcoin Core developers
// All Rights Reserved. Ilgamos International 2017©

#ifndef ILCOIN_TEST_RANDOM_H
#define ILCOIN_TEST_RANDOM_H

#include "random.h"

extern FastRandomContext insecure_rand_ctx;

static inline void seed_insecure_rand(bool fDeterministic = false)
{
    insecure_rand_ctx = FastRandomContext(fDeterministic);
}

static inline uint32_t insecure_rand(void)
{
    return insecure_rand_ctx.rand32();
}

#endif
