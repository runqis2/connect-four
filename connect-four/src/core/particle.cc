#include <core/particle.h>
#include <math.h>

namespace gas {

Particle::Particle(glm::vec2 pos, glm::vec2 vel, float mass, float radius,
                   cinder::Color color, int num) {
  position = pos;
  velocity = vel;
  particle_mass = mass;
  particle_radius = radius;
  particle_color = color;
  number = num;
}
float Particle::get_distance(Particle other) {
  float p1 = (position[0] - other.get_position()[0]) * (position[0] - other.get_position()[0]);
  float p2 = (position[1] - other.get_position()[1]) * (position[0] - other.get_position()[0]);
  //std::cout <<std::sqrt(abs(p1 - p2)) << "\n";
  return std::sqrt(abs(p1 - p2));
}
bool Particle::is_collided(Particle other) {
  if (get_distance(other) > (particle_radius + other.get_radius())) {

    return false;
  } else {

    return true;
  }
}

void Particle::collision(Particle other) {

  glm::vec2 stuff = (velocity - other.get_velocity()) * (position - other.get_position());
  if (stuff[0] < 0 && stuff[1] < 0) {
    //std::cout << 2 * velocity << " \n";
    float mass_multiplier = (2 * other.get_mass()) / (particle_mass + other.get_mass());
    glm::vec2 top = (velocity - other.velocity) * (position - other.position);
    float bottom = (position[0] - other.position[0]) * (position[0] - other.position[0]) + (position[1] - other.position[1]) * (position[1] - other.position[1]);
    glm::vec2 last = position - other.position;

    glm::vec2 final = mass_multiplier * (top/bottom) * last;
    velocity -= final;
    std::cout <<final << "\n";

              //std::cout << (2 * other.get_mass())/ (particle_mass + other.get_mass()) << "\n";
    //std::cout << ((velocity )) << " \n";
    //std::cout << get_distance(other) * get_distance(other) *(position - other.get_position()) << "\n";
    //std::cout << "_______________________________________" << "\n";

  }
}

void Particle::set_position(glm::vec2 pos) {
  position = pos;
}
void Particle::set_velocity(glm::vec2 vel) {
  velocity = vel;
}
void Particle::set_mass(float new_mass) {
  particle_mass = new_mass;
}

glm::vec2 Particle::get_position() {
  return position;
}
glm::vec2 Particle::get_velocity() {
  return velocity;
}
float Particle::get_mass() {
  return particle_mass;
}
float Particle::get_radius() {
  return particle_radius;
}
int Particle::get_number() {
  return number;
}
cinder::Color Particle::get_color() {
  return particle_color;
}
void Particle::move() {
  position += velocity;
}
}  // namespace gas