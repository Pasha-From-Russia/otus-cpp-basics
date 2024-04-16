#include "highscore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string.h>

//----------------------------------------------------------------------------
uint32_t crc32c(const char *t_buf) {
    if (!t_buf || !*t_buf) {
        return 0;
    }
    size_t len = strlen(t_buf);

    #define POLY 0x12345678

    uint32_t crc = ~0;
    while (len--) {
        crc ^= (uint8_t)*t_buf++;
        for (int k = 0; k < 8; k++) {
            crc = (crc & 1) ? (crc >> 1) ^ POLY : crc >> 1;
        }
    }
    return ~crc;
}


//----------------------------------------------------------------------------
void hiscore(const std::string &t_name, const int t_score) {
    std::string line;
    std::stringstream split;

    std::fstream hiscoreFile;
    hiscoreFile.open("./hiscore", std::fstream::in);
    std::map<uint32_t, HiScore> playersTable;
    while (std::getline(hiscoreFile, line)) {
        HiScore data;
        split << line;
        split >> data.name;
        split >> data.score;
        split.clear();
        uint32_t hash = crc32c(data.name.c_str());
        auto it = playersTable.find(hash);
        if (it == playersTable.end()) {
            // добавляем только новые
            playersTable[hash] = data;
        }
    }
    hiscoreFile.close();
    if (t_score != -1) {
        uint32_t hash = crc32c(t_name.c_str());
        HiScore data;
        data.name = t_name;
        data.score = t_score;
        auto it = playersTable.find(hash);
        if (it == playersTable.end()) {
            playersTable[hash] = data;
        } else {
            playersTable[hash].score = t_score;
        }
        hiscoreFile.open("./hiscore", std::fstream::out);
        for (const auto & item : playersTable) {
            hiscoreFile << item.second.name << " " << item.second.score << std::endl;
        }
        hiscoreFile.close();
    }
    std::cout
        << "High scores table:"
        << std::endl
        << "Player"
        << std::setw(kMaxNameLen + 1)
        << "Attempts"
        << std::endl;
    // недостаток: из-за особенностей std::map получаем список, не отсортированный по имени
    for (const auto & item : playersTable) {
        std::cout
            << item.second.name
            << " "
            << std::setw(kMaxNameLen - strlen(item.second.name.c_str()))
            << item.second.score
            << std::endl;
    }
    playersTable.clear();
}
