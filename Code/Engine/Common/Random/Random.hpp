#pragma once

#include "Util.hpp"

namespace cp
{
    class Random
    {
    public:
        template <class T> static T get_linear(T min, T max);
		template <class T> static T get_gauss(T min, T max);

		static vec2 get_circle(f32 radius);
		static vec2 get_disk(f32 radius);

		static vec3 get_sphere(f32 radius);
		static vec3 get_ball(f32 radius);

		static void seed();

	private:
		Random() = delete;
        Random(const Random &) = delete;

        Random &operator=(const Random &) = delete;
    };
}