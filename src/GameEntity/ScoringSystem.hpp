#pragma once
#include <vector>
#include <functional>
#include <map>
#include "ScoreAction.hpp"

namespace GameEntity {
    class ScoringSystem
    {
    private:
        int m_score;
        int m_level;
        int m_cleared;
        std::vector<std::function<void(int)>> m_subscribed_fns;
        int scoreSingle();
        int scoreDouble();
        int scoreTriple();
        int scoreTetris();
        int scoreSoftDrop(int count);
        int scoreHardDrop(int count);
    public:
        ScoringSystem();
        void updateLineScore(LineAction scoreAction);
        void updateDropScore(DropAction dropAction, int count);
        void addSubscription(std::function<void(int)> fn);
    };
}
