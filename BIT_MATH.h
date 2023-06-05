

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*______________________________________________________________
 * BIT MATH OPERATIONS :-
 * _____________________________________________________________
 * *************************************************************/
 
/*READ MODIFY WRITE*/
#define SET_BIT(VAR,BIT_NO) (VAR |= 1UL<<BIT_NO)        /*SET_BIT set BIT_NO with HIGH in Variable*/
#define CLR_BIT(VAR,BIT_NO) (VAR &= ~(1UL<<BIT_NO))     /*Clear it set BIT_NO with LOW in Variable*/
#define TOGGLE_BIT(VAR,BIT_NO) (VAR ^= (1UL<<BIT_NO))   /*TOGGLE if BIT_NO is HIGH it set it to LOW and Vice Versa*/
#define ASSIGN_BIT(VAR,BIT_NO,VALUE)  (VAR=(VAR &(~(1UL<<BIT_NO))) | (VALUE<<BIT_NO))  //ASSIGHN BIT_NO in variable to HIGH or LOW*/
#define GET_BIT(VAR,BIT_NO)  ((VAR>>BIT_NO) & 0x01UL)   /*GET BIT_NO Value*/


#define BITBAND_PERI_BASE 			0x40000000
#define ALIAS_PERI_BASE 				0x42000000
/*Get Bit Register Address in Alias Region*/
#define BIT_WORD_ADDR(BITBAND_ADDR, BIT_NUMB)	(*(volatile uint32_t*)(ALIAS_PERI_BASE + ((BITBAND_ADDR - BITBAND_PERI_BASE) *32) + (BIT_NUMB * 4)))

/*SET , CLR OF BITS IN ALIAS REGION*/
#define SET_BIT_ALIAS( REG_ADDR , BIT )		BIT_WORD_ADDR ( REG_ADDR , BIT ) = 0x01
#define CLR_BIT_ALIAS( REG_ADDR , BIT )		BIT_WORD_ADDR ( REG_ADDR , BIT ) = 0x00


//________________________________________________________________

#endif /* BIT_MATH_H_ */
