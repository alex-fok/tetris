#pragma once
#include <vector>
#include <functional>

namespace GameEntity {
    class ScoringSystem
    {
    private:
        int m_score;
        int m_level;
        int m_cleared;
        std::vector<std::function<void(int)>> m_subscribed_fns;
    public:
        ScoringSystem();
        void updateScore(int linesCleared);
        void addSubscription(std::function<void(int)> fn);
    };
}
