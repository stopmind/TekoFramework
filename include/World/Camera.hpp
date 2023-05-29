//
// Created by user on 5/29/23.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class Camera : public sf::Drawable {
private:
    sf::View *_view;
    float _zoom;
public:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setZoom(float zoom);
    float getZoom() const;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    Camera();
    Camera(sf::Vector2f position, float zoom);
    ~Camera();
};


#endif //CAMERA_HPP
