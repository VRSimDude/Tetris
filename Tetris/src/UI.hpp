#pragma once

#pragma region include project
#include "Object.hpp"
#pragma endregion

#pragma region forward declaration
class Player;
#pragma endregion

/// <summary>
/// ui object
/// </summary>
class UI : public Object
{
public:
	#pragma region override methods
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override {}

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
	/// set score to display
	/// </summary>
	/// <param name="_score">score to display</param>
	inline void SetScore(int _score) { m_score = _score; }

	/// <summary>
	/// set player reference
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	inline void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
	#pragma endregion

private:
	#pragma region primitive variable
	/// <summary>
	/// score to display
	/// </summary>
	int m_score = 0;
	#pragma endregion

	#pragma region pointer
	/// <summary>
	/// player reference
	/// </summary>
	Player* m_pPlayer = nullptr;
	#pragma endregion

	#pragma region methods
	/// <summary>
	/// show score on screen at line
	/// </summary>
	/// <param name="_line">line</param>
	/// <param name="_pScreen">screen reference</param>
	/// <param name="_screenWidth">screen width</param>
	void ShowScore(int _line, char* _pScreen, int _screenWidth);
	#pragma endregion
};
