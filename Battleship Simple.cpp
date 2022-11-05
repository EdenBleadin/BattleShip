#include <iostream>
#include <random>


int aigrid[16][16] =
{ {171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
{171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171},
};
int grid[16][16] =
{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
struct number {
	int x;
	int y;
};
int count;
int ships = 0;

number coordinate = { 1, 1 };
number storedcoordinate = { 1, 1 };
void randomizer(int Grid[16][16])
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist15(0, 15);
	for (int i = 1; i <= 10; ++i)
	{
		int x = dist15(rng);
		int y = dist15(rng);

		if (Grid[x][y] == 1)
		{
			i--;
		}
		Grid[x][y] = 1;
	}
}
void print(int Grid[16][16])
{
	for (int x = 0; x <= 15; ++x)
	{
		for (int y = 0; y <= 15; ++y)
		{
			/*char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
			char aChar = digits[Grid[x][y]];
			std::cout << aChar;*/
			char aChar = '0' + Grid[x][y];
			std::cout << aChar;
		}
		printf("\n");
	}
}
int revealer(number coord)
{
	aigrid[coordinate.x][coordinate.y] = 1;
	if (grid[coord.x][coord.y] == 1)
	{
		ships++;
		return 1;
	}
	aigrid[coordinate.x][coordinate.y] = 2;
	if (coord.x - 1 >= 0)
	{
		if (grid[coord.x - 1][coord.y] == 1)
		{
			return 2;
		}
	}
	if (coord.y - 1 >= 0)
	{
		if (grid[coord.x][coord.y - 1] == 1)
		{
			return 2;
		}
	}
	if (coord.x + 1 <= 15)
	{
		if (grid[coord.x + 1][coord.y] == 1)
		{
			return 2;
		}
	}
	if (coord.y + 1 <= 15)
	{
		if (grid[coord.x][coord.y + 1] == 1)
		{
			return 2;
		}
	}
	aigrid[coordinate.x][coordinate.y] = 0;
	return 0;

}
void guesser(int Grid[16][16])
{

	while (ships < 10)
	{
		count++;
		switch (revealer(coordinate)) {
		case 0:
			aigrid[coordinate.x - 1][coordinate.y] = 0;
			aigrid[coordinate.x][coordinate.y - 1] = 0;
			aigrid[coordinate.x + 1][coordinate.y] = 0;
			aigrid[coordinate.x][coordinate.y + 1] = 0;
			break;
		
		default:
			coordinate.x--;
			revealer(coordinate);
			coordinate.x++;
			coordinate.y++;
			revealer(coordinate);
			coordinate.y--;
			coordinate.x++;
			revealer(coordinate);
			coordinate.y--;
			coordinate.x--;
			revealer(coordinate);
			coordinate.y++;

		}
		if (coordinate.y + 5 > 14)
		{
			if (storedcoordinate.y - 3 > 0)
			{
				storedcoordinate.y -= 3;
			}
			else
			{
				storedcoordinate.y += 2;
			}
			storedcoordinate.x++;
			if (storedcoordinate.x == 15)
			{
				return;
			}

			coordinate = storedcoordinate;

		}
		else
		{
			coordinate.y += 5;
		}
		print(aigrid);
		printf("\n");
	}
}
void edges(int Grid[16][16])
{
	count++;
	switch (revealer(coordinate)) {
	case 0:
		if (coordinate.x - 1 >= 0)
		{
			aigrid[coordinate.x - 1][coordinate.y] = 0;
		}
		if (coordinate.y - 1 >= 0)
		{
			aigrid[coordinate.x][coordinate.y - 1] = 0;
		}
		if (coordinate.x + 1 <= 15)
		{
			aigrid[coordinate.x + 1][coordinate.y] = 0;
		}
		if (coordinate.y + 1 <= 15)
		{
			aigrid[coordinate.x][coordinate.y + 1] = 0;
		}
		break;

	default:
		if (coordinate.x - 1 >= 0)
		{
			if (aigrid[coordinate.x-1][coordinate.y] != 171)
			{
				break;
			}
			else
			{
				coordinate.x--;
				revealer(coordinate);
				coordinate.x++;
			}	
		}
		if (coordinate.y - 1 >= 0)
		{
			if (aigrid[coordinate.x][coordinate.y-1] != 171)
			{
				break;
			}
			else
			{
				coordinate.y--;
				revealer(coordinate);
				coordinate.y++;
			}
		}
		if (coordinate.x + 1 <= 15)
		{
			if (aigrid[coordinate.x+1][coordinate.y] != 171)
			{
				break;
			}
			else
			{
				coordinate.x++;
				revealer(coordinate);
				coordinate.x--;
			}
		}
		if (coordinate.y + 1 <= 15)
		{
			if (aigrid[coordinate.x][coordinate.y+1] != 171)
			{
				break;
			}
			else
			{
				coordinate.y++;
				revealer(coordinate);
				coordinate.y--;
			}
		}

	}
	print(aigrid);
	printf("\n");
}

void outeredges(int Grid[16][16])
{
	coordinate.x = 0;
	coordinate.y = 0;
	revealer(coordinate);
	if (ships < 10)
	{
		coordinate.x += 3;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 2;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y = 15;
		coordinate.x = 0;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 3;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 2;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y = 4;
		coordinate.x = 0;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x = 15;
		coordinate.y = 4;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y = 2;
		coordinate.x = 0;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y = 0;
		coordinate.x = 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y = 15;
		coordinate.x = 6;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x += 5;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.x = 15;
		coordinate.y = 6;
		edges(grid);
	}
	if (ships < 10)
	{
		coordinate.y += 5;
		edges(grid);
		return;
	}
}
int main()
{
	int total=0;
	int ccount = 0;
	float avg;
	while (ccount < 100)
	{
		for (int x = 0; x <= 15; ++x)
		{
			for (int y = 0; y <= 15; ++y)
			{
				grid[x][y] = 0;
			}
		}
		for (int x = 0; x <= 15; ++x)
		{
			for (int y = 0; y <= 15; ++y)
			{
				aigrid[x][y] = 171;
			}
		}
		randomizer(grid);
		guesser(grid);
		outeredges(grid);
		total += count;
		count = 0;
		ships = 0;
		coordinate.x = 1;
		coordinate.y = 1;
		storedcoordinate.x = 1;
		storedcoordinate.y = 1;
		ccount++;
	}
	float Total = total;
	printf("The average amount of moves is ");
	std::cout << Total/100;
	
}