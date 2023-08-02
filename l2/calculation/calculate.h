/* header guard example - *IMPORTANT* must be included in ALL header files */
#ifndef CALCULATE_H
#define CALCULATE_H

/* Forward Declarations stored in .h so they don't have to be repeated file-wise */
int square(int n);
int cube(int n);

/* Boolean data-types do not exist in C89 - useful to create a #define */
#define FALSE 0
#define TRUE !FALSE /* TRUE = 1 */
 
/* Macro example */
#define CUBE(x) ((x) * (x) * (x))

#endif /* end header guard */
