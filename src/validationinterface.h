// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Ilcoin Core developers
// All Rights Reserved. ILCoin Blockchain Project 2019©

#ifndef ILCOIN_VALIDATIONINTERFACE_H
#define ILCOIN_VALIDATIONINTERFACE_H

#include <boost/signals2/signal.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>

class CBlock;
class CBlock2;
class CBlock3;
class CBlockIndex;
class CMiniBlockIndex;
struct CBlockLocator;
class CBlockIndex;
class CConnman;
class CReserveScript;
class CTransaction;
class CValidationInterface;
class CValidationState;
class uint256;

// These functions dispatch to one or all registered wallets

/** Register a wallet to receive updates from core */
void RegisterValidationInterface(CValidationInterface* pwalletIn);
/** Unregister a wallet from core */
void UnregisterValidationInterface(CValidationInterface* pwalletIn);
/** Unregister all wallets from core */
void UnregisterAllValidationInterfaces();

class CValidationInterface {
protected:
    virtual void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) {}
    virtual void UpdatedMiniBlockTip(const CMiniBlockIndex *pindexNew, const CMiniBlockIndex *pindexFork, bool fInitialDownload) {}
    virtual void SyncTransaction(const CTransaction &tx, const CBlockIndex *pindex, int posInBlock) {}
    virtual void SyncTransaction2(const CTransaction &tx, const CMiniBlockIndex *pindex, int posInBlock) {}
    virtual void SetBestChain(const CBlockLocator &locator) {}
    virtual void UpdatedTransaction(const uint256 &hash) {}
    virtual void Inventory(const uint256 &hash) {}
    virtual void ResendWalletTransactions(int64_t nBestBlockTime, CConnman* connman) {}
    virtual void BlockChecked(const CBlock&, const CValidationState&) {}
    virtual void BlockChecked2(const CBlock2&, const CValidationState&) {}
    virtual void BlockChecked3(const CBlock3&, const CValidationState&) {}
    virtual void GetScriptForMining(boost::shared_ptr<CReserveScript>&) {};
    virtual void ResetRequestCount(const uint256 &hash) {};
    virtual void NewPoWValidBlock(const CBlockIndex *pindex, const std::shared_ptr<const CBlock>& block) {};
    virtual void NewPoWValidBlock2(const CBlockIndex *pindex, const std::shared_ptr<const CBlock2>& block) {};
    virtual void NewPoWValidBlock3(const CMiniBlockIndex *pindex, const std::shared_ptr<const CBlock3>& block) {};
    virtual void NewPoWValidBlock4(const CBlockIndex *pindex, const std::shared_ptr<const CBlock3>& block) {};
    friend void ::RegisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterAllValidationInterfaces();
};

struct CMainSignals {
    /** Notifies listeners of updated block chain tip */
    boost::signals2::signal<void (const CBlockIndex *, const CBlockIndex *, bool fInitialDownload)> UpdatedBlockTip;
    boost::signals2::signal<void (const CMiniBlockIndex *, const CMiniBlockIndex *, bool fInitialDownload)> UpdatedMiniBlockTip;
    /** A posInBlock value for SyncTransaction calls for transactions not
     * included in connected blocks such as transactions removed from mempool,
     * accepted to mempool or appearing in disconnected blocks.*/
    static const int SYNC_TRANSACTION_NOT_IN_BLOCK = -1;
    /** Notifies listeners of updated transaction data (transaction, and
     * optionally the block it is found in). Called with block data when
     * transaction is included in a connected block, and without block data when
     * transaction was accepted to mempool, removed from mempool (only when
     * removal was due to conflict from connected block), or appeared in a
     * disconnected block.*/
    boost::signals2::signal<void (const CTransaction &, const CBlockIndex *pindex, int posInBlock)> SyncTransaction;
    boost::signals2::signal<void (const CTransaction &, const CMiniBlockIndex *pindex, int posInBlock)> SyncTransaction2;
    /** Notifies listeners of an updated transaction without new data (for now: a coinbase potentially becoming visible). */
    boost::signals2::signal<void (const uint256 &)> UpdatedTransaction;
    /** Notifies listeners of a new active block chain. */
    boost::signals2::signal<void (const CBlockLocator &)> SetBestChain;
    /** Notifies listeners about an inventory item being seen on the network. */
    boost::signals2::signal<void (const uint256 &)> Inventory;
    /** Tells listeners to broadcast their data. */
    boost::signals2::signal<void (int64_t nBestBlockTime, CConnman* connman)> Broadcast;
    /** Notifies listeners of a block validation result */
    boost::signals2::signal<void (const CBlock&, const CValidationState&)> BlockChecked;
    boost::signals2::signal<void (const CBlock2&, const CValidationState&)> BlockChecked2;
    boost::signals2::signal<void (const CBlock3&, const CValidationState&)> BlockChecked3;
    /** Notifies listeners that a key for mining is required (coinbase) */
    boost::signals2::signal<void (boost::shared_ptr<CReserveScript>&)> ScriptForMining;
    /** Notifies listeners that a block has been successfully mined */
    boost::signals2::signal<void (const uint256 &)> BlockFound;
    /**
     * Notifies listeners that a block which builds directly on our current tip
     * has been received and connected to the headers tree, though not validated yet */
    boost::signals2::signal<void (const CBlockIndex *, const std::shared_ptr<const CBlock>&)> NewPoWValidBlock;
    boost::signals2::signal<void (const CBlockIndex *, const std::shared_ptr<const CBlock2>&)> NewPoWValidBlock2;
    boost::signals2::signal<void (const CMiniBlockIndex *, const std::shared_ptr<const CBlock3>&)> NewPoWValidBlock3;
    boost::signals2::signal<void (const CBlockIndex *, const std::shared_ptr<const CBlock3>&)> NewPoWValidBlock4;
};

CMainSignals& GetMainSignals();

#endif // ILCOIN_VALIDATIONINTERFACE_H
