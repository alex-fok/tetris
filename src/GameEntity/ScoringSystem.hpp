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
        int m_combo;
        bool m_isB2BActive;
        static const int comboMultiplier = 50;
        std::vector<std::function<void(int)>> m_subscribed_fns;
        void scoreSingle();
        void scoreDouble();
        void scoreTriple();
        void scoreTetris();
        void scoreSoftDrop(int count);
        void scoreHardDrop(int count);
    public:
        ScoringSystem();
        void updateLineScore(LineAction scoreAction);
        void updateDropScore(DropAction dropAction, int count);
        void clearCombo();
        void addSubscription(std::function<void(int)> fn);
    };
}
