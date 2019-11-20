#!/usr/bin/env python3
# Copyright (c) 2016 The Ilcoin Core developers
# All Rights Reserved. ILCoin Blockchain Project 2019©
"""Create a blockchain cache.

Creating a cache of the blockchain speeds up test execution when running
multiple qa tests. This helper script is executed by rpc-tests when multiple
tests are being run in parallel.
"""

from test_framework.test_framework import IlcoinTestFramework

class CreateCache(IlcoinTestFramework):

    def __init__(self):
        super().__init__()

        # Test network and test nodes are not required:
        self.num_nodes = 0
        self.nodes = []

    def setup_network(self):
        pass

    def run_test(self):
        pass

if __name__ == '__main__':
    CreateCache().main()
