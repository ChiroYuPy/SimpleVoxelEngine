//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/VoxelType.h"
#include <algorithm>

namespace voxel {


    VoxelTypeRegistry::VoxelTypeRegistry() {
        resetToDefaults();
    }

    VoxelTypeRegistry& VoxelTypeRegistry::getInstance() {
        static VoxelTypeRegistry instance;
        return instance;
    }

    std::optional<VoxelTypeDefinition> VoxelTypeRegistry::tryGetDefinition(ID voxelID) const noexcept {
        if (!isValidVoxelID(voxelID)) {
            return std::nullopt;
        }
        return registry_[voxelID];
    }

    const VoxelTypeDefinition& VoxelTypeRegistry::getDefinition(ID voxelID) const noexcept {
        static const VoxelTypeDefinition fallback{"Invalid Block", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)};

        if (!isValidVoxelID(voxelID)) {
            return fallback;
        }
        return registry_[voxelID];
    }

    bool VoxelTypeRegistry::registerVoxel(ID voxelID, const VoxelTypeDefinition& definition) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID] = definition;
        return true;
    }

    bool VoxelTypeRegistry::registerVoxel(ID voxelID, const VoxelBuilder& builder) noexcept {
        return registerVoxel(voxelID, builder.build());
    }

    bool VoxelTypeRegistry::updateDefinition(ID voxelID, const VoxelTypeDefinition& definition) noexcept {
        return registerVoxel(voxelID, definition);
    }

    bool VoxelTypeRegistry::updateColor(ID voxelID, const glm::vec4& color) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID].color = color;
        return true;
    }

    bool VoxelTypeRegistry::updateRenderMode(ID voxelID, RenderMode mode) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID].renderMode = mode;
        return true;
    }

    bool VoxelTypeRegistry::updateProperties(ID voxelID, const VoxelProperties& properties) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID].properties = properties;
        return true;
    }

    bool VoxelTypeRegistry::updateLightLevel(ID voxelID, float level) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID].lightEmissionLevel = std::clamp(level, 0.0f, 1.0f);
        registry_[voxelID].properties.emitsLight = level > 0.0f;
        return true;
    }

    bool VoxelTypeRegistry::updateDisplayName(ID voxelID, std::string_view name) noexcept {
        if (!isValidVoxelID(voxelID)) {
            return false;
        }
        registry_[voxelID].displayName = name;
        return true;
    }

    bool VoxelTypeRegistry::isRegistered(ID voxelID) const noexcept {
        return isValidVoxelID(voxelID) && registry_[voxelID].displayName != "Unknown Block";
    }

    std::vector<ID> VoxelTypeRegistry::getAllRegisteredIDs() const {
        std::vector<ID> result;
        result.reserve(32);

        for (ID id = 0; id <= MAX_VALID_VOXEL_ID; ++id) {
            if (isRegistered(id)) {
                result.push_back(id);
            }
        }
        return result;
    }

    void VoxelTypeRegistry::resetToDefaults() noexcept {
        // Réinitialiser tous les types à "Unknown Block" par défaut
        for (auto& def : registry_) {
            def = VoxelTypeDefinition{};
        }

        // Définir les types de base avec le builder pattern
        registry_[AIR] = VoxelBuilder("Air")
                .color(0.0f, 0.0f, 0.0f, 0.0f)
                .invisible()
                .collision(false)
                .build();

        registry_[DIRT] = VoxelBuilder("Dirt")
                .color(0.502f, 0.322f, 0.184f, 1.0f)
                .opaque()
                .build();

        registry_[GRASS] = VoxelBuilder("Grass")
                .color(0.486f, 0.675f, 0.09f, 1.0f)
                .opaque()
                .build();

        registry_[STONE] = VoxelBuilder("Stone")
                .color(0.498f, 0.498f, 0.498f, 1.0f)
                .opaque()
                .build();

        registry_[SAND] = VoxelBuilder("Sand")
                .color(0.98f, 0.941f, 0.812f, 1.0f)
                .opaque()
                .build();

        registry_[WATER] = VoxelBuilder("Water")
                .color(0.247f, 0.463f, 0.894f, 0.4f)
                .transparent()
                .collision(false)
                .liquid()
                .build();

        registry_[LAVA] = VoxelBuilder("Lava")
                .color(0.812f, 0.29f, 0.059f, 0.9f)
                .transparent()
                .collision(false)
                .liquid()
                .light(0.8f)
                .build();

        registry_[GLASS] = VoxelBuilder("Glass Block")
                .color(1.0f, 1.0f, 1.0f, 0.5f)
                .transparent()
                .build();

        registry_[WOOD] = VoxelBuilder("Wood Log")
                .color(0.42f, 0.31f, 0.184f, 1.0f)
                .opaque()
                .build();

        registry_[LEAVES] = VoxelBuilder("Leaves")
                .color(0.298f, 0.608f, 0.137f, 0.5f)
                .transparent()
                .build();

        registry_[LIGHT_BLOCK] = VoxelBuilder("Light Block")
                .color(1.0f, 1.0f, 0.8f, 1.0f)
                .opaque()
                .light(1.0f)
                .build();
    }

    // Fonctions utilitaires globales
    bool isValidVoxelID(ID voxelID) noexcept {
        return voxelID <= MAX_VALID_VOXEL_ID;
    }

    const VoxelTypeDefinition& getVoxelDefinition(ID voxelID) noexcept {
        return VoxelTypeRegistry::getInstance().getDefinition(voxelID);
    }

    const std::string& getDisplayName(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).displayName;
    }

    glm::vec4 getVoxelColor(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).color;
    }

    RenderMode getRenderMode(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).renderMode;
    }

    bool hasCollision(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).hasCollision();
    }

    bool isTransparent(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).isTransparent();
    }

    bool isOpaque(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).isOpaque();
    }

    bool isVisible(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).isVisible();
    }

    bool isAir(ID voxelID) noexcept {
        return voxelID == AIR;
    }

    bool isLiquid(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).isLiquid();
    }

    bool isSolid(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).isSolid();
    }

    bool emitsLight(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).emitsLight();
    }

    float getLightLevel(ID voxelID) noexcept {
        return getVoxelDefinition(voxelID).lightEmissionLevel;
    }

    bool shouldRenderFace(ID currentVoxel, ID neighborVoxel) noexcept {
        const auto& current = getVoxelDefinition(currentVoxel);
        const auto& neighbor = getVoxelDefinition(neighborVoxel);

        // Ne pas rendre les faces des voxels invisibles
        if (!current.isVisible()) {
            return false;
        }

        // Toujours rendre les faces contre l'air
        if (isAir(neighborVoxel)) {
            return true;
        }

        // Si les deux voxels sont opaques, pas besoin de rendre la face
        if (current.isOpaque() && neighbor.isOpaque()) {
            return false;
        }

        // Cas spéciaux pour les liquides identiques
        if (currentVoxel == neighborVoxel && current.isLiquid()) {
            return false;
        }

        return true;
    }

    bool blocksLight(ID voxelID) noexcept {
        return isOpaque(voxelID);
    }

    bool allowsFluidFlow(ID voxelID) noexcept {
        const auto& def = getVoxelDefinition(voxelID);
        return isAir(voxelID) || !def.hasCollision();
    }

}