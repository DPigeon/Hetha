#pragma once

class GameInterface
{
  private:
    int uiSound = 2000;
  public:
    void Introduction();
    void SelectionSound();
    void MenuIntro(bool textColor);
    void LevelUp(int level);
    void GameOver();
    ~GameInterface();
};
