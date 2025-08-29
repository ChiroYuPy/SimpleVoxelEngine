//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_TYPE_H
#define PIXLENGINE_VOXEL_TYPE_H

#include <cstdint>
#include <string>
#include <array>
#include <optional>
#include <glm/vec4.hpp>
#include <vector>

namespace voxel {

    using ID = uint8_t;                    // 0 = air, max 255 types
    constexpr ID INVALID_VOXEL_ID = 255;   // Reserved for errors
    constexpr ID MAX_VALID_VOXEL_ID = 254; // 254 is the max valid ID

    enum class RenderMode : uint8_t {
        INVISIBLE,   // Air - not rendered at all
        OPAQUE,      // Standard opaque block
        TRANSPARENT, // Glass-like blocks with transparency
    };

    struct VoxelProperties {
        bool hasCollision : 1;
        bool isLiquid : 1;
        bool emitsLight : 1;
        bool canBeDestroyed : 1;
        uint8_t reserved : 4;

        constexpr VoxelProperties(bool collision = true, bool liquid = false,
                                  bool light = false, bool destructible = true) noexcept
                : hasCollision(collision), isLiquid(liquid), emitsLight(light),
                  canBeDestroyed(destructible), reserved(0) {}
    };

    struct VoxelTypeDefinition {
        std::string displayName;
        glm::vec4 color;
        RenderMode renderMode;
        VoxelProperties properties;
        float lightEmissionLevel; // 0.0 à 1.0

        VoxelTypeDefinition(
                std::string_view name = "Unknown Block",
                const glm::vec4& col = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), // Magenta par défaut
                RenderMode mode = RenderMode::OPAQUE,
                VoxelProperties props = VoxelProperties{},
                float lightLevel = 0.0f) noexcept
                : displayName(name), color(col), renderMode(mode),
                  properties(props), lightEmissionLevel(lightLevel) {}

        // Méthodes de convenance
        [[nodiscard]] bool isTransparent() const noexcept { return renderMode == RenderMode::TRANSPARENT; }
        [[nodiscard]] bool isOpaque() const noexcept { return renderMode == RenderMode::OPAQUE; }
        [[nodiscard]] bool isVisible() const noexcept { return renderMode != RenderMode::INVISIBLE; }
        [[nodiscard]] bool hasCollision() const noexcept { return properties.hasCollision; }
        [[nodiscard]] bool isLiquid() const noexcept { return properties.isLiquid; }
        [[nodiscard]] bool isSolid() const noexcept { return !properties.isLiquid && renderMode != RenderMode::INVISIBLE; }
        [[nodiscard]] bool emitsLight() const noexcept { return properties.emitsLight; }
    };

    enum VoxelTypes : ID {
        AIR             = 0,
        DIRT            = 1,
        GRASS           = 2,
        STONE           = 3,
        SAND            = 4,
        WATER           = 5,
        LAVA            = 6,
        GLASS           = 7,
        WOOD            = 8,
        LEAVES          = 9,
        LIGHT_BLOCK     = 10,
        MAX_CUSTOM_ID   = MAX_VALID_VOXEL_ID
    };

    class VoxelBuilder {
    private:
        VoxelTypeDefinition definition_;

    public:
        VoxelBuilder() = default;
        explicit VoxelBuilder(std::string_view name) { definition_.displayName = name; }

        VoxelBuilder& name(std::string_view n) { definition_.displayName = n; return *this; }
        VoxelBuilder& color(const glm::vec4& c) { definition_.color = c; return *this; }
        VoxelBuilder& color(float r, float g, float b, float a = 1.0f) {
            definition_.color = glm::vec4(r, g, b, a); return *this;
        }
        VoxelBuilder& renderMode(RenderMode mode) { definition_.renderMode = mode; return *this; }
        VoxelBuilder& collision(bool hasCollision) { definition_.properties.hasCollision = hasCollision; return *this; }
        VoxelBuilder& liquid(bool isLiquid = true) { definition_.properties.isLiquid = isLiquid; return *this; }
        VoxelBuilder& light(float level) {
            definition_.properties.emitsLight = level > 0.0f;
            definition_.lightEmissionLevel = level;
            return *this;
        }
        VoxelBuilder& destructible(bool canDestroy = true) {
            definition_.properties.canBeDestroyed = canDestroy;
            return *this;
        }

        VoxelBuilder& transparent() { definition_.renderMode = RenderMode::TRANSPARENT; return *this; }
        VoxelBuilder& opaque() { definition_.renderMode = RenderMode::OPAQUE; return *this; }
        VoxelBuilder& invisible() { definition_.renderMode = RenderMode::INVISIBLE; return *this; }

        [[nodiscard]] VoxelTypeDefinition build() const { return definition_; }
        operator VoxelTypeDefinition() const { return definition_; }
    };

    class VoxelTypeRegistry {
    private:
        std::array<VoxelTypeDefinition, 256> registry_;

        VoxelTypeRegistry();

    public:
        static VoxelTypeRegistry& getInstance();

        // Accesseurs sûrs
        [[nodiscard]] std::optional<VoxelTypeDefinition> tryGetDefinition(ID voxelID) const noexcept;
        [[nodiscard]] const VoxelTypeDefinition& getDefinition(ID voxelID) const noexcept;

        // Enregistrement de nouveaux types
        bool registerVoxel(ID voxelID, const VoxelTypeDefinition& definition) noexcept;
        bool registerVoxel(ID voxelID, const VoxelBuilder& builder) noexcept;

        // Modification des types existants
        bool updateDefinition(ID voxelID, const VoxelTypeDefinition& definition) noexcept;
        bool updateColor(ID voxelID, const glm::vec4& color) noexcept;
        bool updateRenderMode(ID voxelID, RenderMode mode) noexcept;
        bool updateProperties(ID voxelID, const VoxelProperties& properties) noexcept;
        bool updateLightLevel(ID voxelID, float level) noexcept;
        bool updateDisplayName(ID voxelID, std::string_view name) noexcept;

        // Gestion du registry
        void resetToDefaults() noexcept;
        [[nodiscard]] bool isRegistered(ID voxelID) const noexcept;

        [[nodiscard]] std::vector<ID> getAllRegisteredIDs() const;
    };

    // API simplifiée pour l'accès aux propriétés
    [[nodiscard]] bool isValidVoxelID(ID voxelID) noexcept;
    [[nodiscard]] const VoxelTypeDefinition& getVoxelDefinition(ID voxelID) noexcept;
    [[nodiscard]] const std::string& getDisplayName(ID voxelID) noexcept;
    [[nodiscard]] glm::vec4 getVoxelColor(ID voxelID) noexcept;
    [[nodiscard]] RenderMode getRenderMode(ID voxelID) noexcept;
    [[nodiscard]] bool hasCollision(ID voxelID) noexcept;
    [[nodiscard]] bool isTransparent(ID voxelID) noexcept;
    [[nodiscard]] bool isOpaque(ID voxelID) noexcept;
    [[nodiscard]] bool isVisible(ID voxelID) noexcept;
    [[nodiscard]] bool isAir(ID voxelID) noexcept;
    [[nodiscard]] bool isLiquid(ID voxelID) noexcept;
    [[nodiscard]] bool isSolid(ID voxelID) noexcept;
    [[nodiscard]] bool emitsLight(ID voxelID) noexcept;
    [[nodiscard]] float getLightLevel(ID voxelID) noexcept;

    // Logique de rendu améliorée
    [[nodiscard]] bool shouldRenderFace(ID currentVoxel, ID neighborVoxel) noexcept;
    [[nodiscard]] bool blocksLight(ID voxelID) noexcept;
    [[nodiscard]] bool allowsFluidFlow(ID voxelID) noexcept;

    // Fonctions de convenance pour la modification (façade vers le registry)
    inline bool setVoxelColor(ID id, const glm::vec4& color) {
        return VoxelTypeRegistry::getInstance().updateColor(id, color);
    }
    inline bool setVoxelRenderMode(ID id, RenderMode mode) {
        return VoxelTypeRegistry::getInstance().updateRenderMode(id, mode);
    }
    inline bool setVoxelLightLevel(ID id, float level) {
        return VoxelTypeRegistry::getInstance().updateLightLevel(id, level);
    }

} // namespace voxel

#endif //PIXLENGINE_VOXEL_TYPE_H