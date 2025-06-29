#pragma once

#pragma region include project
#include "Object.hpp"
#pragma endregion

#pragma region const
const int WAIT_TIME_COMPLETED_ROW_MS = 500;
#pragma endregion

#pragma region forward declaration
class Player;
class UI;
#pragma endregion

/// <summary>
/// playfield class that includes all blocks except the current moved one
/// </summary>
class Playfield : public Object
{
public:
	#pragma region constructor

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_playfieldWidth">playfield width between</param>
	/// <param name="_playfieldHeight">playfield height</param>
	Playfield(int _playfieldWidth, int _playfieldHeight);
	#pragma endregion

	#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~Playfield();
	#pragma endregion

	#pragma region override methods
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;

	/// <summary>
	/// render every frame
	/// </summary>
	/// <param name="_pScreen">screen array pointer</param>
	/// <param name="_screenWidth">screen width</param>
	/// <param name="_screenHeight">screen height</param>
	virtual void Render(char* _pScreen, int _screenWidth, int _screenHeight) override;
	#pragma endregion

	#pragma region inline methods
	/// <summary>
	/// get playfield width
	/// </summary>
	/// <returns>playfield width</returns>
	inline const int& GetPlayfieldWidth() { return m_playfieldWidth; }

	/// <summary>
	/// set ui reference
	/// </summary>
	/// <param name="_pUI">ui reference</param>
	inline void SetUI(UI* _pUI) { m_pUI = _pUI; }

	/// <summary>
	/// set player reference
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	inline void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// if player is colliding with the playfield
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	/// <returns>true if player collides with playfield</returns>
	bool IsColliding(Player* _pPlayer);

	/// <summary>
	/// add players current tetromino to playfield
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	void AddTetrominoToPlayfield(Player* _pPlayer);

	/// <summary>
	/// reset playfield
	/// </summary>
	void Reset();
	#pragma endregion

private:
	#pragma region primitive variable
	/// <summary>
	/// full lines count
	/// </summary>
	int m_fullLines = 0;

	/// <summary>
	/// playfield width
	/// </summary>
	int m_playfieldWidth = 9;

	/// <summary>
	/// playfield height
	/// </summary>
	int m_playfieldHeight = 11;

	/// <summary>
	/// block count per row for full line check
	/// </summary>
	int m_blockCountPerRow = 0;

	/// <summary>
	/// player score
	/// </summary>
	int m_playerScore = 0;

	/// <summary>
	/// score player needs to increase speed
	/// </summary>
	float m_playerScoreToIncreaseSpeed = 100.0f;

	/// <summary>
	/// time it needs after a row has been completed to show effects
	/// </summary>
	float m_timeToCompleteNextRow = WAIT_TIME_COMPLETED_ROW_MS / 1000.0f;
	#pragma endregion

	#pragma region pointer
	/// <summary>
	/// playfield string array
	/// </summary>
	char* m_pPlayfield = nullptr;

	/// <summary>
	/// player reference
	/// </summary>
	Player* m_pPlayer = nullptr;

	/// <summary>
	/// ui reference
	/// </summary>
	UI* m_pUI = nullptr;
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// if any line is full from bottom to top
	/// </summary>
	void IsLineFull();

	/// <summary>
	/// remove line from playfield
	/// </summary>
	void RemoveLine();

	/// <summary>
	/// check player score to increase speed
	/// </summary>
	void CheckPlayerScoreToIncreaseSpeed();

	/// <summary>
	/// move all blocks down that have no blocks below
	/// </summary>
	void MoveBlocksDown();
	#pragma endregion
};