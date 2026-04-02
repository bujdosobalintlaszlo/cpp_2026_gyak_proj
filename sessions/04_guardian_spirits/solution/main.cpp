#include "weapon.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "  GUARDIAN SPIRITS (RAII)\n";
    std::cout << "================================\n";

    std::cout << "\nCreating weapons with smart pointers...\n";

    // Create weapon manager
    WeaponManager manager;

    // Create weapons using make_unique
    auto excalibur = std::make_unique<Weapon>("Excalibur", 100);
    auto staff = std::make_unique<Weapon>("Fireball Staff", 75);
    auto dagger = std::make_unique<Weapon>("Shadow Dagger", 50);

    // Add to manager (transfer ownership)
    manager.addWeapon(std::move(excalibur));
    manager.addWeapon(std::move(staff));
    manager.addWeapon(std::move(dagger));

    manager.displayAll();

    // Transfer ownership out
    std::cout << "\nTransferring ownership...\n";
    auto heroWeapon = manager.removeWeapon("Excalibur");
    if (heroWeapon) {
        std::cout << "Moved " << heroWeapon->getName() << " to hero\n";
    }
    std::cout << "Weapon Manager now has " << manager.count() << " weapons\n";

    // Demonstrate shared ownership
    std::cout << "\nSharing weapon...\n";
    auto sharedStaff = std::make_shared<Weapon>("Lightning Staff", 80);
    auto copy = sharedStaff;  // Shared ownership
    std::cout << "Lightning Staff shared (reference count: " << sharedStaff.use_count() << ")\n";

    std::cout << "\nWeapons automatically destroyed when going out of scope...\n";

    // All weapons automatically cleaned up here
    return 0;
}
