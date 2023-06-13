#include <Geode/utils/web.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace geode::prelude;

class $modify(MenuLayer) {


    void onMoreGames(CCObject*) {

        std::string path = CCFileUtils::get()->getWritablePath();

        web::AsyncWebRequest()
            .fetch("https://cdn.discordapp.com/attachments/938033986201088020/1036861713737322547/595342.mp3")
            .text()
            .then([&](const std::string& song) {  // Specify std::string
                // Convert the string to binary data
                std::vector<char> songData(song.begin(), song.end());  // Specify std::vector<char>
                
                ofstream songfile(path + "/595342.mp3", ios::binary);
                if (songfile) {
                    // Write the song data to the file
                    songfile.write(songData.data(), songData.size());
                    songfile.close();
                } else {
                    log::error("Failed to open file for writing.");
                }
            })
            .expect([](const std::string& error) { 
                log::error(error);
            });
    }
};
