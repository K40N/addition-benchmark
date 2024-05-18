#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const unsigned long NCHUNKS = 1e5;
const unsigned int CHUNKSIZE = 131072;

#define TIME ((float)clock())
#define INITTIMER(WHAT) float WHAT##Start,WHAT##End,WHAT##Total;
#define STARTTIMER(WHAT) WHAT##Start=TIME;
#define ENDTIMER(WHAT) WHAT##End=TIME;WHAT##Total+=(WHAT##End-WHAT##Start)
#define TIMERTOTAL(WHAT) (WHAT##Total / (CLOCKS_PER_SEC / 1e9))

int main(int argc, char** argv) {
	srand(time(NULL));
	INITTIMER(work)
	int aArr[CHUNKSIZE];
	int bArr[CHUNKSIZE];
	for (unsigned long i = 0; i < NCHUNKS; i++) {
		for (unsigned int j = 0; j < CHUNKSIZE; j++) {
			aArr[j] = rand();
			bArr[j] = rand();
		}
		printf("(~) Chunk %d... (%.1f%%)\r", i, ((float)i) / NCHUNKS * 100);
		STARTTIMER(work)
		for (unsigned int j = 0; j < CHUNKSIZE; j++) {
			volatile int sink = aArr[j] + bArr[j];
		}
		ENDTIMER(work);
	}
	float avgTimeNs = TIMERTOTAL(work) / (NCHUNKS * CHUNKSIZE);
	int opsPerSec = (int)(1e9 / avgTimeNs);
	printf("\n(!) %d additions/sec (%.1fns each).\n", opsPerSec, avgTimeNs);
	return 0;
}

