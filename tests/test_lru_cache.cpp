//==============================================================================
// LRU CHACHE TEST SUITE
//==============================================================================
#include "lru_cache/lru_cache.h"
#include "gtest/gtest.h"
//==============================================================================
// LRUCacheTest Class
// Description: This class defines the test fixture for the LRUCache class. It
//              sets up the testing environment and includes all the test cases
//              for the LRUCache class.
//==============================================================================
class LRUCacheTest : public ::testing::Test {
protected:
    LRUCache<HockeyPlayer>* cache;

    void SetUp() override {
        cache = new LRUCache<HockeyPlayer>(3); // Cache with capacity 3
    }

    void TearDown() override {
        delete cache;
    }
};
//==============================================================================
// Test Cases
//==============================================================================
TEST_F(LRUCacheTest, IsEmptyInitially) {
    EXPECT_TRUE(cache->isEmpty());
}

TEST_F(LRUCacheTest, AddsAndRetrievesSingleItem) {
    HockeyPlayer* player = new HockeyPlayer(/* parameters */);
    cache->refer(1, player);
    EXPECT_EQ(cache->getPlayer(1), player);
}

TEST_F(LRUCacheTest, EvictsLRUItem) {
    HockeyPlayer* player1 = new HockeyPlayer(/* parameters */);
    HockeyPlayer* player2 = new HockeyPlayer(/* parameters */);
    HockeyPlayer* player3 = new HockeyPlayer(/* parameters */);
    HockeyPlayer* player4 = new HockeyPlayer(/* parameters */);

    cache->refer(1, player1);
    cache->refer(2, player2);
    cache->refer(3, player3);
    // Cache is full now
    cache->refer(4, player4);
    // Player 1 should be evicted
    EXPECT_EQ(cache->getPlayer(1), nullptr);
    EXPECT_EQ(cache->getPlayer(4), player4);
}

TEST_F(LRUCacheTest, UpdatesLRUOrder) {
    HockeyPlayer* player1 = new HockeyPlayer(/* parameters */);
    HockeyPlayer* player2 = new HockeyPlayer(/* parameters */);
    HockeyPlayer* player3 = new HockeyPlayer(/* parameters */);

    cache->refer(1, player1);
    cache->refer(2, player2);
    cache->refer(3, player3);
    // Accessing player 1 again
    cache->getPlayer(1);
    cache->refer(4, new HockeyPlayer(/* parameters */)); // This should evict player 2

    EXPECT_EQ(cache->getPlayer(1), player1);
    EXPECT_EQ(cache->getPlayer(2), nullptr);
}
