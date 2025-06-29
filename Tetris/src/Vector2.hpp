/// <summary>
/// vector 2 class with x and y values
/// </summary>
struct Vector2
{
public:
	#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	Vector2() {}
	#pragma endregion

	#pragma region primitive variables
	/// <summary>
	/// x value
	/// </summary>
	float X = 0;

	/// <summary>
	/// y value
	/// </summary>
	float Y = 0;
	#pragma endregion
};

/// <summary>
/// operator minus
/// </summary>
/// <param name="_one">first vector 2</param>
/// <param name="_two">second vector 2</param>
/// <returns>calculated vector</returns>
inline Vector2 operator-(Vector2 _one, const Vector2& _two)
{
	_one.X -= _two.X;
	_one.Y -= _two.Y;
	return _one;
}