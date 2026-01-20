// example obtained from https://godbolt.org/z/Efr7bK9jn
// in context of https://simdjson.github.io/simdjson_talks/cppcon2025/cppcon_2025_slides.html

#include <iostream>
#include <map>

#define SIMDJSON_STATIC_REFLECTION 1

#include </nix/store/hf1rkb0a4m2a7rn71cqw9bh6bc80qklm-simdjson-4.2.4/include/simdjson.h>
using namespace simdjson;



struct Equipment {
    std::string name;
    int damage; int durability;
};
struct Achievement {
    std::string title; std::string description; bool unlocked;
    uint64_t unlock_time;
};
struct Player {
    std::string username;
    int level; double health;
    std::vector<std::string> inventory;
    std::map<std::string, Equipment> equipped;     // New!
    std::vector<Achievement> achievements;         // New!
    std::optional<std::string> guild_name;         // New!
};


void save_player(const Player& p) {
    std::string json = simdjson::to_json(p);  // That's it!
    // Save json to file...
}

Player load_player(std::string& json_str) {
    return simdjson::from(json_str);  // That's it!
}

int main() {
    std::string json =  R"( {
  "username": "Aventurier42",
  "level": 10,
  "health": 85.5,
  "inventory": ["Potion de soin", "Épée en fer", "Bouclier en bois"],
  "equipped": {
    "arme": {
      "name": "Épée en fer",
      "damage": 15,
      "durability": 80
    },
    "armure": {
      "name": "Plastron en cuir",
      "damage": 0,
      "durability": 60
    }
  },
  "achievements": [
    {
      "title": "Premier combat",
      "description": "Vaincre un ennemi pour la première fois",
      "unlocked": true,
      "unlock_time": 321321312312321321
    },
    {
      "title": "Explorateur novice",
      "description": "Découvrir 5 lieux différents",
      "unlocked": false,
      "unlock_time": 321321312312321321
    }
  ],
  "guild_name": "Les Gardiens de l'Aube"
} )";
    Player p = load_player(json);
    std::cout << simdjson::to_json(p) << "\n";
    return EXIT_SUCCESS;
}


