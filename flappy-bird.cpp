// 1. Ce que le code fait : 
//- g�re les inputs du joueur
//- Affiche le jeu
//- calcul les scores, les enregistre dans un fichier et les affiche
//- d�termine les donn�es de  l'oiseau (position, vitesse, etc) > pr�fixe b
//- d�termine les donn�es des pipes > pr�fixe p
//- run le jeu : d�place les pipes sur l'�cran, le comportement de l'oiseau 


// 2. Les probl�mes de ce code : 
//- un fichier qui fait tout : god class dont tout d�pend
//- nommage des variables avec des raccourcis non parlant. exe : h et outputHandle
//- met des commentaires pour expliquer les variables > faudrait mieux les nommer directement et se passer de commentaires
//- beaucoup de variables de m�me types ( exemple : int pour birdTop, birdBottom, bl ) > donne la possibilit�s de se tromper quand on passe une variable.
//- d�clenche des erreurs avec juste le mot "error" sans expliquer de quoi il s'agit > difficile de d�bugger avec aussi peu d'information
//- il reste du vieux code commenter qui n'a pas �t� nettoy�
//- le code n'est pas d�coup� en fonctions. La fonction main fait absolument tout
//- imbrique les if les uns dans les autres
//- utilise des magis numbers au lieu de mettre des variables ou des constantes



// TODO: clean this up later

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>
#include <fstream>

int main()
{
  HANDLE inputHandle  = GetStdHandle(STD_INPUT_HANDLE);  // input
  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE); // output
  if (inputHandle == INVALID_HANDLE_VALUE)  { std::cerr << "error"  << std::endl; return 1; }
  if (outputHandle == INVALID_HANDLE_VALUE) { std::cerr << "error" << std::endl; return 1; }

  // use words for console io
  DWORD m  = 0;
  DWORD m2 = 0;
  DWORD m3 = 0;
  if (!GetConsoleMode(inputHandle,  &m))  { std::cerr << "error" << std::endl; return 1; }
  m2 = m;
  m2 &= ~ENABLE_LINE_INPUT;
  m2 &= ~ENABLE_ECHO_INPUT;
  if (!SetConsoleMode(inputHandle, m2))   { std::cerr << "error" << std::endl; return 1; }
  if (GetConsoleMode(outputHandle, &m3))  SetConsoleMode(outputHandle, m3 | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  // bird
  float birdYPosition = 9.0f;         // y position (float)
  float birdVelocity = 0.0f;         // velocity
  int   birdTop = 0;            // top (int)
  int   birdBottom = 0;            // bottom (int)
  int   birdLeft = 10;           // left
  int   birdRight = 10 + 2 - 1;  // right
  int bDead = 0;            // 0 = alive, 1 = dead
  float spawnTimer  = 0.0f;         // spawn timer
  unsigned long long currentScore  = 0; // current score
  unsigned long long bestScore = 0; // best score

  // hud padding
  int leftPadding = 0; // left padding
  int rightPadding = 0; // right padding

  // pipe data
  std::vector<float> pipesXPosition; // x positions
  std::vector<int>   pipesGapTop; // gap tops
  std::vector<int>   pipesBScored; // scored flag (0 or 1)

  // randomNumberGenerator
  std::mt19937 randomNumberGenerator(std::random_device{}());
  std::uniform_int_distribution<int> d(2, 20 - 6 - 2); // gap position

  INPUT_RECORD rec;
  DWORD ne = 0;

  // int debug = 1;
  // if (debug) std::cout << "debug: game starting" << std::endl;

  // load best score
  std::ifstream fin("best-score.txt");
  if (fin)
  {
    fin >> bestScore;
    if (!fin) bestScore = 0; // reset if read failed
  }
  fin.close(); // close the file

  auto prev = std::chrono::steady_clock::now();

  // main loop
  while (bDead == 0)
  {
    // delta time
    auto now = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(now - prev).count();
    prev = now;
    if (dt > 0.1f) dt = 0.1f; // clamp delta time

    // read input events
    DWORD nEvents = 0;
    if (!GetNumberOfConsoleInputEvents(inputHandle, &nEvents)) {
      SetConsoleMode(inputHandle, m);
      return 1;
    }

    for (DWORD i = 0; i < nEvents; ++i) // loop through events
    {
      if (!ReadConsoleInput(inputHandle, &rec, 1, &ne))
      {
        std::cerr << "Failed to read console input." << std::endl;
        SetConsoleMode(inputHandle, m);
        return 1;
      } // end if ReadConsoleInput

      if (rec.EventType == KEY_EVENT)
      {
        KEY_EVENT_RECORD k = rec.Event.KeyEvent;
        if (k.bKeyDown == TRUE)
        {
          if (k.wVirtualKeyCode == VK_RETURN)
          {
            birdVelocity = -14.0f;
          } // end if enter
        } // end if key down
      } // end if key event
    } // end for each event

    birdVelocity = birdVelocity + 42.0f * dt;
    birdYPosition = birdYPosition + birdVelocity * dt;

    spawnTimer = spawnTimer + dt;
    if (spawnTimer >= 1.4f)
    {
      spawnTimer = spawnTimer - 1.4f;
      pipesXPosition.push_back(50.0f); 
      pipesGapTop.push_back(d(randomNumberGenerator)); 
      pipesBScored.push_back(0); 
    } 

    for (int i = 0; i < (int)pipesXPosition.size(); i++) // loop over all pipes
    {
      pipesXPosition[i] = pipesXPosition[i] - 18.0f * dt; // move pipe left

      int pipeRight = (int)std::floor(pipesXPosition[i]) + 6 - 1;
      if (pipesBScored[i] == 0 && pipeRight < 10) {
        pipesBScored[i] = 1;         
        currentScore = currentScore + 1;        
        if (currentScore > bestScore) bestScore = currentScore;
      }}

    for (int i = (int)pipesXPosition.size() - 1; i >= 0; i--) {
      if (pipesXPosition[i] + 6.0f < 0.0f) 
      {
        pipesXPosition.erase(pipesXPosition.begin() + i); 
        pipesGapTop.erase(pipesGapTop.begin() + i); 
        pipesBScored.erase(pipesBScored.begin() + i); 
      }
    }

    // collision
    birdTop = (int)std::floor(birdYPosition); 
    birdBottom = birdTop + 2 - 1;          
    birdLeft = 10;                   // same every frame
    birdRight = 10 + 2 - 1;           // same every frame
    // check wall 
    if (birdTop < 0 || birdBottom >= 20)  { bDead = 1;  }

    if (!bDead)
    {
      for (int i = 0; i < (int)pipesXPosition.size(); i++)
      {
        int pl = (int)std::floor(pipesXPosition[i]);
        int pr = pl + 6 - 1;

        if (birdRight >= pl && birdLeft <= pr)
        {
          for (int y = birdTop; y <= birdBottom; y++)
          {
            if (y < pipesGapTop[i] || y >= pipesGapTop[i] + 6)
            {
              bDead = 1;
              break;
            }
          }
        }

        if (bDead != 0) break;
      }
    }

    if (bDead != 0) break;

    std::vector<std::string> frame(20, std::string(50, ' '));

    for (int i = 0; i < (int)pipesXPosition.size(); i++)
    {
      int pl = (int)std::floor(pipesXPosition[i]);
      for (int dx = 0; dx < 6; dx++)
      {
        int x = pl + dx;
        if (x < 0 || x >= 50) continue;
        for (int y = 0; y < 20; y++)
        {
          if (!(y >= pipesGapTop[i] && y < pipesGapTop[i] + 6))
          {
            frame[y][x] = 'P';
          }
        }
      }
    }

    for (int dy = 0; dy < 2; dy++)
    {
      int y = birdTop + dy;
      if (y < 0 || y >= 20) continue;
      for (int dx = 0; dx < 2; dx++)
      {
        int x = 10 + dx;
        if (x >= 0 && x < 50) frame[y][x] = 'B';
      }
    }

    std::string scoreText = "Score: " + std::to_string(currentScore) + "   Best: " + std::to_string(bestScore);
    if (scoreText.size() > 50) scoreText = scoreText.substr(0, 50);
    leftPadding = (int)((50 - (int)scoreText.size()) / 2);
    rightPadding = 50 - leftPadding - (int)scoreText.size();

    std::cout << "\x1b[2J\x1b[H";
    std::cout << "+" << std::string(50, '-') << "+" << "\n";
    for (int y = 0; y < 20; y++)
    {
      std::cout << "|";
      for (int x = 0; x < 50; x++)
      {
        char c = frame[y][x];
        if (c == 'P')
        {
          std::cout << "\x1b[32mP\x1b[0m";
        }
        else if (c == 'B')
        {
          std::cout << "\x1b[33mB\x1b[0m";
        }
        else
        {
          std::cout << ' ';
        }
      }
      std::cout << "|\n";
    }
    std::cout << "+" << std::string(50, '-') << "+" << "\n";
    std::cout << "+" << std::string(50, '-') << "+" << "\n";
    std::cout << "|" << std::string(leftPadding, ' ') << scoreText << std::string(rightPadding, ' ') << "|\n";
    std::cout << "+" << std::string(50, '-') << "+" << "\n";
    std::cout.flush();

    float ft = std::chrono::duration<float>(std::chrono::steady_clock::now() - now).count();
    if (ft < 1.0f / 30.0f)
    {
      std::this_thread::sleep_for(std::chrono::duration<float>(1.0f / 30.0f - ft));
    }
  }

  // save best score to file
  std::ofstream fout("best-score.txt", std::ios::trunc);
  if (fout) fout << bestScore; // write best score
  fout.close(); // close the file

  // restore original console mode
  SetConsoleMode(inputHandle, m);
  return 0;
}