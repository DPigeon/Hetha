
#include "Projectile.h"
#include "World.h"

Projectile::Projectile(int x, int y, int velocity) {
  pPosX = x;
  pPosY = y;
  velocityY = velocity;
}

Projectile::Draw() {
  if (pPosX != 0 && pPosY != 0)
    display.fillCircle(pPosX, pPosY - player.GetSize(), pSize, WHITE); // place it in front of player
}

Projectile::Update(float dt) {
  //pPosX -= velocityX * dt;
  pPosY -= velocityY * dt; // We want the projectile to go up the screen
}

Projectile::DeleteOutOfMap() {
  if (pPosY < 0) {
    World* world = World::GetInstance();
    world->RemoveProjectile(); 
    delete this; // Freeing up memory once a projectile is not in map anymore ERROR here
  }
}

Projectile::SetPosition(int x, int y) {
  pPosX = x;
  pPosY = y;
}

Projectile::SetVelocity(int vX, int vY) {
  velocityX = vX;
  velocityY = vY;
}

Projectile::~Projectile() {
}
