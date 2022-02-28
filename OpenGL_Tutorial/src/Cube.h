#pragma once

const int VERTICES_AMOUNT = 24;
const int INDICIES_AMOUNT = 48;

struct Cube
{
	float positions[VERTICES_AMOUNT] =
	{
		-0.5f, -0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};

	unsigned int indicies[INDICIES_AMOUNT] =
	{
		//Front side
		0,1, 1,2, 2,3, 3,0,
		//Back side
		4,5, 5,6, 6,7, 7,4,
		//Top side
		3,2, 2,6, 6,7, 7,3,
		//Bottom side
		0,1, 1,5, 5,4, 4,0,
		//Right side
		1,5, 5,6, 6,2, 2,1,
		//Left side
		0,4, 4,7, 7,3, 3,0
	};
};