.name "Candy"
.comment ""

	st		r1, r12
	sti		r12, %:live, %1
live:
	live	%0
	ld      %0, r14
	zjmp	%:live
