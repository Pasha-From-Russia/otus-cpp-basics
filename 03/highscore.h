#pragma once
#include <string>

static constexpr int kMaxPlayersInTable = 10;
static constexpr int kMaxNameLen = 32;

typedef struct {
    std::string name;
    int score;
} HiScore;

void hiscore(const std::string &name, const int score);
