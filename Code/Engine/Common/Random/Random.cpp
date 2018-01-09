#include "Random.inl"

namespace cp
{
    glm::vec2 Random::get_circle(f32 radius)
	{
		return glm::circularRand(radius);
	}

	glm::vec2 Random::get_disk(f32 radius)
	{
		return glm::diskRand(radius);
	}

	glm::vec3 Random::get_sphere(f32 radius)
	{
		return glm::sphericalRand(radius);
	}

	glm::vec3 Random::get_ball(f32 radius)
	{
		return glm::ballRand(radius);
	}

	void Random::seed()
	{
		cout << "seeding the random" << endl;

		srand(static_cast<i32>(time(0)));
	}
}