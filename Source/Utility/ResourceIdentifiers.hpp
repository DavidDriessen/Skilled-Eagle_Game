//
// Created by endargon on 1/27/17.
//

#ifndef SKILLED_EAGLE_GAME_RESOURCEIDENTIFIERS_HPP
#define SKILLED_EAGLE_GAME_RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes
namespace sf
{
    class Texture;
    class Font;
    class Shader;
}
namespace Textures
{
    enum ID
    {
        Assault,
        Sniper,
        Pistol,
        Sword,
        Floor,
        Floor1,
        Floor2,
        Floor3,
        Floor4,
        Finish,
        Loot,
        LootUsed,
        Level1,
        SplashScreen,
        SplashName,
        SplashPresents,
        Cyber
    };
}

namespace Shaders
{
    enum ID
    {
        BrightnessPass,
        DownSamplePass,
        GaussianBlurPass,
        AddPass,
    };
}

namespace Fonts
{
    enum ID
    {
        Default,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;
#endif //SKILLED_EAGLE_GAME_RESOURCEIDENTIFIERS_HPP
