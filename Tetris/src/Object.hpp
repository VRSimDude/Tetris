#pragma once

#pragma region include project
#include "Vector2.hpp"
#pragma endregion

#pragma region forward declaration
class Game;
#pragma endregion

/// <summary>
/// base object abstract class that has a position
/// </summary>
class Object
{
public:
	#pragma region constructor
	/// <summary>
	/// basic constructor
	/// </summary>
	Object() {}

	/// <summary>
	/// constructor that set the position
	/// </summary>
	/// <param name="_pos">position</param>
	Object(Vector2 _pos)
	{
		m_pos = _pos;
	}
	#pragma endregion

	#pragma region virtual methods
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) = 0;

	/// <summary>
	/// render every frame
	/// </summary>
	/// <param name="_pScreen">screen array pointer</param>
	/// <param name="_screenWidth">screen width</param>
	/// <param name="_screenHeight">screen height</param>
	virtual void Render(char* _pScreen, int _screenWidth, int _screenHeight) = 0;
	#pragma endregion

	#pragma region inline methods
	/// <summary>
	/// get position of object
	/// </summary>
	/// <returns>position of object</returns>
	inline const Vector2& GetPos() { return m_pos; }

	/// <summary>
	/// set position of object
	/// </summary>
	/// <param name="_pos">new position of object</param>
	inline void SetPos(Vector2 _pos) { m_pos = _pos; }

	/// <summary>
	/// set game reference
	/// </summary>
	/// <param name="_pGame">game reference</param>
	inline void SetGame(Game* _pGame) { m_pGame = _pGame; }
	#pragma endregion

protected:
	#pragma region variables
	/// <summary>
	/// position of object
	/// </summary>
	Vector2 m_pos = Vector2();
	#pragma endregion

	#pragma region private pointer
	/// <summary>
	/// game reference
	/// </summary>
	Game* m_pGame = nullptr;
	#pragma endregion
};