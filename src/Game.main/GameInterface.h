#pragma once

class GameInterface
{
  private:
    int uiSound = 90000;
  public:
    void Introduction();
    void SelectionSound();
    void MenuIntro(bool textColor);
    void GameOver();
    ~GameInterface();
};
