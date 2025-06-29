#pragma once

#pragma region include system
#include <string>
#pragma endregion

#pragma region include project
#include "Object.hpp"
#pragma endregion

#pragma region forward declaration
class Playfield;
#pragma endregion

/// <summary>
/// player class that handles movement and the current block
/// </summary>
class Player : public Object
{
public:
	#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pPlayfield">playfield reference</param>
	Player(Playfield* _pPlayfield);
	#pragma endregion

	#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~Player();
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
	/// get current tetromino char array
	/// </summary>
	/// <returns>current tetromino char array</returns>
	inline const char const* GetCurrentTetromino() { return m_pCurrentTetromino; }

	/// <summary>
	/// get next tetromino char array
	/// </summary>
	/// <returns>next tetromino char array</returns>
	inline const char const* GetNextTetromino() { return m_pNextTetromino; }
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// reset player
	/// </summary>
	void Reset();

	/// <summary>
	/// increase speed
	/// </summary>
	void IncreaseSpeed();
	#pragma endregion

private:
	#pragma region primitive variables
	/// <summary>
	/// base movement speed down in blocks per second
	/// </summary>
	float m_movementSpeedDownBase = 2.5f;

	/// <summary>
	/// movement speed down in blocks per second
	/// </summary>
	float m_movementSpeedDown = m_movementSpeedDownBase;

	/// <summary>
	/// if space was pressed last frame
	/// </summary>
	bool m_isSpaceDownLastFrame = false;

	/// <summary>
	/// if space was pressed this frame
	/// </summary>
	bool m_isSpaceDownThisFrame = false;

	/// <summary>
	/// if return was pressed last frame
	/// </summary>
	bool m_isReturnDownLastFrame = false;

	/// <summary>
	/// if return was pressed this frame
	/// </summary>
	bool m_isReturnDownThisFrame = false;

	/// <summary>
	/// if arrow key was pressed last frame
	/// 0=up, 1=left, 2=down, 3=right
	/// </summary>
	bool m_isArrowDownLastFrame[4];

	/// <summary>
	/// if arrow key was pressed this frame
	/// 0=up, 1=left, 2=down, 3=right
	/// </summary>
	bool m_isArrowDownThisFrame[4];
	#pragma endregion

	#pragma region variables
	/// <summary>
	/// all tetrominos
	/// </summary>
	std::wstring m_tetrominos[7];

	/// <summary>
	/// position of player before movement
	/// </summary>
	Vector2 m_posBeforeMovement = Vector2();
	#pragma endregion

	#pragma region pointer
	/// <summary>
	/// current tetromino
	/// </summary>
	char* m_pCurrentTetromino = nullptr;

	/// <summary>
	/// next tetromino
	/// </summary>
	char* m_pNextTetromino = nullptr;

	/// <summary>
	/// rotated tetromino
	/// </summary>
	char* m_pTetrominoBeforeRotate = nullptr;

	/// <summary>
	/// play field reference
	/// </summary>
	Playfield* m_pPlayfield = nullptr;
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// rotate tetromino counter clock wise
	/// </summary>
	void RotateTetromino();

	/// <summary>
	/// reset player to top of playfield with new random tetromino and position
	/// </summary>
	void ResetToTop();
	#pragma endregion
};