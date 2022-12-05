#include "EntryPoint.h"
#include "Example.h"

int main(void)
{
	Example example(L"Shapes", { 600, 600 }, { 1.0f, 1.0f });
	EntryPoint entryPoint;
	entryPoint.Run(&example);
}