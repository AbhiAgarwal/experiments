/*
 * -----------------------------------------
 * | BSA - Bad segregated (fits) allocator |
 * -----------------------------------------
 *
 * Informazioni:
 * 
* Created by Emilio Cup <ercoppa@gmail.com> for the thesis of the course 
 * Engineering Algorithms held by the lecturer Camil Demetrescu 
 * At the University 'La Sapienza University of Rome faculty' of Engineering 
 * Data from 2009 to 2010. 
 * 
 * Introduction: 
 * 
 * BSA and 'a segregated fits allocator of the family, it has 
 * Head in a heap lookup table with pointers to lists 
 * Free blocks. 
 * 
 * The lookup table 'consists of two "levels": 
 * 
 * - The first level 'consists of lists that contain blocks 
 * Of exact size according to their index (example: list 
 * I-th will contain 'blocks (FIXED_SIZE * i) bytes). The first list 
 * Necessarily will contain 'block size MIN_BLOCK_SIZE, to 
 * Not the last list for this level will contain 'blocks 
 * Size equal to MAX_FIXED. Among a list and the other, the blocks 
 * Will have a difference in size of FIXED_BLOCK_SIZE. 
 * 
 * - The second level and 'consists of lists that contain blocks 
 * A size between (EXP_BASE ^ (i-1)) +1 and EXP_BASE ^ i, where i 
 * And 'the index on the list. The minimum index for the listings of 
 * Second level and 'calculated from the last index lists 
 * First level (plus one) or, if the latter does not 
 * Are present, based on MIN_BLOCK_SIZE. The maximum index and ' 
 * Equal to MAX_EXP. Each block is larger than any 
 * List 'attached to the last. 
 * 
 * Date a dimension (of an allocation request), the choice 
 * Block within a list and 'carried out with the following policies: 
 * 
 * - FirstFit: is chosen met the first block in the list, 
 * As long 'sufficiently large 
 * - BESTFIT: the block is chosen in the list more 'small (but 
 * Large enough to meet the demand) 
 * 
 * Such behavior and 'determined by the macro POLICY. With 
 * Either mode 'and' can indicate to choose, in the event 
 * Free blocks of equal size, one to address 
 * Less memory. Such behavior is' set defining the 
 * Macro ADDRESS_ORDER. 
 * 
 * Each block has returned an address multiple of ALIGNMENT. 
 * 
 * Each block at any time can 'be in two states: 
 * - In use (then out of any list) 
 * - Free (added to a list) 
 * And has a header containing the following dimension header_size 
 * Information: 
 * - The block size 
 * - Relative flag to his state 
 * - Flag relative to the state of the previous block 
 * The last two flags are stored thanks to the technique of 
 * Bit stealing in the size of the block, that being a multiple of 
 * ALIGNMENT, and the latter being at least equal to 8, allows 
 * To exploit up to 3 bits. 
 * 
 * Each free block contains in its payload the following information: 
 * - Head to the block a pointer to the next free block 
 * List of belonging (possibly NULL if empty) 
 * - A pointer to the block in the queue at his head 
 * 
 * BSA adopts the following strategy: 
 * 
 * - A block, when requested with malloc (), is searched 
 * In the appropriate list. If the latter does not allow the selection 
 * A block, then the search continues in the subsequent lists. If 
 * No list has a block sufficient for the request 
 * Then expands the heap (in number of 'equal to the size of 
 * Page and if 'the macro defined PAGE_ALLOCATION or just for the 
 * Size request) 
 * 
 * - A block, when freed with free (), is merged with any 
 * Free blocks (previous and / or next) and inserted 
 * In the appropriate list 
 * 
 * - A block, of which 'was required downsize by 
 * Realloc (), is: 
 * 
 * - Released if the new size and 'zero 
 * 
 * - Do not change if the new size and 'less than the 
 * Original size 
 * 
 * - Expanded (if 'the last block in the heap) size equal 
 * The difference between the new and the original size or 
 * Of a quantity 'multiple of the page size and if' 
 * PAGE_ALLOCATION defined the macro. In the second case, the amount ' 
 * Space in excess is removed to form a new block 
 * Free. 
 * 
 * - Merged with the next block 
 * 
 * - Freed but 'request advance copy byte by byte 
 * Of its content in a new block allocated with malloc () 
 * 
 * / 

/ * 
 * BSA has been changed and now the can 'be enhanced (BSA + +) 
 * Using pre-acquired information on the patterns of allocation 
 * An application. 
 * 
 * For more info visit http://www.ercoppa.org/malloc 
 * / 

/* Standard header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define DISABLE_SPLIT_COALESCE
//#define DISABLE_ALTERNATE_SPLIT_SIDE
//#define PLUS_PLUS

#ifdef MALLOCLAB

#define malloc   mm_malloc
#define free	 mm_free
#define realloc  mm_realloc
#define calloc   mm_calloc
#define end_heap ((void *)(mem_heap_hi()+1))
#define sbrk	 mem_sbrk

/* Defined header */
#include "mm.h"
#include "memlib.h"
#ifdef PLUS_PLUS
#include "alloc-stats.h"
#define MOST_USED_SIZE_CLASS_NUMBER 0
#endif

/*
 * Struttura dati contenente informazioni sugli autori del codice,
 * usata da mallaclab.
 */
team_t team = {
	/* Team name */
	"ercoppa",
	/* First member's full name */
	"Emilio Coppa",
	/* First member's email address */
	"ercoppa@gmail.com",
	/* Second member's full name (leave blank if none) */
	"",
	/* Second member's email address (leave blank if none) */
	""
};

#else

static unsigned int do_init = 0;
#define end_heap sbrk(0)

#endif

static const char LogTable256[256] = 
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
	-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
	LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

/*
 * Definire queste macro per avere alcune print() di supporto
 * in fase di debugging. E' necessario definire almeno DEBUG in caso
 * di definizione di un'altra macro di debugging.
 */
/*
#define DEBUG
#define DEBUG_INIT
#define DEBUG_MALLOC
#define DEBUG_FREE
#define DEBUG_REALLOC
#define DEBUG_COALESCE
#define DEBUG_GET_INTEX
#define DEBUG_IN_LIST
#define DEBUG_OUT_LIST
#define DEBUG_SPLIT
*/
/* Allineamento */
#define ALIGNMENT 8
/*
 * Soglia da cui in poi dentro la realloc() se il nuovo blocco Ã¨
 * piccolo del vecchio avviene il troncamente dell'eccesso
 */
#define REALLOC_SPLIT_THRESHOLD 32
/*
 * Differenza in dimensione blocchi primo livello
 * fra una lista e la successiva
 */
#define FIXED_BLOCK_SIZE 8
/*
 * Dimensione minima di un blocco: un blocco deve poter contenere
 * almeno i due puntatori necessari per lo stato di blocco libero.
 */
#define MIN_BLOCK_SIZE (2 * sizeof(void *))
/* Dimensione massima blocchi primo livello */
#define MAX_FIXED 512
/*
 * Base per blocchi secondo livello
 * Nota: al momento non e' supportata alcuna base diversa da 2 in quanto
 *	   poco efficiente nel calcolo delle potenza
 */
#define EXP_BASE 2
/* Massimo esponente per blocchi secondo livello */
#ifdef __i386__
#define MAX_EXP 25
#else
#define MAX_EXP 25
#endif
/*
 * Dimensione dell' header per ogni blocco: essa deve essere pari a
 * sizeof(size_t) e sempre multipla di ALIGNMENT
 */
#define HEADER_SIZE 8
/*
 * Se e' definita PAGE_ALLOCATION, l'heap crescera' a multipli
 * della dimensione di pagina
 */
//#define HEAP_GROWSIZE mem_pagesize()
#define HEAP_GROWSIZE 4096
/* Politica di gestione delle liste */
#define FIRSTFIT 1
#define BESTFIT  2
#define POLICY FIRSTFIT

/*
 * L'operazione di coalesce(void * ptr, int mode) ha due modalita'
 * (specificata con il secondo parametro):
 * - NORMAL: fusione con il blocco precedente e successivo
 * - FORWARD: fusione con il blocco successivo
 * - BACKWARD: fusion con il blocco precedente
 */
#define NORMAL   1
#define FORWARD  2
#define BACKWARD 3

/*
 * L'operazione di split di un blocco puo' invocare o meno, l'eventuale
 * coalescing sul blocco creato. Il terzo parametro mode e':
 * - NO_COALESCE: no fusione
 * - COALESCE: fusione
 */
#define NO_COALESCE 1
#define COALESCE	2
/*
 * L'allocazione puo' avvenire a blocchi di pagina o in base alla reale
 * necessita'.
 */
//#define PAGE_ALLOCATION
/*
 * L'inserimento nelle liste puo' avvennire in address order
 */
//#define ADDRESS_ORDER

/*
 * Alcune macro di servizio
 */

/* Dimensione payload di un blocco */
#define PAYLOAD_SIZE(ptr) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & ~3)
/*
 * Imposta la dimensione di payload per un blocco (non alterando il
 * flag di stato per il blocco precedente)
 */
#define SET_PAYLOAD_SIZE(ptr, size) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE))) = ((size) | (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & 3));
/*
 * Imposta la dimensione di payload per un blocco (alterando il
 * flag di stato per il blocco precedente)
 */
#define INIT_SIZE(ptr, size) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE))) = size;
/* Gestione errore fatale */
#define FATAL_ERROR(message) { \
								fprintf(stderr, "%s\n", message); \
								exit(EXIT_FAILURE); \
							}
/* Puntatore al successivo blocco libero della lista di appartenenza*/
#define NEXT_FREE(ptr) *((char **)ptr)
/* Puntatore al successivo blocco */
#define NEXT(ptr) (((char *) ptr)+PAYLOAD_SIZE(ptr)+HEADER_SIZE)
/* Puntatore al precedente blocco */
#define PREV(ptr) *((char **)((char *)ptr - HEADER_SIZE - sizeof(void *)))
/* Imposta in coda al blocco (libero) il puntatore alla sua testa */
#define SET_END_POINTER(ptr) *((char **)((char *)ptr + PAYLOAD_SIZE(ptr) - sizeof(void *))) = ptr;
/*
 * Interpretazione valore per le successive tre macro:
 * - 1 => si
 * - 0 => no
 */
/* Blocco libero */
#define IS_FREE(ptr) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & 1)
/* Primo blocco nell'heap */
#define IS_FIRST_BLOCK(ptr) (((ptr) - HEADER_SIZE) == start_heap + heap_allocator_size)
/* Blocco precedente libero */
#define IS_PREV_FREE(ptr) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & 2)
/* Flag di stato per il blocco e quello precedente */
#define GET_FLAG(ptr) (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & 3)
/* Marca un blocco come libero:
 * - setta il flag di blocco libero
 * - inserisce alla fine del blocco un puntatore alla sua testa
 * - segnala al blocco successivo di essere libero
*/
#define MARK_AS_FREE(ptr) { \
							(*((size_t *)(((char *)(ptr)) - HEADER_SIZE))) = (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) | 1); \
							SET_END_POINTER(ptr); \
							ANNOUNCE_FREE_TO_NEXT(ptr); \
							}
/* Segnala al blocco successivo che e' un blocco libero */						  
#define ANNOUNCE_FREE_TO_NEXT(ptr) { \
									if ((void *)NEXT(ptr) < end_heap) \
										*((size_t *)(((char *)(NEXT(ptr))) - HEADER_SIZE)) = (*((size_t *)(((char *)(NEXT(ptr))) - HEADER_SIZE)) | 2); \
									}
/* Segnala al blocco successivo che e' un blocco in uso */
#define ANNOUNCE_USE_TO_NEXT(ptr) { \
									if ((void *)NEXT(ptr) < end_heap) \
										*((size_t *)(((char *)(NEXT(ptr))) - HEADER_SIZE)) = (*((size_t *)(((char *)(NEXT(ptr))) - HEADER_SIZE)) & ~2); \
									}
/* Marco un blocco come in uso:
 * - imposta il flag di blocco in uso
 * - annuncio al blocco successivo di essere in uso
 */
#define MARK_AS_USED(ptr) { \
							(*((size_t *)(((char *)(ptr)) - HEADER_SIZE))) = (*((size_t *)(((char *)(ptr)) - HEADER_SIZE)) & ~1); \
							ANNOUNCE_USE_TO_NEXT(ptr); \
							}
/* Arrotonda la dimensione ad un multiplo di ALIGNMENT */
#define ROUND(size) { \
						if (size < MIN_BLOCK_SIZE) size = MIN_BLOCK_SIZE; \
						else size = ((size + ALIGNMENT-1) & -ALIGNMENT); \
					}
					
/* Inizio heap */
static void * start_heap = 0;
/* Dimensione strutture BSA */
static unsigned int heap_allocator_size = 0;
/* Minino esponente utilizzato */
static unsigned int min_exp;
/* Puntatore all'ultimo blocco in heap */
static void * last_block;
/* Indice massimo liste */
//unsigned int max_index = 0;
/*
 * Dato un blocco e una dimensione, in caso di split divido verso
 * destra o sinistra?
 */
char split_side = 0;
#ifdef DEBUG
/* Funzione di debug dell'heap */
static void debug_heap();
/* Debug */
static unsigned int op = 0;
static unsigned int block_in_list = 0;
static unsigned int heap_asize = 0;
static unsigned int block_allocated = 0;
#endif

/*
 * Funzione privata che data una dimensione di blocco, ritorna
 * l'indice (spiazzamento dall'inizio di heap) della lista di
 * appartenenza.
 */
static inline unsigned int get_index(size_t size, unsigned int popular_index) {

	/* Arrotondiamo la dimensione */
	//ROUND(size);

	#ifdef DEBUG_GET_INTEX
	printf("Arrontondato a %u\n", size);
	#endif

	#ifdef POPULAR_SIZE_CLASS_NUMBER
	if (popular_index) {
		unsigned int j;
		for(j = 0; j < POPULAR_SIZE_CLASS_NUMBER; j++)
			if (popular_size_class[j] == size) 
				return j;
	}
	#endif
	/*
	#ifdef MOST_USED_SIZE_CLASS_NUMBER
	if (popular_index) {
		unsigned int j;
		for(j = 0; j < MOST_USED_SIZE_CLASS_NUMBER; j++)
			if (most_used_size_class[j] == size) 
				return POPULAR_SIZE_CLASS_NUMBER + j;
	}
	#endif 
	*/

	if (size <= MAX_FIXED) {

		#ifdef DEBUG_GET_INTEX
		printf("%u - %u - %u\n", ((size - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE), MIN_BLOCK_SIZE, FIXED_BLOCK_SIZE);
		#endif
		
		#ifdef POPULAR_SIZE_CLASS_NUMBER
		return ((size - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE) + (POPULAR_SIZE_CLASS_NUMBER + MOST_USED_SIZE_CLASS_NUMBER);
		#else
		return ((size - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE);
		#endif

	}

	#if 0
	unsigned int v = size;  // 32-bit value to find the log2 of 
	const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
	const unsigned int S[] = {1, 2, 4, 8, 16};
	int i;
	register unsigned int exp = 0; // result of log2(v) will go here
	for (i = 4; i >= 0; i--) // unroll for speed...
	{
	  if (v & b[i])
	  {
		v >>= S[i];
		exp |= S[i];
	  } 
	}
	if (exp < min_exp) exp = min_exp;
	else if (exp > MAX_EXP) exp = MAX_EXP;

	#elif 1

	unsigned int v = size; // 32-bit word to find the log of
	unsigned int exp;	 // r will be lg(v)
	register unsigned int t, tt; // temporaries

	if ((tt = v >> 16)) {
	  exp = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
	} else {
	  exp = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
	}
	if (exp < min_exp) exp = min_exp;
	else if (exp > MAX_EXP) exp = MAX_EXP;

	#else
	
	unsigned int exp;
	for(exp = min_exp; exp < MAX_EXP; exp++) {
		
		unsigned int num;
		num = 2 << exp;
		if (num >= size) break;

	}
	
	#endif

	if (MAX_FIXED != 0 && FIXED_BLOCK_SIZE != 0) {
		#ifdef POPULAR_SIZE_CLASS_NUMBER
		return ((MAX_FIXED - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE) + 1 + exp - min_exp + (POPULAR_SIZE_CLASS_NUMBER + MOST_USED_SIZE_CLASS_NUMBER);
		#else
		return ((MAX_FIXED - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE) + 1 + exp - min_exp;
		#endif
	} else {
		#ifdef POPULAR_SIZE_CLASS_NUMBER
		return exp - min_exp + (POPULAR_SIZE_CLASS_NUMBER + MOST_USED_SIZE_CLASS_NUMBER);
		#else
		return exp - min_exp;
		#endif
	}
}

/*
 * Funzione privata che rimuove un blocco libero dalla sua lista
 */
static inline void out_list(void * ptr) {

	#ifdef DEBUG
	block_in_list--;
	#endif
	
	unsigned int index = get_index(PAYLOAD_SIZE(ptr), 1);

	#ifdef DEBUG_OUT_LIST
	printf("Metto fuori lista %u un blocco da %u ad %u\n", index, PAYLOAD_SIZE(ptr), (unsigned int) ptr);
	#endif
	
	void * heap_start = start_heap;
	void * prev = NULL;
	while(1) {

		#ifdef DEBUG_OUT_LIST
		printf("Scorro lista...\n");
		#endif

		if (prev == NULL) {

			if (NEXT_FREE(heap_start + index) == ptr) {

				#ifdef DEBUG_OUT_LIST
				printf("Blocco in testa alla lista\n");
				//if (NEXT_FREE(ptr) != NULL)
				//	printf("Successivo blocco a %u da %u\n", (unsigned int) NEXT_FREE(ptr), PAYLOAD_SIZE(NEXT_FREE(ptr)));
				#endif

				NEXT_FREE(heap_start + index) = NEXT_FREE(ptr);
				break;

			} else {

				prev = NEXT_FREE(heap_start + index);

			}

		} else {

			if (NEXT_FREE(prev) == ptr) {

				NEXT_FREE(prev) = NEXT_FREE(ptr);
				break;

			} else {
				
				prev = NEXT_FREE(prev);

			}
			
		}

		#ifdef DEBUG
		if(prev == NULL) {

			FATAL_ERROR("Un blocco dichiarato libero non e' stato trovato nella sua lista!");			
			break;

		}
		#endif
		
	}

	return;

}

/*
 * Funzione privata che dato un puntatore ad un blocco lo inserisce
 * nella lista appropriata.
 */
static inline void in_list(void * ptr) {

	#ifdef DEBUG
	block_in_list++;
	#endif
	
	size_t size = PAYLOAD_SIZE(ptr);
	char ** addr_heap = start_heap;
	NEXT_FREE(ptr) = NULL;

	#ifdef POPULAR_SIZE_CLASS_NUMBER
	unsigned int j;
	for(j = 0; j < POPULAR_SIZE_CLASS_NUMBER; j++) {
		if (popular_size_class[j] == size) {
			INIT_SIZE(ptr, size);
			ANNOUNCE_USE_TO_NEXT(ptr);
			NEXT_FREE(ptr) = addr_heap[j];
			addr_heap[j] = ptr;
			return;
		}
	} 
	#endif
	/*
	#ifdef MOST_USED_SIZE_CLASS_NUMBER
	for(j = 0; j < MOST_USED_SIZE_CLASS_NUMBER; j++) {
		if (most_used_size_class[j] == size) {
			NEXT_FREE(ptr) = addr_heap[POPULAR_SIZE_CLASS_NUMBER + j];
			addr_heap[POPULAR_SIZE_CLASS_NUMBER + j] = ptr;
			return;
		}
	}
	#endif
	*/

	unsigned int index = get_index(size, 0);
	
	#ifdef DEBUG_IN_LIST
	printf("Inserisco in lista %u il blocco %u di dimensione %u\n", index, (unsigned int) ptr, size);
	#endif

	if (size <= MAX_FIXED) {

		#ifndef ADDRESS_ORDER
		NEXT_FREE(ptr) = NEXT_FREE(addr_heap + index);
		NEXT_FREE(addr_heap + index) = ptr;
		#else
		NEXT_FREE(ptr) = NEXT_FREE(addr_heap + index);
		void * prev = NULL;
		while(NEXT_FREE(ptr) != NULL) {

			if (ptr < (void *)NEXT_FREE(ptr)) break;
			else {

				prev = NEXT_FREE(ptr);
				NEXT_FREE(ptr) = NEXT_FREE(NEXT_FREE(ptr));

			}

		}
		if (prev == NULL)
			NEXT_FREE(addr_heap + index) = ptr;
		else
			NEXT_FREE(prev) = ptr;
		#endif

	} else {

		#if POLICY == FIRSTFIT

		#ifndef ADDRESS_ORDER
		NEXT_FREE(ptr) = NEXT_FREE(addr_heap + index);
		NEXT_FREE(addr_heap + index) = ptr;
		#else
		NEXT_FREE(ptr) = NEXT_FREE(addr_heap + index);
		void * prev = NULL;
		while(NEXT_FREE(ptr) != NULL) {

			if (ptr < (void *)NEXT_FREE(ptr)) break;
			else {

				prev = NEXT_FREE(ptr);
				NEXT_FREE(ptr) = NEXT_FREE(NEXT_FREE(ptr));

			}

		}
		if (prev == NULL)
			NEXT_FREE(addr_heap + index) = ptr;
		else
			NEXT_FREE(prev) = ptr;
		#endif
		
		#endif
		
		#if POLICY == BESTFIT
		NEXT_FREE(ptr) = NEXT_FREE(addr_heap + index);
		void * prev = NULL;
		while(NEXT_FREE(ptr) != NULL) {

			#ifndef ADDRESS_ORDER
			if (PAYLOAD_SIZE(NEXT_FREE(ptr)) >= size) break;
			#else
			if (PAYLOAD_SIZE(NEXT_FREE(ptr)) > size) break;
			else if (PAYLOAD_SIZE(NEXT_FREE(ptr)) == size && ptr < (void *)NEXT_FREE(ptr)) break;
			#endif
			else {

				prev = NEXT_FREE(ptr);
				NEXT_FREE(ptr) = NEXT_FREE(NEXT_FREE(ptr));

			}

		}
		if (prev == NULL)
			NEXT_FREE(addr_heap + index) = ptr;
		else
			NEXT_FREE(prev) = ptr;
		#endif
		
	}

	#ifdef DEBUG_IN_LIST
	//debug_heap();
	#endif

	/*
	if (ptr != last_block && IS_FREE(NEXT(ptr))) {
		printf("Blocco successivo libero ma non fuso!\n");
		exit(EXIT_FAILURE);
	}
	*/
		

	return;

}

/*
 * Funzione privata che fonde, se liberi, il blocco successivo e/o
 * quello precedente al blocco passato. La modalita' di fusione
 * e' definita in base alle macro NORMAL, FORWARD, BACKWARD che
 * rispettivamente fondono il blocco, se possibile, con:
 * - blocco successivo e/o precedente
 * - blocco successivo
 * - blocco precedente
 * Viene restituito il puntatore alla nuova testa del blocco (con
 * dimensione  e stato correttamente impostato).
 */
static inline void * coalesce(void * ptr, int mode) {

	if(ptr == NULL) return NULL;

	#ifdef DEBUG_COALESCE
	printf("Invocato coalescing...\n");
	if (mode == NORMAL)
		printf("Modalita' NORMAL\n");
	else if (mode == FORWARD)
		printf("Modalita' FORWARD\n");
	#endif

	/* La fine dell'heap */
	void * end = end_heap;

	#ifdef DEBUG_COALESCE
	printf("Inizio a leggere da %u\n", (unsigned int) ptr);
	#endif

	/* Fusione in avanti */
	if (mode == NORMAL || mode == FORWARD) {
		
		/* Cerco di fondere il blocco con il blocco successivo */
		void * next = NEXT(ptr);

		#ifdef DEBUG_COALESCE
		//printf("Localizzato il blocco successivo a %u del blocco %u di %u\n", (unsigned int) next, (unsigned int) ptr, PAYLOAD_SIZE(ptr));
		#endif
		
		if (next < end && IS_FREE(next)) {

			#ifdef DEBUG_COALESCE
			printf("Il blocco successivo locato a %u di %u e' libero\n", (unsigned int) next, PAYLOAD_SIZE(next));
			#endif

			/* Rimuovo il blocco dalla lista di appartenenza */
			out_list(next);
			/* Aggiorno la dimensione del blocco fuso */
			SET_PAYLOAD_SIZE(ptr, PAYLOAD_SIZE(ptr) + HEADER_SIZE + PAYLOAD_SIZE(next));
			if (IS_FREE(ptr)) {
				SET_END_POINTER(ptr);
				ANNOUNCE_FREE_TO_NEXT(ptr);
			} else {
				ANNOUNCE_USE_TO_NEXT(ptr);
			}

			if (last_block == next)
				last_block = ptr;

		}

		#ifdef DEBUG_COALESCE
		printf("Fine tentativo fusione in avanti\n");
		#endif

	}

	/* Fusione all'indietro */
	if ((mode == NORMAL || mode == BACKWARD) && !(IS_FIRST_BLOCK(ptr)) && IS_PREV_FREE(ptr)) {

		#ifdef DEBUG_COALESCE
		//debug_heap();
		printf("Avvio tentativo fusione in indietro...\n");
		#endif

		/* Cerco di fondere il blocco con il blocco precedente */
		void * prev = PREV(ptr);

		#ifdef DEBUG_COALESCE
		printf("Il blocco precedente locato a %u di %u e' libero\n", (unsigned int) prev, PAYLOAD_SIZE(prev));
		#endif

		/* Rimuovo il blocco dalla lista di appartenenza */
		out_list(prev);
		/* Aggiorno la dimensione del blocco fuso */
		SET_PAYLOAD_SIZE(prev, PAYLOAD_SIZE(ptr) + HEADER_SIZE + PAYLOAD_SIZE(prev));

		if (IS_FREE(ptr)) {
			SET_END_POINTER(prev);
			ANNOUNCE_FREE_TO_NEXT(prev);
		} else {
			ANNOUNCE_USE_TO_NEXT(prev);
		}

		if (last_block == ptr)
			last_block = prev;

		/* Il mio blocco ha cambiato "testa" */
		ptr = prev;
		
	}

	#ifdef DEBUG_COALESCE
	printf("Fine coalescing.\n");
	#endif

	return ptr;

}

/*
 * Funzione privata che "stacca" l'eventuale spazio residuo non
 * necessario per la richiesta di allocazione. La dimensione
 * effettivamente richiesta e' indicata con need_size e ptr e'
 * il puntatore al blocco da cui rimuovere il residuo.
 * 
 * La creazione del blocco residuo e' derivata rimuovendo la "parte" in
 * eccesso da:
 * - lato sinistro del blocco se split_side = 1
 * - lato destro del blocco se split_side = 0;
 *
 * L'operazione di split puo' invocare o meno sul nuovo blocco creato un
 * tentativo di fusione a secondo del parametro mode. Tale parametro
 * puo' assumere i valori (macro):
 * - NO_COALESCE: nessun tentativo di fusione
 * - COALESCE: tentativo di fusione
 *
 * Viene restituito il puntatore alla testa del blocco non residuo. Il
 * blocco residuo e' impostato nello stato libero ed inserito
 * nell'opportuna lista.
 */
static inline void * split(void * ptr, size_t need_size, int mode) {

	#ifdef DEBUG_SPLIT
	printf("Invocato split su %u di %u ma necessari %u\n", (unsigned int) ptr, PAYLOAD_SIZE(ptr), need_size);
	if (mode == NO_COALESCE)
		printf("Modalita' NO_COALESCE\n");
	else if (mode == COALESCE)
		printf("Modalita' COALESCE\n");
	#endif

	if(PAYLOAD_SIZE(ptr) > need_size + HEADER_SIZE + MIN_BLOCK_SIZE) {

		/* Il residuo viene "staccato" a destra del blocco */
		if(!split_side) {

			/* Calcolo la testa del blocco */
			void * block = ptr + need_size + HEADER_SIZE;
			/* Imposto le nuovi dimensioni */
			INIT_SIZE(block, PAYLOAD_SIZE(ptr) - need_size - HEADER_SIZE);
			SET_PAYLOAD_SIZE(ptr, need_size);
			
			if (ptr == last_block && IS_FREE(ptr))
				ANNOUNCE_FREE_TO_NEXT(ptr);
			/* Marco il blocco creato come libero */
			MARK_AS_FREE(block);
			#ifndef DISABLE_SPLIT_COALESCE
			/* Il blocco potrebbe avere un blocco successivo libero */
			if (mode == COALESCE)
				block = coalesce(block, FORWARD);
			#endif
			/* Inserisco il blocco creato nella lista opportuna */
			in_list(block);
			if(block > last_block)
				last_block = block;

			#ifndef DISABLE_ALTERNATE_SPLIT_SIDE
			split_side = !split_side;
			#endif

			return ptr;

		} else {

			/* Calcolo la testa del blocco */
			void * block = ptr + PAYLOAD_SIZE(ptr) - need_size;
			/* Imposto le nuove dimensioni */
			INIT_SIZE(block, need_size);
			SET_PAYLOAD_SIZE(ptr, PAYLOAD_SIZE(ptr) - need_size - HEADER_SIZE);
			/* Marco il blocco residuo come libero */
			MARK_AS_FREE(ptr);
			#ifndef DISABLE_SPLIT_COALESCE
			/* Il blocco potrebbe avere un blocco precedente libero */
			if (mode == COALESCE)
				ptr = coalesce(ptr, BACKWARD);
			#endif
			/* Inserisco il blocco creato nella lista opportuna */
			in_list(ptr);
			if(block > last_block)
				last_block = block;

			#ifndef DISABLE_ALTERNATE_SPLIT_SIDE
			split_side = !split_side;
			#endif
			
			return block;

		}

	}
	#ifdef DEBUG_SPLIT
	else printf("Non e' possibile splittare lo spazio in eccesso\n");
	#endif

	return ptr;

}

/* 
 * Inizializzatore dell'allocatore, in caso di errore viene
 * restituito -1.
 */
int mm_init(void) {

	#ifdef DEBUG
	block_in_list = 0;
	block_allocated = 0;
	#endif

	split_side = 0;

	#ifdef DEBUG
	/* Alcuni controlli preliminari */
	if (   (HEADER_SIZE % ALIGNMENT != 0)
		|| (MIN_BLOCK_SIZE % ALIGNMENT != 0)
		|| (FIXED_BLOCK_SIZE % ALIGNMENT != 0)
		|| (MAX_FIXED % FIXED_BLOCK_SIZE) != 0) {
		
		#ifdef DEBUG
		FATAL_ERROR("HEADER_SIZE e/o MIN_BLOCK_SIZE e/o FIXED_BLOCK_SIZE e/o MAX_FIXED dimensionati in modo scorretto.");
		#endif

		return -1;
		
	}
	#endif

	#ifdef MALLOCLAB
	start_heap = mem_heap_lo();
	#else
	start_heap = end_heap;
	#endif

	/*
	 * Calcoliamo la dimensione del heap necessaria per l'allocatore:
	 * - spazio per l'array di puntatori alle liste di primo livello, a
	 *   spiazzamento lineare
	 * - spazio per l'array di puntatori alle liste di secondo livello
	 *   a spiazzamento esponenziale
	 */
	#ifdef POPULAR_SIZE_CLASS_NUMBER
	#ifdef MOST_USED_SIZE_CLASS_NUMBER
	size_t heap_init_size = (MOST_USED_SIZE_CLASS_NUMBER + POPULAR_SIZE_CLASS_NUMBER) * sizeof(void *);
	#else
	size_t heap_init_size = (POPULAR_SIZE_CLASS_NUMBER) * sizeof(void *);
	#endif
	#else
	size_t heap_init_size = 0;
	#endif

	if (MAX_FIXED != 0 && FIXED_BLOCK_SIZE != 0)
		heap_init_size += (((MAX_FIXED - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE) +1) * sizeof(void *);

	#ifdef DEBUG_INIT
	printf("MAX_FIXED: %u - MIN_BLOCK_SIZE: %u - FIXED_BLOCK_SIZE: %u\n", MAX_FIXED, MIN_BLOCK_SIZE, FIXED_BLOCK_SIZE);
	printf("Indici per liste esatte: %u\n", ((MAX_FIXED - MIN_BLOCK_SIZE) / FIXED_BLOCK_SIZE) +1);
	#endif

	/* Esponente minimo per lista blocchi esponenziali? */
	for(min_exp = 0; min_exp < MAX_EXP+1; min_exp++) {

		unsigned int num;
		num = EXP_BASE << min_exp;
		
		if (num >= MIN_BLOCK_SIZE && num > MAX_FIXED) break;

	}
	if (min_exp != MAX_EXP+1)
		heap_init_size += (MAX_EXP - min_exp + 1) * sizeof(void *);

	#ifdef DEBUG_INIT
	printf("min: %u - indici liste esponenziali %u\n", min_exp, MAX_EXP - min_exp + 1);
	#endif

	//max_index = heap_init_size / sizeof(void *);
	ROUND(heap_init_size);
	heap_allocator_size = heap_init_size;

	#ifdef PAGE_ALLOCATION

	// Scelgo una dimensione di base multipla della dimensione di pagina
	size_t size = (heap_init_size + HEAP_GROWSIZE-1) & -HEAP_GROWSIZE;

	/*
	 * Sperimentalmente e' risultato conveniente per alcune traccie
	 * impostare una minima dimensione 
	 */
	/*
	#ifdef __i386__
	if (size < 8704) size = 8704;
	#else
	if (size < 8880) size = 8880;
	#endif
	*/
	
	#else
	size_t size = heap_init_size;
	#endif

	void * addr = sbrk(size);
	if ((long int) addr == -1) {

		#ifdef DEBUG
		FATAL_ERROR("Errore nell'allocare lo spazio basico");
		#endif

		return -1;

	}
	
	#ifdef DEBUG
	heap_asize = size;
	if (heap_asize != mem_heapsize()) {
		printf("Dimensione heap sbagliata - %u\n", heap_asize);
		exit(0);
	}
	#endif

	/* Imposto tutte le liste a NULL */
	unsigned int i = 0;
	while (i < (heap_init_size / sizeof(void *)))
		NEXT_FREE(addr + i++) = NULL;

	/*
	 * Ho allocato piu' spazio del dovuto, se possibile, lo spazio
	 * che non mi serve lo uso per un blocco libero
	 */
	if ((size - heap_init_size) >= MIN_BLOCK_SIZE + HEADER_SIZE) {

		#ifdef DEBUG_INIT
		printf("Creo un blocco di %u\n", size - heap_init_size - HEADER_SIZE);
		#endif
		void * ptr = start_heap + heap_init_size + HEADER_SIZE;
		SET_PAYLOAD_SIZE(ptr, size - heap_init_size - HEADER_SIZE);
		MARK_AS_FREE(ptr);
		in_list(ptr);
		last_block = ptr;

	} else {

		last_block = NULL;

	}

	#ifdef DEBUG_INIT
	printf("Dimensione heap iniziale: %u\n", heap_allocator_size);
	printf("Dimensione di pagina: %u\n", HEAP_GROWSIZE);
	printf("Dimensione header: %u\n", HEADER_SIZE);
	printf("Dimensione blocco minimo: %u\n", MIN_BLOCK_SIZE);
	//debug_heap();
	#endif

	return 0;
	
}

#ifndef MALLOCLAB
static inline void init(){
	if (!do_init) {
		mm_init();
		do_init = 1;
	}
}
#endif

/* 
 * Primitiva per l'allocazione di un nuovo blocco di memoria di
 * dimensione pari (o superiore) alla quantita' size. In caso di
 * errore viene restituito l'indirizzo NULL.
 */
static inline void * alloc(size_t size, void * ptr) {

	#ifndef MALLOCLAB
	init();
	#endif

	#ifdef DEBUG_MALLOC
	printf("Alloco %u operazione %u\n", size, op++);
	#endif

	/* Arrotondo in eccesso per ottenere un multiplo di ALIGNMENT */
	if (size == 0) return NULL;
	ROUND(size);
		
	void * addr = NULL;
	char ** addr_heap = start_heap;

	#ifdef POPULAR_SIZE_CLASS_NUMBER
	unsigned int j;
	for(j = 0; j < POPULAR_SIZE_CLASS_NUMBER; j++) {
		if (popular_size_class[j] == size)
			if (addr_heap[j] != NULL) {
				addr = addr_heap[j];
				addr_heap[j] = NEXT_FREE(addr);
				if (ptr != NULL) {
					if (PAYLOAD_SIZE(ptr) < size)
						memcpy(addr, ptr, PAYLOAD_SIZE(ptr));
					else
						memcpy(addr, ptr, size);
					free(ptr);
				}
				return addr;
			}
	} 
	#endif
	/*
	#ifdef MOST_USED_SIZE_CLASS_NUMBER
		for(j = 0; j < MOST_USED_SIZE_CLASS_NUMBER; j++) {
		if (most_used_size_class[j] == size)
			if (addr_heap[POPULAR_SIZE_CLASS_NUMBER + j] != NULL) {
				addr = addr_heap[POPULAR_SIZE_CLASS_NUMBER + j];
				addr_heap[POPULAR_SIZE_CLASS_NUMBER + j] = NEXT_FREE(addr);
				MARK_AS_USED(addr);
				return addr;
			}
	}
	#endif
	*/

	unsigned int index = get_index(size, 0);
	char block_from_list = 0;

	if (size <= MAX_FIXED){

		/*
		 * Se esiste cerco di prendere un blocco libero della stessa
		 * taglia nelle liste di primo livello
		 */
		addr = NEXT_FREE(addr_heap + index);
		if (addr != NULL) {
			NEXT_FREE(addr_heap + index) = NEXT_FREE(addr);

			#ifdef DEBUG
			block_in_list--;
			#endif
		}

	} else {

		/*
		 * Cerco un blocco uguale o maggiore in dimensione nelle liste
		 * di secondo livello
		*/

		addr = NEXT_FREE(addr_heap + index);
		void * prev = NULL;
		while(addr != NULL) {

			if (PAYLOAD_SIZE(addr) >= size) break;
			else {

				prev = addr;
				addr = NEXT_FREE(addr);

			}

		}
		
		if (addr != NULL) {

			if (prev == NULL)
				NEXT_FREE(addr_heap + index) = NEXT_FREE(addr);
			else 
				NEXT_FREE(prev) = NEXT_FREE(addr);

			#ifdef DEBUG
			block_in_list--;
			#endif
			
		}


	}

	/*
	 * Se la precendente ricerca non ha prodotto esiti positivi
	 * allora cerco anche nelle successive liste di secondo livello
	 */
	if (addr == NULL) {

		#ifdef DEBUG_MALLOC
		printf("Calcolo indice massimo\n");
		#endif
		unsigned int max_index = get_index(~1 - ALIGNMENT, 0);

		/* Lista successiva */
		index++;
		
		while (index <= max_index && NEXT_FREE(addr_heap + index) == NULL) {

			if (index < max_index) index++;
			else break;

		}

		#ifdef DEBUG_MALLOC
		//printf("max: %u\n", max_index);
		#endif

		/* Ho trovato un blocco libero piu' grande */
		if (index <= max_index && NEXT_FREE(addr_heap + index) != NULL) {

			addr = NEXT_FREE(addr_heap + index);
			NEXT_FREE(addr_heap + index) = NEXT_FREE(addr);

			#ifdef DEBUG
			block_in_list--;
			#endif

			#ifdef DEBUG_MALLOC
			//printf("Ho trovato un blocco libero a %u di %u\n", (unsigned int) addr, PAYLOAD_SIZE(addr));
			#endif
			
		}

	}

	/*
	 * Se ho trovato un blocco della dimensione prevista non
	 * devo fare una divisione del residuo successivamente
	 */
	if (addr != NULL)
		block_from_list = 1;

	/*
	 * Se ptr non e' NULL, allora la funzione e' stato invocata
	 * da dentro realloc() e quindi posso tentare di espandere l'heap
	 * e "allungare" il blocco per cui e' stata richiesta una
	 * reallocazione
	 */
	if (addr == NULL && ptr != NULL) {

		//printf("Espando heap...\n");

		size_t diff = size - PAYLOAD_SIZE(ptr);

		/* Quanto devo far crescere? */
		#ifdef PAGE_ALLOCATION
		size_t grow = (diff + HEAP_GROWSIZE-1) & -HEAP_GROWSIZE;
		#else
		size_t grow = diff;
		#endif

		void * bp = sbrk(grow);
		if ((long int) bp == -1) {

			#ifdef DEBUG
			FATAL_ERROR("Impossibile espandere l'heap.");
			#endif
			
			return NULL;

		}
		
		#ifdef DEBUG
		heap_asize += grow;
		if (heap_asize != mem_heapsize()) {
			printf("Dimensione heap sbagliata - %u\n", heap_asize);
			exit(0);
		}
		#endif

		/* Aggiorno la dimensione del blocco */
		SET_PAYLOAD_SIZE(ptr, PAYLOAD_SIZE(ptr) + grow);
		/*
		 * Non voglio che il blocco residuo eventuale
		 * sia "staccato" a sinistra, altrimenti perderei
		 * la parte che contiene i precedenti dati
		 * contenuti nel blocco e sarebbe necessario
		 * farne una copia
		 */
		#ifdef PAGE_ALLOCATION
		#ifndef DISABLE_SPLIT_COALESCE
		split_side = 0;
		ptr = split(ptr, size, NO_COALESCE);
		#endif
		#endif
		return ptr;

	}

	/*
	 * Se non e' stato possibile trovare un blocco libero
	 * sfruttabile per la richiesta, occorre espandere l'heap.
	 * L'heap viene fatto crescere a pagine se e' definita la
	 * macro PAGE_ALLOCATION.
	 */
	if (addr == NULL) {

		//printf("\n\nEspando l'heap, mi e' stato chiesto un blocco da %u bytes...\n", size);
		//debug_heap();

		/* Quanto devo far crescere? */
		size_t grow = HEAP_GROWSIZE;

		#ifdef DEBUG_MALLOC
		//printf("Grow iniziale %u\n", grow);
		#endif

		#ifdef PAGE_ALLOCATION
		grow = (size + HEADER_SIZE + HEAP_GROWSIZE-1) & -HEAP_GROWSIZE;
		#else
		grow = size + HEADER_SIZE;
		#endif

		#ifdef DEBUG_MALLOC
		printf("Sto facendo crescere l'heap di %u per un blocco di %u\n", grow, size);
		#endif

		/* Faccio crescere l'heap */
		addr = sbrk(grow);
		if ((long int) addr == -1) {

			#ifdef DEBUG
			FATAL_ERROR("Impossibile aumentare l'heap ulteriormente.");
			#endif

			return NULL;

		}

		#ifdef DEBUG
		heap_asize += grow;
		if (heap_asize != mem_heapsize()) {
			printf("Dimensione heap sbagliata - %u\n", heap_asize);
			exit(0);
		}
		#endif

		/* Traslo l'indirizzo di HEADER_SIZE */
		addr += HEADER_SIZE;

		/* Scrivo l'header */
		INIT_SIZE(addr, grow - HEADER_SIZE);
		#ifndef DISABLE_SPLIT_COALESCE
		if (last_block != NULL && IS_FREE(last_block)) {
			ANNOUNCE_FREE_TO_NEXT(last_block);
		}
		#endif

	}

	#ifndef DISABLE_SPLIT_COALESCE
	/* Eventualmente splitto il residuo in eccesso */
	if(block_from_list)
		addr = split(addr, size, NO_COALESCE);
	else
		addr = split(addr, size, COALESCE);
	#endif

	#ifdef DEBUG_MALLOC
	//printf("Sto marcando %u di %u con flag %u.\n", size, (unsigned int)addr, GET_FLAG(addr));
	#endif

	#ifndef DISABLE_SPLIT_COALESCE
	/* Marco il blocco come in uso */
	MARK_AS_USED(addr);
	#endif

	if(addr > last_block)
		last_block = addr;

	#ifdef DEBUG_MALLOC
	printf("Allocato blocco di %u ad %u con flag %u.\n", size, (unsigned int)addr, GET_FLAG(addr));
	//debug_heap();
	#endif

	#ifdef DEBUG
	if (IS_FREE(addr))
		FATAL_ERROR("Il blocco risulta libero ma e' stato appena allocato!\n");
	#endif

	#ifdef VERBOSE
	printf("malloc(%u) -> %u\n", size, (unsigned int)addr);
	#endif

	if (ptr != NULL) {

		if (PAYLOAD_SIZE(ptr) < size)
			memcpy(addr, ptr, PAYLOAD_SIZE(ptr));
		else
			memcpy(addr, ptr, size);

		#ifdef DEBUG
		block_allocated++;
		#endif
		
		free(ptr);
	}

	return addr;

}

void * malloc(size_t size) {

	#ifdef DEBUG_MALLOC
	printf("Inizio malloc(%u)\n", size);
	#endif

	#ifdef DEBUG
	debug_heap();
	if (size > 0) block_allocated++;
	#endif
	
	return alloc(size, NULL);
}


/*
 * Primitiva per il rilascio al sistema di un blocco in uso
 * precedentemente allocato con BSA. Prende come parametro il
 * puntatore al blocco e non restuisce alcunche'. Ammessa la
 * possibilita' di ricevere un indirizzo NULL.
 */
void free(void * ptr) {

	#ifdef DEBUG_FREE
	printf("Inizio free() -> %u\n", PAYLOAD_SIZE(ptr));
	#endif

	#ifdef DEBUG
	debug_heap();
	if (ptr != NULL) block_allocated--;
	#endif

	#ifndef MALLOCLAB
	init();
	#endif
	
	if(ptr == NULL) return;

	#ifdef POPULAR_SIZE_CLASS_NUMBER
	unsigned int j;
	for(j = 0; j < POPULAR_SIZE_CLASS_NUMBER; j++) {
		unsigned int size = PAYLOAD_SIZE(ptr);
		if (popular_size_class[j] == size) {
			char ** heap = start_heap;
			NEXT_FREE(ptr) = heap[j];
			heap[j] = ptr;
			return;
		}
	} 
	#endif

	#ifdef DEBUG_FREE
	printf("Libero blocco a %u di %u, operazione %u\n", (unsigned int) ptr, PAYLOAD_SIZE(ptr), op++);
	//debug_heap();
	fflush(stdout);
	#endif

	#ifndef DISABLE_SPLIT_COALESCE
	/* Fondiamo i blocchi liberi (precedente o successivo) ove possibile */
	ptr = coalesce(ptr, NORMAL);
	#endif

	#ifndef DISABLE_SPLIT_COALESCE
	/* Marco il nuovo blocco libero */
	MARK_AS_FREE(ptr);
	#endif

	/* Inserisco il blocco nella lista appropriata */
	in_list(ptr);

	#ifdef DEBUG_FREE
	//printf("Libero blocco a %u di %u, operazione %u\n", (unsigned int) ptr, PAYLOAD_SIZE(ptr), op++);
	//debug_heap();
	fflush(stdout);
	#endif

	#ifdef VERBOSE
	printf("free(%u)\n", (unsigned int)ptr);
	#endif

	#ifdef DEBUG_FREE
	if (!IS_FREE(ptr)) {
		printf("Il blocco non e' stato effettivamente liberato\n");
		exit(0);
	}
	#endif

	return;
	
}

/*
 * Primitiva per il ridimensionamento di un blocco precedentemente
 * allocato con BSA. La nuova dimensione size, puo' inferiore o
 * superiore all'originale. Il primo parametro e' il puntatore al
 * blocco ed e' ammesso che esso sia pari a NULL (in tal caso la
 * primitica e' equivalente ad una malloc(size)). Se la nuova dimensione
 * e' nulla, il comportamente e' equivalente ad una free(ptr).
 */
void * realloc(void * ptr, size_t size) {

	#ifdef DEBUG_REALLOC
	printf("Inizio realloc(ADDR, %u) -> %u\n", size, PAYLOAD_SIZE(ptr));
	#endif

	#ifdef DEBUG
	debug_heap();
	#endif

	#ifndef MALLOCLAB
	init();
	#endif

	void * newptr = NULL;

	/*
	#ifdef POPULAR_SIZE_CLASS_NUMBER
	unsigned int j;
	if (size > 0 && ptr != NULL)
		for(j = 0; j < POPULAR_SIZE_CLASS_NUMBER; j++) {
			if (popular_size_class[j] == PAYLOAD_SIZE(ptr)) { 
				
				if (size <= popular_size_class[j])
					return ptr;
				
			}
		} 
	#endif
	*/

	#ifdef DEBUG_REALLOC
	printf("Realloc di %u su %u\n", size, (unsigned int) ptr);
	if (ptr != NULL) printf("Blocco originale di %d\n", PAYLOAD_SIZE(ptr));
	#endif

	if (size > 0) {

		ROUND(size);

		if (ptr != NULL) {
			
			/* Calcola la dimensione effettiva del vecchio blocco */
			size_t oldsize = PAYLOAD_SIZE(ptr);

			if (size > oldsize) {

				#ifndef DISABLE_SPLIT_COALESCE
				/*
				 * Proviamo a vedere se  c'e' possibilita di accorpare
				 * blocchi liberi consecutivi per soddisfare la richiesta
				 */
				ptr = coalesce(ptr, FORWARD);

				/*
				 * Se ho effettuato una fusione, devo segnalare al blocco
				 * successivo che non sono piu' libero
				 */
				if (PAYLOAD_SIZE(ptr) > oldsize) {
					
					ANNOUNCE_USE_TO_NEXT(ptr);

				}

				
				/* Sono riuscito nel mio intento */
				if (PAYLOAD_SIZE(ptr) >= size) {

					#ifdef DEBUG_REALLOC
					//debug_heap();
					#endif

					#ifndef DISABLE_SPLIT_COALESCE
					if (PAYLOAD_SIZE(ptr) - size > REALLOC_SPLIT_THRESHOLD) {
						split_side = 0;
						split(ptr, size, NO_COALESCE);
					}
					#endif
					
					return ptr;
					
				}
				#endif
				
				/*
				 * Se il blocco da espandere e' alla fine dell'heap e
				 * non c'e' alcun blocco disponibile, proviamo
				 * semplicemente ad espandere per la differenza
				 */
				if (ptr == last_block) {

					return alloc(size, ptr);
					
				}

			} else {

				#ifndef DISABLE_SPLIT_COALESCE
				/* Effetto un trancamento, creando un blocco libero */
				if (oldsize - size > REALLOC_SPLIT_THRESHOLD) {
					split_side = 0;
					split(ptr, size, COALESCE);
				}
				#endif

				return ptr;

			}


			/*
			 * Lo spazio contiguo non e' sufficiente, occorre
			 * allocare nuovo spazio
			*/
			newptr = alloc(size, NULL);

			#ifdef DEBUG
			block_allocated++;
			#endif
			
			if (newptr == NULL) {

				#ifdef DEBUG
				FATAL_ERROR("Ottenuto indirizzo non valido in fase di realloc.");
				#endif
				
				return NULL;

			}

			if (ptr != NULL) {

				if (oldsize < size)
					memcpy(newptr, ptr, oldsize);
				else
					memcpy(newptr, ptr, size);

			}
			
		} else {
			
			newptr = alloc(size, NULL);

			#ifdef DEBUG
			block_allocated++;
			#endif
		}

	}

	#ifdef VERBOSE
	printf("realloc(%u, %u) -> %u\n", (unsigned int) ptr, size, (unsigned int)newptr);
	#endif

	free(ptr);
	return newptr;
	
}

#ifndef MALLOCLAB
/* Calloc */
void * calloc(size_t nmemb, size_t size) {
	
	init();

	void * ret = malloc(nmemb * size);
	bzero(ret, nmemb * size);

	#ifdef VERBOSE
	printf("calloc(%u, %u) -> %u\n", nmemb, size, (unsigned int)ret);
	#endif

	return ret;

}
#endif

#ifdef DEBUG
/*
 * Funzione di debug che stampa in output:
 * - indirizzo di inizio, fine dell'heap
 * - dimensione dell'heap
 * - il numero di liste della lookup table
 * - i blocchi presenti in ciascuna lista (con relative informazioni
 *   su di essi)
 * - i blocchi nell'heap
 */
static void debug_heap(){

	if (++op > 30) return;
	//printf("Heap %u\n", heap_asize);
	//if (heap_asize <= 6000000) return; 

	unsigned int head = (unsigned int) start_heap;
	unsigned int end = (unsigned int) end_heap;
	unsigned int size = end - head;
	//printf("Heap -> inizio %u - fine: %u - size: %u\n", head, end, size);

	if (heap_asize != size) {
		printf("heap stimata: %u - reale: %u\n", size, heap_asize);
		printf("Non torna la dimensione heap\n");
		printf("Dimensione: %u\n", mem_heapsize());
		exit(0);
	}

	unsigned int num_list = get_index(~1 - ALIGNMENT, 0) + 1;
	//printf("Sono presenti %u liste\n", num_list);

	unsigned int index;
	unsigned int blocks = 0;
	for(index = 0; index < num_list; index++) {

		void * ptr = NEXT_FREE(head + index);
		//if (ptr != NULL) printf("(%u) -> Lista[%u]:\n", index, (unsigned int)((char **)head + index));
		unsigned int block_num = 0;
		while(ptr != NULL) {

			blocks++;
			/*printf("\tBlocco[%u] -> inizio: %u - size: %u - libero: %u - flag: %u - next: %u", block_num, (unsigned int) ptr, PAYLOAD_SIZE(ptr), IS_FREE(ptr), GET_FLAG(ptr), (unsigned int) NEXT(ptr));
			if (!IS_FIRST_BLOCK(ptr)) { 
				if(IS_PREV_FREE(ptr))
					printf(" - prev: %u\n", (unsigned int) PREV(ptr));
				else
					printf(" - prev: in uso\n");
			} else
				printf("\n");
			
			if (!IS_FREE(ptr)) {
				printf("\t\tIl blocco non risulta libero!\n");
				exit(EXIT_FAILURE);
			}*/

			if (ptr != last_block && IS_FREE(NEXT(ptr))) {
				printf("Il blocco successivo e' libero ma non e' stato fuso!\n");
				exit(EXIT_FAILURE);
			}

			ptr = NEXT_FREE(ptr);
			block_num++;
			
		}

	
	}

	/*
	if (blocks != block_in_list) {
		printf("I blocchu liberi dovrebbero essere %u e invece sono %u\n", block_in_list, blocks);
		exit(0);
	}
	*/

	void * ptr = (char *)head + heap_allocator_size + HEADER_SIZE;
	//printf("Blocco in heap:\n");
	index = 0;
	unsigned int ablock_allocated = 0;
	while (ptr < (void *)end) {

		if (!IS_FREE(ptr))
			ablock_allocated++;
		/*
		printf("\tBlocco[%u] -> inizio: %u - size: %u - libero: %u - flag: %u - next: %u ",index, (unsigned int) ptr, PAYLOAD_SIZE(ptr), IS_FREE(ptr), GET_FLAG(ptr), (unsigned int) NEXT(ptr));
		if (!IS_FIRST_BLOCK(ptr)) { 
			if(IS_PREV_FREE(ptr))
				printf(" - prev: %u ", (unsigned int) PREV(ptr));
			else
				printf(" - prev: in uso ");
		}
		if(IS_FREE(ptr))
			if (ptr != *((char **)((char *)ptr + PAYLOAD_SIZE(ptr) - sizeof(void *)))) {
				printf("- end_pointer: NON VALIDO ");
				//stop = 1;
			}

		if (IS_FREE(ptr))
			printf("- next_free: %u", (unsigned int) NEXT_FREE(ptr));
		printf("\n");
		*/

		ptr = NEXT(ptr);
		index++;

	}
	/*
	if (ablock_allocated != block_allocated) {
		printf("I blocchi allocati dovrebbero essere %u invece sono %u\n", block_allocated, ablock_allocated);
		exit(0);
	}
	*/

}
#endif