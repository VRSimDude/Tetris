#pragma once

#pragma region include system
#include <windows.h>
#include <chrono>
#pragma endregion

#pragma region Macro
#define NOW std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count()
#pragma endregion

#pragma region forward declarations
class Player;
class Playfield;
class UI;
#pragma endregion

/// <summary>
/// main game class
/// </summary>
class Game
{
public:
	#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~Game();
	#pragma endregion

	#pragma region inline methods
	/// <summary>
	/// if game is running
	/// </summary>
	/// <returns>game is running</returns>
	inline const bool& IsRunning() { return m_isRunning; }

	/// <summary>
	/// stop game completely
	/// </summary>
	inline void StopGame() { m_isRunning = false; }

	/// <summary>
	/// if game is started
	/// </summary>
	/// <returns>game is started</returns>
	inline const bool& IsGameStarted() { return m_isGameStarted; }

	/// <summary>
	/// start game
	/// </summary>
	inline void StartGame() { m_isGameStarted = true; }

	/// <summary>
	/// if game is over
	/// </summary>
	/// <returns>game is over</returns>
	inline const bool& IsGameOver() { return m_isGameOver; }

	/// <summary>
	/// set game over
	/// </summary>
	inline void GameOver() { m_isGameOver = true; }
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// initialize the game
	/// </summary>
	/// <param name="_playfieldWidth">width of the playfield</param>
	/// <param name="_playfieldHeight">height of the playfield</param>
	void Init(int _playfieldWidth = 9, int _playfieldHeight = 11);

	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();

	/// <summary>
	/// reset game
	/// </summary>
	void Reset();
	#pragma endregion

private:
	#pragma region primitive variables
	/// <summary>
	/// if game is running
	/// </summary>
	bool m_isRunning = false;

	/// <summary>
	/// if game was started or waiting for player
	/// </summary>
	bool m_isGameStarted = false;

	/// <summary>
	/// if game is over
	/// </summary>
	bool m_isGameOver = false;

	/// <summary>
	/// screen width
	/// </summary>
	int m_screenWidth = 0;

	/// <summary>
	/// screen height
	/// </summary>
	int m_screenHeight = 0;

	/// <summary>
	/// bytes written to console
	/// </summary>
	DWORD m_dwBytesWritten = 0;

	/// <summary>
	/// time since last frame
	/// </summary>
	float m_deltaTime = 0.0f;

	/// <summary>
	/// time at begin of frame
	/// </summary>
	long long m_timeThisFrame = NOW;
	
	/// <summary>
	/// time at end of frame
	/// </summary>
	long long m_timeLastFrame = NOW;
	#pragma endregion

	#pragma region pointer
	/// <summary>
	/// screen to render
	/// </summary>
	char* m_pScreen = nullptr;

	/// <summary>
	/// console handle
	/// </summary>
	HANDLE m_pConsole = nullptr;

	/// <summary>
	/// console window
	/// </summary>
	HWND m_pConsoleWindow = nullptr;

	/// <summary>
	/// player
	/// </summary>
	Player* m_pPlayer = nullptr;

	/// <summary>
	/// playfield
	/// </summary>
	Playfield* m_pPlayfield = nullptr;

	/// <summary>
	/// ui
	/// </summary>
	UI* m_pUI = nullptr;
	#pragma endregion
};