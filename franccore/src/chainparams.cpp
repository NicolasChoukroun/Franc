// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2018-2019 The Franc Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <arith_uint256.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


//Mining algorithm


const arith_uint256 maxUint = UintToArith256(
        uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

static void MineGenesis(CBlockHeader &genesisBlock, const uint256 &powLimit, bool noProduction) {
    if (noProduction) genesisBlock.nTime = std::time(nullptr);
    genesisBlock.nNonce = std::time(nullptr);

    printf("NOTE: Genesis nTime = %u \n", genesisBlock.nTime);
    printf("WARN: Genesis nNonce (BLANK!) = %u \n", genesisBlock.nNonce);

    arith_uint256 besthash;
    memset(&besthash, 0xFF, 32);
    arith_uint256 hashTarget = UintToArith256(powLimit);
    printf("Target: %s\n", hashTarget.GetHex().c_str());
    arith_uint256 newhash = UintToArith256(genesisBlock.GetHash());
    while (newhash > hashTarget) {
        genesisBlock.nNonce++;
        if (genesisBlock.nNonce == 0) {
            printf("NONCE WRAPPED, incrementing time\n");
            ++genesisBlock.nTime;
        }
        // If nothing found after trying for a while, print status
        if ((genesisBlock.nNonce & 0xffff) == 0)
            printf("nonce %08X: hash = %s target=%s \r",
                   genesisBlock.nNonce, newhash.ToString().c_str(),
                   hashTarget.ToString().c_str());

        if (newhash < besthash) {
            besthash = newhash;
            printf("New best: %s\n", newhash.GetHex().c_str());
        }
        newhash = UintToArith256(genesisBlock.GetHash());
    }
    printf("\nGenesis nTime = %u \n", genesisBlock.nTime);
    printf("Genesis nNonce = %u \n", genesisBlock.nNonce);
    printf("Genesis nBits: %08x\n", genesisBlock.nBits);
    printf("Genesis Hash = %s\n", newhash.ToString().c_str());
    printf("Genesis Hash Merkle Root = %s\n", genesisBlock.hashMerkleRoot.ToString().c_str());
    printf("Genesis Hash Merkle Root = %s\n", genesisBlock.hashMerkleRoot.ToString().c_str());
}


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Aug 26,2019 Swiss Crypto Banks Receive Licenses From Financial Regulator.";
    const CScript genesisOutputScript = CScript() << ParseHex("046f97a8ca2e3acc219671775ef19563dc1e0649d8ebd4b69c30b9e0dd924aae7a73d6a23b6270f52db2849450c8a7b5b90e16affb2328278524f1e174d72bf5d2") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 525600/2.5;

        consensus.BIP16Exception = uint256S("0x000407e630c17ccf96bc4cf12bc78153956f8715bbd5c955a67af23fd0a3c013");
        consensus.BIP34Height = 40000; // optimization starting from 1;
        consensus.BIP34Hash = uint256S("0x000407e630c17ccf96bc4cf12bc78153956f8715bbd5c955a67af23fd0a3c013");
        consensus.BIP65Height = 40000; // optimization starting from 1; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP65Height = 40000; // optimization starting from 1; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931

        //consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit=uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for genesis only
        //consensus.powLimit=uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nPowTargetTimespan =   2.5 * 60 * 10;
        consensus.nPowTargetSpacing = 2.5 * 60 ;


        assert(consensus.nPowTargetTimespan>= consensus.nPowTargetSpacing );

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916*4; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016*4;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        //consensus.nMinimumChainWork = uint256S("0x0");
        //consensus.nMinimumChainWork = uint256S("0x1d00fff0");
        consensus.nMinimumChainWork = uint256S("00000000000000000000000000000000000000000000000000000844d3096fc6");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0"); //563378

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x1b;
        pchMessageStart[1] = 0x19;
        pchMessageStart[2] = 0x16;
        pchMessageStart[3] = 0x10;
        nDefaultPort = 1791;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 10; //10
        m_assumed_chain_state_size = 3; //3

        //genesis = CreateGenesisBlock(std::time(nullptr), 546521654, 0x1d00ffff, 1, 50 * COIN);
        //MineGenesis(genesis, consensus.powLimit, true);
        //exit (0);
        genesis = CreateGenesisBlock(1569352641,1569355124,0x1d00ffff,1, 50*COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("000677a45f51a07efe866d2eb0748ad463439ce2edef4eae67098d93ce482787"));
        assert(genesis.hashMerkleRoot == uint256S("49d0adba8beb9322eae3458279121075bd9d0e84b61e651d7b67262bbccb292b"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("seed1.franc.eu.com"); // removed
        vSeeds.emplace_back("seed2.franc.eu.com"); // removed
        vSeeds.emplace_back("seed3.franc.eu.com"); // removed
        vSeeds.emplace_back("seed4.franc.eu.com"); //

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,95);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,'+');
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1F};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE5};

        bech32_hrp = "ff";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        //fMineBlocksOnDemand = false;

        checkpointData = {
                {
                        {1, uint256S("00000000c41f5a07f0c54d85f9bc79ae00e94d8a20614566d5efd6aea4960010")},
                        {1000, uint256S("000000005ea2dd2a7c11fda143b8516f78d3bfac2e29db11ef05cc3e9df48817")},
                        {2000, uint256S("0000000006a84029be6839e298fccba128ce0065f6bbdaf5e0e9f60bae8af627")},
                        {3000, uint256S("0000000036a7e0ad6f2d144ab560d5c8363bf1d29acccc65a8ad2a6babe9bf0d")},
                        {4000, uint256S("000000003ef1988c266578223cb7d5258566d4e12715400a8f22f4977159a1a7")},
                        {5000, uint256S("00000000e4ee741e3891741bf4b4d2eff69825fa763f62e4a3048540f4c79514")},
                        {7000, uint256S("00000000e93509769adad800721d7ec879c58cfe116908e82ff8368ee8b74be7")},
                        {9000, uint256S("00000000bf1a12a2724141dbacb4b647c60a0e8201ec0989712ca03e1e850b72")},
                        {10000, uint256S("0000000035998a7b3f5a2f9359a33871ed841e7c9663970ee9c111979622b5e0")},
                        {12000, uint256S("000000007c3c9b38f2e8db4b799b412732be669fab032ca30f658cfd100f2716")},
                        {14000, uint256S("0000000042c7c678e6d357027b03a1b5d9a2ad105cde1ddd7d2135f0acf19cf2")},
                        {16000, uint256S("00000000855044699edecd7f1a5e4ce517651aeb205b957472d1827ea558f52a")},

                }
        };

        chainTxData = ChainTxData{

        };

        /* disable fallback fee on mainnet */
        //m_fallback_fee_enabled = false;
    }
};
/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 525600/2.5;

        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 1; // optimization starting from 1;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1; // optimization starting from 1; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP65Height = 1; // optimization starting from 1; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        //consensus.powLimit("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetSpacing = 2.5 * 60 * 10; // retarget difficulty every 10 blocs or 1500s or 25 min
        consensus.nPowTargetTimespan =   2.5 * 60 ; // block generated every...
        assert(consensus.nPowTargetTimespan<= consensus.nPowTargetSpacing );
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); //1354312

        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x07;
        nDefaultPort = 11791;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 10;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1569352641,1569355124,0x1d00ffff,1, 50*COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("000677a45f51a07efe866d2eb0748ad463439ce2edef4eae67098d93ce482787"));
        assert(genesis.hashMerkleRoot == uint256S("49d0adba8beb9322eae3458279121075bd9d0e84b61e651d7b67262bbccb292b"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xDF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0xA4};

        bech32_hrp = "tff";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        //fMineBlocksOnDemand = true;


        checkpointData = {
        };

        chainTxData = ChainTxData{
                // Data from rpc: getchaintxstats 4096 0000000000000037a8cd3e06cd5edbfe9dd1dbcc5dacab279376ef7cfc2b4c75
                /* nTime    */ 0,
                /* nTxCount */ 0,
                /* dTxRate  */ 0
        };

        /* enable fallback fee on testnet */
        //m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 1;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 1; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1; // optimization starting from 1; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP65Height = 1; // optimization starting from 1; // BIP66 activated on regtest (Used in functional tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nPowTargetSpacing = 2.5 * 60 * 10; // retarget difficulty every 10 blocs or 1500s or 25 min
        consensus.nPowTargetTimespan =   2.5 * 60 ; // block generated every...
        assert(consensus.nPowTargetTimespan<= consensus.nPowTargetSpacing );
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdf;
        nDefaultPort = 18791;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateVersionBitsParametersFromArgs(args);

        genesis = CreateGenesisBlock(1569352641,1569355124,0x1d00ffff,1, 50*COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("000677a45f51a07efe866d2eb0748ad463439ce2edef4eae67098d93ce482787"));
        assert(genesis.hashMerkleRoot == uint256S("49d0adba8beb9322eae3458279121075bd9d0e84b61e651d7b67262bbccb292b"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        //fMineBlocksOnDemand = true;

        checkpointData = {
        };

        chainTxData = ChainTxData{
                0,
                0,
                0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "ffrt";

        /* enable fallback fee on regtest */
        //m_fallback_fee_enabled = true;
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateVersionBitsParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateVersionBitsParametersFromArgs(const ArgsManager& args)
{
    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
 