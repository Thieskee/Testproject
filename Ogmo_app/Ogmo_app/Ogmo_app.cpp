// Copyright2020 Shit Team
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <rapidxml/rapidxml.hpp>

void drawObject(const int xOrigin, const int yOrigin,
    const int width, const int height, const std::string assetPath);
void drawForegroundTile(const int xOrigin, const int yOrigin,
    const int width, const int height, const std::string assetPath);
void drawBackgroundTile(const int xOrigin, const int yOrigin,
    const int width, const int height, const std::string assetPath);

void parseFiles(const std::string JSON_FILE);
void draw(int x, int y, std::string imgurl);

/*
 * nuget packages:
 * nlohmann
 * rapidxml
 */

 /*
  * call order:
  *
  *  tiles:
  *      x: 0, y: 0
  *      x: 0, y: 1
  *      x: 0, y: 2
  *      x: 0, y: 3
  *      x: 0, y: etc
  *
  *      x: 1, y: 0
  *      x: 1, y: 1
  *      x: 1, y: 2
  *      x: 1, y: 3
  *      x: 1, y: etc
  *
  *  objects
  *
  */

int main() {
    // contains the map
    const std::string JSON_FILE = "../assets/W1.json";

    parseFiles(JSON_FILE);
}


void drawObject(const int xOrigin, const int yOrigin,
    const int width, const int height, const std::string assetPath) {
    /* Your code here */ std::cout << "drawObject:         "
        /* Your code here */ << xOrigin << "/" << yOrigin << " \t"
        /* Your code here */ << width << "/" << height << " \t"
        /* Your code here */ << assetPath << "\n";
}

void drawForegroundTile(const int xOrigin, const int yOrigin,
    const int width, const int height, const std::string assetPath) {
    /* Your code here */ std::cout << "drawForegroundTile: "
        /* Your code here */ << xOrigin << "/" << yOrigin << " \t"
        /* Your code here */ << width << "/" << height << " \t"
        /* Your code here */ << assetPath << "\n";
}


void parseFiles(const std::string JSON_FILE) {
    // Parse JSON map data
    nlohmann::json jsonData;
    {
        std::ifstream ifs(JSON_FILE);
        ifs >> jsonData;
    }


    // Parse data & make call to draw functions
    for (nlohmann::json layer : jsonData.at("layers")) {
        if (layer.at("name") == "Tile_layer") {
            int width = layer.at("gridCellsX").get<int>();
            int height = layer.at("gridCellsY").get<int>();
            //std::vector<int> test = layer.at("dataCoords").get<std::vector<int>>();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int iterator = i + j * height;
                    int spriteData = layer.at("dataCoords").at(iterator).get<int>();

                    if (spriteData != -1) { // Empty
                        std::string assetPath = "../assets/Tiles/" + std::to_string(spriteData);
                        int x = i * 32;
                        int y = j * 32;
                        int width = layer.at("gridCellWidth").get<int>();
                        int height = layer.at("gridCellHeight").get<int>();


                        drawForegroundTile(x, y, width, height, assetPath);
                    }
                }
            }
        }
        
        else if (layer.at("name") == "Entity_layer") {
            for (nlohmann::json object : layer.at("entities")) {
                int spriteID = object.at("id").get<int>();

                std::string assetPath = "../assets/npc" + std::to_string(spriteID);
                int x = object.at("x").get<int>();
                int y = object.at("y").get<int>();
                int width = object.at("width").get<int>();
                int height = object.at("height").get<int>();

                drawObject(x, y, width, height, assetPath);
            }
        }
    }

}