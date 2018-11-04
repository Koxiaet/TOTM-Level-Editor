class LCG
{
private:
	unsigned long next = 1;
public:
	LCG(unsigned long seed) : next(seed) {}

	const unsigned long rand_max = 32767;

	int rand()
	{
		next = next * 1103515245 + 12345;
		return (unsigned int)(next/65536) % 32768;
	}

	void reseed(unsigned long seed)
	{
		next = seed;
	}

	unsigned long getseed()
	{
		return next;
	}
};

#ifndef RAND_NO_DEFINE
extern LCG r;
#endif