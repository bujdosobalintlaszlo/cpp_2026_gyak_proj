#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Weapon {
   private:
    std::string name_;
    int damage_;

   public:
    Weapon(const std::string& name, int damage) : name_(name), damage_(damage) {
        std::cout << "Created: " << name_ << "\n";
    }

    ~Weapon() { std::cout << "Guardian Spirit released: " << name_ << "\n"; }

    // Move constructor
    Weapon(Weapon&& other) noexcept = default;

    // Move assignment
    Weapon& operator=(Weapon&& other) noexcept = default;

    // Delete copy operations (move-only)
    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;

    const std::string& getName() const { return name_; }
    int getDamage() const { return damage_; }

    void attack() const { std::cout << name_ << " deals " << damage_ << " damage!\n"; }
};

class WeaponManager {
   private:
    std::vector<std::unique_ptr<Weapon>> weapons_;

   public:
    void addWeapon(std::unique_ptr<Weapon> weapon) { weapons_.push_back(std::move(weapon)); }

    std::unique_ptr<Weapon> removeWeapon(const std::string& name) {
        auto it = std::find_if(weapons_.begin(), weapons_.end(),
                               [&name](const auto& w) { return w->getName() == name; });

        if (it != weapons_.end()) {
            auto weapon = std::move(*it);
            weapons_.erase(it);
            return weapon;
        }
        return nullptr;
    }

    size_t count() const { return weapons_.size(); }

    void displayAll() const {
        std::cout << "\nWeapon Manager has " << weapons_.size() << " weapons:\n";
        for (const auto& weapon : weapons_) {
            std::cout << "  - " << weapon->getName() << " (damage: " << weapon->getDamage()
                      << ")\n";
        }
    }
};
