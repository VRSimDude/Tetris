#pragma region include project
#include "Player.hpp"
#include "Playfield.hpp"
#include "UI.hpp"
#include "Game.hpp"
#pragma endregion

// destructor
Game::~Game()
{
	// clear memory
	delete(m_pUI);
	delete(m_pPlayfield);
	delete(m_pPlayer);
	delete(m_pScreen);
	DestroyWindow(m_pConsoleWindow);
	CloseHandle(m_pConsole);
}

// initialize the game
void Game::Init(int _playfieldWidth, int _playfieldHeight)
{
	// set playfield width between 9 and 32
	int playfieldWidth = _playfieldWidth < 9 ? 9 : (_playfieldWidth > 32 ? 32 : _playfieldWidth);

	// set playfield height between 11 and 64
	int playfieldHeight = _playfieldHeight < 11 ? 11 : (_playfieldHeight > 64 ? 64 : _playfieldHeight);

	// set screen width and height
	m_screenWidth = (playfieldWidth + 12);
	m_screenHeight = (playfieldHeight + 2);

	// create screen to render
	m_pScreen = new char[m_screenWidth * m_screenHeight];
	for (int i = 0; i < m_screenWidth * m_screenHeight; i++)
		m_pScreen[i] = ' ';
	
	// create console screen buffer and set to active screen
	m_pConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_pConsole);
	m_dwBytesWritten = 0;

	// get console window
	m_pConsoleWindow = GetConsoleWindow();

	// set console style to not resize able, no menu, no border and maximized box
	SetWindowLong(m_pConsoleWindow, GWL_STYLE, GetWindowLong(m_pConsoleWindow, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);

	// mode for editing console
	DWORD mode;

	// get console mode
	GetConsoleMode(m_pConsoleWindow, &mode);

	// set console mode to not editable
	mode = ~ENABLE_QUICK_EDIT_MODE;

	// set console mode
	SetConsoleMode(m_pConsoleWindow, mode);

	// create playfield, player and ui
	m_pPlayfield = new Playfield(playfieldWidth, playfieldHeight);
	m_pPlayer = new Player(m_pPlayfield);
	m_pUI = new UI();

	// set references
	m_pPlayfield->SetGame(this);
	m_pPlayfield->SetUI(m_pUI);
	m_pPlayfield->SetPlayer(m_pPlayer);
	m_pPlayer->SetGame(this);
	m_pUI->SetGame(this);
	m_pUI->SetPlayer(m_pPlayer);

	// set game running true
	m_isRunning = true;
}

// update every frame
void Game::Update()
{
	// calculate time since last frame
	m_deltaTime = static_cast<float>(m_timeLastFrame - m_timeThisFrame) / 1000.0f;

	// save time begin of frame
	m_timeThisFrame = NOW;

	// update player and playfield
	m_pPlayer->Update(m_deltaTime);
	m_pPlayfield->Update(m_deltaTime);
}

// render every frame
void Game::Render()
{
	// reset screen
	for (int i = 0; i < m_screenWidth * m_screenHeight; i++)
		m_pScreen[i] = ' ';

	// render player and playfield
	m_pPlayfield->Render(m_pScreen, m_screenWidth, m_screenHeight);
	m_pPlayer->Render(m_pScreen, m_screenWidth, m_screenHeight);

	// render ui
	m_pUI->Render(m_pScreen, m_screenWidth, m_screenHeight);

	// write screen to window
	WriteConsoleOutputCharacter(m_pConsole, m_pScreen, m_screenWidth * m_screenHeight, { 0,0 }, &m_dwBytesWritten);

	// save time end of frame
	m_timeLastFrame = NOW;
}

// reset game
void Game::Reset()
{
	// set game over false and reset player and playfield
	m_isGameOver = false;
	m_pPlayer->Reset();
	m_pPlayfield->Reset();
}
