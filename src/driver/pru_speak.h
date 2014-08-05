#ifndef PRU_SPEAK_H_
#define PRU_SPEAK_H_

/* maximum PRUs that PRU Speak uses*/
#define MAX_PRUS	2

/* max/min shared memory segments per PRU */
#define MAX_SHARED	4
#define MIN_SHARED	2

/* index for shm of botspeak code */
#define BS_CODE		0
/* index for shm of return values */
#define BS_RET		1

/**
 * struct pru_shm - shared memory details per PRU
 * @idx: ID of the PRU this pru_shm structure represents. [PRU0 or PRU1]
 * @vaddr : virtual address of the shared memory, for access from kernel
 * @paddr : physical address of the shared memory, for access from PRU
 * @is_valid : this is = 1 if this structure represents a valid shared memory segment
 */

struct pru_shm {
	int idx;
	void __iomem *vaddr;
	void __iomem *paddr;
	int size_in_pages;
	unsigned int is_valid :1;
};

/**
 * The main PRU Speak structure that handles all reqd data
 * NOTE : reqd. data as of now is just the shm units, 
 * 	all other data is abstracted and is concern of pru_rproc
 */
struct pru_speak{
	struct pru_shm shm[MAX_SHARED];
	int shm_count;
	struct platform_device *pdev_rproc; //pointer to pdev of pp_ps in pru_rproc.c
};
extern int pruspeak_downcall_idx(int idx, u32 nr, u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
extern struct platform_device *pruspeak_get_pdev_rproc(void);
#endif