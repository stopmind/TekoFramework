//
// Created by user on 5/29/23.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include "World/Camera.hpp"

void Camera::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    _view->setSize((sf::Vector2f)target.getSize());
    _view->zoom(_zoom);
    target.setView(*_view);
}

void Camera::setZoom(float zoom) {
    _zoom = zoom;
}

float Camera::getZoom() const {
    return _zoom;
}

void Camera::setPosition(sf::Vector2f position) {
    _view->setCenter(position);
}

sf::Vector2f Camera::getPosition() {
    return _view->getCenter();
}

Camera::Camera() : Camera({}, 1) {
}

Camera::Camera(sf::Vector2f position, float zoom) {
    _view = new sf::View();
    _view->setCenter(position);
    _zoom = zoom;
}

Camera::~Camera() {
    delete _view;
}