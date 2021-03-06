#!/usr/bin/env python3
# Copyright (c) 2016 The Ilcoin Core developers
# All Rights Reserved. ILCoin Blockchain Project 2019©
"""Test using named arguments for RPCs."""

from test_framework.test_framework import IlcoinTestFramework
from test_framework.util import (
    assert_equal,
    assert_raises_jsonrpc,
    start_nodes,
)


class NamedArgumentTest(IlcoinTestFramework):
    """
    Test named arguments on RPC calls.
    """

    def __init__(self):
        super().__init__()
        self.setup_clean_chain = False
        self.num_nodes = 1

    def setup_network(self, split=False):
        self.nodes = start_nodes(self.num_nodes, self.options.tmpdir)
        self.is_network_split = False
        self.sync_all()

    def run_test(self):
        node = self.nodes[0]
        h = node.help(command='getinfo')
        assert(h.startswith('getinfo\n'))

        assert_raises_jsonrpc(-8, 'Unknown named parameter', node.help, random='getinfo')

        h = node.getblockhash(height=0)
        node.getblock(blockhash=h)

        assert_equal(node.echo(), [])
        assert_equal(node.echo(arg0=0,arg9=9), [0] + [None]*8 + [9])
        assert_equal(node.echo(arg1=1), [None, 1])
        assert_equal(node.echo(arg9=None), [None]*10)
        assert_equal(node.echo(arg0=0,arg3=3,arg9=9), [0] + [None]*2 + [3] + [None]*5 + [9])

if __name__ == '__main__':
    NamedArgumentTest().main()
