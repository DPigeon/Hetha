
class World { 
  private:
    const static int numEnemy = 5;
    static World* instance; 
    Enemy* enemies[numEnemy];
  public:
    World() {
      instance = this;
    }
    World* GetInstance() {
      return instance;
    }
    void addEnemy(Enemy* enemy) {
      for (int i = 0; i < numEnemy; i++) {
        Enemy* enemy = new Enemy();
        enemies[i] = enemy;
      }
  }

    ~World() {
    }
};

World* World::instance;
