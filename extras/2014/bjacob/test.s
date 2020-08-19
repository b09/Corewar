.name "Candy"

.comment "dasf"

	st		r1, r12
	ld      %0 , r14
    ld      :fun, r6
	zjmp    %:fun

stuff:

fun:
	st		r1, r12
